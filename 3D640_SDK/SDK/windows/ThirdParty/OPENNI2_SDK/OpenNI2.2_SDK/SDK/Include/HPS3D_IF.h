/**********************************************************************
* COPYRIGHT NOTICE - HYPERSEN TECHNOLOGY
*
* Copyright (c) 2020, Hypersen Technology, Inc.
*
* All rights reserved.
*
*======================================================================
* @projectName HPS3D
* @file HPS3D_IF.h
* @brief TODO
* @author Lance
* @email Lance_Hu@hypersen.com
* @version 1.0.0
* @date 2020年8月24日 上午10:48:20
* @license public & classified
*---------------------------------------------------------------------
* Remark: This project is still under construction.
*======================================================================
* Change History:
*---------------------------------------------------------------------
* <Date>      | <Version>  | <Author>      | <Description>
*---------------------------------------------------------------------
* 2020年8月24日       | V1.0.0  | Lance        | Create file
*======================================================================
* Detailed Notes:
*---------------------------------------------------------------------
* <Version>    | <Description>
*---------------------------------------------------------------------
* V1.0.0    | TODO
*---------------------------------------------------------------------

**********************************************************************/

#ifndef HPS3D_IF_H_
#define HPS3D_IF_H_


#include <stdbool.h>
#include <stdint.h>



#include "HPS3D_DEFINE.h"

