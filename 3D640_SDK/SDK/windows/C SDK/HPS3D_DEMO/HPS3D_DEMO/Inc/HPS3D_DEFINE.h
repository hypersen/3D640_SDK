#ifndef HPS3D_DEFINE_H_
#define HPS3D_DEFINE_H_



/*�������صĽ��*/
#define RET_OK						 (0x01)
#define RET_ERROR					 (0x02)
#define RET_BUSY					 (0x03)
#define RET_CONNECT_FAILED			 (0x04)		/*����ʧ��*/
#define RET_CREAT_PTHREAD_ERR		 (0x05)		/*�̴߳���ʧ��*/
#define RET_WRITE_ERR				 (0x06)		/*���ݷ���ʧ��*/
#define RET_READ_ERR				 (0x07)		/*������ʧ��*/
#define RET_PACKET_HEAD_ERR			 (0x08)		/*���ݰ���ʽ��ͷ��β����*/
#define RET_PACKET_ERR				 (0x09) 	/*���ݰ���������*/
#define RET_BUFF_EMPTY				 (0x0A)		/*������Ϊ�ջ򲻿���*/
#define RET_VER_MISMATCH			 (0x0B) 	/*�̼��汾��SDK�汾��ƥ��*/
#define RET_INVALID_LICENSE			 (0x0C)		/*�����Ч����������*/


/*����ģʽ*/
#define RUN_IDLE 					 (0x00)			/*������ֹͣ����*/
#define RUN_SINGLE_SHOT 			 (0x01)			/*���β���*/
#define RUN_CONTINUOUS 				 (0x02)			/*��������*/


/*�����������*/
#define OUTPUT_AMPLITUDE				(0x00)      //�����ֵ����
#define OUTPUT_DISTANCE_FULL			(0x01)      //��������������
#define OUTPUT_DISTANCE_SIMPLE			(0x02)		//������������

//ROI�ο�ֵ����
#define ROI_REF_DIST_AVR						(0x01)/*ROI����ľ���ƽ��ֵ��Ϊ�ο�ֵ*/
#define ROI_REF_DIST_MIN						(0x02)/*ROI����ľ�����Сֵ��Ϊ�ο�ֵ*/
#define ROI_REF_DIST_MAX						(0x03)/*ROI����ľ������ֵ��Ϊ�ο�ֵ*/
#define ROI_REF_SAT_COUNT						(0x04)/*ROI����ı������ص�������Ϊ�ο�ֵ*/
#define ROI_REF_AMPLITUDE						(0x05)/*ROI����ķ�ֵƽ��ֵ��Ϊ�ο�ֵ*/
#define ROI_REF_VAILD_AMPLITUDE					(0x06)/*ROI�������Ч��ֵƽ��ֵ��Ϊ�ο�ֵ*/
#define ROI_REF_THRESHOLD_PIX_NUM				(0x07)/*�����趨��ֵ�����ص�����������ֵ�ȽϺ���Сֵ�ȽϾ��и��ߵĿɿ���*/

//ƽ���˲�������
#define SMOOTH_FILTER_DISABLE			(0x00)	//��ʹ��ƽ���˲���
#define SMOOTH_FILTER_AVERAGE			(0x01)	//����ƽ���˲���
#define SMOOTH_FILTER_GAUSS				(0x02)	//��˹ƽ���˲���

//����ͼ����ģʽ
#define MIRROR_DISABLE					(0x00)	//��ʹ�þ���
#define MIRROR_HORIZONTAL				(0x01)	//ˮƽ����
#define MIRROR_VERTICLA					(0x02)	//��ֱ����
#define MIRROR_ALL						(0x03)	//��ֱ��ˮƽ����

//�豸����ģʽ
#define  DSITMODE_GENERAL					(0x01) //��ͨģʽ
#define  DSITMODE_SHORTDIST_HIGH_ACCURACY	(0x02) //������߾���
#define  DSITMODE_LONGDIST_HIGH_ACCURACY	(0x03) //Զ����߾���
#define  DSITMODE_LONGDIST_LOW_ACCURACY		(0x04)  //Զ����;���

/*����¼�*/
#define EVENT_DEVDISCONNECT				 (0x01) 		/*�Ͽ������¼�*/

#define EVENT_SIMPLEDISTANCERECVD 	     (0x02)			/*��������ݽ����¼�*/

#define EVENT_FULLDISTANCERECVD 	     (0x03)			/*����������ݽ����¼�*/

#define EVENT_AMPLITUDE					 (0x04)			/*������ݽ����¼�*/

#define EVENT_FULLPOINTCLOUDRECVD  		 (0x05)			/*�������ƽ����¼�*/

#define EVENT_ROIPOINTCLOUDRECVD		 (0x06)			/*ROI���ƽ��ս����¼�*/

#define EVENT_ROIFULLDISTANCERECVD 		 (0x07) 		/*ROI������Ƚ����¼�*/

#define EVENT_ROISIMPLEDISTANCERECVD	 (0x08) 		/*ROI����Ƚ����¼�*/
#endif /* HPS3D_DEFINE_H_ */