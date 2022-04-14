#include "ros/ros.h"//ros
#include <sstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include "HPS3D_IF.h"
#include <time.h>
#include <sys/time.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

uint32_t g_fps = 0;
uint16_t g_aver_distance = 0;
uint16_t g_max_distance = 0;
uint16_t g_min_distance = 0;
uint16_t g_valid_aver_amp = 0;
uint16_t g_all_aver_amp = 0;
uint16_t g_roi_aver_distance = 0;
uint16_t g_roi_max_distance = 0;
uint16_t g_roi_min_distance = 0;
uint16_t g_roi_valid_aver_amp = 0;
uint16_t g_roi_all_aver_amp = 0;
uint16_t g_max_amp = 0;
uint16_t g_min_amp = 0;
uint8_t g_device_id = 99;
uint8_t g_connect_flag = 0;
uint8_t g_roi_id[8] = { 0 };
uint16_t g_roi_data[8][307200];
uint16_t g_roi_area[8][4];
float64_t g_point_data[307200][3];
uint32_t g_point_count = 0;
uint32_t g_roi_data_count = 0;
uint16_t g_distance_data[307200] = { 0 };
uint8_t g_grayscale_data[307200] = { 0 };
uint16_t g_amplitude_data[307200] = { 0 };
sem_t signal_pointcloud;

ros::Publisher camera_pub;//Global variable, because the observer callback function needs to be used
pcl::PointCloud<pcl::PointXYZ> cloud;
sensor_msgs::PointCloud2 output; 


