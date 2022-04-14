#pragma once


#include "HPS3D_IF.h"
#include "HPS3D_DEFINE.h"
#include <stdio.h>
#include <time.h>



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
clock_t g_start, g_end;
uint8_t g_roi_id[8] = { 0 };
uint16_t g_roi_data[8][307200];
uint16_t g_roi_area[8][4];
float64_t g_point_data[307200][3];
uint32_t g_point_count = 0;
uint32_t g_roi_data_count = 0;
uint16_t g_distance_data[307200] = { 0 };
uint8_t g_grayscale_data[307200] = { 0 };
uint16_t g_amplitude_data[307200] = { 0 };

uint8_t Init();
uint8_t SetupDevice();
uint8_t QueryDeviceInf();
uint8_t SetOutPutType();

//Debug信息回调函数，只需要将str打印即可
void debugFunc(char *str, void *contex)
{
	printf("%s", str);
}


//输出事件回调函数，注意请不要在回调函数中进行耗时较长的操作
void OutputEventFunc(uint8_t out_id, uint8_t event, void *contex)
{
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
		//完整点云图，能够获取每个像素的点云数据，和深度数据信息，点云数据自动过滤了无效值
		
		//获取每个像素的点云数据
		HPS3D_GetPointCloudData_CB(out_id, g_point_data, &g_point_count); //获取点云数据



#if false   //需要深度信息时自行开启
		//获取深度数据
		HPS3D_GetDistanceData_CB(out_id, g_distance_data);
#endif

		////获取深度的数学统计信息
		HPS3D_GetAverageDistance_CB(out_id, &g_aver_distance); //获取平均距离
		HPS3D_GetMaxDistance_CB(out_id, &g_max_distance);		//获取最大距离
		HPS3D_GetMinDistance_CB(out_id, &g_min_distance);		//获取最小距离
		HPS3D_GetValidAverAmplitude_CB(out_id, &g_valid_aver_amp);	//有效平均幅值，计算不包含0幅值
		HPS3D_GetAllAverAmplitude_CB(out_id, &g_all_aver_amp);	//平均幅值，计算包含0幅值

		////以下为数据显示
		printf("aver_distance:%d  max_distance:%d  min_distance:%d\n", g_aver_distance, g_max_distance, g_min_distance);
		printf("valid_aver_amp:%d  all_aver_amp:%d  fps:%d\n", g_valid_aver_amp, g_all_aver_amp, g_fps);
		printf("point_count:%d  g_point_data:%f  fps:%d\n", g_point_count, g_point_data[g_point_count - 1][0], g_fps);

	}
	else if (event == EVENT_ROIPOINTCLOUDRECVD) //ROI点云通知事件
	{
		//ROI点云事件可以获取ROI点云信息和每个ROI的深度信息
		uint32_t count = 0;
		//其中获取点云数据有两种方式
		//第一种，通过点云数据获取接口直接获取点云信息，自动将多个ROI点云数据拼接成
		HPS3D_GetPointCloudData_CB(out_id, g_point_data, &g_point_count); //获取点云数据
		printf("point_count:%d g_point_data:%f\n", g_point_count, g_point_data[g_point_count - 1][0]);

		//第二种，获取指定ROI的点云信息
		uint8_t group_id = 0;
		uint8_t roi_number = 0;
		//获取指定ROI的点云信息前，需要通过ROI参数接口，获取当前输出的ROI信息，（有几个ROI，ROI的ID等）

		//获取ROI参数
		HPS3D_GetOutRoiParam_CB(out_id, &group_id, &roi_number, g_roi_id);
		//依次获取每个ROI值
		for (int i = 0; i < roi_number; i++)
		{
			HPS3D_GetOutRoiPointCloudData_CB(out_id, g_roi_id[i], g_point_data, &g_point_count);
			printf("point_count:%d g_point_data:%f\n", g_point_count, g_point_data[g_point_count - 1][0]);

#if false   //需要深度信息时自行开启
			//获取ROI距离值
			HPS3D_GetOutRoiDistanceData_CB(out_id, g_roi_id[i], g_roi_data[g_roi_id[i]], g_roi_area[g_roi_id[i]]);
			//ROI深度数据的数据量需要通过ROI区域计算
			g_roi_data_count = (g_roi_area[g_roi_id[i]][2] - g_roi_area[g_roi_id[i]][0] + 1) * (g_roi_area[g_roi_id[i]][3] - g_roi_area[g_roi_id[i]][1] + 1);
			printf("roi_data_count:%d roi_data:%d\n", g_roi_data_count, g_roi_data[g_roi_id[i]][g_roi_data_count - 1]);
#endif
			//获取ROI的深度数学统计信息
			HPS3D_GetOutRoiAverageDistance_CB(out_id, g_roi_id[i], &g_roi_aver_distance);
			HPS3D_GetOutRoiMaxDistance_CB(out_id, g_roi_id[i], &g_roi_max_distance);
			HPS3D_GetOutRoiMinDistance_CB(out_id, g_roi_id[i], &g_roi_min_distance);
			HPS3D_GetOutRoiAllAverAmplitude_CB(out_id, g_roi_id[i], &g_roi_all_aver_amp);
			HPS3D_GetOutRoiValidAverAmplitude_CB(out_id, g_roi_id[i], &g_roi_valid_aver_amp);
			printf("roi_aver_distance:%d  roi_max_distance:%d  roi_min_distance:%d\n", g_roi_aver_distance, g_roi_max_distance, g_roi_min_distance);
			printf("roi_all_aver_amp:%d  roi_valid_aver_amp:%d\n", g_roi_all_aver_amp, g_roi_valid_aver_amp);
			printf("point_count:%d  g_point_data:%f  fps:%d\n", g_point_count, g_point_data[g_point_count - 1][0], g_fps);
		}

	}
	else if (event == EVENT_ROIFULLDISTANCERECVD) //ROI完整深度通知事件
	{

		//ROI完整深度事件，可以获取每个ROI的深度数据和每个ROI的深度数学统计信息

		uint8_t group_id = 0;
		uint8_t roi_number = 0;

		//获取指定ROI的深度信息前，需要通过ROI参数接口，获取当前输出的ROI信息，（有几个ROI，ROI的ID等）
		//获取ROI参数
		HPS3D_GetOutRoiParam_CB(out_id, &group_id, &roi_number, g_roi_id);

		for (int i = 0; i < roi_number; i++)
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
		for (int i = 0; i < roi_number; i++)
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
}


