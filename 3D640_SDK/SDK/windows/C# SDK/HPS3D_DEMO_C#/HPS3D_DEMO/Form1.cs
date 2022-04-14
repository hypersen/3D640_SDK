using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using HPS3D_DeviceLib;
using System.Threading;


namespace HPS3D_DEMO
{
    public partial class Form1 : Form
    {
        struct ROI_DATA
        {
            public UInt16[] distance_data;
            public UInt16[] area;
        };


        UInt32 g_fps = 0;
        UInt16 g_aver_distance = 0;
        UInt16 g_max_distance = 0;
        UInt16 g_min_distance = 0;
        UInt16 g_valid_aver_amp = 0;
        UInt16 g_all_aver_amp = 0;
        UInt16 g_roi_aver_distance = 0;
        UInt16 g_roi_max_distance = 0;
        UInt16 g_roi_min_distance = 0;
        UInt16 g_roi_valid_aver_amp = 0;
        UInt16 g_roi_all_aver_amp = 0;
        UInt16 g_max_amp = 0;
        UInt16 g_min_amp = 0;
        byte g_device_id = 99;
        byte g_roi_number = 0;
        byte[] g_roi_id = new byte[8];
        ROI_DATA[] g_roi_data = new ROI_DATA[8];
        double[,] g_point_data = new double[HPS3D_Device.PIXEL_NUM, 3];
        UInt32 g_point_count = 0;
        UInt16[] g_distance_data = new UInt16[HPS3D_Device.PIXEL_NUM];
        byte[] g_grayscale_data = new byte[HPS3D_Device.PIXEL_NUM];
        UInt16[] g_amplitude_data = new UInt16[HPS3D_Device.PIXEL_NUM];
        bool g_isConnect = false;
        private static readonly Mutex g_mutex = new Mutex();
        private static readonly Mutex g_debug_mutex = new Mutex();
        private System.Windows.Forms.Timer DataTimer = new System.Windows.Forms.Timer();
        private System.Windows.Forms.Timer DebugTimer = new System.Windows.Forms.Timer();
        //用于定时器刷新时判断是否有数据，//0：无数据 1：简单深度数据  2：完整深度数据
        //3.幅值数据 4：完整点云数据 5：ROI点云数据 6：ROI完整深度数据 7：ROI简单深度数据
        byte g_hasData = 0;
        List<string> StringList = new List<string>();
        string Time;
        bool g_isContinuous = false; //开启连续测量标志

        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Debug信息回调函数
        /// </summary>
        /// <param name="id"></param>
        /// <param name="data"></param>
        /// <param name="ret_event"></param>
        public void DebugPrintfFunc(string pack, IntPtr contex)
        {
            g_debug_mutex.WaitOne();
            string temp = pack + "\n";
            //可能在其他线程回调数据，不能直接打印
            StringList.Add(temp);
            g_debug_mutex.ReleaseMutex();
            //debugText.AppendText(pack + "\n");
        }