//The OutputCallBack Func
void User_Func(uint8_t out_id, uint8_t event, void *contex)
{
	



	/*
	*
	*
	* 注意:
	*     回调函数不能做耗时操作，否则会导致丢帧。	
	*     数据处理应该在另外一条线程进行，回调函数只做简单的数据拷贝。
	*
	*/


        g_fps++;
	if (event == EVENT_SIMPLEDISTANCERECVD) //简单深度通知事件
	{
		//简单深度通知事件只能获取数学统计信息
		HPS3D_GetAverageDistance_CB(out_id, &g_aver_distance); //获取平均距离
		HPS3D_GetMaxDistance_CB(out_id, &g_max_distance);		//获取最大距离
		HPS3D_GetMinDistance_CB(out_id, &g_min_distance);		//获取最小距离
		HPS3D_GetValidAverAmplitude_CB(out_id, &g_valid_aver_amp);	//有效平均幅值，计算不包含0幅值
		HPS3D_GetAllAverAmplitude_CB(out_id, &g_all_aver_amp);	//平均幅值，计算包含0幅值

																//以下为数据显示
		printf("aver_distance:%d  max_distance:%d  min_distance:%d\n", g_aver_distance, g_max_distance, g_min_distance);
		printf("valid_aver_amp:%d  all_aver_amp:%d  fps:%d\n", g_valid_aver_amp, g_all_aver_amp, g_fps);
	}
	else if (event == EVENT_FULLDISTANCERECVD) //完整深度通知事件
	{
		//完整深度通知事件可以获取数学统计信息和每个像素点的深度值

		//获取每个像素点的深度数据
		HPS3D_GetDistanceData_CB(out_id, g_distance_data);

		//获取深度数据的数学统计信息
		HPS3D_GetAverageDistance_CB(out_id, &g_aver_distance); //获取平均距离
		HPS3D_GetMaxDistance_CB(out_id, &g_max_distance);		//获取最大距离
		HPS3D_GetMinDistance_CB(out_id, &g_min_distance);		//获取最小距离
		HPS3D_GetValidAverAmplitude_CB(out_id, &g_valid_aver_amp);	//有效平均幅值，计算不包含0幅值
		HPS3D_GetAllAverAmplitude_CB(out_id, &g_all_aver_amp);	//平均幅值，计算包含0幅值

																//以下为数据显示
		printf("aver_distance:%d  max_distance:%d  min_distance:%d\n", g_aver_distance, g_max_distance, g_min_distance);
		printf("valid_aver_amp:%d  all_aver_amp:%d  fps:%d\n", g_valid_aver_amp, g_all_aver_amp, g_fps);
		printf("distance_data:%d\n", g_distance_data[1]);
	}
	else if (event == EVENT_AMPLITUDE) //幅值通知事件
	{
		//振幅通知事件可以获取每个像素点的灰度数据或者幅值数据，以及幅值相关的数学统计信息

		//获取每个像素点的灰度数据，灰度数据由振幅数据归一化处理得到
		HPS3D_GetGrayscaleData_CB(out_id, g_grayscale_data);

		//获取每个像素点的幅值数据
		HPS3D_GetAmplitudeData_CB(out_id, g_amplitude_data);

		//获取振幅相关的数学统计信息
		HPS3D_GetValidAverAmplitude_CB(out_id, &g_valid_aver_amp); // 有效平均幅值
		HPS3D_GetMaxAmplitudeData_CB(out_id, &g_max_amp); //最大幅值
		HPS3D_GetMinAmplitudeData_CB(out_id, &g_min_amp); //最小幅值

														  //以下为数据显示
		printf("valid_aver_amp:%d  max_amp:%d  min_amp:%d\n", g_valid_aver_amp, g_max_amp, g_min_amp);
		printf("grayscale_data:%d  amplitude_data:%d  fps:%d\n", g_grayscale_data[1], g_amplitude_data[1], g_fps);
	}
	else if (event == EVENT_FULLPOINTCLOUDRECVD) //完整点云通知事件
	{
          //完整点云图，能够获取每个像素的点云数据，和深度数据的数学统信息，点云数据自动过滤了无效值
          HPS3D_GetPointCloudData_CB(out_id, g_point_data, &g_point_count); //获取点云数据

          //发送信号,由另外一条线程处理点云数据  注意:回调函数不能做耗时操作，否则会导致丢帧。
          sem_post(&signal_pointcloud);
		
		
	}
	else if (event == EVENT_ROIPOINTCLOUDRECVD) //ROI点云通知事件
	{
		//ROI点云事件可以获取ROI点云信息和每个ROI的深度数学统计信息
		uint32_t count = 0;
		//其中获取点云数据有两种方式
		//第一种，通过点云数据获取接口直接获取点云信息，自动将多个ROI点云数据拼接成
		HPS3D_GetPointCloudData_CB(out_id, g_point_data, &g_point_count); //获取点云数据
		cloud.points.clear();
		for (size_t i = 0; i < g_point_count; i++)
		{
			pcl::PointXYZ temp;
			temp.x = g_point_data[i][0];
			temp.y = g_point_data[i][1];
			temp.z = g_point_data[i][2];
			cloud.points.push_back(temp);
		}
		pcl::toROSMsg(cloud, output);
		output.header.frame_id = "hps";
		camera_pub.publish(output);


	}
	else if (event == EVENT_ROIFULLDISTANCERECVD) //ROI完整深度通知事件
	{


		//ROI完整深度事件，可以获取每个ROI的深度数据和每个ROI的深度数学统计信息


		uint8_t group_id = 0;
		uint8_t roi_number = 0;

		//获取指定ROI的深度信息前，需要通过ROI参数接口，获取当前输出的ROI信息，（有几个ROI，ROI的ID等）
		//获取ROI参数
		HPS3D_GetOutRoiParam_CB(out_id, &group_id, &roi_number, g_roi_id);
		int i = 0;
		for (i = 0; i < roi_number; i++)
		{
			//获取ROI距离值
			HPS3D_GetOutRoiDistanceData_CB(out_id, g_roi_id[i], g_roi_data[g_roi_id[i]], g_roi_area[g_roi_id[i]]);

			//ROI深度数据的数据量需要通过ROI区域计算
			g_roi_data_count = (g_roi_area[g_roi_id[i]][2] - g_roi_area[g_roi_id[i]][0] + 1) * (g_roi_area[g_roi_id[i]][3] - g_roi_area[g_roi_id[i]][1] + 1);
			printf("roi_data_count:%d roi_data:%d\n", g_roi_data_count, g_roi_data[g_roi_id[i]][g_roi_data_count - 1]);

			//获取ROI数学统计信息
			HPS3D_GetOutRoiAverageDistance_CB(out_id, g_roi_id[i], &g_roi_aver_distance);
			HPS3D_GetOutRoiMaxDistance_CB(out_id, g_roi_id[i], &g_roi_max_distance);
			HPS3D_GetOutRoiMinDistance_CB(out_id, g_roi_id[i], &g_roi_min_distance);
			HPS3D_GetOutRoiAllAverAmplitude_CB(out_id, g_roi_id[i], &g_roi_all_aver_amp);
			HPS3D_GetOutRoiValidAverAmplitude_CB(out_id, g_roi_id[i], &g_roi_valid_aver_amp);
			printf("roi_aver_distance:%d  roi_max_distance:%d  roi_min_distance:%d\n", g_roi_aver_distance, g_roi_max_distance, g_roi_min_distance);
			printf("roi_all_aver_amp:%d  roi_valid_aver_amp:%d\n", g_roi_all_aver_amp, g_roi_valid_aver_amp);
		}
	}
	else if (event == EVENT_ROISIMPLEDISTANCERECVD) //ROI简单深度通知事件
	{

		//简单深度事件，可以获取每个ROI的深度数学统计信息
		uint8_t group_id = 0;
		uint8_t roi_number = 0;

		//获取指定ROI的深度信息前，需要通过ROI参数接口，获取当前输出的ROI信息，（有几个ROI，ROI的ID等）
		//获取ROI参数
		HPS3D_GetOutRoiParam_CB(out_id, &group_id, &roi_number, g_roi_id);
		int i = 0;
		for (i = 0; i < roi_number; i++)
		{
			//获取ROI数学统计信息
			HPS3D_GetOutRoiAverageDistance_CB(out_id, g_roi_id[i], &g_roi_aver_distance);
			HPS3D_GetOutRoiMaxDistance_CB(out_id, g_roi_id[i], &g_roi_max_distance);
			HPS3D_GetOutRoiMinDistance_CB(out_id, g_roi_id[i], &g_roi_min_distance);
			HPS3D_GetOutRoiAllAverAmplitude_CB(out_id, g_roi_id[i], &g_roi_all_aver_amp);
			HPS3D_GetOutRoiValidAverAmplitude_CB(out_id, g_roi_id[i], &g_roi_valid_aver_amp);
			printf("roi_aver_distance:%d  roi_max_distance:%d  roi_min_distance:%d\n", g_roi_aver_distance, g_roi_max_distance, g_roi_min_distance);
			printf("roi_all_aver_amp:%d  roi_valid_aver_amp:%d\n", g_roi_all_aver_amp, g_roi_valid_aver_amp);
		}
	}
	else if (event == EVENT_DEVDISCONNECT) //断开连接
	{
		//断开连接，回收资源
		HPS3D_DisConnect(out_id);
	}
	else
	{
		printf("system error!\n");
	}
}