#ifdef _WIN32 /*windows平台*/
#if BUILDING_DLL
#define HPS3D640_API __declspec(dllexport)
#else
#define HPS3D640_API __declspec(dllimport)
#endif
#else
#define __stdcall  
#define __cdecl  
#define HPS3D640_API extern
#endif
#ifdef __cplusplus
extern "C"
{
#endif

#define     __IN
#define     __OUT

typedef float 			float32_t;
typedef double 			float64_t;

#define     DEV_NUM		(0x04)							/*最大连接设备数量*/
#define		X_PIX_NUM	640
#define		Y_PIX_NUM	480
#define		PIXEL_NUM	307200
 
/**
* @brief	输出事件回调
* @param    out_id		    输出设备的ID
* @param    event			输出的事件，OUTPUT_EVENT_SIMPLEDATARECVD
* @param    contex			用户自定义参数，回调上下文
*/
typedef void(__cdecl *HPS3D_CALLBACK_OUTPUT)(uint8_t out_id, uint8_t event, void *contex);


/**
* @brief	DEBUG信息回调
* @param    str			输出的DEBUG信息
* @param    contex		用户自定义参数，回调上下文
*/
typedef void(__cdecl *HPS3D_CALLBACK_DEBUG)(char *str, void *contex);

	/**
	* @brief	HPS3D_SetDebugCallBack
	*			设置Debug回调函数
	* @param	call_back	HPS3D_CALLBACK_DEBUG
	call_back设置为NULL时将停止该功能
	* @param    contex      用户自定义参数，回调上下文，不需要时则置为NULL
	* @retval	成功返回 RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetDebugCallBack(__IN HPS3D_CALLBACK_DEBUG call_back, __IN void *contex);

	/**
	* @brief	HPS3D_ConnectByEthernet
	*			设置以太网连接方式
	* @param	server_ip		设备IP， ASCII编码，"192.168.0.1"
	* @param	server_port		设备端口号
	* @param	device_id		设备ID号，设置失败时，ID返回值为99
	* @note     必须与固件上设置的连接方式对应
	* @retval	成功返回 RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_ConnectByEthernet(__IN char *server_ip, __IN uint16_t server_port, __OUT uint8_t *device_id);
	
	/**
	* @brief	HPS3D_ScanDeviceList
	*			扫描设备的ID列表
	* @param	device_list[0]      设备ID号
	* @param	device_list[1]      设备ID号
	* @param	device_list[2]      设备ID号
	* @param	device_list[3]      设备ID号
	* @param	device_count		已经连接设备的数量
	* @note     device_list数组最少开辟4个空间，device_list[DEV_NUM]
	* @note		例如：当只有一台设备连接时
				device_count 返回值为1时，device_list[0] = 当前已连接的设备ID
				device_list[1] = device_list[2] = device_list[3] = 99
	* @retval	成功返回 RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_ScanDeviceList(__OUT uint8_t* device_list, __OUT uint8_t* device_count);

	/**
	* @brief	HPS3D_DisConnect
	*			断开设备
	* @param	device_id	设备ID
	* @note     device_id必须与连接时返回的ID对应
	* @note		程序运行完成后需要调用此接口断开连接，释放资源
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_DisConnect(__IN uint8_t device_id);
	
	/**
	* @brief	HPS3D_SetOutputCallBack
	*			设置输出事件回调函数
	* @param	call_back	HPS3D_CALLBACK_OUTPUT，
							call_back设置为NULL时将停止该功能
	* @param	device_id	设备ID
	* @param    contex		用户自定义参数，回调上下文，不需要时则置为NULL
	* @note     device_id必须与连接时返回的ID对应
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetOutputCallBack(__IN HPS3D_CALLBACK_OUTPUT call_back, __IN uint8_t device_id, __IN void *contex);
	
	/**
	* @brief	HPS3D_GetAverageDistance_CB
	*			获取平均距离（回调函数中使用）
	* @param	device_id			设备ID
	* @param    aver_distance		返回平均距离，单位毫米
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_SIMPLEDISTANCERECVD
				或者 EVENT_FULLDISTANCERECVD 或者 EVENT_FULLPOINTCLOUDRECVD 通知时调用
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetAverageDistance_CB(__IN uint8_t device_id, __OUT uint16_t *aver_distance);

	/**
	* @brief	HPS3D_GetMaxDistance_CB
	*			获取最大距离（回调函数中使用）
	* @param	device_id			设备ID
	* @param    max_distance		返回最大距离，单位毫米
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_SIMPLEDISTANCERECVD
				或者 EVENT_FULLDISTANCERECVD 或者 EVENT_FULLPOINTCLOUDRECVD 通知时调用
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetMaxDistance_CB(__IN uint8_t device_id, __OUT uint16_t *max_distance);

	/**
	* @brief	HPS3D_GetMinDistance_CB
	*			获取最小距离（回调函数中使用）
	* @param	device_id			设备ID
	* @param    min_distance		返回最小距离，单位毫米
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_SIMPLEDISTANCERECVD
				或者 EVENT_FULLDISTANCERECVD 或者 EVENT_FULLPOINTCLOUDRECVD 通知时调用
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetMinDistance_CB(__IN uint8_t device_id, __OUT uint16_t *min_distance);

	/**
	* @brief	HPS3D_GetAllAverAmplitude_CB
	*			获取所有平均幅值（回调函数中使用）
	* @param	device_id			设备ID
	* @param    all_aver_amp		所有平均幅值（包括0幅值）
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_SIMPLEDISTANCERECVD
				或者 EVENT_FULLDISTANCERECVD 或者 EVENT_FULLPOINTCLOUDRECVD 通知时调用
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetAllAverAmplitude_CB(__IN uint8_t device_id, __OUT uint16_t *all_aver_amp);

	/**
	* @brief	HPS3D_GetValidAverAmplitude_CB
	*			获取有效的平均幅值（回调函数中使用）
	* @param	device_id			设备ID
	* @param    valid_aver_amp		返回有效的平均幅值
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_SIMPLEDISTANCERECVD
				或者 EVENT_FULLDISTANCERECVD 或者 EVENT_AMPLITUDE 或者 EVENT_FULLPOINTCLOUDRECVD 通知时调用
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetValidAverAmplitude_CB(__IN uint8_t device_id, __OUT uint16_t *valid_aver_amp);

	/**
	* @brief	HPS3D_GetDistanceData_CB
	*			获取距离数据（回调函数中使用）
	* @param	device_id			设备ID
	* @param    distance_data		距离数据,单位毫米（需要开辟307200个空间)
	* @note     该接口只能在回调函数中收到 EVENT_FULLDISTANCERECVD 通知时调用
	* @note     device_id必须与回调函数输出的ID对应
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetDistanceData_CB(__IN uint8_t device_id, __OUT uint16_t *distance_data);

	/**
	* @brief	HPS3D_GetGrayscaleData_CB
	*			获取灰度数据（回调函数中使用）
	* @param	device_id			设备ID
	* @param    grayscale_data		灰度数据,单位灰度值（范围0~255）（需要开辟307200个空间)
	* @note     该接口只能在回调函数中收到 EVENT_AMPLITUDE 通知时调用
	* @note     device_id必须与回调函数输出的ID对应
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetGrayscaleData_CB(__IN uint8_t device_id, __OUT uint8_t *grayscale_data);


	/**
	* @brief	HPS3D_GetAmplitudeData_CB
	*			获取幅值数据（回调函数中使用）
	* @param	device_id			设备ID
	* @param    amplitude_data		幅值数据,（需要开辟307200个空间)
	* @note     该接口只能在回调函数中收到 EVENT_AMPLITUDE 通知时调用
	* @note     device_id必须与回调函数输出的ID对应
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetAmplitudeData_CB(__IN uint8_t device_id, __OUT uint16_t *amplitude_data);

	/**
	* @brief	HPS3D_GetMaxAmplitudeData_CB
	*			获取最大幅值数据（回调函数中使用）
	* @param	device_id			设备ID
	* @param    max_amplitude		最大幅值数据
	* @note     该接口只能在回调函数中收到 EVENT_AMPLITUDE 通知时调用
	* @note     device_id必须与回调函数输出的ID对应
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetMaxAmplitudeData_CB(__IN uint8_t device_id, __OUT uint16_t *max_amplitude);

	/**
	* @brief	HPS3D_GetMinAmplitudeData_CB
	*			获取最小幅值数据（回调函数中使用）
	* @param	device_id			设备ID
	* @param    min_amplitude		最小幅值数据
	* @note     该接口只能在回调函数中收到 EVENT_AMPLITUDE 通知时调用
	* @note     device_id必须与回调函数输出的ID对应
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetMinAmplitudeData_CB(__IN uint8_t device_id, __OUT uint16_t *min_amplitude);


	/**
	* @brief	HPS3D_GetPointCloudData_CB
	*			获取点云数据（回调函数中使用）
	* @param	device_id			设备ID
	* @param    point_data		    点云数据,定义方式,point_data[307200][3]
	* @param    point_count		    有效点的数量
	* @note     该接口只能在回调函数中收到 EVENT_FULLPOINTCLOUDRECVD
				或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
	* @note     device_id必须与回调函数输出的ID对应
	* @note     point_data中，[3]的值：0表示X轴值，1表示Y轴值，2表示Z轴值
	* @note		其中，无效点已经被自动过滤
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetPointCloudData_CB(__IN uint8_t device_id, __OUT double(*point_data)[3], __OUT uint32_t *point_count);

	/**
	* @brief	HPS3D_GetOutRoiParam_CB
	*			获取输出的ROI参数信息（回调函数中使用）
	* @param	device_id			设备ID
	* @param    group_id			返回ROI组ID
	* @param    roi_number			返回ROI个数
	* @param    roi_id				返回ROI的ID，需要开辟8个空间，roi_id[8]
	* @note		roi_number的值决定roi_id的有效数据个数，
				例如：roi_number = 1时
				roi_id[0] = ROI的ID。roi_id[1~7] 无效
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_ROIPOINTCLOUDRECVD
				或者 EVENT_ROIFULLDISTANCERECVD 或者 EVENT_ROISIMPLEDISTANCERECVD 通知时调用
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiParam_CB(__IN uint8_t device_id, __OUT uint8_t *group_id, __OUT uint8_t *roi_number, __OUT uint8_t *roi_id);

	/**
	* @brief	HPS3D_GetOutRoiPointCloudData_CB
	*			获取输出ROI的点云数据（回调函数中使用）
	* @param	device_id			设备ID
	* @param	roi_id				Roi的ID
	* @param    roi_point_data		    点云数据,定义方式,point_data[307200][3]
	* @param    roi_point_count		    返回有效点的数量
	* @note     该接口只能在回调函数中收到 EVENT_ROIPOINTCLOUDRECVD 通知时调用
	* @note     device_id必须与回调函数输出的ID对应
	* @note     roi_point_data中，[3]的值：0表示X轴值，1表示Y轴值，2表示Z轴值
	* @note		其中，无效点已经被自动过滤
	* @note     调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiPointCloudData_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT double (*roi_point_data)[3], __OUT uint32_t *roi_point_count);

	/**
	* @brief	HPS3D_GetOutRoiDistanceData_CB
	*			获取输出的ROI深度数据（回调函数中使用）
	* @param	device_id			设备ID
	* @param    roi_id			    ROI的ID
	* @param    roi_distance_data	ROI的深度数据，单位毫米，需要开辟307200个空间，roi_distance_data[307200]
	* @param    roi_area	        ROI的范围，需要开辟4个空间，roi_area[4]
	* @note     device_id必须与回调函数输出的ID对应
	* @note     roi_area[0]：表示左上角点的X坐标  roi_area[1]：表示左上角点的Y坐标
				roi_area[2]：表示右下角点的X坐标  roi_area[3]：标志右下角点的Y坐标
				该区域的像素个数计算公式为： (right_bottom_x - left_top_x + 1) * (right_bottom_y - left_top_y + 1));
				pixel_number = (roi_area[2] - roi_area[0] + 1) * (roi_area[3] - roi_area[1] + 1)
	* @note     该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 通知时调用
	* @note     调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiDistanceData_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *roi_distance_data, __OUT uint16_t *roi_area);

	/**
	* @brief	HPS3D_GetOutRoiAverageDistance_CB
	*			获取输出的ROI平均距离（回调函数中使用）
	* @param	device_id			设备ID
	* @param	roi_id				ROI的ID
	* @param    aver_distance		返回平均距离，单位毫米
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 或者
	EVENT_ROISIMPLEDISTANCERECVD 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
	* @note     调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiAverageDistance_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *aver_distance);

	/**
	* @brief	HPS3D_GetOutRoiMaxDistance_CB
	*			获取输出的ROI最大距离（回调函数中使用）
	* @param	device_id			设备ID
	* @param	roi_id				ROI的ID
	* @param    max_distance		返回最大距离，单位毫米
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 或者
				EVENT_ROISIMPLEDISTANCERECVD 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
	* @note     调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiMaxDistance_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *max_distance);

	/**
	* @brief	HPS3D_GetOutRoiMinDistance_CB
	*			获取输出的ROI最小距离（回调函数中使用）
	* @param	device_id			设备ID
	* @param	roi_id				ROI的ID
	* @param    min_distance		返回最小距离，单位毫米
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 或者
				EVENT_ROISIMPLEDISTANCERECVD 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
	* @note     调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiMinDistance_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *min_distance);

	/**
	* @brief	HPS3D_GetOutRoiAllAverAmplitude_CB
	*			获取输出的ROI所有平均幅值（回调函数中使用）
	* @param	device_id			设备ID
	* @param	roi_id				ROI的ID
	* @param    all_aver_amp		所有平均幅值（包括0幅值）
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 或者
				EVENT_ROISIMPLEDISTANCERECVD 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
	* @note     调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiAllAverAmplitude_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *all_aver_amp);

	/**
	* @brief	HPS3D_GetOutRoiValidAverAmplitude_CB
	*			获取输出的ROI有效平均幅值（回调函数中使用）
	* @param	device_id			设备ID
	* @param	roi_id				ROI的ID
	* @param    valid_aver_amp		返回有效的平均幅值（不包括0幅值）
	* @note     device_id必须与回调函数输出的ID对应
	* @note     该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 或者
				EVENT_ROISIMPLEDISTANCERECVD 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
	* @note     调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiValidAverAmplitude_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *valid_aver_amp);

	/**
	* @brief	HPS3D_GetCameraParam
	*			获取相机内参矩阵
	* @param	device_id
	* @param	cameraParam    相机内参
	* @note     device_id必须与连接时返回的ID对应
	* @note     CameraParam[0]   光心坐标，CX
	* @note     CameraParam[1]   光心坐标，CY
	* @note     CameraParam[2]   相机焦距，FX
	* @note     CameraParam[3]   相机焦距，FY
	* @note     CameraParam[4]   径向畸变系数，K1
	* @note     CameraParam[5]   径向畸变系数，K2
	* @note     CameraParam[6]   斜向畸变系数，P1
	* @note     CameraParam[7]   斜向畸变系数，P2
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetCameraParam(__IN uint8_t device_id, __OUT float64_t *cameraParam);

	/**
	* @brief	HPS3D_SetRunMode
	*			设置运行模式
	* @param	device_id
	* @param	run_mode	运行模式，RUN_IDLE
	* @note     device_id必须与连接时返回的ID对应
	* @note		每次设置为 RUN_SINGLE_SHOT 将通过回调函数吐一帧数据
	* @retval	成功返回 RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetRunMode(__IN uint8_t device_id, __IN uint8_t run_mode);

	/**
	* @brief	HPS3D_GetRunMode
	*			获取运行模式
	* @param	device_id
	* @param	run_mode	返回当前运行模式，RUN_IDLE
	* @note     device_id必须与连接时返回的ID对应
	* @retval	成功返回 RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetRunMode(__IN uint8_t device_id, __OUT uint8_t *run_mode);

	/**
	* @brief	HPS3D_SetPointCloudMode
	*			设置点云模式配置
	* @param	device_id					设备ID
	* @param	point_cloud_enable			点云图使能
	* @param    mirror_mode					点云图镜像模式,MIRROR_DISABLE
	* @note     device_id必须与连接时返回的ID对应
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetPointCloudMode(__IN uint8_t device_id, __IN bool point_cloud_enable, __IN uint8_t mirror_mode);
	
	/**
	* @brief	HPS3D_GetPointCloudMode
	*			获取点云模式配置
	* @param	device_id			设备ID
	* @param	point_cloud_enable	返回点云图使能
	* @param    mirror_mode			返回点云图镜像模式,MIRROR_DISABLE
	* @note     device_id必须与连接时返回的ID对应
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetPointCloudMode(__IN uint8_t device_id, __OUT bool *point_cloud_enable, __OUT uint8_t *mirror_mode);

	/*
	* @brief	HPS3D_SetMeasureMode
	*			设置测量模式
	* @param	device_id
	* @param	measure_mode	  测量模式，DSITMODE_GENERAL
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetMeasureMode(__IN uint8_t device_id, __IN uint8_t measure_mode);

	/*
	* @brief	HPS3D_GetMeasureMode
	*			获取测量模式
	* @param	device_id
	* @param	measure_mode		返回测量模式，DSITMODE_GENERAL
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetMeasureMode(__IN uint8_t device_id, __OUT uint8_t *measure_mode);
	
	/*
	* @brief	HPS3D_GetSDKVersion
	*			获取SDK版本信息
	* @param	device_id
	* @param	version			SDK版本信息
	* @param	version[0] 		year
	* @param	version[1]		month;
	* @param	version[2]		day;
	* @param	version[3]		major;
	* @param	version[4]		minor;
	* @param	version[5]		rev;
	* @note     version数组最少开辟6个空间，version[6]
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetSDKVersion(__OUT uint8_t *version);

	/*
	* @brief	HPS3D_GetDeviceVersion
	*			获取设备版本信息
	* @param	device_id
	* @param	version			设备版本信息
	* @param	version[0] 		year
	* @param	version[1]		month;
	* @param	version[2]		day;
	* @param	version[3]		major;
	* @param	version[4]		minor;
	* @param	version[5]		rev;
	* @note     device_id必须与连接时返回的ID对应
	* @note     version数组最少开辟6个空间，version[6]
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @see      HPS3D_SetRunMode
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetDeviceVersion(__IN uint8_t device_id, __OUT uint8_t *version);

	/*
	* @brief	HPS3D_GetDeviceSN
	*			获取设备序列号
	* @param	device_id
	* @param	SN		返回设备序列号
	* @note     device_id必须与连接时返回的ID对应
	* @note		SN最小开辟64个空间，SN[64]
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetDeviceSN(__IN uint8_t device_id, __OUT char * SN);

	/*
	* @brief	HPS3D_GetOutputDataType
	*			获取输出数据类型
	* @param	device_id
	* @param	data_type		返回输出数据类型,OUTPUT_AMPLITUDE
	* @note     device_id必须与连接时返回的ID对应
	* @note     OUTPUT_AMPLITUDE，将通过回调函数输出振幅数据
				OUTPUT_DISTANCE_FULL，将通过回调函数输出完整深度数据，包含各像素点数据
				OUTPUT_DISTANCE_SIMPLE，将通过回调函数输出简单深度数据，不包含各像素点数据，只包含数学统计数据
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutputDataType(__IN uint8_t device_id, __OUT uint8_t *data_type);

	/*
	* @brief	HPS3D_SetOutputDataType
	*			设置输出数据类型
	* @param	device_id
	* @param	data_type		输出数据类型,OUTPUT_AMPLITUDE
	* @note     device_id必须与连接时返回的ID对应
	* @note     OUTPUT_AMPLITUDE，将通过回调函数输出振幅数据
				OUTPUT_DISTANCE_FULL，将通过回调函数输出完整深度数据，包含各像素点数据
				OUTPUT_DISTANCE_SIMPLE，将通过回调函数输出简单深度数据，不包含各像素点数据，只包含数学统计数据
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetOutputDataType(__IN uint8_t device_id, __IN uint8_t data_type);

	/*
	* @brief	HPS3D_SetComInConf
	*			设置输入端口的配置
	* @param	device_id
	* @param	in_port			端口号（输入端口），GPIN_1
	* @param	in_func			端口功能，GPIN_FUNC_DISABLE
	* @param	in_polarity		端口极性，GPIO_POLARITY_LOW
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetComInConf(__IN uint8_t device_id, __IN uint8_t in_port, __IN uint8_t in_func, __IN uint8_t in_polarity);

	/*
	* @brief	HPS3D_GetComInConf
	*			获取输入端口的配置
	* @param	device_id
	* @param	in_port   		需要获取的输入端口号，GPIN_1
	* @param	in_func   		端口功能，GPIN_FUNC_DISABLE
	* @param	in_polarity   	端口极性，GPIO_POLARITY_LOW
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetComInConf(__IN uint8_t device_id, __IN uint8_t in_port, __OUT uint8_t *in_func, __OUT uint8_t *in_polarity);

	/*
	* @brief	HPS3D_SetComOutConf
	*			设置输出端口的配置
	* @param	device_id
	* @param	out_port		端口号（输出端口），GPOUT_1
	* @param	out_func		端口功能，GPOUT_FUNC_DISABLE
	* @param	out_polarity	端口极性，GPIO_POLARITY_LOW
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetComOutConf(__IN uint8_t device_id, __IN uint8_t out_port, __IN uint8_t out_func, __IN uint8_t out_polarity);

	/*
	* @brief	HPS3D_GetComOutConf
	*			获取输出端口的配置
	* @param	device_id
	* @param	out_port		需要获取的输出端口号，GPOUT_1
	* @param	out_func   		端口功能，GPOUT_FUNC_DISABLE
	* @param	out_polarity  	端口极性，GPIO_POLARITY_LOW
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetComOutConf(__IN uint8_t device_id, __IN uint8_t out_port, __OUT uint8_t *out_func, __OUT uint8_t *out_polarity);

	/**
	* @brief	HPS3D_SetIntegTime
	*			设置积分时间
	* @param	device_id
	* @param	time_us		积分时间(单位us，范围50~1000)
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetIntegTime(__IN uint8_t device_id, __IN uint32_t time_us);

	/**
	* @brief	HPS3D_GetIntegTime
	*			获取积分时间
	* @param	device_id
	* @param	time_us		返回积分时间(单位us，最大设置为1000)
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetIntegTime(__IN uint8_t device_id, __OUT uint32_t *time_us);

	/**
	* @brief	HPS3D_ProfileSaveToUser
	*			保存到用户设置表
	* @param	device_id
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_ProfileSaveToUser(__IN uint8_t device_id);


	/**
	* @brief	HPS3D_ProfileClearUser
	*			清除用户设置表
	* @param	device_id
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_ProfileClearUser(__IN uint8_t device_id);

	/**
	* @brief	HPS3D_SetROIGroup
	*			选择ROI组
	* @param	device_id
	* @param	group_id    ROI组的ID,0~1
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetROIGroup(__IN uint8_t device_id, __IN uint8_t group_id);

	/**
	* @brief	HPS3D_GetROIGroup
	*			获取当前的ROI组ID
	* @param	device_id
	* @param	group_id    返回的ROI组ID
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetROIGroup(__IN uint8_t device_id, __OUT uint8_t *group_id);
	
	/**
	* @brief	HPS3D_SetROIEnable
	*			设置ROI使能
	* @param	device_id
	* @param	roi_id		ROI的ID
	* @param	enable		ROI使能		
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetROIEnable(__IN uint8_t device_id, __IN uint8_t roi_id, __IN bool enable);
	
	/**
	* @brief	HPS3D_GetROIEnable
	*			获取ROI使能
	* @param	device_id
	* @param	roi_id		ROI的ID
	* @param	enable		返回ROI使能状态
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetROIEnable(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT bool *enable);

	/**
	* @brief	HPS3D_GetNumberOfROI
	*			获取当前设备支持的ROI数量和阈值数量
	* @param	device_id
	* @param	roi_number			支持的ROI数量
	* @param	threshold_number	支持的阈值数量
	* @param	roi_number_group	支持的ROI组数量
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetNumberOfROI(__IN uint8_t device_id, __OUT uint8_t *roi_number, __OUT uint8_t *threshold_number, __OUT uint8_t *roi_number_group);

	/**
	* @brief	HPS3D_SetSmoothFilter
	*			设置平滑滤波器
	* @param	device_id
	* @param	filter_type			平滑滤波器类型，SMOOTH_FILTER_DISABLE
	* @param	filter_times		平滑滤波器滤波次数，范围0~10
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetSmoothFilter(__IN uint8_t device_id, __IN uint8_t filter_type, __IN uint32_t filter_times);

	/**
	* @brief	HPS3D_GetSmoothFilter
	*			获取平滑滤波器设置
	* @param	device_id
	* @param	filter_type			返回平滑滤波器类型，SMOOTH_FILTER_DISABLE
	* @param	filter_times		返回平滑滤波器滤波次数，范围0~10
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetSmoothFilter(__IN uint8_t device_id, __OUT uint8_t *filter_type, __OUT uint32_t *filter_times);

	/**
	* @brief	HPS3D_SoftwareReset
	*			软件复位
	* @param	device_id
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SoftwareReset(__IN uint8_t device_id);

	/**
	* @brief	HPS3D_SetOffset
	*			设置距离偏移
	* @param	device_id
	* @param	offset_mm			偏移距离，单位MM
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetOffset(__IN uint8_t device_id, __IN int16_t offset_mm);

	/**
	* @brief	HPS3D_GetOffset
	*			获取距离偏移
	* @param	device_id
	* @param	offset_mm			返回偏移距离，单位MM
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOffset(__IN uint8_t device_id, __OUT int16_t *offset_mm);

	
	
	/**
	* @brief	HPS3D_SetSimpleKalmanFilter
	*			设置卡尔曼滤波器
	* @param	device_id
	* @param	kalman_enable			卡尔曼滤波器使能
	* @param	kalman_k				卡尔曼滤波器比例系数
	* @param	kalman_number			卡尔曼滤波器阈值检查帧数
	* @param	kalman_threshold		卡尔曼滤波器噪声阈值
	* @note     device_id必须与连接时返回的ID对应
	* @note     enable使能设置为false后其他值将不会被写入，可设置为NULL
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetSimpleKalmanFilter(__IN uint8_t device_id, __IN bool kalman_enable, __IN float64_t kalman_k, __IN uint32_t kalman_number, __IN uint32_t kalman_threshold);

	/**
	* @brief	HPS3D_GetSimpleKalmanFilter
	*			获取卡尔曼滤波器配置
	* @param	device_id
	* @param	kalman_enable			返回卡尔曼滤波器使能
	* @param	kalman_k				返回卡尔曼滤波器比例系数
	* @param	kalman_number			返回卡尔曼滤波器过滤个数
	* @param	kalman_threshold		返回卡尔曼滤波器过滤阈值
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetSimpleKalmanFilter(__IN uint8_t device_id, __OUT bool *kalman_enable, __OUT float64_t *kalman_k, __OUT uint32_t *kalman_number, __OUT uint32_t *kalman_threshold);

	/**
	* @brief	HPS3D_SetWatchDogEnable
	*			设置看门狗使能
	* @param	device_id
	* @param	enable			看门狗使能
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @note		单步调试程序时需要将看门狗使能关闭，否则可能会导致设备断连
	* @note		正式运行程序时需要将看门狗使能打开
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetWatchDogEnable(__IN uint8_t device_id, __IN bool enable);

	/**
	* @brief	HPS3D_GetWatchDogEnable
	*			获取看门狗使能
	* @param	device_id
	* @param	enable			返回看门狗使能
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetWatchDogEnable(__IN uint8_t device_id, __OUT bool *enable);

	/**
	* @brief	HPS3D_GetEdgeFilter
	*			获取边缘滤波器设置
	* @param	device_id
	* @param	enable				返回边缘滤波器使能状态
	* @param	args				返回边缘滤波器过滤参数，单位MM
	* @note     device_id必须与连接时返回的ID对应
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetEdgeFilter(__IN uint8_t device_id, __OUT bool *enable, __OUT uint32_t *args);

	/**
	* @brief	HPS3D_SetEdgeFilter
	*			设置边缘滤波器
	* @param	device_id
	* @param	enable				边缘滤波器使能状态
	* @param	args				边缘滤波器过滤参数，单位MM
	* @note     device_id必须与连接时返回的ID对应
	* @note     当enable设置为false时，args将不会被写入，可设置为NULL
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetEdgeFilter(__IN uint8_t device_id, __IN bool enable, __IN uint32_t args);


	/**
	* @brief	HPS3D_SetHDREnable
	*			设置HDR模式使能
	* @param	device_id
	* @param	hdr_enable			HDR模式使能
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetHDREnable(__IN uint8_t device_id, __IN bool hdr_enable);

	/**
	* @brief	HPS3D_GetHDREnable
	*			获取HDR模式使能
	* @param	device_id
	* @param	hdr_enable			返回HDR模式使能
	* @note     device_id必须与连接时返回的ID对应
	* @note		执行该命令前，需要将运行模式设置为 RUN_IDLE
	* @retval	成功返回RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetHDREnable(__IN uint8_t device_id, __OUT bool *hdr_enable);
#ifdef __cplusplus
}
#endif

#endif /* HPS3D_IF_H_*/
