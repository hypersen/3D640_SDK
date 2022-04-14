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
* @date 2020��8��24�� ����10:48:20
* @license public & classified
*---------------------------------------------------------------------
* Remark: This project is still under construction.
*======================================================================
* Change History:
*---------------------------------------------------------------------
* <Date>      | <Version>  | <Author>      | <Description>
*---------------------------------------------------------------------
* 2020��8��24��       | V1.0.0  | Lance        | Create file
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

#ifdef _WIN32 /*windowsƽ̨*/
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

#define     DEV_NUM		(0x04)							/*��������豸����*/
#define		X_PIX_NUM	640
#define		Y_PIX_NUM	480
#define		PIXEL_NUM	307200
 
/**
* @brief	����¼��ص�
* @param    out_id		    ����豸��ID
* @param    event			������¼���OUTPUT_EVENT_SIMPLEDATARECVD
* @param    contex			�û��Զ���������ص�������
*/
typedef void(__cdecl *HPS3D_CALLBACK_OUTPUT)(uint8_t out_id, uint8_t event, void *contex);


/**
* @brief	DEBUG��Ϣ�ص�
* @param    str			�����DEBUG��Ϣ
* @param    contex		�û��Զ���������ص�������
*/
typedef void(__cdecl *HPS3D_CALLBACK_DEBUG)(char *str, void *contex);

	/**
	* @brief	HPS3D_SetDebugCallBack
	*			����Debug�ص�����
	* @param	call_back	HPS3D_CALLBACK_DEBUG
	call_back����ΪNULLʱ��ֹͣ�ù���
	* @param    contex      �û��Զ���������ص������ģ�����Ҫʱ����ΪNULL
	* @retval	�ɹ����� RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetDebugCallBack(__IN HPS3D_CALLBACK_DEBUG call_back, __IN void *contex);

	/**
	* @brief	HPS3D_ConnectByEthernet
	*			������̫�����ӷ�ʽ
	* @param	server_ip		�豸IP�� ASCII���룬"192.168.0.1"
	* @param	server_port		�豸�˿ں�
	* @param	device_id		�豸ID�ţ�����ʧ��ʱ��ID����ֵΪ99
	* @note     ������̼������õ����ӷ�ʽ��Ӧ
	* @retval	�ɹ����� RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_ConnectByEthernet(__IN char *server_ip, __IN uint16_t server_port, __OUT uint8_t *device_id);
	
	/**
	* @brief	HPS3D_ScanDeviceList
	*			ɨ���豸��ID�б�
	* @param	device_list[0]      �豸ID��
	* @param	device_list[1]      �豸ID��
	* @param	device_list[2]      �豸ID��
	* @param	device_list[3]      �豸ID��
	* @param	device_count		�Ѿ������豸������
	* @note     device_list�������ٿ���4���ռ䣬device_list[DEV_NUM]
	* @note		���磺��ֻ��һ̨�豸����ʱ
				device_count ����ֵΪ1ʱ��device_list[0] = ��ǰ�����ӵ��豸ID
				device_list[1] = device_list[2] = device_list[3] = 99
	* @retval	�ɹ����� RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_ScanDeviceList(__OUT uint8_t* device_list, __OUT uint8_t* device_count);

	/**
	* @brief	HPS3D_DisConnect
	*			�Ͽ��豸
	* @param	device_id	�豸ID
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		����������ɺ���Ҫ���ô˽ӿڶϿ����ӣ��ͷ���Դ
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_DisConnect(__IN uint8_t device_id);
	
	/**
	* @brief	HPS3D_SetOutputCallBack
	*			��������¼��ص�����
	* @param	call_back	HPS3D_CALLBACK_OUTPUT��
							call_back����ΪNULLʱ��ֹͣ�ù���
	* @param	device_id	�豸ID
	* @param    contex		�û��Զ���������ص������ģ�����Ҫʱ����ΪNULL
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetOutputCallBack(__IN HPS3D_CALLBACK_OUTPUT call_back, __IN uint8_t device_id, __IN void *contex);
	
	/**
	* @brief	HPS3D_GetAverageDistance_CB
	*			��ȡƽ�����루�ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    aver_distance		����ƽ�����룬��λ����
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_SIMPLEDISTANCERECVD
				���� EVENT_FULLDISTANCERECVD ���� EVENT_FULLPOINTCLOUDRECVD ֪ͨʱ����
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetAverageDistance_CB(__IN uint8_t device_id, __OUT uint16_t *aver_distance);

	/**
	* @brief	HPS3D_GetMaxDistance_CB
	*			��ȡ�����루�ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    max_distance		���������룬��λ����
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_SIMPLEDISTANCERECVD
				���� EVENT_FULLDISTANCERECVD ���� EVENT_FULLPOINTCLOUDRECVD ֪ͨʱ����
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetMaxDistance_CB(__IN uint8_t device_id, __OUT uint16_t *max_distance);

	/**
	* @brief	HPS3D_GetMinDistance_CB
	*			��ȡ��С���루�ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    min_distance		������С���룬��λ����
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_SIMPLEDISTANCERECVD
				���� EVENT_FULLDISTANCERECVD ���� EVENT_FULLPOINTCLOUDRECVD ֪ͨʱ����
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetMinDistance_CB(__IN uint8_t device_id, __OUT uint16_t *min_distance);

	/**
	* @brief	HPS3D_GetAllAverAmplitude_CB
	*			��ȡ����ƽ����ֵ���ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    all_aver_amp		����ƽ����ֵ������0��ֵ��
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_SIMPLEDISTANCERECVD
				���� EVENT_FULLDISTANCERECVD ���� EVENT_FULLPOINTCLOUDRECVD ֪ͨʱ����
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetAllAverAmplitude_CB(__IN uint8_t device_id, __OUT uint16_t *all_aver_amp);

	/**
	* @brief	HPS3D_GetValidAverAmplitude_CB
	*			��ȡ��Ч��ƽ����ֵ���ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    valid_aver_amp		������Ч��ƽ����ֵ
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_SIMPLEDISTANCERECVD
				���� EVENT_FULLDISTANCERECVD ���� EVENT_AMPLITUDE ���� EVENT_FULLPOINTCLOUDRECVD ֪ͨʱ����
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetValidAverAmplitude_CB(__IN uint8_t device_id, __OUT uint16_t *valid_aver_amp);

	/**
	* @brief	HPS3D_GetDistanceData_CB
	*			��ȡ�������ݣ��ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    distance_data		��������,��λ���ף���Ҫ����307200���ռ�)
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_FULLDISTANCERECVD ֪ͨʱ����
	* @note     device_id������ص����������ID��Ӧ
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetDistanceData_CB(__IN uint8_t device_id, __OUT uint16_t *distance_data);

	/**
	* @brief	HPS3D_GetGrayscaleData_CB
	*			��ȡ�Ҷ����ݣ��ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    grayscale_data		�Ҷ�����,��λ�Ҷ�ֵ����Χ0~255������Ҫ����307200���ռ�)
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_AMPLITUDE ֪ͨʱ����
	* @note     device_id������ص����������ID��Ӧ
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetGrayscaleData_CB(__IN uint8_t device_id, __OUT uint8_t *grayscale_data);


	/**
	* @brief	HPS3D_GetAmplitudeData_CB
	*			��ȡ��ֵ���ݣ��ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    amplitude_data		��ֵ����,����Ҫ����307200���ռ�)
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_AMPLITUDE ֪ͨʱ����
	* @note     device_id������ص����������ID��Ӧ
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetAmplitudeData_CB(__IN uint8_t device_id, __OUT uint16_t *amplitude_data);

	/**
	* @brief	HPS3D_GetMaxAmplitudeData_CB
	*			��ȡ����ֵ���ݣ��ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    max_amplitude		����ֵ����
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_AMPLITUDE ֪ͨʱ����
	* @note     device_id������ص����������ID��Ӧ
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetMaxAmplitudeData_CB(__IN uint8_t device_id, __OUT uint16_t *max_amplitude);

	/**
	* @brief	HPS3D_GetMinAmplitudeData_CB
	*			��ȡ��С��ֵ���ݣ��ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    min_amplitude		��С��ֵ����
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_AMPLITUDE ֪ͨʱ����
	* @note     device_id������ص����������ID��Ӧ
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetMinAmplitudeData_CB(__IN uint8_t device_id, __OUT uint16_t *min_amplitude);


	/**
	* @brief	HPS3D_GetPointCloudData_CB
	*			��ȡ�������ݣ��ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    point_data		    ��������,���巽ʽ,point_data[307200][3]
	* @param    point_count		    ��Ч�������
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_FULLPOINTCLOUDRECVD
				���� EVENT_ROIPOINTCLOUDRECVD ֪ͨʱ����
	* @note     device_id������ص����������ID��Ӧ
	* @note     point_data�У�[3]��ֵ��0��ʾX��ֵ��1��ʾY��ֵ��2��ʾZ��ֵ
	* @note		���У���Ч���Ѿ����Զ�����
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetPointCloudData_CB(__IN uint8_t device_id, __OUT double(*point_data)[3], __OUT uint32_t *point_count);

	/**
	* @brief	HPS3D_GetOutRoiParam_CB
	*			��ȡ�����ROI������Ϣ���ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    group_id			����ROI��ID
	* @param    roi_number			����ROI����
	* @param    roi_id				����ROI��ID����Ҫ����8���ռ䣬roi_id[8]
	* @note		roi_number��ֵ����roi_id����Ч���ݸ�����
				���磺roi_number = 1ʱ
				roi_id[0] = ROI��ID��roi_id[1~7] ��Ч
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_ROIPOINTCLOUDRECVD
				���� EVENT_ROIFULLDISTANCERECVD ���� EVENT_ROISIMPLEDISTANCERECVD ֪ͨʱ����
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiParam_CB(__IN uint8_t device_id, __OUT uint8_t *group_id, __OUT uint8_t *roi_number, __OUT uint8_t *roi_id);

	/**
	* @brief	HPS3D_GetOutRoiPointCloudData_CB
	*			��ȡ���ROI�ĵ������ݣ��ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param	roi_id				Roi��ID
	* @param    roi_point_data		    ��������,���巽ʽ,point_data[307200][3]
	* @param    roi_point_count		    ������Ч�������
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_ROIPOINTCLOUDRECVD ֪ͨʱ����
	* @note     device_id������ص����������ID��Ӧ
	* @note     roi_point_data�У�[3]��ֵ��0��ʾX��ֵ��1��ʾY��ֵ��2��ʾZ��ֵ
	* @note		���У���Ч���Ѿ����Զ�����
	* @note     ����ǰ�ȵ��� HPS3D_GetOutRoiParam_CB �ӿڻ�ȡ��Ӧ���������
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiPointCloudData_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT double (*roi_point_data)[3], __OUT uint32_t *roi_point_count);

	/**
	* @brief	HPS3D_GetOutRoiDistanceData_CB
	*			��ȡ�����ROI������ݣ��ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param    roi_id			    ROI��ID
	* @param    roi_distance_data	ROI��������ݣ���λ���ף���Ҫ����307200���ռ䣬roi_distance_data[307200]
	* @param    roi_area	        ROI�ķ�Χ����Ҫ����4���ռ䣬roi_area[4]
	* @note     device_id������ص����������ID��Ӧ
	* @note     roi_area[0]����ʾ���Ͻǵ��X����  roi_area[1]����ʾ���Ͻǵ��Y����
				roi_area[2]����ʾ���½ǵ��X����  roi_area[3]����־���½ǵ��Y����
				����������ظ������㹫ʽΪ�� (right_bottom_x - left_top_x + 1) * (right_bottom_y - left_top_y + 1));
				pixel_number = (roi_area[2] - roi_area[0] + 1) * (roi_area[3] - roi_area[1] + 1)
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_ROIFULLDISTANCERECVD ֪ͨʱ����
	* @note     ����ǰ�ȵ��� HPS3D_GetOutRoiParam_CB �ӿڻ�ȡ��Ӧ���������
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiDistanceData_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *roi_distance_data, __OUT uint16_t *roi_area);

	/**
	* @brief	HPS3D_GetOutRoiAverageDistance_CB
	*			��ȡ�����ROIƽ�����루�ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param	roi_id				ROI��ID
	* @param    aver_distance		����ƽ�����룬��λ����
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_ROIFULLDISTANCERECVD ����
	EVENT_ROISIMPLEDISTANCERECVD ���� EVENT_ROIPOINTCLOUDRECVD ֪ͨʱ����
	* @note     ����ǰ�ȵ��� HPS3D_GetOutRoiParam_CB �ӿڻ�ȡ��Ӧ���������
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiAverageDistance_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *aver_distance);

	/**
	* @brief	HPS3D_GetOutRoiMaxDistance_CB
	*			��ȡ�����ROI�����루�ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param	roi_id				ROI��ID
	* @param    max_distance		���������룬��λ����
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_ROIFULLDISTANCERECVD ����
				EVENT_ROISIMPLEDISTANCERECVD ���� EVENT_ROIPOINTCLOUDRECVD ֪ͨʱ����
	* @note     ����ǰ�ȵ��� HPS3D_GetOutRoiParam_CB �ӿڻ�ȡ��Ӧ���������
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiMaxDistance_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *max_distance);

	/**
	* @brief	HPS3D_GetOutRoiMinDistance_CB
	*			��ȡ�����ROI��С���루�ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param	roi_id				ROI��ID
	* @param    min_distance		������С���룬��λ����
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_ROIFULLDISTANCERECVD ����
				EVENT_ROISIMPLEDISTANCERECVD ���� EVENT_ROIPOINTCLOUDRECVD ֪ͨʱ����
	* @note     ����ǰ�ȵ��� HPS3D_GetOutRoiParam_CB �ӿڻ�ȡ��Ӧ���������
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiMinDistance_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *min_distance);

	/**
	* @brief	HPS3D_GetOutRoiAllAverAmplitude_CB
	*			��ȡ�����ROI����ƽ����ֵ���ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param	roi_id				ROI��ID
	* @param    all_aver_amp		����ƽ����ֵ������0��ֵ��
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_ROIFULLDISTANCERECVD ����
				EVENT_ROISIMPLEDISTANCERECVD ���� EVENT_ROIPOINTCLOUDRECVD ֪ͨʱ����
	* @note     ����ǰ�ȵ��� HPS3D_GetOutRoiParam_CB �ӿڻ�ȡ��Ӧ���������
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiAllAverAmplitude_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *all_aver_amp);

	/**
	* @brief	HPS3D_GetOutRoiValidAverAmplitude_CB
	*			��ȡ�����ROI��Чƽ����ֵ���ص�������ʹ�ã�
	* @param	device_id			�豸ID
	* @param	roi_id				ROI��ID
	* @param    valid_aver_amp		������Ч��ƽ����ֵ��������0��ֵ��
	* @note     device_id������ص����������ID��Ӧ
	* @note     �ýӿ�ֻ���ڻص��������յ� EVENT_ROIFULLDISTANCERECVD ����
				EVENT_ROISIMPLEDISTANCERECVD ���� EVENT_ROIPOINTCLOUDRECVD ֪ͨʱ����
	* @note     ����ǰ�ȵ��� HPS3D_GetOutRoiParam_CB �ӿڻ�ȡ��Ӧ���������
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutRoiValidAverAmplitude_CB(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT uint16_t *valid_aver_amp);

	/**
	* @brief	HPS3D_GetCameraParam
	*			��ȡ����ڲξ���
	* @param	device_id
	* @param	cameraParam    ����ڲ�
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note     CameraParam[0]   �������꣬CX
	* @note     CameraParam[1]   �������꣬CY
	* @note     CameraParam[2]   ������࣬FX
	* @note     CameraParam[3]   ������࣬FY
	* @note     CameraParam[4]   �������ϵ����K1
	* @note     CameraParam[5]   �������ϵ����K2
	* @note     CameraParam[6]   б�����ϵ����P1
	* @note     CameraParam[7]   б�����ϵ����P2
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetCameraParam(__IN uint8_t device_id, __OUT float64_t *cameraParam);

	/**
	* @brief	HPS3D_SetRunMode
	*			��������ģʽ
	* @param	device_id
	* @param	run_mode	����ģʽ��RUN_IDLE
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ÿ������Ϊ RUN_SINGLE_SHOT ��ͨ���ص�������һ֡����
	* @retval	�ɹ����� RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetRunMode(__IN uint8_t device_id, __IN uint8_t run_mode);

	/**
	* @brief	HPS3D_GetRunMode
	*			��ȡ����ģʽ
	* @param	device_id
	* @param	run_mode	���ص�ǰ����ģʽ��RUN_IDLE
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @retval	�ɹ����� RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetRunMode(__IN uint8_t device_id, __OUT uint8_t *run_mode);

	/**
	* @brief	HPS3D_SetPointCloudMode
	*			���õ���ģʽ����
	* @param	device_id					�豸ID
	* @param	point_cloud_enable			����ͼʹ��
	* @param    mirror_mode					����ͼ����ģʽ,MIRROR_DISABLE
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetPointCloudMode(__IN uint8_t device_id, __IN bool point_cloud_enable, __IN uint8_t mirror_mode);
	
	/**
	* @brief	HPS3D_GetPointCloudMode
	*			��ȡ����ģʽ����
	* @param	device_id			�豸ID
	* @param	point_cloud_enable	���ص���ͼʹ��
	* @param    mirror_mode			���ص���ͼ����ģʽ,MIRROR_DISABLE
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetPointCloudMode(__IN uint8_t device_id, __OUT bool *point_cloud_enable, __OUT uint8_t *mirror_mode);

	/*
	* @brief	HPS3D_SetMeasureMode
	*			���ò���ģʽ
	* @param	device_id
	* @param	measure_mode	  ����ģʽ��DSITMODE_GENERAL
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetMeasureMode(__IN uint8_t device_id, __IN uint8_t measure_mode);

	/*
	* @brief	HPS3D_GetMeasureMode
	*			��ȡ����ģʽ
	* @param	device_id
	* @param	measure_mode		���ز���ģʽ��DSITMODE_GENERAL
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetMeasureMode(__IN uint8_t device_id, __OUT uint8_t *measure_mode);
	
	/*
	* @brief	HPS3D_GetSDKVersion
	*			��ȡSDK�汾��Ϣ
	* @param	device_id
	* @param	version			SDK�汾��Ϣ
	* @param	version[0] 		year
	* @param	version[1]		month;
	* @param	version[2]		day;
	* @param	version[3]		major;
	* @param	version[4]		minor;
	* @param	version[5]		rev;
	* @note     version�������ٿ���6���ռ䣬version[6]
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetSDKVersion(__OUT uint8_t *version);

	/*
	* @brief	HPS3D_GetDeviceVersion
	*			��ȡ�豸�汾��Ϣ
	* @param	device_id
	* @param	version			�豸�汾��Ϣ
	* @param	version[0] 		year
	* @param	version[1]		month;
	* @param	version[2]		day;
	* @param	version[3]		major;
	* @param	version[4]		minor;
	* @param	version[5]		rev;
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note     version�������ٿ���6���ռ䣬version[6]
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @see      HPS3D_SetRunMode
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetDeviceVersion(__IN uint8_t device_id, __OUT uint8_t *version);

	/*
	* @brief	HPS3D_GetDeviceSN
	*			��ȡ�豸���к�
	* @param	device_id
	* @param	SN		�����豸���к�
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		SN��С����64���ռ䣬SN[64]
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetDeviceSN(__IN uint8_t device_id, __OUT char * SN);

	/*
	* @brief	HPS3D_GetOutputDataType
	*			��ȡ�����������
	* @param	device_id
	* @param	data_type		���������������,OUTPUT_AMPLITUDE
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note     OUTPUT_AMPLITUDE����ͨ���ص���������������
				OUTPUT_DISTANCE_FULL����ͨ���ص������������������ݣ����������ص�����
				OUTPUT_DISTANCE_SIMPLE����ͨ���ص����������������ݣ������������ص����ݣ�ֻ������ѧͳ������
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOutputDataType(__IN uint8_t device_id, __OUT uint8_t *data_type);

	/*
	* @brief	HPS3D_SetOutputDataType
	*			���������������
	* @param	device_id
	* @param	data_type		�����������,OUTPUT_AMPLITUDE
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note     OUTPUT_AMPLITUDE����ͨ���ص���������������
				OUTPUT_DISTANCE_FULL����ͨ���ص������������������ݣ����������ص�����
				OUTPUT_DISTANCE_SIMPLE����ͨ���ص����������������ݣ������������ص����ݣ�ֻ������ѧͳ������
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetOutputDataType(__IN uint8_t device_id, __IN uint8_t data_type);

	/*
	* @brief	HPS3D_SetComInConf
	*			��������˿ڵ�����
	* @param	device_id
	* @param	in_port			�˿ںţ�����˿ڣ���GPIN_1
	* @param	in_func			�˿ڹ��ܣ�GPIN_FUNC_DISABLE
	* @param	in_polarity		�˿ڼ��ԣ�GPIO_POLARITY_LOW
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetComInConf(__IN uint8_t device_id, __IN uint8_t in_port, __IN uint8_t in_func, __IN uint8_t in_polarity);

	/*
	* @brief	HPS3D_GetComInConf
	*			��ȡ����˿ڵ�����
	* @param	device_id
	* @param	in_port   		��Ҫ��ȡ������˿ںţ�GPIN_1
	* @param	in_func   		�˿ڹ��ܣ�GPIN_FUNC_DISABLE
	* @param	in_polarity   	�˿ڼ��ԣ�GPIO_POLARITY_LOW
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetComInConf(__IN uint8_t device_id, __IN uint8_t in_port, __OUT uint8_t *in_func, __OUT uint8_t *in_polarity);

	/*
	* @brief	HPS3D_SetComOutConf
	*			��������˿ڵ�����
	* @param	device_id
	* @param	out_port		�˿ںţ�����˿ڣ���GPOUT_1
	* @param	out_func		�˿ڹ��ܣ�GPOUT_FUNC_DISABLE
	* @param	out_polarity	�˿ڼ��ԣ�GPIO_POLARITY_LOW
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetComOutConf(__IN uint8_t device_id, __IN uint8_t out_port, __IN uint8_t out_func, __IN uint8_t out_polarity);

	/*
	* @brief	HPS3D_GetComOutConf
	*			��ȡ����˿ڵ�����
	* @param	device_id
	* @param	out_port		��Ҫ��ȡ������˿ںţ�GPOUT_1
	* @param	out_func   		�˿ڹ��ܣ�GPOUT_FUNC_DISABLE
	* @param	out_polarity  	�˿ڼ��ԣ�GPIO_POLARITY_LOW
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetComOutConf(__IN uint8_t device_id, __IN uint8_t out_port, __OUT uint8_t *out_func, __OUT uint8_t *out_polarity);

	/**
	* @brief	HPS3D_SetIntegTime
	*			���û���ʱ��
	* @param	device_id
	* @param	time_us		����ʱ��(��λus����Χ50~1000)
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetIntegTime(__IN uint8_t device_id, __IN uint32_t time_us);

	/**
	* @brief	HPS3D_GetIntegTime
	*			��ȡ����ʱ��
	* @param	device_id
	* @param	time_us		���ػ���ʱ��(��λus���������Ϊ1000)
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetIntegTime(__IN uint8_t device_id, __OUT uint32_t *time_us);

	/**
	* @brief	HPS3D_ProfileSaveToUser
	*			���浽�û����ñ�
	* @param	device_id
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_ProfileSaveToUser(__IN uint8_t device_id);


	/**
	* @brief	HPS3D_ProfileClearUser
	*			����û����ñ�
	* @param	device_id
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_ProfileClearUser(__IN uint8_t device_id);

	/**
	* @brief	HPS3D_SetROIGroup
	*			ѡ��ROI��
	* @param	device_id
	* @param	group_id    ROI���ID,0~1
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetROIGroup(__IN uint8_t device_id, __IN uint8_t group_id);

	/**
	* @brief	HPS3D_GetROIGroup
	*			��ȡ��ǰ��ROI��ID
	* @param	device_id
	* @param	group_id    ���ص�ROI��ID
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetROIGroup(__IN uint8_t device_id, __OUT uint8_t *group_id);
	
	/**
	* @brief	HPS3D_SetROIEnable
	*			����ROIʹ��
	* @param	device_id
	* @param	roi_id		ROI��ID
	* @param	enable		ROIʹ��		
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetROIEnable(__IN uint8_t device_id, __IN uint8_t roi_id, __IN bool enable);
	
	/**
	* @brief	HPS3D_GetROIEnable
	*			��ȡROIʹ��
	* @param	device_id
	* @param	roi_id		ROI��ID
	* @param	enable		����ROIʹ��״̬
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetROIEnable(__IN uint8_t device_id, __IN uint8_t roi_id, __OUT bool *enable);

	/**
	* @brief	HPS3D_GetNumberOfROI
	*			��ȡ��ǰ�豸֧�ֵ�ROI��������ֵ����
	* @param	device_id
	* @param	roi_number			֧�ֵ�ROI����
	* @param	threshold_number	֧�ֵ���ֵ����
	* @param	roi_number_group	֧�ֵ�ROI������
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetNumberOfROI(__IN uint8_t device_id, __OUT uint8_t *roi_number, __OUT uint8_t *threshold_number, __OUT uint8_t *roi_number_group);

	/**
	* @brief	HPS3D_SetSmoothFilter
	*			����ƽ���˲���
	* @param	device_id
	* @param	filter_type			ƽ���˲������ͣ�SMOOTH_FILTER_DISABLE
	* @param	filter_times		ƽ���˲����˲���������Χ0~10
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetSmoothFilter(__IN uint8_t device_id, __IN uint8_t filter_type, __IN uint32_t filter_times);

	/**
	* @brief	HPS3D_GetSmoothFilter
	*			��ȡƽ���˲�������
	* @param	device_id
	* @param	filter_type			����ƽ���˲������ͣ�SMOOTH_FILTER_DISABLE
	* @param	filter_times		����ƽ���˲����˲���������Χ0~10
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetSmoothFilter(__IN uint8_t device_id, __OUT uint8_t *filter_type, __OUT uint32_t *filter_times);

	/**
	* @brief	HPS3D_SoftwareReset
	*			�����λ
	* @param	device_id
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SoftwareReset(__IN uint8_t device_id);

	/**
	* @brief	HPS3D_SetOffset
	*			���þ���ƫ��
	* @param	device_id
	* @param	offset_mm			ƫ�ƾ��룬��λMM
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetOffset(__IN uint8_t device_id, __IN int16_t offset_mm);

	/**
	* @brief	HPS3D_GetOffset
	*			��ȡ����ƫ��
	* @param	device_id
	* @param	offset_mm			����ƫ�ƾ��룬��λMM
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetOffset(__IN uint8_t device_id, __OUT int16_t *offset_mm);

	
	
	/**
	* @brief	HPS3D_SetSimpleKalmanFilter
	*			���ÿ������˲���
	* @param	device_id
	* @param	kalman_enable			�������˲���ʹ��
	* @param	kalman_k				�������˲�������ϵ��
	* @param	kalman_number			�������˲�����ֵ���֡��
	* @param	kalman_threshold		�������˲���������ֵ
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note     enableʹ������Ϊfalse������ֵ�����ᱻд�룬������ΪNULL
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetSimpleKalmanFilter(__IN uint8_t device_id, __IN bool kalman_enable, __IN float64_t kalman_k, __IN uint32_t kalman_number, __IN uint32_t kalman_threshold);

	/**
	* @brief	HPS3D_GetSimpleKalmanFilter
	*			��ȡ�������˲�������
	* @param	device_id
	* @param	kalman_enable			���ؿ������˲���ʹ��
	* @param	kalman_k				���ؿ������˲�������ϵ��
	* @param	kalman_number			���ؿ������˲������˸���
	* @param	kalman_threshold		���ؿ������˲���������ֵ
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetSimpleKalmanFilter(__IN uint8_t device_id, __OUT bool *kalman_enable, __OUT float64_t *kalman_k, __OUT uint32_t *kalman_number, __OUT uint32_t *kalman_threshold);

	/**
	* @brief	HPS3D_SetWatchDogEnable
	*			���ÿ��Ź�ʹ��
	* @param	device_id
	* @param	enable			���Ź�ʹ��
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @note		�������Գ���ʱ��Ҫ�����Ź�ʹ�ܹرգ�������ܻᵼ���豸����
	* @note		��ʽ���г���ʱ��Ҫ�����Ź�ʹ�ܴ�
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetWatchDogEnable(__IN uint8_t device_id, __IN bool enable);

	/**
	* @brief	HPS3D_GetWatchDogEnable
	*			��ȡ���Ź�ʹ��
	* @param	device_id
	* @param	enable			���ؿ��Ź�ʹ��
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetWatchDogEnable(__IN uint8_t device_id, __OUT bool *enable);

	/**
	* @brief	HPS3D_GetEdgeFilter
	*			��ȡ��Ե�˲�������
	* @param	device_id
	* @param	enable				���ر�Ե�˲���ʹ��״̬
	* @param	args				���ر�Ե�˲������˲�������λMM
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetEdgeFilter(__IN uint8_t device_id, __OUT bool *enable, __OUT uint32_t *args);

	/**
	* @brief	HPS3D_SetEdgeFilter
	*			���ñ�Ե�˲���
	* @param	device_id
	* @param	enable				��Ե�˲���ʹ��״̬
	* @param	args				��Ե�˲������˲�������λMM
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note     ��enable����Ϊfalseʱ��args�����ᱻд�룬������ΪNULL
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetEdgeFilter(__IN uint8_t device_id, __IN bool enable, __IN uint32_t args);


	/**
	* @brief	HPS3D_SetHDREnable
	*			����HDRģʽʹ��
	* @param	device_id
	* @param	hdr_enable			HDRģʽʹ��
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_SetHDREnable(__IN uint8_t device_id, __IN bool hdr_enable);

	/**
	* @brief	HPS3D_GetHDREnable
	*			��ȡHDRģʽʹ��
	* @param	device_id
	* @param	hdr_enable			����HDRģʽʹ��
	* @note     device_id����������ʱ���ص�ID��Ӧ
	* @note		ִ�и�����ǰ����Ҫ������ģʽ����Ϊ RUN_IDLE
	* @retval	�ɹ�����RET_OK
	*/
	HPS3D640_API uint8_t __stdcall HPS3D_GetHDREnable(__IN uint8_t device_id, __OUT bool *hdr_enable);
#ifdef __cplusplus
}
#endif

#endif /* HPS3D_IF_H_*/