int main()
{
	//第一步，初始化
	if (Init() != RET_OK)
	{
		printf("设备初始化:..........失败!\n");
		return -1;
	}
	else
	{
		printf("设备初始化:..........成功!\n");
	}
	//第二步，输出数据（必要）
	//输出数据可以选择输出一次数据和连续输出数据两种
	
	//1.输出一次数据
	HPS3D_SetRunMode(g_device_id, RUN_SINGLE_SHOT);
	printf("执行输出一次数据，按回车键继续运行!\n");
	getchar();
	g_fps = 0;
	//2.连续输出数据
	uint8_t tem = 0;
	HPS3D_SetRunMode(g_device_id, RUN_CONTINUOUS);
	g_start = clock();
	while (1)
	{
		g_end = clock();
		if ((g_end - g_start) >= 1000)
		{
			g_start = clock();
			printf("%d", g_fps);
			g_fps = 0;
			tem++;
		}
		//两秒后退出
		if (tem == 2)
		{
			break;
		}
	}

	//停止输出数据
	HPS3D_SetRunMode(g_device_id, RUN_IDLE);
	//断开设备
	HPS3D_DisConnect(g_device_id);
	printf("程序运行完成，按回车键退出\n");
	getchar();
	return 0;
}

//设备初始化
uint8_t Init()
{
	uint8_t ret = 0; 
	//第一步，设置Debug信息回调函数，用于打印错误信息
	//调试时使用，不需要可以不注册（可选）
	ret =  HPS3D_SetDebugCallBack(debugFunc, NULL);
	if (ret != RET_OK)
	{
		printf("DEBUG信息回调函数注册:..........失败!\n");
	}
	else
	{
		printf("DEBUG信息回调函数注册:..........成功!\n");
	}
	

	//第二步，连接设备（必要），以下为设备的默认IP和端口号
	ret = HPS3D_ConnectByEthernet((char*)"192.168.30.202", 12345, &g_device_id);
	if (ret != RET_OK)
	{
		printf("设备连接:..........失败!\n");
		return RET_ERROR;
	}
	else
	{
		printf("设备连接:..........成功!\n");
	}

	//第三步，注册输出事件回调函数（必要）
	ret = HPS3D_SetOutputCallBack(OutputEventFunc, g_device_id, NULL);
	if (ret != RET_OK)
	{
		printf("输出事件回调函数注册:..........失败!\n");
		return RET_ERROR;
	}
	else
	{
		printf("输出事件回调函数注册:..........成功!\n");
	}


	//第四步，关闭开门狗使能（可选）
	//调试时使用，调试完成后需要及时开启
	//ret = HPS3D_SetWatchDogEnable(g_device_id, false);
	//if (ret != RET_OK)
	//{
	//	printf("看门狗关闭:..........失败!\n");
	//	printf("按回车键继续运行!!\n");
	//	getchar();
	//}
	//else 
	//{
	//	printf("看门狗关闭:..........成功!\n");
	//}
	

	//查询设备信息
	QueryDeviceInf();

	//第五步，设备参数配置（可选）,该部分可以使用客户端配置
	//首次运行设备时需要配置参数，之后保存到用户配置后再次运行不需要重新配置
	if (SetupDevice() != RET_OK)
	{
		return RET_ERROR;
	}


	//第六步，设置设备输出类型（必要）
	if (SetOutPutType() != RET_OK)
	{
		return RET_ERROR;
	}
	return RET_OK;
}

