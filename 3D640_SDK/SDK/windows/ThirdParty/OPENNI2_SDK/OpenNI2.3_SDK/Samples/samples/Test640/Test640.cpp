#if 0
#include "OpenNI.h"
#include <conio.h>
using namespace openni;

int g_imageCount = 0; //计算帧率

#define MIN_DISTANCE 0  // Unit(mm)
#define MAX_DISTANCE 15000 //Unit(mm)

typedef struct
{
	double worldX;
	double worldY;
	double worldZ;
}PointCloudeDef; //点云定义

typedef struct
{
	int originX;
	int originY;
	int Height;
	int width;
}ImageAreaDef; //图像区域定义

HPSCameraParams g_cameraParam;
PointCloudeDef g_pointCloudeData[307200];

void getCameraParams(Device& Device, HPSCameraParams& cameraParam)
{
	int dataSize = sizeof(cameraParam);
	memset(&cameraParam, 0, sizeof(cameraParam));
	openni::Status rc = Device.getProperty(HPS_DEVICE_PROPERTY_CAM_PARAMS, (uint8_t *)&cameraParam, &dataSize);
	if (rc != openni::STATUS_OK)
	{
		printf("Error: %s\n", OpenNI::getExtendedError());
		return;
	}
}

//深度转点云范例
void convertDepthToPointCloud(const uint16_t *pDepth, ImageAreaDef area, PointCloudeDef * pointCloudeData)
{
	if (NULL == pDepth)
	{
		printf("depth frame is NULL\n!");
		return;
	}
	uint16_t maxDepth = MAX_DISTANCE;
	uint16_t minDepth = MIN_DISTANCE;
	int validCount = 0;
	int dataCount = 0;
	for (int y = area.originY; y < area.Height; ++y)
	{
		for (int x = area.originX; x < area.width; ++x)
		{
			uint16_t depth = pDepth[dataCount];
			dataCount++;
			if (depth <= minDepth || depth > maxDepth)
				continue;

			float tx = (x - g_cameraParam.cx) / g_cameraParam.fx;
			float ty = (g_cameraParam.cy - y) / g_cameraParam.fy;
			pointCloudeData[validCount].worldX = depth * tx;
			pointCloudeData[validCount].worldY = depth * ty;
			pointCloudeData[validCount].worldZ = depth;
			validCount++;
		}
	}
}

void analyzeFrame(const VideoFrameRef& frame)
{
	DepthPixel* pDepth;
	ImageAreaDef area;
	g_imageCount++;
	switch (frame.getVideoMode().getPixelFormat())
	{
	case PIXEL_FORMAT_DEPTH_1_MM:
		pDepth = (DepthPixel*)frame.getData();
		
		memset(g_pointCloudeData, 0, sizeof(g_pointCloudeData));

		area.originX = frame.getCropOriginX();
		area.originY = frame.getCropOriginY();
		area.width = frame.getWidth();
		area.Height = frame.getHeight();

		convertDepthToPointCloud(pDepth, area, g_pointCloudeData);
		printf("[%llu] worldX:%.3f worldY:%.3f worldZ:%.3f\n ", (long long)frame.getTimestamp(),
			g_pointCloudeData[0].worldX, g_pointCloudeData[0].worldY, g_pointCloudeData[0].worldZ);
		break;
	default:
		printf("Unknown format\n");
	}
}

class PrintCallback : public VideoStream::NewFrameListener
{
public:
	void onNewFrame(VideoStream& stream)
	{
		stream.readFrame(&m_frame);
		analyzeFrame(m_frame);
	}
private:
	VideoFrameRef m_frame;
};
PrintCallback depthPrinter;

class DisconnectCallback : public OpenNI::DeviceDisconnectedListener
{
public:
	void onDeviceDisconnected(const DeviceInfo* deviceInfo)
	{
		printf("%s is close\n", deviceInfo->getUri());
	}
};

DisconnectCallback DisconnectObserver;


class ConnectCallback : public OpenNI::DeviceConnectedListener
{
public:
	void onDeviceConnected(const DeviceInfo* deviceInfo)
	{
		printf("%s is open\n", deviceInfo->getUri());
	}
};
ConnectCallback ConnectObserver;