        /// <summary>
        /// 输出事件回调函数
        /// </summary>
        /// <param name="out_id"></param>
        /// <param name="ret_event"></param>
        /// <param name="ret_event"></param>
        public void OutputEventFunc(byte out_id, byte ret_event, IntPtr contex)
        {
            if (out_id == g_device_id) //如果输出事件的设备与连接的设备相同
            {
                g_mutex.WaitOne();
                g_fps++;
                OUTPUT_EVENT_ENUM Event = (OUTPUT_EVENT_ENUM)ret_event;
                if (Event == OUTPUT_EVENT_ENUM.EVENT_DEVDISCONNECT) //设备连接被断开
                {
                    if (g_isConnect)
                    {
                        //断开连接，回收资源
                        HPS3D_Device.DisConnect(g_device_id);
                        g_isConnect = false;
                    }
                    MessageBox.Show("设备连接已中断");
                }
                else if (Event == OUTPUT_EVENT_ENUM.EVENT_SIMPLEDISTANCERECVD) //简单深度通知事件
                {
                    //简单深度通知事件只能获取数学统计信息
                    HPS3D_Device.GetAverageDistance_CB(out_id, ref g_aver_distance); //获取平均距离
                    HPS3D_Device.GetMaxDistance_CB(out_id, ref g_max_distance);       //获取最大距离
                    HPS3D_Device.GetMinDistance_CB(out_id, ref g_min_distance);       //获取最小距离
                    HPS3D_Device.GetValidAverAmplitude_CB(out_id, ref g_valid_aver_amp);  //有效平均幅值，计算不包含0幅值
                    HPS3D_Device.GetAllAverAmplitude_CB(out_id, ref g_all_aver_amp);    //平均幅值，计算包含0幅值
                    g_hasData = 1;
                    Time = DateTime.Now.ToString();
                }
                else if (Event == OUTPUT_EVENT_ENUM.EVENT_FULLDISTANCERECVD) //完整深度通知事件
                {
                    //完整深度通知事件可以获取数学统计信息和每个像素点的深度值

                    //获取每个像素点的深度数据
                    HPS3D_Device.GetDistanceData_CB(out_id, g_distance_data);

                    //简单深度通知事件只能获取数学统计信息
                    HPS3D_Device.GetAverageDistance_CB(out_id, ref g_aver_distance); //获取平均距离
                    HPS3D_Device.GetMaxDistance_CB(out_id, ref g_max_distance);       //获取最大距离
                    HPS3D_Device.GetMinDistance_CB(out_id, ref g_min_distance);       //获取最小距离
                    HPS3D_Device.GetValidAverAmplitude_CB(out_id, ref g_valid_aver_amp);  //有效平均幅值，计算不包含0幅值
                    HPS3D_Device.GetAllAverAmplitude_CB(out_id, ref g_all_aver_amp);    //平均幅值，计算包含0幅值
                    g_hasData = 2;
                    Time = DateTime.Now.ToString();
                }
                else if (Event == OUTPUT_EVENT_ENUM.EVENT_AMPLITUDE) //幅值通知事件
                {
                    //振幅通知事件可以获取每个像素点的灰度数据或者幅值数据，以及幅值相关的数学统计信息

                    //获取每个像素点的灰度数据，灰度数据由振幅数据归一化处理得到
                    HPS3D_Device.GetGrayscaleData_CB(out_id, g_grayscale_data);

                    //获取每个像素点的幅值数据
                    HPS3D_Device.GetAmplitudeData_CB(out_id, g_amplitude_data);

                    //获取振幅相关的数学统计信息
                    HPS3D_Device.GetValidAverAmplitude_CB(out_id, ref g_valid_aver_amp); // 有效平均幅值
                    HPS3D_Device.GetMaxAmplitudeData_CB(out_id, ref g_max_amp); //最大幅值
                    HPS3D_Device.GetMinAmplitudeData_CB(out_id, ref g_min_amp); //最小幅值
                    g_hasData = 3;
                    Time = DateTime.Now.ToString();
                }
                else if (Event == OUTPUT_EVENT_ENUM.EVENT_FULLPOINTCLOUDRECVD) //完整点云通知事件
                {
                    //完整点云图，能够获取每个像素的点云数据，和深度数据的数学统信息，点云数据自动过滤了无效值

                    //获取每个像素的点云数据
                    HPS3D_Device.GetPointCloudData_CB(out_id, g_point_data, ref g_point_count); //获取点云数据

                    //获取深度的数学统计信息
                    HPS3D_Device.GetAverageDistance_CB(out_id, ref g_aver_distance); //获取平均距离
                    HPS3D_Device.GetMaxDistance_CB(out_id, ref g_max_distance);       //获取最大距离
                    HPS3D_Device.GetMinDistance_CB(out_id, ref g_min_distance);       //获取最小距离
                    HPS3D_Device.GetValidAverAmplitude_CB(out_id, ref g_valid_aver_amp);  //有效平均幅值，计算不包含0幅值
                    HPS3D_Device.GetAllAverAmplitude_CB(out_id, ref g_all_aver_amp);	//平均幅值，计算包含0幅值
                    g_hasData = 4;
                    Time = DateTime.Now.ToString();
                }
                else if (Event == OUTPUT_EVENT_ENUM.EVENT_ROIPOINTCLOUDRECVD) //ROI点云通知事件
                {
                    //ROI点云事件可以获取ROI点云信息和每个ROI的深度数学统计信息
                    //其中获取点云数据有两种方式
                    //第一种，通过点云数据获取接口直接获取点云信息，自动将多个ROI点云数据拼接成
                    HPS3D_Device.GetPointCloudData_CB(out_id, g_point_data, ref g_point_count); //获取点云数据

                    //第二种，获取指定ROI的点云信息
                    byte group_id = 0;
                    //获取指定ROI的点云信息前，需要通过ROI参数接口，获取当前输出的ROI信息，（有几个ROI，ROI的ID等）

                    //获取ROI参数
                    HPS3D_Device.GetOutRoiParam_CB(out_id, ref group_id, ref g_roi_number, g_roi_id);
                    //依次获取每个ROI值
                    for (int i = 0; i < g_roi_number; i++)
                    {
                        HPS3D_Device.GetOutRoiPointCloudData_CB(out_id, g_roi_id[i], g_point_data, ref g_point_count);

                        //获取ROI的深度数学统计信息
                        HPS3D_Device.GetOutRoiAverageDistance_CB(out_id, g_roi_id[i], ref g_roi_aver_distance);
                        HPS3D_Device.GetOutRoiMaxDistance_CB(out_id, g_roi_id[i], ref g_roi_max_distance);
                        HPS3D_Device.GetOutRoiMinDistance_CB(out_id, g_roi_id[i], ref g_roi_min_distance);
                        HPS3D_Device.GetOutRoiAllAverAmplitude_CB(out_id, g_roi_id[i], ref g_roi_all_aver_amp);
                        HPS3D_Device.GetOutRoiValidAverAmplitude_CB(out_id, g_roi_id[i], ref g_roi_valid_aver_amp);
                    }
                    g_hasData = 5;
                    Time = DateTime.Now.ToString();
                }
                else if (Event == OUTPUT_EVENT_ENUM.EVENT_ROIFULLDISTANCERECVD) //ROI完整深度通知事件
                {
                    //ROI完整深度事件，可以获取每个ROI的深度数据和每个ROI的深度数学统计信息

                    byte group_id = 0;

                    //获取指定ROI的深度信息前，需要通过ROI参数接口，获取当前输出的ROI信息，（有几个ROI，ROI的ID等）
                    //获取ROI参数
                    HPS3D_Device.GetOutRoiParam_CB(out_id, ref group_id, ref g_roi_number, g_roi_id);

                    for (int i = 0; i < g_roi_number; i++)
                    {
                        //获取ROI距离值
                        HPS3D_Device.GetOutRoiDistanceData_CB(out_id, g_roi_id[i], g_roi_data[g_roi_id[i]].distance_data, g_roi_data[g_roi_id[i]].area);

                        //ROI深度数据的数据量需要通过ROI区域计算
                        g_point_count = ((UInt32)g_roi_data[g_roi_id[i]].area[2] - g_roi_data[g_roi_id[i]].area[0] + 1) * ((UInt32)g_roi_data[g_roi_id[i]].area[3] - g_roi_data[g_roi_id[i]].area[1] + 1);

                        //获取ROI数学统计信息
                        HPS3D_Device.GetOutRoiAverageDistance_CB(out_id, g_roi_id[i], ref g_roi_aver_distance);
                        HPS3D_Device.GetOutRoiMaxDistance_CB(out_id, g_roi_id[i], ref g_roi_max_distance);
                        HPS3D_Device.GetOutRoiMinDistance_CB(out_id, g_roi_id[i], ref g_roi_min_distance);
                        HPS3D_Device.GetOutRoiAllAverAmplitude_CB(out_id, g_roi_id[i], ref g_roi_all_aver_amp);
                        HPS3D_Device.GetOutRoiValidAverAmplitude_CB(out_id, g_roi_id[i], ref g_roi_valid_aver_amp);
                    }
                    g_hasData = 6;
                    Time = DateTime.Now.ToString();
                }
                else if (Event == OUTPUT_EVENT_ENUM.EVENT_ROISIMPLEDISTANCERECVD) //ROI简单深度通知事件
                {
                    //简单深度事件，可以获取每个ROI的深度数学统计信息
                    byte group_id = 0;

                    //获取指定ROI的深度信息前，需要通过ROI参数接口，获取当前输出的ROI信息，（有几个ROI，ROI的ID等）
                    //获取ROI参数
                    HPS3D_Device.GetOutRoiParam_CB(out_id, ref group_id, ref g_roi_number, g_roi_id);
                    for (int i = 0; i < g_roi_number; i++)
                    {
                        //获取ROI数学统计信息
                        HPS3D_Device.GetOutRoiAverageDistance_CB(out_id, g_roi_id[i], ref g_roi_aver_distance);
                        HPS3D_Device.GetOutRoiMaxDistance_CB(out_id, g_roi_id[i], ref g_roi_max_distance);
                        HPS3D_Device.GetOutRoiMinDistance_CB(out_id, g_roi_id[i], ref g_roi_min_distance);
                        HPS3D_Device.GetOutRoiAllAverAmplitude_CB(out_id, g_roi_id[i], ref g_roi_all_aver_amp);
                        HPS3D_Device.GetOutRoiValidAverAmplitude_CB(out_id, g_roi_id[i], ref g_roi_valid_aver_amp);
                    }
                    g_hasData = 7;
                    Time = DateTime.Now.ToString();
                }
                g_mutex.ReleaseMutex();
            }
        }