//设备信息获取
uint8_t QueryDeviceInf()
{
	uint8_t ret = 0;
	uint8_t sdk_version[6] = { 0 };
	uint8_t device_version[6] = { 0 };
	char SN[64] = { 0 };

	ret = HPS3D_GetSDKVersion(sdk_version);
	if (ret != RET_OK)
	{
		printf("SDK版本信息获取:..........失败!\n");
		printf("按回车键继续运行!\n");
		getchar();
	}
	else
	{
		printf("SDK版本:20%d-%d-%d V%d.%d.%d\n", sdk_version[0], sdk_version[1]
			, sdk_version[2], sdk_version[3], sdk_version[4], sdk_version[5]);
	}
	
	
	//获取设备版本前，需要确保设备已经正常连接
	ret = HPS3D_GetDeviceVersion(g_device_id, device_version);
	if (ret != RET_OK)
	{
		printf("设备版本信息获取:..........失败!\n");
		printf("按回车键继续运行!\n");
		getchar();
	}
	else
	{
		printf("设备版本:20%d-%d-%d V%d.%d.%d\n", device_version[0], device_version[1]
			, device_version[2], device_version[3], device_version[4], device_version[5]);
	}
	

	//获取设备序列号前，需要确保设备已经正常连接
	ret = HPS3D_GetDeviceSN(g_device_id, SN);
	if (ret != RET_OK)
	{
		printf("设备序列号获取:..........失败!\n");
		printf("按回车键继续运行!\n");
		getchar();
	}
	else
	{
		printf("设备序列号:%s\n", SN);
	}
	return RET_OK;
}