//check ctrl+c signal
void signal_handler(int signo)
{
	if (HPS3D_DisConnect(g_device_id) != RET_OK)
	{
		printf("HPS3D_DisConnect faild\n");
	}
	else
	{
                g_connect_flag=0; 
		printf("HPS3D_DisConnect succeed\n");
	}
	exit(0);
}


//printf log callback function
void my_printf(char *str, void *contex)
{
	std::cout << str;
}


void* printf_thread(void*arg)
{
  while(g_connect_flag)
  {
    usleep(1000000);
    printf("FPS:%d\n",g_fps);
    g_fps=0;
  }
  return NULL;

}

int main(int argc, char **argv)
{

        sem_init(&signal_pointcloud, 0, 1);
        pthread_t printfthread;
        
	ros::init(argc, argv, "ros_camera_client");//ros init
	ros::NodeHandle n;//Create a node
	uint32_t a = 0;
	char fileName[10][20];
	uint32_t dev_cnt = 0;
	uint32_t indx = 0;
	uint8_t ret = RET_OK;

	std::stringstream sclient_name;

	//Install the signal
	if (signal(SIGINT, signal_handler) == SIG_ERR || signal(SIGTSTP, signal_handler) == SIG_ERR)
	{
		printf("sigint error");
	}

	//Create a topic
	camera_pub = n.advertise<sensor_msgs::PointCloud2>("output", 100);

	//set debug enable and install printf log callback function
	HPS3D_SetDebugCallBack(my_printf,NULL);


	do
	{
		//Device Connection
		ret = HPS3D_ConnectByEthernet((char*)"192.168.30.202", 12345, &g_device_id);
		if (ret != RET_OK)
		{
			printf("HPS3D_ConnectByEthernet faild!\n");
			break;
		}
		else
		{
                        g_connect_flag=1; 
			printf("HPS3D_ConnectByEthernet succeed!\n");
		}

		/*set OutputCallBack Func*/
		ret = HPS3D_SetOutputCallBack(User_Func, g_device_id, NULL);
		if (ret != RET_OK)
		{
			printf("HPS3D_SetOutputCallBack faild!\n");
			break;
		}
		else
		{
			printf("HPS3D_SetOutputCallBack succeed!\n");
		}

		/*set watch dog enable*/
		ret = HPS3D_SetWatchDogEnable(g_device_id, false);
		if (ret != RET_OK)
		{
			printf("HPS3D_SetWatchDogEnable faild!\n");

		}
		else
		{
			printf("HPS3D_SetWatchDogEnable succeed!\n");
		}

		/*set convert point cloud data enable*/
		HPS3D_SetOutputDataType(g_device_id, OUTPUT_DISTANCE_FULL);
		HPS3D_SetPointCloudMode(g_device_id, true, MIRROR_DISABLE);
		if (HPS3D_SetROIEnable(g_device_id, 0, false) != RET_OK)
		{
			printf("设置ROI点云事件:..........失败!\n");
			return RET_ERROR;
		}
		//Set running mode
		HPS3D_SetRunMode(g_device_id,RUN_CONTINUOUS);

	} while (0);

	if (ret != RET_OK)
	{
		//Remove device and disconnect
		HPS3D_DisConnect(g_device_id);
		printf("Initialization failed, Remove device\n");
		return 0;
	}
	HPS3D_SetEdgeFilter(g_device_id,false,60);//边缘滤波 有需要则打开，参数越小效果越强
	printf("secced 1000");
	printf("Program running...\n");
	printf("Use Ctrl + C can exit the program!\n");
        //创建帧率打印线程
        pthread_create(&printfthread, NULL, printf_thread, NULL);
	while (1)
	{

	 //等待接收回调函数信号
         sem_wait(&signal_pointcloud); 

	 //显示点云 
	 cloud.points.clear();												  
	 int i = 0;
	  for (i = 0; i < g_point_count; i++)
	  {
	    pcl::PointXYZ temp;
	    temp.x = g_point_data[i][0];
	    temp.y = g_point_data[i][1];
	    temp.z = g_point_data[i][2];
	    cloud.points.push_back(temp);
	  }
	  pcl::toROSMsg(cloud, output);
	  output.header.frame_id = "hps";
	  camera_pub.publish(output);
       }

	return 0;
}