        //连接设备
        private void BtnConnect_Click(object sender, EventArgs e)
        {
            string ip = TextIP.Text;
            UInt16 port = Convert.ToUInt16(TextPort.Text);
            //以太网连接
            if (HPS3D_Device.ConnectByEthernet(ip, port, ref g_device_id) != RET_STATUS_ENUM.RET_OK)
            {
                MessageBox.Show("设备连接失败，请重试");
                return;
            }

            //注册传感器传感器接收回调函数
            if (HPS3D_Device.SetOutputCallBack(new HPS3D_CALLBACK_OUTPUT(OutputEventFunc), g_device_id, IntPtr.Zero) != RET_STATUS_ENUM.RET_OK)
            {
                HPS3D_Device.DisConnect(g_device_id);
                MessageBox.Show("回调函数注册失败，请重试");
                return;
            }

            //获取设备版本号
            string DeviceVersion = "";
            if (HPS3D_Device.GetDeviceVersion(g_device_id, ref DeviceVersion) != RET_STATUS_ENUM.RET_OK)
            {
                HPS3D_Device.DisConnect(g_device_id);
                MessageBox.Show("设备连接失败，请重试");
                return;
            }

            //获取SDK版本号
            string SDKVersion = "";
            if(HPS3D_Device.GetSDKVersion(ref SDKVersion) != RET_STATUS_ENUM.RET_OK)
            {
                HPS3D_Device.DisConnect(g_device_id);
                MessageBox.Show("设备连接失败，请重试");
                return;
            }

            //获取设备SN版本号
            string SN = "";
            if (HPS3D_Device.GetDeviceSN(g_device_id, ref SN) != RET_STATUS_ENUM.RET_OK)
            {
                HPS3D_Device.DisConnect(g_device_id);
                MessageBox.Show("设备连接失败，请重试");
                return;
            }
            g_isConnect = true;

            LabSDKVersion.Text = SDKVersion;
            LabDeviceSN.Text = SN;
            LabDeviceVersion.Text = DeviceVersion;
        }