//配置设备参数，需要确保设备已经正常连接
uint8_t SetupDevice()
{
	uint8_t ret = 0;
	uint32_t time_us = 0;

	//积分时间根据现场环境和被测物体信号反射强度进行调节（必要）
	ret = HPS3D_SetIntegTime(g_device_id, 1000);
	if (ret != RET_OK)
	{
		printf("设置积分时间:..........失败!\n");
		printf("按回车键继续运行!\n");
		getchar();
		return RET_ERROR;
	}
	else
	{
		printf("设置积分时间:..........成功!\n");
	}
	

	//获取积分时间
	//ret = HPS3D_GetIntegTime(g_device_id, &time_us);
	//if (ret != RET_OK)
	//{
	//	printf("获取积分时间失败，按回车键继续运行!\n");
	//	getchar();
	//}
	//printf("积分时间：%d us\n", time_us);

	//滤波器配置（可选）
	//1.平滑滤波器配置,根据需要自行选择滤波器类型,以下为关闭
	ret = HPS3D_SetSmoothFilter(g_device_id, SMOOTH_FILTER_DISABLE, 0);
	if (ret != RET_OK)
	{
		printf("设置平滑滤波器:..........失败!\n");
		printf("按回车键继续运行!\n");
		getchar();
	}
	else
	{
		printf("设置平滑滤波器:..........成功!\n");
	}
	

	//2.卡尔曼滤波器，根据需要自行选择滤波器参数,以下为关闭
	ret = HPS3D_SetSimpleKalmanFilter(g_device_id, false, NULL, NULL, NULL);
	if (ret != RET_OK)
	{
		printf("设置卡尔曼滤波器:..........失败!\n");
		printf("按回车键继续运行!\n");
		getchar();
	}
	else
	{
		printf("设置卡尔曼滤波器:..........成功!\n");
	}
	

	//距离偏移（可选），以下默认设置为0
	ret = HPS3D_SetOffset(g_device_id, 0);
	if (ret != RET_OK)
	{
		printf("设置距离偏移:..........失败!\n");
		printf("按回车键继续运行!\n");
		getchar();
	}
	else
	{
		printf("设置距离偏移:..........成功!\n");
	}
	

	//将设置保存到用户配置表，保存后重新上电不会丢失
	ret = HPS3D_ProfileSaveToUser(g_device_id);
	if (ret != RET_OK)
	{
		printf("用户配置表保存:..........失败!\n");
		printf("按回车键继续运行!\n");
		getchar();
	}
	else
	{
		printf("用户配置表保存:..........成功!\n");
	}
	

	//还原到出厂设置
	//ret = HPS3D_ProfileRestoreFactory(g_device_id);
	//if (ret != RET_OK)
	//{
	//	printf("还原到出厂设置失败，按回车键继续运行!\n");
	//	getchar();
	//}
	return RET_OK;

}