int main(int argc, char **argv)
{
	//创建设备连接和关闭监听
	OpenNI::addDeviceDisconnectedListener(&DisconnectObserver);
	OpenNI::addDeviceConnectedListener(&ConnectObserver);
	//初始化OpenNI
	Status nRetVal = OpenNI::initialize();
	if (nRetVal != STATUS_OK)
	{
		return 1;
	}

	Device device;
	//使用URI打开设备，URI格式IP=x,PORT=x(x根据设备参数设置)
	nRetVal = device.open("IP=192.168.30.202,PORT=12345");
	if (nRetVal != STATUS_OK)
	{
		printf("SimpleViewer: Device open failed:\n%s\n", OpenNI::getExtendedError());
		OpenNI::shutdown();
		return 2;
	}


	//创建流
	VideoStream depth;
	//判断设备是否支持深度流
	if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
	{
		nRetVal = depth.create(device, SENSOR_DEPTH);
		if (nRetVal != STATUS_OK)
		{
			printf("Couldn't create depth stream\n%s\n", OpenNI::getExtendedError());
			return 3;
		}
	}

	//开始输出深度数据
	nRetVal = depth.start();
	if (nRetVal != STATUS_OK)
	{
		printf("Couldn't start the depth stream\n%s\n", OpenNI::getExtendedError());
		return 4;
	}

	//初始化相机内参
	getCameraParams(device, g_cameraParam);
	//注册深度事件监听
	depth.addNewFrameListener(&depthPrinter);
	//敲击键盘退出
	while (!_kbhit())
	{
		Sleep(1000);
		printf("FPS：%d\n", g_imageCount);
		g_imageCount = 0;
	}
	//移除深度事件监听
	depth.removeNewFrameListener(&depthPrinter);


	//删除设备连接监听
	OpenNI::removeDeviceDisconnectedListener(&DisconnectObserver);
	OpenNI::removeDeviceConnectedListener(&ConnectObserver);
	//停止流
	depth.stop();
	//销毁流
	depth.destroy();
	device.close();
	openni::OpenNI::shutdown();
	return openni::STATUS_OK;
}
#endif

#include <OpenNI.h>
#include <conio.h> //非必须
using namespace openni;
int main(int argc, char **argv)
{
	//初始化OpenNI
	Status nRetVal = openni::OpenNI::initialize();
	if (nRetVal != STATUS_OK)
	{
		return 1;
	}

	Device device;
	//使用URI打开设备，URI格式IP=x,PORT=x(x根据设备参数设置)
	nRetVal = device.open("IP=192.168.30.202,PORT=12345");
	if (nRetVal != STATUS_OK)
	{
		printf("Device open failed! %s\n", OpenNI::getExtendedError());
		OpenNI::shutdown();
		return 2;
	}


	//创建流
	VideoStream depth;
	//判断设备是否支持深度流
	if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
	{
		nRetVal = depth.create(device, SENSOR_DEPTH);
		if (nRetVal != STATUS_OK)
		{
			printf("Couldn't create depth stream! %s\n", OpenNI::getExtendedError());
			return 3;
		}
	}

	//开始输出深度数据
	nRetVal = depth.start();
	if (nRetVal != STATUS_OK)
	{
		printf("Couldn't start the depth stream! %s\n", OpenNI::getExtendedError());
		return 4;
	}

	//创建单帧
	VideoFrameRef frame;
	//敲击键盘退出
	while (!_kbhit())
	{
		int ReadyStreamIndex;
		VideoStream* pStream = &depth;
		//等待当前流的一帧数据
		nRetVal = OpenNI::waitForAnyStream(&pStream, 1, &ReadyStreamIndex, 300);
		if (nRetVal != STATUS_OK)
		{
			printf("Wait Time Out! %s\n", OpenNI::getExtendedError());
			continue;
		}
		//读取当前流中的一帧数据
		nRetVal = depth.readFrame(&frame);
		if (nRetVal != STATUS_OK)
		{
			printf("Read failed! %s\n", OpenNI::getExtendedError());
			continue;
		}

		//获取当前帧的数据
		DepthPixel* depthData = (DepthPixel*)frame.getData();
		//打印中心点数据
		printf("Timestamp:%d depthData:%d\n", frame.getTimestamp(), depthData[307200/2]);
	}
	
	//停止流
	depth.stop();
	//销毁流
	depth.destroy();
	//关闭设备
	device.close();
	//卸载驱动
	openni::OpenNI::shutdown();
	return openni::STATUS_OK;
}