        //启动窗口
        private void Form1_Load(object sender, EventArgs e)
        {
            //注册debug信息回调函数
            if (HPS3D_Device.SetDebugCallBack(DebugPrintfFunc, IntPtr.Zero) != RET_STATUS_ENUM.RET_OK)
            {
                MessageBox.Show("Debug信息注册失败");
            }

            //初始化参数
            for(int i =0; i < 8; i++)
            {
                g_roi_data[i].distance_data = new UInt16[307200];
                g_roi_data[i].area = new UInt16[4];
            }

            //开启定时器
            DataTimer.Tick += new EventHandler(TimeOut);
            DataTimer.Interval = 1000;
            DataTimer.Enabled = true;
            DataTimer.Start();
            DebugTimer.Tick += new EventHandler(DebugTimeOut);
            DebugTimer.Interval = 50;
            DebugTimer.Enabled = true;
            DebugTimer.Start();
        }

        //定时器回调函数
        private void TimeOut(Object myObject, EventArgs myEventArgs)
        {
            g_mutex.WaitOne();
            if (g_hasData == 1) //简单深度数据
            {
                TextData.AppendText("简单深度数据:" + Time + "\n");
                TextData.AppendText("平均深度(单位,MM):" + g_aver_distance.ToString() + "\n");
                TextData.AppendText("最大深度(单位,MM):" + g_max_distance.ToString() + "\n");
                TextData.AppendText("最小深度(单位,MM):" + g_min_distance.ToString() + "\n");
                TextData.AppendText("有效平均幅值(不包含0幅值):" + g_valid_aver_amp.ToString() + "\n");
                TextData.AppendText("平均幅值(不包含0幅值):" + g_all_aver_amp.ToString() + "\n\n");
            }
            else if(g_hasData == 2) //完整深度数据
            {
                TextData.AppendText("完整深度数据:" + Time + "\n");
                //显示像素点数据，一共307200个像素点，本次展示中间像素点数据
                TextData.AppendText("指定点深度(单位,MM):" + g_distance_data[153600].ToString() + "\n");
                TextData.AppendText("平均深度(单位,MM):" + g_aver_distance.ToString() + "\n");
                TextData.AppendText("最大深度(单位,MM):" + g_max_distance.ToString() + "\n");
                TextData.AppendText("最小深度(单位,MM):" + g_min_distance.ToString() + "\n");
                TextData.AppendText("有效平均幅值(不包含0幅值):" + g_valid_aver_amp.ToString() + "\n");
                TextData.AppendText("平均幅值(不包含0幅值):" + g_all_aver_amp.ToString() + "\n\n");
            }
            else if (g_hasData == 3) //幅值数据
            {
                TextData.AppendText("幅值数据:" + Time + "\n");
                //显示像素点数据，一共307200个像素点，本次展示中间像素点数据
                TextData.AppendText("指定点灰度:" + g_distance_data[153600].ToString() + "\n");
                TextData.AppendText("指定点幅值:" + g_distance_data[153600].ToString() + "\n");
                TextData.AppendText("平均幅值:" + g_valid_aver_amp.ToString() + "\n");
                TextData.AppendText("最大幅值:" + g_max_amp.ToString() + "\n");
                TextData.AppendText("最小幅值:" + g_min_amp.ToString() + "\n\n");
            }
            else if (g_hasData == 4) //完整点云数据
            {
                TextData.AppendText("完整点云数据:" + Time + "\n");
                //本次展示最后一个点的XZY坐标
                TextData.AppendText("点云坐标(单位,M):" + "X:" + g_point_data[g_point_count - 1, 0].ToString("f4") + " Y:" + g_point_data[g_point_count - 1, 1].ToString("f4") + " Z:" + g_point_data[g_point_count - 1, 2].ToString("f4") + "\n");
                TextData.AppendText("平均深度(单位,MM):" + g_aver_distance.ToString() + "\n");
                TextData.AppendText("最大深度(单位,MM):" + g_max_distance.ToString() + "\n");
                TextData.AppendText("最小深度(单位,MM):" + g_min_distance.ToString() + "\n");
                TextData.AppendText("有效平均幅值(不包含0幅值):" + g_valid_aver_amp.ToString() + "\n");
                TextData.AppendText("平均幅值(不包含0幅值):" + g_all_aver_amp.ToString() + "\n\n");
            }
            else if (g_hasData == 5) //ROI点云数据
            {
                TextData.AppendText("ROI点云数据:" + Time + "\n");
                //本次展示最后一个ROI的数据，的最后一个点数据
                TextData.AppendText("ROI的ID：" + g_roi_id[g_roi_number - 1].ToString() + "\n");
                TextData.AppendText("点云坐标(单位,M):" + "X:" + g_point_data[g_point_count - 1, 0].ToString("f4") + " Y:" + g_point_data[g_point_count - 1, 1].ToString("f4") + " Z:" + g_point_data[g_point_count - 1, 2].ToString("f4") + "\n");

                TextData.AppendText("平均深度(单位,MM):" + g_roi_aver_distance.ToString() + "\n");
                TextData.AppendText("最大深度(单位,MM):" + g_roi_max_distance.ToString() + "\n");
                TextData.AppendText("最小深度(单位,MM):" + g_roi_min_distance.ToString() + "\n");
                TextData.AppendText("有效平均幅值(不包含0幅值):" + g_roi_all_aver_amp.ToString() + "\n");
                TextData.AppendText("平均幅值(不包含0幅值):" + g_roi_valid_aver_amp.ToString() + "\n\n");
            }
            else if (g_hasData == 6) //ROI完整深度数据
            {
                TextData.AppendText("ROI点云数据:" + Time + "\n");
                //本次展示最后一个ROI的数据，的最后一个点数据
                TextData.AppendText("ROI的ID：" + g_roi_id[g_roi_number - 1].ToString() + "\n");
                TextData.AppendText("指定点深度(单位,MM):" + g_roi_data[g_roi_id[g_roi_number - 1]].distance_data[g_point_count - 1].ToString() + "\n");

                TextData.AppendText("平均深度(单位,MM):" + g_roi_aver_distance.ToString() + "\n");
                TextData.AppendText("最大深度(单位,MM):" + g_roi_max_distance.ToString() + "\n");
                TextData.AppendText("最小深度(单位,MM):" + g_roi_min_distance.ToString() + "\n");
                TextData.AppendText("有效平均幅值(不包含0幅值):" + g_roi_all_aver_amp.ToString() + "\n");
                TextData.AppendText("平均幅值(不包含0幅值):" + g_roi_valid_aver_amp.ToString() + "\n\n");
            }
            else if (g_hasData == 7) //ROI完整深度数据
            {
                TextData.AppendText("ROI点云数据:" + Time + "\n");
                //本次展示最后一个ROI的数学统计数据
                TextData.AppendText("ROI的ID：" + g_roi_id[g_roi_number - 1].ToString() + "\n");
                TextData.AppendText("平均深度(单位,MM):" + g_roi_aver_distance.ToString() + "\n");
                TextData.AppendText("最大深度(单位,MM):" + g_roi_max_distance.ToString() + "\n");
                TextData.AppendText("最小深度(单位,MM):" + g_roi_min_distance.ToString() + "\n");
                TextData.AppendText("有效平均幅值(不包含0幅值):" + g_roi_all_aver_amp.ToString() + "\n");
                TextData.AppendText("平均幅值(不包含0幅值):" + g_roi_valid_aver_amp.ToString() + "\n\n");
            }
            LabFps.Text = g_fps.ToString();
            g_fps = 0;
            g_mutex.ReleaseMutex();
            g_hasData = 0;
        }