//设置设备输出类型，需要确保设备已经正常连接
uint8_t SetOutPutType()
{
	//选定一种需要输出的数据，配置完成后将通过回调函数 OutputEventFunc 通知对应事件。
	//每次只能输出一种类型的数据

	//1：简单深度事件 2：完整深度事件 3：幅值事件 4：完整点云事件 
	//5：ROI点云事件 6：ROI完整深度事件 7：ROI简单深度事件
	uint8_t type = 2;  
	switch (type)
	{
	case 1: //设置简单深度事件，需要进行以下配置
		if (HPS3D_SetOutputDataType(g_device_id, OUTPUT_DISTANCE_SIMPLE) != RET_OK)
		{
			printf("设置简单深度事件:..........失败!\n");
			return RET_ERROR;
		}
		//如果开启了ROI需要关闭，开启了哪个就关闭哪个，以下示例为全部关闭
		for (int i = 0; i < 8; i++)
		{
			if (HPS3D_SetROIEnable(g_device_id, i, false) != RET_OK)
			{
				printf("设置简单深度事件:..........失败!\n");
				return RET_ERROR;
			}
		}
		break;

	case 2://设置完整深度事件，需要进行以下配置
		if (HPS3D_SetOutputDataType(g_device_id, OUTPUT_DISTANCE_FULL) != RET_OK)
		{
			printf("设置完整深度事件:..........失败!\n");
			return RET_ERROR;
		}
		//如果开启了点云转换，则需要关闭
		if (HPS3D_SetPointCloudMode(g_device_id, false, MIRROR_DISABLE) != RET_OK)
		{
			printf("设置完整深度事件:..........失败!\n");
			return RET_ERROR;
		}
		//如果开启了ROI需要关闭，开启了哪个就关闭哪个，以下示例为全部关闭
		for (int i = 0; i < 8; i++)
		{
			if (HPS3D_SetROIEnable(g_device_id, i, false) != RET_OK)
			{
				printf("设置完整深度事件:..........失败!\n");
				return RET_ERROR;
			}
		}
		break;

	case 3://设置幅值事件，需要进行以下配置
		if (HPS3D_SetOutputDataType(g_device_id, OUTPUT_AMPLITUDE) != RET_OK)
		{
			printf("设置振幅事件:..........失败!\n");
			return RET_ERROR;
		}
		break;
	
	case 4://设置完整点云事件，需要进行以下配置
		if (HPS3D_SetOutputDataType(g_device_id, OUTPUT_DISTANCE_FULL) != RET_OK)
		{
			printf("设置完整点云事件:..........失败!\n");
			return RET_ERROR;
		}
		//如果没有开启点云转换，则需要开启
		if (HPS3D_SetPointCloudMode(g_device_id, true, MIRROR_DISABLE) != RET_OK)
		{
			printf("设置完整点云事件:..........失败!\n");
			return RET_ERROR;
		}
		//如果开启了ROI需要关闭，开启了哪个就关闭哪个，以下示例为全部关闭
		for (int i = 0; i < 8; i++)
		{
			if (HPS3D_SetROIEnable(g_device_id, i, false) != RET_OK)
			{
				printf("设置完整点云事件:..........失败!\n");
				return RET_ERROR;
			}
		}
		break;
	
	case 5://设置ROI点云事件，需要进行以下配置
		if (HPS3D_SetOutputDataType(g_device_id, OUTPUT_DISTANCE_FULL) != RET_OK)
		{
			printf("设置ROI点云事件:..........失败!\n");
			return RET_ERROR;
		}
		//如果没有开启点云转换，则需要开启
		if (HPS3D_SetPointCloudMode(g_device_id, true, MIRROR_DISABLE) != RET_OK)
		{
			printf("设置ROI点云事件:..........失败!\n");
			return RET_ERROR;
		}
		//如果没有开启ROI需要开启（ROI配置需要使用客户端）SDK仅提供ROI使能开关
		//以下开启ROI 0,注意如果没有使用客户端绘制ROI区域，设置ROi使能将无效
		if (HPS3D_SetROIEnable(g_device_id, 0, true) != RET_OK)
		{
			printf("设置ROI点云事件:..........失败!\n");
			return RET_ERROR;
		}
		break;

	case 6://设置ROI完整深度事件，需要进行以下配置
		if (HPS3D_SetOutputDataType(g_device_id, OUTPUT_DISTANCE_FULL) != RET_OK)
		{
			printf("设置ROI完整深度事件:..........失败!\n");
			return RET_ERROR;
		}
		//如果开启了点云转换，则需要关闭
		if (HPS3D_SetPointCloudMode(g_device_id, false, MIRROR_DISABLE) != RET_OK)
		{
			printf("设置ROI完整深度事件:..........失败!\n");
			return RET_ERROR;
		}
		//如果没有开启ROI需要开启（ROI配置需要使用客户端）SDK仅提供ROI使能开关
		//以下开启ROI 0,注意如果没有使用客户端绘制ROI区域，设置ROi使能将无效
		if (HPS3D_SetROIEnable(g_device_id, 0, true) != RET_OK)
		{
			printf("设置ROI完整深度事件:..........失败!\n");
			return RET_ERROR;
		}
		break;

	case 7://设置ROI简单深度事件，需要进行以下配置
		if (HPS3D_SetOutputDataType(g_device_id, OUTPUT_DISTANCE_SIMPLE) != RET_OK)
		{
			printf("设置ROI简单深度事件:..........失败!\n");
			return RET_ERROR;
		}
		//如果没有开启ROI需要开启（ROI配置需要使用客户端）SDK仅提供ROI使能开关
		//以下开启ROI 0,注意如果没有使用客户端绘制ROI区域，设置ROi使能将无效
		if (HPS3D_SetROIEnable(g_device_id, 0, true) != RET_OK)
		{
			printf("设置ROI简单深度事件:..........失败!\n");
			return RET_ERROR;
		}
		break;

	default:
		break;
	}
	printf("设置输出类型配置:..........成功!\n");
	return RET_OK;
}

