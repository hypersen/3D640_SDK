using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace HPS3D_DeviceLib
{
    //返回码定义
    public enum RET_STATUS_ENUM
    {
        RET_OK = 0x01,
        RET_ERROR = 0x02,
        RET_BUSY = 0x03,
        RET_CONNECT_FAILED = 0x04,			 		/*连接失败*/
        RET_CREAT_PTHREAD_ERR = 0x05,		 		/*线程创建失败*/
        RET_WRITE_ERR = 0x06,				 		/*数据发送失败*/
        RET_READ_ERR = 0x07,				 		/*读数据失败*/
        RET_PACKET_HEAD_ERR = 0x08,			 	/*数据包格式报头或报尾错误*/
        RET_PACKET_ERR = 0x09,				  	    /*数据包解析错误*/
        RET_BUFF_EMPTY,				 		/*缓冲区为空或不可用*/
        RET_VER_MISMATCH,			    	/*固件版本与SDK版本不匹配*/
        RET_INVALID_LICENSE,			 	/*许可无效，需更新许可*/
    };

    //运行模式定义
    public enum RUN_MODE_ENUM
    {
        RUN_IDLE = 0,           /*待机或停止测量*/
        RUN_SINGLE_SHOT,        /*单次测量*/
        RUN_CONTINUOUS,         /*连续测量*/
    };

    //输出数据类型
    public enum OUTPUT_TYPE_ENUM
    {
        OUTPUT_AMPLITUDE = 0x00,      //输出幅值数据
        OUTPUT_DISTANCE_FULL = 0x01,      //输出完整深度数据
        OUTPUT_DISTANCE_SIMPLE = 0x02,		//输出简单深度数据
    };

    //平滑滤波器类型
    public enum SMOOTH_FILTER_TYPE_ENUM
    {
        SMOOTH_FILTER_DISABLE = 0x00,	//不使用平滑滤波器
        SMOOTH_FILTER_AVERAGE = 0x01,	//滑动平均滤波器
        SMOOTH_FILTER_GAUSS = 0x02,	//高斯平滑滤波器
    };

    //点云镜像模式
    public enum POINTCLOUD_MIRROR_MODE_ENUM
    {
        MIRROR_DISABLE = 0x00,	//不使用镜像
        MIRROR_HORIZONTAL = 0x01,	//水平镜像
        MIRROR_VERTICLA = 0x02,	//垂直镜像
        MIRROR_ALL = 0x03,	//垂直和水平镜像
    };

    //设备测量模式
    public enum MEASURE_MODE_ENUM
    {
        DSITMODE_GENERAL = 0x01,                    //普通模式
        DSITMODE_SHORTDIST_HIGH_ACCURACY = 0x02,    //近距离高精度
        DSITMODE_LONGDIST_HIGH_ACCURACY = 0x03,     //远距离高精度
        DSITMODE_LONGDIST_LOW_ACCURACY = 0x04,      //远距离低精度
    };

    //输出返回事件定义
    public enum OUTPUT_EVENT_ENUM
    {
        EVENT_DEVDISCONNECT = 0x01, 		/*断开连接事件*/
        EVENT_SIMPLEDISTANCERECVD = 0x02,			/*简单深度数据接收事件*/
        EVENT_FULLDISTANCERECVD = 0x03,			/*完整深度数据接收事件*/
        EVENT_AMPLITUDE = 0x04,			/*振幅数据接收事件*/
        EVENT_FULLPOINTCLOUDRECVD = 0x05,			/*完整点云接收事件*/
        EVENT_ROIPOINTCLOUDRECVD = 0x06,			/*ROI点云接收接收事件*/
        EVENT_ROIFULLDISTANCERECVD = 0x07, 		/*ROI完整深度接收事件*/
        EVENT_ROISIMPLEDISTANCERECVD = 0x08, 		/*ROI简单深度接收事件*/
    };

    /**
    * @brief	输出事件回调
    * @param    out_id      输出设备的ID
    * @param    ret_event   输出的事件,EVENT_DEVDISCONNECT
    * @param    contex      用户自定义参数，回调上下文
    */
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void HPS3D_CALLBACK_OUTPUT(byte out_id, byte ret_event, IntPtr contex);

    /**
    * @brief	DEBUG信息接收函数
    * @param    str    输出的DEBUG信息
    * @param    contex 用户自定义参数，回调上下文
    */
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void HPS3D_CALLBACK_DEBUG(string str, IntPtr contex);

    class HPS3D_Device
    {
        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetDebugCallBack(HPS3D_CALLBACK_DEBUG call_back, IntPtr contex);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_ConnectByEthernet(byte[] server_ip, UInt16 server_port, ref byte device_id);

        [DllImport("HPSLC_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_ScanDeviceList(byte[] device_list, ref byte device_count);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_DisConnect(byte device_id);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetOutputCallBack(HPS3D_CALLBACK_OUTPUT call_back, byte device_id, IntPtr contex);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetAverageDistance_CB(byte device_id, ref UInt16 aver_distance);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetMaxDistance_CB(byte device_id, ref UInt16 max_distance);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetMinDistance_CB(byte device_id, ref UInt16 min_distance);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetAllAverAmplitude_CB(byte device_id, ref UInt16 all_aver_amp);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetValidAverAmplitude_CB(byte device_id, ref UInt16 valid_aver_amp);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetDistanceData_CB(byte device_id, UInt16[] distance_data);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetGrayscaleData_CB(byte device_id, byte[] grayscale_data);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetAmplitudeData_CB(byte device_id, UInt16[] amplitude_data);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetMaxAmplitudeData_CB(byte device_id, ref UInt16 max_amplitude);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetMinAmplitudeData_CB(byte device_id, ref UInt16 min_amplitude);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetPointCloudData_CB(byte device_id, double[,] point_data, ref UInt32 point_count);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetOutRoiParam_CB(byte device_id, ref byte group_id, ref byte roi_number, byte[] roi_id);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetOutRoiPointCloudData_CB(byte device_id, byte roi_id, double[,] roi_point_data, ref UInt32 roi_point_count);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetOutRoiDistanceData_CB(byte device_id, byte roi_id, UInt16[] roi_distance_data, UInt16[] roi_area);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetOutRoiAverageDistance_CB(byte device_id, byte roi_id, ref UInt16 aver_distance);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetOutRoiMaxDistance_CB(byte device_id, byte roi_id, ref UInt16 max_distance);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetOutRoiMinDistance_CB(byte device_id, byte roi_id, ref UInt16 min_distance);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetOutRoiAllAverAmplitude_CB(byte device_id, byte roi_id, ref UInt16 all_aver_amp);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetOutRoiValidAverAmplitude_CB(byte device_id, byte roi_id, ref UInt16 valid_aver_amp);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetRunMode(byte device_id, byte run_mode);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetRunMode(byte device_id, ref byte run_mode);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetPointCloudMode(byte device_id, bool point_cloud_enable, byte mirror_mode);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetPointCloudMode(byte device_id, ref bool point_cloud_enable, ref byte mirror_mode);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetMeasureMode(byte device_id, byte measure_mode);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetMeasureMode(byte device_id, ref byte measure_mode);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetSDKVersion(byte[] version);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetDeviceVersion(byte device_id, byte[] version);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetDeviceSN(byte device_id, byte[] SN);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetOutputDataType(byte device_id, ref byte data_type);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetOutputDataType(byte device_id, byte data_type);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetIntegTime(byte device_id, ref UInt32 time_us);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetIntegTime(byte device_id, UInt32 time_us);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_ProfileSaveToUser(byte device_id);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_ProfileClearUser(byte device_id);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_ProfileRestoreFactory(byte device_id);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetROIGroup(byte device_id, byte group_id);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetROIGroup(byte device_id, ref byte group_id);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetROIEnable(byte device_id, byte roi_id, bool enable);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetROIEnable(byte device_id, byte roi_id, ref bool enable);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetNumberOfROI(byte device_id, ref byte roi_number, ref byte threshold_number, ref byte roi_number_group);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetSmoothFilter(byte device_id, byte filter_type, UInt32 filter_times);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetSmoothFilter(byte device_id, ref byte filter_type, ref UInt32 filter_times);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SoftwareReset(byte device_id);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetOffset(byte device_id, UInt16 offset_mm);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetOffset(byte device_id, ref UInt16 offset_mm);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetSimpleKalmanFilter(byte device_id, bool kalman_enable, double kalman_k, UInt32 kalman_number, UInt32 kalman_threshold);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetSimpleKalmanFilter(byte device_id, ref bool kalman_enable, ref double kalman_k, ref UInt32 kalman_number, ref UInt32 kalman_threshold);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetWatchDogEnable(byte device_id, bool enable);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetWatchDogEnable(byte device_id, ref bool enable);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetEdgeFilter(byte device_id, ref bool enable, ref UInt32 args);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetEdgeFilter(byte device_id, bool enable, UInt32 args);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_SetHDREnable(byte device_id, bool enable);

        [DllImport("HPS3D_SDK.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        extern static byte HPS3D_GetHDREnable(byte device_id, ref bool enable);

        static HPS3D_CALLBACK_OUTPUT OutputCallBack;
        static HPS3D_CALLBACK_DEBUG DebugCallBack;

        public const int DEV_NUM = 4; //最大连接设备数
        public const int X_PIX_NUM = 640;
        public const int Y_PIX_NUM = 480;
        public const int PIXEL_NUM = 307200;
        /// <summary>
        /// 设置Debug信息接收函数
        /// </summary>
        /// <param name="call_back">回调函数</param>
        /// <param name="contex">回调上下文</param>
        /// call_back置为NULL将停止该功能
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetDebugCallBack(HPS3D_CALLBACK_DEBUG call_back, IntPtr contex)
        {
            DebugCallBack = call_back;
            byte ret = HPS3D_SetDebugCallBack(DebugCallBack, contex);
            return (RET_STATUS_ENUM)ret;
        }


        /// <summary>
        /// 设置以太网连接方式
        /// </summary>
        /// <param name="server_ip">IP号</param>
        /// <param name="server_port">端口号</param>
        /// <param name="device_id">设备ID号，设置失败时，ID返回值为99</param>
        /// <note>必须与固件上设置的连接方式对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM ConnectByEthernet(string server_ip, UInt16 server_port, ref byte device_id)
        {
            byte[] ip = System.Text.Encoding.ASCII.GetBytes(server_ip);//转码成ASCII编码
            byte ret = HPS3D_ConnectByEthernet(ip, server_port, ref device_id);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 扫描设备的ID列表
        /// </summary>
        /// <param name="device_list">设备列表</param>
        /// <param name="device_count">已经连接设备的数量</param>
        /// <note>device_list数组最少开辟4个空间，device_list[DEV_NUM]</note>
        /// 当只有一台设备连接时，之后的设备ID返回值为0。
        /// 例如：当device_count 返回值为1时，device_list[0] = 设备ID，
        ///	device_list[1] = device_list[2] = device_list[3] = 99
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM ScanDeviceList(byte[] device_list, ref byte device_count)
        {
            byte ret = HPS3D_ScanDeviceList(device_list, ref device_count);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 断开设备连接，回收资源
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM DisConnect(byte device_id)
        {
            byte ret = HPS3D_DisConnect(device_id);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置看门狗运行使能
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="enable">看门狗使能</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <note>调试时将使能设置为false,调试完成后注意及时将使能设置为true</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetWatchDogEnable(byte device_id, bool enable)
        {
            byte ret = HPS3D_SetWatchDogEnable(device_id, enable);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取看门狗运行使能
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="enable">返回看门狗使能</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <note>调试时将使能设置为false,调试完成后注意及时将使能设置为true</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetWatchDogEnable(byte device_id, ref bool enable)
        {
            byte ret = HPS3D_GetWatchDogEnable(device_id, ref enable);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置输出事件回调函数
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="call_back">回调函数</param>
        /// <param name="contex">回调上下文</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// call_back置为NULL将停止该功能
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetOutputCallBack(HPS3D_CALLBACK_OUTPUT call_back, byte device_id, IntPtr contex)
        {
            OutputCallBack = call_back;
            byte ret = HPS3D_SetOutputCallBack(OutputCallBack, device_id, contex);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取平均距离（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="aver_distance">返回平均距离，单位毫米</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_SIMPLEDISTANCERECVD
        /// 或者 EVENT_FULLDISTANCERECVD 或者 EVENT_FULLPOINTCLOUDRECVD 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetAverageDistance_CB(byte device_id, ref UInt16 aver_distance)
        {
            byte ret = HPS3D_GetAverageDistance_CB(device_id, ref aver_distance);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取最大距离（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="max_distance">返回最大距离，单位毫米</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_SIMPLEDISTANCERECVD
        /// 或者 EVENT_FULLDISTANCERECVD 或者 EVENT_FULLPOINTCLOUDRECVD 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetMaxDistance_CB(byte device_id, ref UInt16 max_distance)
        {
            byte ret = HPS3D_GetMaxDistance_CB(device_id, ref max_distance);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取最小距离（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="aver_distance">返回最小距离，单位毫米</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_SIMPLEDISTANCERECVD
        /// 或者 EVENT_FULLDISTANCERECVD 或者 EVENT_FULLPOINTCLOUDRECVD 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetMinDistance_CB(byte device_id, ref UInt16 min_distance)
        {
            byte ret = HPS3D_GetMinDistance_CB(device_id, ref min_distance);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取所有平均幅值（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="all_aver_amp">返回所有平均幅值（包括0幅值）</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_SIMPLEDISTANCERECVD
        /// 或者 EVENT_FULLDISTANCERECVD 或者 EVENT_FULLPOINTCLOUDRECVD 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetAllAverAmplitude_CB(byte device_id, ref UInt16 all_aver_amp)
        {
            byte ret = HPS3D_GetAllAverAmplitude_CB(device_id, ref all_aver_amp);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取有效的平均幅值（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="valid_aver_amp">返回有效的平均幅值（不包括0幅值）</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_SIMPLEDISTANCERECVD
        /// 或者 EVENT_FULLDISTANCERECVD 或者 EVENT_FULLPOINTCLOUDRECVD 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetValidAverAmplitude_CB(byte device_id, ref UInt16 valid_aver_amp)
        {
            byte ret = HPS3D_GetValidAverAmplitude_CB(device_id, ref valid_aver_amp);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取距离数据（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="distance_data">距离数据,单位毫米（需要开辟307200个空间)，distance_data[307200]</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_FULLDISTANCERECVD 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetDistanceData_CB(byte device_id, UInt16[] distance_data)
        {
            byte ret = HPS3D_GetDistanceData_CB(device_id, distance_data);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取灰度数据（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="grayscale_data">灰度数据,单位灰度值（范围0~255）（需要开辟307200个空间)，grayscale_data[307200]</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_AMPLITUDE 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetGrayscaleData_CB(byte device_id, byte[] grayscale_data)
        {
            byte ret = HPS3D_GetGrayscaleData_CB(device_id, grayscale_data);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取幅值数据（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="amplitude_data">幅值数据,（需要开辟307200个空间)，amplitude_data[307200]</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_AMPLITUDE 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetAmplitudeData_CB(byte device_id, UInt16[] amplitude_data)
        {
            byte ret = HPS3D_GetAmplitudeData_CB(device_id, amplitude_data);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取最大幅值数据（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="max_amplitude">返回最大幅值数据</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_AMPLITUDE 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetMaxAmplitudeData_CB(byte device_id, ref UInt16 max_amplitude)
        {
            byte ret = HPS3D_GetMaxAmplitudeData_CB(device_id, ref max_amplitude);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取最小幅值数据（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="min_amplitude">返回最小幅值数据</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_AMPLITUDE 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetMinAmplitudeData_CB(byte device_id, ref UInt16 min_amplitude)
        {
            byte ret = HPS3D_GetMinAmplitudeData_CB(device_id, ref min_amplitude);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取点云数据（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="point_data">点云数据,定义方式,point_data[307200][3]</param>
        /// <param name="point_count">有效点的数量</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_FULLPOINTCLOUDRECVD 
        /// 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
        /// point_data中，[3]的值：0表示X轴值，1表示Y轴值，2表示Z轴值。其中，无效点已经被自动过滤
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetPointCloudData_CB(byte device_id, double[,] point_data, ref UInt32 point_count)
        {
            byte ret = HPS3D_GetPointCloudData_CB(device_id, point_data, ref point_count);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取输出的ROI参数信息（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="group_id">返回ROI组ID</param>
        /// <param name="roi_number">返回ROI个数</param>
        /// <param name="roi_id">返回ROI的ID，需要开辟8个空间，roi_id[8]</param>
		/// roi_number的值决定roi_id的有效数据个数
		///	例如：roi_number = 1时
		///	roi_id[0] = ROI的ID。roi_id[1~7] 无效
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_ROIPOINTCLOUDRECVD 
        /// 或者 EVENT_ROIFULLDISTANCERECVD 或者 EVENT_ROISIMPLEDISTANCERECVD 通知时调用
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetOutRoiParam_CB(byte device_id, ref byte group_id, ref byte roi_number, byte[] roi_id)
        {
            byte ret = HPS3D_GetOutRoiParam_CB(device_id, ref group_id, ref roi_number, roi_id);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取输出ROI的点云数据（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="roi_id">ROI的ID</param>
        /// <param name="roi_point_data">点云数据,定义方式,point_data[307200][3]</param>
        /// <param name="roi_point_count">有效点的数量</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_ROIPOINTCLOUDRECVD 通知时调用
        /// point_data中，[3]的值：0表示X轴值，1表示Y轴值，2表示Z轴值。其中，无效点已经被自动过滤
        /// 调用前先调用 GetOutRoiParam_CB 接口获取对应的输入参数
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetOutRoiPointCloudData_CB(byte device_id, byte roi_id, double[,] roi_point_data, ref UInt32 roi_point_count)
        {
            byte ret = HPS3D_GetOutRoiPointCloudData_CB(device_id, roi_id, roi_point_data, ref roi_point_count);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取输出的ROI深度数据（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="roi_id">ROI的ID</param>
        /// <param name="roi_distance_data">ROI的深度数据，单位毫米，需要开辟307200个空间，roi_distance_data[307200]</param>
        /// <param name="roi_area">ROI的范围，需要开辟4个空间，roi_area[4]</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// roi_area[0]：表示左上角点的X坐标  roi_area[1]：表示左上角点的Y坐标
        /// roi_area[2]：表示右下角点的X坐标 roi_area[3]：标志右下角点的Y坐标
        /// 该区域的像素个数计算公式为： (right_bottom_x - left_top_x + 1) * (right_bottom_y - left_top_y + 1));
        /// pixel_number = (roi_area[2] - roi_area[0] + 1) * (roi_area[3] - roi_area[1] + 1)
        /// 该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 通知时调用
        /// 调用前先调用 GetOutRoiParam_CB 接口获取对应的输入参数
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetOutRoiDistanceData_CB(byte device_id, byte roi_id, UInt16[] roi_distance_data, UInt16[] roi_area)
        {
            byte ret = HPS3D_GetOutRoiDistanceData_CB(device_id, roi_id, roi_distance_data, roi_area);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取输出的ROI平均距离（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="roi_id">ROI的ID</param>
        /// <param name="aver_distance">返回平均距离，单位毫米</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 或者
        /// EVENT_ROISIMPLEDISTANCERECVD 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
        /// 调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetOutRoiAverageDistance_CB(byte device_id, byte roi_id, ref UInt16 aver_distance)
        {
            byte ret = HPS3D_GetOutRoiAverageDistance_CB(device_id, roi_id, ref aver_distance);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取输出的ROI最大距离（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="roi_id">ROI的ID</param>
        /// <param name="max_distance">返回最大距离，单位毫米</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 或者
        /// EVENT_ROISIMPLEDISTANCERECVD 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
        /// 调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetOutRoiMaxDistance_CB(byte device_id, byte roi_id, ref UInt16 max_distance)
        {
            byte ret = HPS3D_GetOutRoiMaxDistance_CB(device_id, roi_id, ref max_distance);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取输出的ROI最小距离（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="roi_id">ROI的ID</param>
        /// <param name="min_distance">返回最小距离，单位毫米</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 或者
        /// EVENT_ROISIMPLEDISTANCERECVD 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
        /// 调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetOutRoiMinDistance_CB(byte device_id, byte roi_id, ref UInt16 min_distance)
        {
            byte ret = HPS3D_GetOutRoiMinDistance_CB(device_id, roi_id, ref min_distance);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取输出的ROI所有平均幅值（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="roi_id">ROI的ID</param>
        /// <param name="all_aver_amp">所有平均幅值（包括0幅值）</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 或者
        /// EVENT_ROISIMPLEDISTANCERECVD 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
        /// 调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetOutRoiAllAverAmplitude_CB(byte device_id, byte roi_id, ref UInt16 all_aver_amp)
        {
            byte ret = HPS3D_GetOutRoiAllAverAmplitude_CB(device_id, roi_id, ref all_aver_amp);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取输出的ROI有效平均幅值（回调函数中使用）
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="roi_id">ROI的ID</param>
        /// <param name="valid_aver_amp">返回有效的平均幅值（不包括0幅值）</param>
        /// <note>device_id必须与回调函数输出的ID对应</note>
        /// 该接口只能在回调函数中收到 EVENT_ROIFULLDISTANCERECVD 或者
        /// EVENT_ROISIMPLEDISTANCERECVD 或者 EVENT_ROIPOINTCLOUDRECVD 通知时调用
        /// 调用前先调用 HPS3D_GetOutRoiParam_CB 接口获取对应的输入参数
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetOutRoiValidAverAmplitude_CB(byte device_id, byte roi_id, ref UInt16 valid_aver_amp)
        {
            byte ret = HPS3D_GetOutRoiValidAverAmplitude_CB(device_id, roi_id, ref valid_aver_amp);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置运行模式
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="run_mode">运行模式</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetRunMode(byte device_id, RUN_MODE_ENUM run_mode)
        {
            byte ret = HPS3D_SetRunMode(device_id, (byte)run_mode);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取运行模式
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="run_mode">运行模式</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetRunMode(byte device_id, ref RUN_MODE_ENUM run_mode)
        {
            byte mode = 0;
            byte ret = HPS3D_GetRunMode(device_id, ref mode);
            run_mode = (RUN_MODE_ENUM)mode;
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置点云模式配置
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="point_cloud_enable">点云图使能</param>
        /// <param name="mirror_mode">点云图镜像模式,MIRROR_DISABLE</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetPointCloudMode(byte device_id, bool point_cloud_enable, POINTCLOUD_MIRROR_MODE_ENUM mirror_mode)
        {
            byte ret = HPS3D_SetPointCloudMode(device_id, point_cloud_enable, (byte)mirror_mode);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取点云模式配置
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="point_cloud_enable">返回点云图使能</param>
        /// <param name="mirror_mode">返回点云图镜像模式,MIRROR_DISABLE</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetPointCloudMode(byte device_id, ref bool point_cloud_enable, ref POINTCLOUD_MIRROR_MODE_ENUM mirror_mode)
        {
            byte mode = 0;
            byte ret = HPS3D_GetPointCloudMode(device_id, ref point_cloud_enable, ref mode);
            mirror_mode = (POINTCLOUD_MIRROR_MODE_ENUM)mode;
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置测量模式
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="measure_mode">测量模式，DSITMODE_GENERAL</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetMeasureMode(byte device_id, MEASURE_MODE_ENUM measure_mode)
        {
            byte ret = HPS3D_SetMeasureMode(device_id, (byte)measure_mode);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取测量模式
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="measure_mode">返回测量模式，DSITMODE_GENERAL</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetMeasureMode(byte device_id, ref MEASURE_MODE_ENUM measure_mode)
        {
            byte mode = 0;
            byte ret = HPS3D_GetMeasureMode(device_id, ref mode);
            measure_mode = (MEASURE_MODE_ENUM)mode;
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取SDK版本信息
        /// </summary>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetSDKVersion(ref string SDKVersion)
        {
            SDKVersion = "20";
            byte[] temp = new byte[6];
            byte ret = HPS3D_GetSDKVersion(temp);
            if (ret == 0x01)
            {
                SDKVersion = SDKVersion + temp[0] + "-" + temp[1];
                SDKVersion = SDKVersion + "-" + temp[2] + " ";
                SDKVersion = SDKVersion + "V" + temp[3];
                SDKVersion = SDKVersion + "." + temp[4] + " ";
                SDKVersion = SDKVersion + "Rev:" + temp[5];
            }
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取设备版本信息
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetDeviceVersion(byte device_id, ref string DeviceVersion)
        {
            DeviceVersion = "20";
            byte[] temp = new byte[6];
            byte ret = HPS3D_GetDeviceVersion(device_id, temp);
            if (ret == 0x01)
            {
                DeviceVersion = DeviceVersion + temp[0] + "-" + temp[1];
                DeviceVersion = DeviceVersion + "-" + temp[2] + " ";
                DeviceVersion = DeviceVersion + "V" + temp[3];
                DeviceVersion = DeviceVersion + "." + temp[4] + " ";
                DeviceVersion = DeviceVersion + "Rev:" + temp[5];
            }
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取设备的序列号
        /// </summary>
        /// <param name="device_id"></param> 
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <note>执行该命令前，需要将运行模式设置为 RUN_MODE_ENUM.RUN_IDLE</note>
        /// <returns>返回传感头序列号</returns>
        public static RET_STATUS_ENUM GetDeviceSN(byte device_id, ref string SN)
        {
            //IntPtr string_ptr = Marshal.StringToHGlobalAnsi(SN);
            byte[] temp = new byte[64];
            byte ret = HPS3D_GetDeviceSN(device_id, temp);
            if (ret == 0x01)
            {
                SN = System.Text.Encoding.ASCII.GetString(temp);
                SN.Replace("-", "");
            }
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取输出数据类型
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="data_type">返回输出数据类型,OUTPUT_AMPLITUDE</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        ///  OUTPUT_AMPLITUDE，将通过回调函数输出振幅数据
        ///  OUTPUT_DISTANCE_FULL，将通过回调函数输出完整深度数据，包含各像素点数据
        ///  OUTPUT_DISTANCE_SIMPLE，将通过回调函数输出简单深度数据，不包含各像素点数据，只包含数学统计数据
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetOutputDataType(byte device_id, ref OUTPUT_TYPE_ENUM data_type)
        {
            byte type = 0;
            byte ret = HPS3D_GetOutputDataType(device_id, ref type);
            data_type = (OUTPUT_TYPE_ENUM)type;
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置输出数据类型
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="data_type">输出数据类型,OUTPUT_AMPLITUDE</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        ///  OUTPUT_AMPLITUDE，将通过回调函数输出振幅数据
        ///  OUTPUT_DISTANCE_FULL，将通过回调函数输出完整深度数据，包含各像素点数据
        ///  OUTPUT_DISTANCE_SIMPLE，将通过回调函数输出简单深度数据，不包含各像素点数据，只包含数学统计数据
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetOutputDataType(byte device_id, OUTPUT_TYPE_ENUM data_type)
        {
            byte ret = HPS3D_SetOutputDataType(device_id, (byte)data_type);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置积分时间
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="time_us">积分时间(单位us，范围50~1000)</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetIntegTime(byte device_id, UInt32 time_us)
        {
            byte ret = HPS3D_SetIntegTime(device_id, time_us);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取积分时间
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="time_us">返回积分时间(单位us，范围50~1000)</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetIntegTime(byte device_id, ref UInt32 time_us)
        {
            byte ret = HPS3D_GetIntegTime(device_id, ref time_us);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 保存到用户设置表
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM ProfileSaveToUser(byte device_id)
        {
            byte ret = HPS3D_ProfileSaveToUser(device_id);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 清除用户设置表
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM ProfileClearUser(byte device_id)
        {
            byte ret = HPS3D_ProfileClearUser(device_id);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 还原出厂设置
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM ProfileRestoreFactory(byte device_id)
        {
            byte ret = HPS3D_ProfileRestoreFactory(device_id);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 选择ROI组
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="group_id">ROI组的ID,0~1</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetROIGroup(byte device_id, byte group_id)
        {
            byte ret = HPS3D_SetROIGroup(device_id, group_id);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 选择ROI组
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="group_id">返回的ROI组ID</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetROIGroup(byte device_id, ref byte group_id)
        {
            byte ret = HPS3D_GetROIGroup(device_id, ref group_id);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置ROI使能
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="roi_id">ROI的ID</param>
        /// <param name="enable">ROI使能</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetROIEnable(byte device_id, byte roi_id, bool enable)
        {
            byte ret = HPS3D_SetROIEnable(device_id, roi_id, enable);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取ROI使能
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="roi_id">ROI的ID</param>
        /// <param name="enable">返回ROI使能</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetROIEnable(byte device_id, byte roi_id, ref bool enable)
        {
            byte ret = HPS3D_GetROIEnable(device_id, roi_id, ref enable);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取当前设备支持的ROI数量和阈值数量
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="roi_number">返回支持的ROI数量</param>
        /// <param name="threshold_number">返回支持的阈值数量</param>
        /// <param name="roi_number_group">返回支持的ROI组数量</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetNumberOfROI(byte device_id, ref byte roi_number, ref byte threshold_number, ref byte roi_number_group)
        {
            byte ret = HPS3D_GetNumberOfROI(device_id, ref roi_number, ref threshold_number, ref roi_number_group);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置平滑滤波器
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="filter_type">平滑滤波器类型，SMOOTH_FILTER_DISABLE</param>
        /// <param name="filter_times">平滑滤波器滤波次数，范围0~10</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetSmoothFilter(byte device_id, SMOOTH_FILTER_TYPE_ENUM filter_type, UInt32 filter_times)
        {
            byte ret = HPS3D_SetSmoothFilter(device_id, (byte)filter_type, filter_times);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取平滑滤波器设置
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="filter_type">返回平滑滤波器类型，SMOOTH_FILTER_DISABLE</param>
        /// <param name="filter_times">返回平滑滤波器滤波次数，范围0~10</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetSmoothFilter(byte device_id, ref SMOOTH_FILTER_TYPE_ENUM filter_type, ref UInt32 filter_times)
        {
            byte type = 0;
            byte ret = HPS3D_GetSmoothFilter(device_id, ref type, ref filter_times);
            filter_type = (SMOOTH_FILTER_TYPE_ENUM)type;
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 软件复位
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SoftwareReset(byte device_id)
        {
            byte ret = HPS3D_SoftwareReset(device_id);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置距离偏移
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="offset_mm">偏移距离，单位MM</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetOffset(byte device_id, UInt16 offset_mm)
        {
            byte ret = HPS3D_SetOffset(device_id, offset_mm);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取距离偏移
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="offset_mm">返回偏移距离，单位MM</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetOffset(byte device_id, ref UInt16 offset_mm)
        {
            byte ret = HPS3D_GetOffset(device_id, ref offset_mm);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置卡尔曼滤波器
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="kalman_enable">卡尔曼滤波器使能</param>
        /// <param name="kalman_k">卡尔曼滤波器比例系数</param>
        /// <param name="kalman_number">卡尔曼滤波器阈值检查帧数</param>
        /// <param name="kalman_threshold">卡尔曼滤波器噪声阈值</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <note>enable使能设置为false后其他值将不会被写入，可设置为0</note>
        /// <note>执行该命令前，需要将运行模式设置为 RUN_IDLE</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetSimpleKalmanFilter(byte device_id, bool kalman_enable, double kalman_k, UInt32 kalman_number, UInt32 kalman_threshold)
        {
            byte ret = HPS3D_SetSimpleKalmanFilter(device_id, kalman_enable, kalman_k, kalman_number, kalman_threshold);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取卡尔曼滤波器
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="kalman_enable">卡尔曼滤波器使能</param>
        /// <param name="kalman_k">卡尔曼滤波器比例系数</param>
        /// <param name="kalman_number">卡尔曼滤波器阈值检查帧数</param>
        /// <param name="kalman_threshold">卡尔曼滤波器噪声阈值</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <note>执行该命令前，需要将运行模式设置为 RUN_IDLE</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetSimpleKalmanFilterv(byte device_id, ref bool kalman_enable, ref double kalman_k, ref UInt32 kalman_number, ref UInt32 kalman_threshold)
        {
            byte ret = HPS3D_GetSimpleKalmanFilter(device_id, ref kalman_enable, ref kalman_k, ref kalman_number, ref kalman_threshold);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置边缘滤波器
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="enable">边缘滤波器使能状态</param>
        /// <param name="args">边缘滤波器过滤参数，单位MM</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <note>enable使能设置为false后其他值将不会被写入，可设置为0</note>
        /// <note>执行该命令前，需要将运行模式设置为 RUN_IDLE</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetEdgeFilter(byte device_id, bool enable, UInt32 args)
        {
            byte ret = HPS3D_SetEdgeFilter(device_id, enable, args);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取边缘滤波器设置
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="enable">边缘滤波器使能状态</param>
        /// <param name="args">边缘滤波器过滤参数，单位MM</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <note>执行该命令前，需要将运行模式设置为 RUN_IDLE</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetEdgeFilter(byte device_id, ref bool enable, ref UInt32 args)
        {
            byte ret = HPS3D_GetEdgeFilter(device_id, ref enable, ref args);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 设置HDR模式使能
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="enable">HDR模式使能</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <note>执行该命令前，需要将运行模式设置为 RUN_IDLE</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM SetHDREnable(byte device_id, bool enable)
        {
            byte ret = HPS3D_SetHDREnable(device_id, enable);
            return (RET_STATUS_ENUM)ret;
        }

        /// <summary>
        /// 获取HDR模式使能
        /// </summary>
        /// <param name="device_id">设备ID</param>
        /// <param name="enable">HDR模式使能</param>
        /// <note>device_id必须与连接时返回的ID对应</note>
        /// <note>执行该命令前，需要将运行模式设置为 RUN_IDLE</note>
        /// <returns>成功返回RET_STATUS_ENUM.RET_OK</returns>
        public static RET_STATUS_ENUM GetHDREnable(byte device_id, ref bool enable)
        {
            byte ret = HPS3D_GetHDREnable(device_id, ref enable);
            return (RET_STATUS_ENUM)ret;
        }
    }
}