        //定时器回调函
        private void DebugTimeOut(Object myObject, EventArgs myEventArgs)
        {
            g_debug_mutex.WaitOne();
            int listLen = StringList.Count;
            for(int i = 0; i < listLen; i++)
            {
                debugText.AppendText(StringList[0]);
                StringList.RemoveAt(0);
            }
            g_debug_mutex.ReleaseMutex();
        }

        //关闭窗口事件
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (g_isConnect)
            {
                if (g_isContinuous)
                {
                    HPS3D_Device.SetRunMode(g_device_id, RUN_MODE_ENUM.RUN_IDLE);
                }
                HPS3D_Device.DisConnect(g_device_id);

            }
        }

        //断开设备
        private void BtnDisconnect_Click(object sender, EventArgs e)
        {
            if (g_isConnect)
            {
                g_isConnect = false;
                HPS3D_Device.DisConnect(g_device_id);
            }
        }

        //清除Debug信息
        private void clearDebugBtn_Click(object sender, EventArgs e)
        {
            debugText.Clear();
        }

        //设置需要获取的数据类型
        private void BtnSetOutput_Click(object sender, EventArgs e)
        {
            if(!g_isConnect)
            {
                MessageBox.Show("请先连接设备!");
                return;
            }
            switch (comboBox1.SelectedItem.ToString()) //获取选择的内容
            {

                case "简单深度数据"://获取简单深度数据，需要进行以下配置
                    if (HPS3D_Device.SetOutputDataType(g_device_id,OUTPUT_TYPE_ENUM.OUTPUT_DISTANCE_SIMPLE) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置简单深度事件失败");
                        return;
                    }
                    //如果开启了ROI需要关闭，开启了哪个就关闭哪个，以下示例为全部关闭
                    for (byte i = 0; i < 8; i++)
                    {
                        if (HPS3D_Device.SetROIEnable(g_device_id, i, false) != RET_STATUS_ENUM.RET_OK)
                        {
                            MessageBox.Show("设置简单深度事件失败");
                            return;
                        }
                    }
                    LabOutput.Text = "简单深度数据";
                    break;

                case "完整深度数据"://获取完整深度数据，需要进行以下配置
                    if (HPS3D_Device.SetOutputDataType(g_device_id, OUTPUT_TYPE_ENUM.OUTPUT_DISTANCE_FULL) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置完整深度事件失败");
                        return;
                    }
                    //如果开启了点云转换，则需要关闭
                    if (HPS3D_Device.SetPointCloudMode(g_device_id, false,POINTCLOUD_MIRROR_MODE_ENUM.MIRROR_DISABLE) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置完整深度事件失败");
                        return;
                    }
                    //如果开启了ROI需要关闭，开启了哪个就关闭哪个，以下示例为全部关闭
                    for (byte i = 0; i < 8; i++)
                    {
                        if (HPS3D_Device.SetROIEnable(g_device_id, i, false) != RET_STATUS_ENUM.RET_OK)
                        {
                            MessageBox.Show("设置完整深度事件失败");
                            return;
                        }
                    }
                    LabOutput.Text = "完整深度数据";
                    break;

                case "幅值数据"://获取幅值数据，需要进行以下配置
                    if (HPS3D_Device.SetOutputDataType(g_device_id, OUTPUT_TYPE_ENUM.OUTPUT_AMPLITUDE) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置幅值事件失败");
                        return;
                    }
                    LabOutput.Text = "幅值数据";
                    break;

                case "完整点云数据"://获取完整点云数据，需要进行以下配置
                    if (HPS3D_Device.SetOutputDataType(g_device_id, OUTPUT_TYPE_ENUM.OUTPUT_DISTANCE_FULL) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置完整点云事件失败");
                        return;
                    }
                    //如果没有开启点云转换，则需要开启
                    if (HPS3D_Device.SetPointCloudMode(g_device_id, true, POINTCLOUD_MIRROR_MODE_ENUM.MIRROR_DISABLE) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置完整点云事件失败");
                        return;
                    }
                    //如果开启了ROI需要关闭，开启了哪个就关闭哪个，以下示例为全部关闭
                    for (byte i = 0; i < 8; i++)
                    {
                        if (HPS3D_Device.SetROIEnable(g_device_id, i, false) != RET_STATUS_ENUM.RET_OK)
                        {
                            MessageBox.Show("设置完整点云事件失败");
                            return;
                        }
                    }
                    LabOutput.Text = "完整点云数据";
                    break;

                case "ROI点云数据"://获取ROI点云数据，需要进行以下配置
                    if (HPS3D_Device.SetOutputDataType(g_device_id, OUTPUT_TYPE_ENUM.OUTPUT_DISTANCE_FULL) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置ROI点云事件失败");
                        return;
                    }
                    //如果没有开启点云转换，则需要开启
                    if (HPS3D_Device.SetPointCloudMode(g_device_id, true, POINTCLOUD_MIRROR_MODE_ENUM.MIRROR_DISABLE) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置ROI点云事件失败");
                        return;
                    }
                    //如果没有开启ROI需要开启（ROI配置需要使用客户端）SDK仅提供ROI使能开关
                    //以下开启ROI 0,注意如果没有使用客户端绘制ROI区域，设置ROi使能将无效
                    if (HPS3D_Device.SetROIEnable(g_device_id, 0, true) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置ROI点云事件失败");
                        return;
                    }
                    LabOutput.Text = "ROI点云数据";
                    break;

                case "ROI完整深度数据"://获取ROI完整深度数据，需要进行以下配置
                    if (HPS3D_Device.SetOutputDataType(g_device_id, OUTPUT_TYPE_ENUM.OUTPUT_DISTANCE_FULL) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置ROI完整深度事件失败");
                        return;
                    }
                    //如果开启了点云转换，则需要关闭
                    if (HPS3D_Device.SetPointCloudMode(g_device_id, false, POINTCLOUD_MIRROR_MODE_ENUM.MIRROR_DISABLE) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置ROI完整深度事件失败");
                        return;
                    }
                    //如果没有开启ROI需要开启（ROI配置需要使用客户端）SDK仅提供ROI使能开关
                    //以下开启ROI 0,注意如果没有使用客户端绘制ROI区域，设置ROi使能将无效
                    if (HPS3D_Device.SetROIEnable(g_device_id, 0, true) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置ROI完整深度事件失败");
                        return;
                    }
                    LabOutput.Text = "ROI完整深度数据";
                    break;

                case "ROI简单深度数据"://获取ROI简单深度数据，需要进行以下配置
                    if (HPS3D_Device.SetOutputDataType(g_device_id, OUTPUT_TYPE_ENUM.OUTPUT_DISTANCE_SIMPLE) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置ROI简单深度事件失败");
                        return;
                    }
                    //如果没有开启ROI需要开启（ROI配置需要使用客户端）SDK仅提供ROI使能开关
                    //以下开启ROI 0,注意如果没有使用客户端绘制ROI区域，设置ROi使能将无效
                    if (HPS3D_Device.SetROIEnable(g_device_id, 0, true) != RET_STATUS_ENUM.RET_OK)
                    {
                        MessageBox.Show("设置ROI简单深度事件失败");
                        return;
                    }
                    LabOutput.Text = "ROI简单深度数据";
                    break;

            }

        }

