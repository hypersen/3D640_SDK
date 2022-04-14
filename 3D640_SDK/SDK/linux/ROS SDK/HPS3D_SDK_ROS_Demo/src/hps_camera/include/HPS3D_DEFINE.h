#ifndef HPS3D_DEFINE_H_
#define HPS3D_DEFINE_H_



/*函数返回的结果*/
#define RET_OK						 (0x01)
#define RET_ERROR					 (0x02)
#define RET_BUSY					 (0x03)
#define RET_CONNECT_FAILED			 (0x04)		/*连接失败*/
#define RET_CREAT_PTHREAD_ERR		 (0x05)		/*线程创建失败*/
#define RET_WRITE_ERR				 (0x06)		/*数据发送失败*/
#define RET_READ_ERR				 (0x07)		/*读数据失败*/
#define RET_PACKET_HEAD_ERR			 (0x08)		/*数据包格式报头或报尾错误*/
#define RET_PACKET_ERR				 (0x09) 	/*数据包解析错误*/
#define RET_BUFF_EMPTY				 (0x0A)		/*缓冲区为空或不可用*/
#define RET_VER_MISMATCH			 (0x0B) 	/*固件版本与SDK版本不匹配*/
#define RET_INVALID_LICENSE			 (0x0C)		/*许可无效，需更新许可*/


/*运行模式*/
#define RUN_IDLE 					 (0x00)			/*待机或停止测量*/
#define RUN_SINGLE_SHOT 			 (0x01)			/*单次测量*/
#define RUN_CONTINUOUS 				 (0x02)			/*连续测量*/


/*输出数据类型*/
#define OUTPUT_AMPLITUDE				(0x00)      //输出幅值数据
#define OUTPUT_DISTANCE_FULL			(0x01)      //输出完整深度数据
#define OUTPUT_DISTANCE_SIMPLE			(0x02)		//输出简单深度数据

//ROI参考值类型
#define ROI_REF_DIST_AVR						(0x01)/*ROI区域的距离平均值作为参考值*/
#define ROI_REF_DIST_MIN						(0x02)/*ROI区域的距离最小值作为参考值*/
#define ROI_REF_DIST_MAX						(0x03)/*ROI区域的距离最大值作为参考值*/
#define ROI_REF_SAT_COUNT						(0x04)/*ROI区域的饱和像素点数量作为参考值*/
#define ROI_REF_AMPLITUDE						(0x05)/*ROI区域的幅值平均值作为参考值*/
#define ROI_REF_VAILD_AMPLITUDE					(0x06)/*ROI区域的有效幅值平均值作为参考值*/
#define ROI_REF_THRESHOLD_PIX_NUM				(0x07)/*超过设定阈值的像素点数，相比最大值比较和最小值比较具有更高的可靠性*/

//平滑滤波器类型
#define SMOOTH_FILTER_DISABLE			(0x00)	//不使用平滑滤波器
#define SMOOTH_FILTER_AVERAGE			(0x01)	//滑动平均滤波器
#define SMOOTH_FILTER_GAUSS				(0x02)	//高斯平滑滤波器

//点云图镜像模式
#define MIRROR_DISABLE					(0x00)	//不使用镜像
#define MIRROR_HORIZONTAL				(0x01)	//水平镜像
#define MIRROR_VERTICLA					(0x02)	//垂直镜像
#define MIRROR_ALL						(0x03)	//垂直和水平镜像

//设备测量模式
#define  DSITMODE_GENERAL					(0x01) //普通模式
#define  DSITMODE_SHORTDIST_HIGH_ACCURACY	(0x02) //近距离高精度
#define  DSITMODE_LONGDIST_HIGH_ACCURACY	(0x03) //远距离高精度
#define  DSITMODE_LONGDIST_LOW_ACCURACY		(0x04)  //远距离低精度

/*输出事件*/
#define EVENT_DEVDISCONNECT				 (0x01) 		/*断开连接事件*/

#define EVENT_SIMPLEDISTANCERECVD 	     (0x02)			/*简单深度数据接收事件*/

#define EVENT_FULLDISTANCERECVD 	     (0x03)			/*完整深度数据接收事件*/

#define EVENT_AMPLITUDE					 (0x04)			/*振幅数据接收事件*/

#define EVENT_FULLPOINTCLOUDRECVD  		 (0x05)			/*完整点云接收事件*/

#define EVENT_ROIPOINTCLOUDRECVD		 (0x06)			/*ROI点云接收接收事件*/

#define EVENT_ROIFULLDISTANCERECVD 		 (0x07) 		/*ROI完整深度接收事件*/

#define EVENT_ROISIMPLEDISTANCERECVD	 (0x08) 		/*ROI简单深度接收事件*/
#endif /* HPS3D_DEFINE_H_ */