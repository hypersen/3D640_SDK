#if 0
#include "OpenNI.h"
#include <conio.h>
using namespace openni;

int g_imageCount = 0; //����֡��

#define MIN_DISTANCE 0  // Unit(mm)
#define MAX_DISTANCE 15000 //Unit(mm)

typedef struct
{
	double worldX;
	double worldY;
	double worldZ;
}PointCloudeDef; //���ƶ���

typedef struct
{
	int originX;
	int originY;
	int Height;
	int width;
}ImageAreaDef; //ͼ��������

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

//���ת���Ʒ���
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
	//�����豸���Ӻ͹رռ���
	OpenNI::addDeviceDisconnectedListener(&DisconnectObserver);
	OpenNI::addDeviceConnectedListener(&ConnectObserver);
	//��ʼ��OpenNI
	Status nRetVal = OpenNI::initialize();
	if (nRetVal != STATUS_OK)
	{
		return 1;
	}

	Device device;
	//ʹ��URI���豸��URI��ʽIP=x,PORT=x(x�����豸��������)
	nRetVal = device.open("IP=192.168.30.202,PORT=12345");
	if (nRetVal != STATUS_OK)
	{
		printf("SimpleViewer: Device open failed:\n%s\n", OpenNI::getExtendedError());
		OpenNI::shutdown();
		return 2;
	}


	//������
	VideoStream depth;
	//�ж��豸�Ƿ�֧�������
	if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
	{
		nRetVal = depth.create(device, SENSOR_DEPTH);
		if (nRetVal != STATUS_OK)
		{
			printf("Couldn't create depth stream\n%s\n", OpenNI::getExtendedError());
			return 3;
		}
	}

	//��ʼ����������
	nRetVal = depth.start();
	if (nRetVal != STATUS_OK)
	{
		printf("Couldn't start the depth stream\n%s\n", OpenNI::getExtendedError());
		return 4;
	}

	//��ʼ������ڲ�
	getCameraParams(device, g_cameraParam);
	//ע������¼�����
	depth.addNewFrameListener(&depthPrinter);
	//�û������˳�
	while (!_kbhit())
	{
		Sleep(1000);
		printf("FPS��%d\n", g_imageCount);
		g_imageCount = 0;
	}
	//�Ƴ�����¼�����
	depth.removeNewFrameListener(&depthPrinter);


	//ɾ���豸���Ӽ���
	OpenNI::removeDeviceDisconnectedListener(&DisconnectObserver);
	OpenNI::removeDeviceConnectedListener(&ConnectObserver);
	//ֹͣ��
	depth.stop();
	//������
	depth.destroy();
	device.close();
	openni::OpenNI::shutdown();
	return openni::STATUS_OK;
}
#endif

#include <OpenNI.h>
#include <conio.h> //�Ǳ���
using namespace openni;
int main(int argc, char **argv)
{
	//��ʼ��OpenNI
	Status nRetVal = openni::OpenNI::initialize();
	if (nRetVal != STATUS_OK)
	{
		return 1;
	}

	Device device;
	//ʹ��URI���豸��URI��ʽIP=x,PORT=x(x�����豸��������)
	nRetVal = device.open("IP=192.168.30.202,PORT=12345");
	if (nRetVal != STATUS_OK)
	{
		printf("Device open failed! %s\n", OpenNI::getExtendedError());
		OpenNI::shutdown();
		return 2;
	}


	//������
	VideoStream depth;
	//�ж��豸�Ƿ�֧�������
	if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
	{
		nRetVal = depth.create(device, SENSOR_DEPTH);
		if (nRetVal != STATUS_OK)
		{
			printf("Couldn't create depth stream! %s\n", OpenNI::getExtendedError());
			return 3;
		}
	}

	//��ʼ����������
	nRetVal = depth.start();
	if (nRetVal != STATUS_OK)
	{
		printf("Couldn't start the depth stream! %s\n", OpenNI::getExtendedError());
		return 4;
	}

	//������֡
	VideoFrameRef frame;
	//�û������˳�
	while (!_kbhit())
	{
		int ReadyStreamIndex;
		VideoStream* pStream = &depth;
		//�ȴ���ǰ����һ֡����
		nRetVal = OpenNI::waitForAnyStream(&pStream, 1, &ReadyStreamIndex, 300);
		if (nRetVal != STATUS_OK)
		{
			printf("Wait Time Out! %s\n", OpenNI::getExtendedError());
			continue;
		}
		//��ȡ��ǰ���е�һ֡����
		nRetVal = depth.readFrame(&frame);
		if (nRetVal != STATUS_OK)
		{
			printf("Read failed! %s\n", OpenNI::getExtendedError());
			continue;
		}

		//��ȡ��ǰ֡������
		DepthPixel* depthData = (DepthPixel*)frame.getData();
		//��ӡ���ĵ�����
		printf("Timestamp:%d depthData:%d\n", frame.getTimestamp(), depthData[307200/2]);
	}
	
	//ֹͣ��
	depth.stop();
	//������
	depth.destroy();
	//�ر��豸
	device.close();
	//ж������
	openni::OpenNI::shutdown();
	return openni::STATUS_OK;
}