        //单次测量
        private void BtnSingleMeasure_Click(object sender, EventArgs e)
        {
            if (!g_isConnect)
            {
                MessageBox.Show("请先连接设备!");
                return;
            }
            if (LabOutput.Text == "")
            {
                MessageBox.Show("请设置需要获取的数据类型!");
                return;
            }
            //1.将运行模式设置为单次测量
            if (HPS3D_Device.SetRunMode(g_device_id, RUN_MODE_ENUM.RUN_SINGLE_SHOT) != RET_STATUS_ENUM.RET_OK)
            {
                MessageBox.Show("设置失败，请重试");
                return;
            }
        }

        //配置设备参数，需要确保设备已经正常连接
        //该部分可以使用客户端配置
        //首次运行设备时需要配置参数，之后保存到用户配置后再次运行不需要重新配置
        private void BtnSetDeviceConf_Click(object sender, EventArgs e)
        {
            if (!g_isConnect)
            {
                MessageBox.Show("请先连接设备!");
                return;
            }

            //积分时间根据现场环境和被测物体信号反射强度进行调节（必要）
            if(HPS3D_Device.SetIntegTime(g_device_id, 1000) != RET_STATUS_ENUM.RET_OK)
            {
                MessageBox.Show("设置积分时间失败!");
                return;
            }

            //滤波器配置（可选）
            //1.平滑滤波器配置,根据需要自行选择滤波器类型,以下为关闭
            if (HPS3D_Device.SetSmoothFilter(g_device_id, SMOOTH_FILTER_TYPE_ENUM.SMOOTH_FILTER_DISABLE, 0) != RET_STATUS_ENUM.RET_OK)
            {
                MessageBox.Show("设置平滑滤波器失败!");
                return;
            }
            //2.卡尔曼滤波器，根据需要自行选择滤波器参数,以下为关闭
            if (HPS3D_Device.SetSimpleKalmanFilter(g_device_id, false, 0, 0, 0) != RET_STATUS_ENUM.RET_OK)
            {
                MessageBox.Show("设置卡尔曼滤波器失败!");
                return;
            }

            //距离偏移（可选），以下默认设置为0
            if (HPS3D_Device.SetOffset(g_device_id, 0) != RET_STATUS_ENUM.RET_OK)
            {
                MessageBox.Show("设置距离偏移失败!");
                return;
            }

            //将设置保存到用户配置表,保存后重新上电不会丢失
            if (HPS3D_Device.ProfileSaveToUser(g_device_id) != RET_STATUS_ENUM.RET_OK)
            {
                MessageBox.Show("用户配置表保存失败!");
                return;
            }

            MessageBox.Show("设置成功!");
        }

        //清除测量数据
        private void clearData_Click(object sender, EventArgs e)
        {
            TextData.Clear();
        }

        //连续测量
        private void BtnContinuous_Click(object sender, EventArgs e)
        {
            if (g_isContinuous != true) //开始测量
            {
                if (!g_isConnect)
                {
                    MessageBox.Show("请先连接设备!");
                    return;
                }
                if (LabOutput.Text == "")
                {
                    MessageBox.Show("请设置需要获取的数据类型!");
                    return;
                }
                //将运行模式设置为连续测量模式
                if (HPS3D_Device.SetRunMode(g_device_id, RUN_MODE_ENUM.RUN_CONTINUOUS) != RET_STATUS_ENUM.RET_OK)
                {
                    MessageBox.Show("设置失败，请重试");
                    return;
                }
                g_isContinuous = true;
                BtnContinuous.Text = "停止";
            }
            else //停止测量
            {
                if (HPS3D_Device.SetRunMode(g_device_id, RUN_MODE_ENUM.RUN_IDLE) != RET_STATUS_ENUM.RET_OK)
                {
                    MessageBox.Show("设置失败，请重试");
                    return;
                }
                g_isContinuous = false;
                BtnContinuous.Text = "连续测量";
            }
        }
    }
}
