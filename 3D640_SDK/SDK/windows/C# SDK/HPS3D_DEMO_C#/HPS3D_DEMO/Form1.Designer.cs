namespace HPS3D_DEMO
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.TextPort = new System.Windows.Forms.TextBox();
            this.TextIP = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.LabDeviceSN = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.TextData = new System.Windows.Forms.RichTextBox();
            this.debugText = new System.Windows.Forms.RichTextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.clearDebugBtn = new System.Windows.Forms.Button();
            this.LabFps = new System.Windows.Forms.Label();
            this.LabDeviceVersion = new System.Windows.Forms.Label();
            this.LabSDKVersion = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.BtnConnect = new System.Windows.Forms.Button();
            this.BtnDisconnect = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.BtnSetDeviceConf = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.BtnSingleMeasure = new System.Windows.Forms.Button();
            this.BtnContinuous = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            this.BtnSetOutput = new System.Windows.Forms.Button();
            this.LabOutput = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label14 = new System.Windows.Forms.Label();
            this.clearData = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.TextPort);
            this.groupBox1.Controls.Add(this.TextIP);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(44, 79);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 100);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "以太网配置";
            // 
            // TextPort
            // 
            this.TextPort.Location = new System.Drawing.Point(79, 58);
            this.TextPort.Name = "TextPort";
            this.TextPort.Size = new System.Drawing.Size(100, 21);
            this.TextPort.TabIndex = 2;
            this.TextPort.Text = "12345";
            // 
            // TextIP
            // 
            this.TextIP.Location = new System.Drawing.Point(79, 31);
            this.TextIP.Name = "TextIP";
            this.TextIP.Size = new System.Drawing.Size(100, 21);
            this.TextIP.TabIndex = 2;
            this.TextIP.Text = "192.168.30.202";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 67);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "Port：";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 31);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "IP：";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.clearData);
            this.groupBox3.Controls.Add(this.LabDeviceSN);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label14);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.TextData);
            this.groupBox3.Controls.Add(this.debugText);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.clearDebugBtn);
            this.groupBox3.Controls.Add(this.LabFps);
            this.groupBox3.Controls.Add(this.LabDeviceVersion);
            this.groupBox3.Controls.Add(this.LabSDKVersion);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Location = new System.Drawing.Point(396, 26);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(442, 607);
            this.groupBox3.TabIndex = 10;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "信息输出";
            // 
            // LabDeviceSN
            // 
            this.LabDeviceSN.AutoSize = true;
            this.LabDeviceSN.Font = new System.Drawing.Font("宋体", 12F);
            this.LabDeviceSN.Location = new System.Drawing.Point(198, 89);
            this.LabDeviceSN.Name = "LabDeviceSN";
            this.LabDeviceSN.Size = new System.Drawing.Size(40, 16);
            this.LabDeviceSN.TabIndex = 10;
            this.LabDeviceSN.Text = "    ";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("宋体", 12F);
            this.label5.Location = new System.Drawing.Point(9, 89);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(72, 16);
            this.label5.TabIndex = 9;
            this.label5.Text = "设备SN：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(6, 333);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(96, 16);
            this.label3.TabIndex = 2;
            this.label3.Text = "Debug信息：";
            // 
            // TextData
            // 
            this.TextData.Location = new System.Drawing.Point(9, 161);
            this.TextData.Name = "TextData";
            this.TextData.Size = new System.Drawing.Size(417, 164);
            this.TextData.TabIndex = 1;
            this.TextData.Text = "";
            // 
            // debugText
            // 
            this.debugText.Location = new System.Drawing.Point(6, 364);
            this.debugText.Name = "debugText";
            this.debugText.Size = new System.Drawing.Size(420, 237);
            this.debugText.TabIndex = 1;
            this.debugText.Text = "";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label10.Location = new System.Drawing.Point(9, 111);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(40, 16);
            this.label10.TabIndex = 8;
            this.label10.Text = "FPS:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.Location = new System.Drawing.Point(9, 64);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(136, 16);
            this.label8.TabIndex = 8;
            this.label8.Text = "设备固件版本号：";
            // 
            // clearDebugBtn
            // 
            this.clearDebugBtn.Location = new System.Drawing.Point(341, 335);
            this.clearDebugBtn.Name = "clearDebugBtn";
            this.clearDebugBtn.Size = new System.Drawing.Size(75, 23);
            this.clearDebugBtn.TabIndex = 3;
            this.clearDebugBtn.Text = "清除";
            this.clearDebugBtn.UseVisualStyleBackColor = true;
            this.clearDebugBtn.Click += new System.EventHandler(this.clearDebugBtn_Click);
            // 
            // LabFps
            // 
            this.LabFps.AutoSize = true;
            this.LabFps.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabFps.Location = new System.Drawing.Point(198, 116);
            this.LabFps.Name = "LabFps";
            this.LabFps.Size = new System.Drawing.Size(40, 16);
            this.LabFps.TabIndex = 8;
            this.LabFps.Text = "    ";
            // 
            // LabDeviceVersion
            // 
            this.LabDeviceVersion.AutoSize = true;
            this.LabDeviceVersion.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabDeviceVersion.Location = new System.Drawing.Point(198, 64);
            this.LabDeviceVersion.Name = "LabDeviceVersion";
            this.LabDeviceVersion.Size = new System.Drawing.Size(40, 16);
            this.LabDeviceVersion.TabIndex = 8;
            this.LabDeviceVersion.Text = "    ";
            // 
            // LabSDKVersion
            // 
            this.LabSDKVersion.AutoSize = true;
            this.LabSDKVersion.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.LabSDKVersion.Location = new System.Drawing.Point(198, 36);
            this.LabSDKVersion.Name = "LabSDKVersion";
            this.LabSDKVersion.Size = new System.Drawing.Size(40, 16);
            this.LabSDKVersion.TabIndex = 8;
            this.LabSDKVersion.Text = "    ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(9, 36);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(96, 16);
            this.label4.TabIndex = 8;
            this.label4.Text = "SDK版本号：";
            // 
            // BtnConnect
            // 
            this.BtnConnect.Location = new System.Drawing.Point(261, 108);
            this.BtnConnect.Name = "BtnConnect";
            this.BtnConnect.Size = new System.Drawing.Size(75, 23);
            this.BtnConnect.TabIndex = 11;
            this.BtnConnect.Text = "连接设备";
            this.BtnConnect.UseVisualStyleBackColor = true;
            this.BtnConnect.Click += new System.EventHandler(this.BtnConnect_Click);
            // 
            // BtnDisconnect
            // 
            this.BtnDisconnect.Location = new System.Drawing.Point(123, 590);
            this.BtnDisconnect.Name = "BtnDisconnect";
            this.BtnDisconnect.Size = new System.Drawing.Size(75, 23);
            this.BtnDisconnect.TabIndex = 12;
            this.BtnDisconnect.Text = "断开连接";
            this.BtnDisconnect.UseVisualStyleBackColor = true;
            this.BtnDisconnect.Click += new System.EventHandler(this.BtnDisconnect_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(51, 40);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(101, 12);
            this.label6.TabIndex = 13;
            this.label6.Text = "第一步：连接设备";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(44, 212);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(101, 12);
            this.label7.TabIndex = 14;
            this.label7.Text = "第二步：配置设备";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(44, 259);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(269, 12);
            this.label9.TabIndex = 15;
            this.label9.Text = "该步骤可以使用客户端进行配置，以下将简单演示";
            // 
            // BtnSetDeviceConf
            // 
            this.BtnSetDeviceConf.Location = new System.Drawing.Point(123, 297);
            this.BtnSetDeviceConf.Name = "BtnSetDeviceConf";
            this.BtnSetDeviceConf.Size = new System.Drawing.Size(75, 23);
            this.BtnSetDeviceConf.TabIndex = 16;
            this.BtnSetDeviceConf.Text = "配置传感器";
            this.BtnSetDeviceConf.UseVisualStyleBackColor = true;
            this.BtnSetDeviceConf.Click += new System.EventHandler(this.BtnSetDeviceConf_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(44, 348);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(185, 12);
            this.label11.TabIndex = 17;
            this.label11.Text = "第三步：设置需要获取的数据类型";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(44, 449);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(101, 12);
            this.label12.TabIndex = 18;
            this.label12.Text = "第四步：开始测量";
            // 
            // BtnSingleMeasure
            // 
            this.BtnSingleMeasure.Location = new System.Drawing.Point(77, 500);
            this.BtnSingleMeasure.Name = "BtnSingleMeasure";
            this.BtnSingleMeasure.Size = new System.Drawing.Size(75, 23);
            this.BtnSingleMeasure.TabIndex = 19;
            this.BtnSingleMeasure.Text = "单次测量";
            this.BtnSingleMeasure.UseVisualStyleBackColor = true;
            this.BtnSingleMeasure.Click += new System.EventHandler(this.BtnSingleMeasure_Click);
            // 
            // BtnContinuous
            // 
            this.BtnContinuous.Location = new System.Drawing.Point(239, 500);
            this.BtnContinuous.Name = "BtnContinuous";
            this.BtnContinuous.Size = new System.Drawing.Size(75, 23);
            this.BtnContinuous.TabIndex = 20;
            this.BtnContinuous.Text = "连续测量";
            this.BtnContinuous.UseVisualStyleBackColor = true;
            this.BtnContinuous.Click += new System.EventHandler(this.BtnContinuous_Click);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(42, 555);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(101, 12);
            this.label13.TabIndex = 21;
            this.label13.Text = "第五步：断开设备";
            // 
            // BtnSetOutput
            // 
            this.BtnSetOutput.Location = new System.Drawing.Point(239, 379);
            this.BtnSetOutput.Name = "BtnSetOutput";
            this.BtnSetOutput.Size = new System.Drawing.Size(75, 23);
            this.BtnSetOutput.TabIndex = 22;
            this.BtnSetOutput.Text = "设置";
            this.BtnSetOutput.UseVisualStyleBackColor = true;
            this.BtnSetOutput.Click += new System.EventHandler(this.BtnSetOutput_Click);
            // 
            // LabOutput
            // 
            this.LabOutput.AutoSize = true;
            this.LabOutput.Location = new System.Drawing.Point(123, 420);
            this.LabOutput.Name = "LabOutput";
            this.LabOutput.Size = new System.Drawing.Size(0, 12);
            this.LabOutput.TabIndex = 23;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "简单深度数据",
            "完整深度数据",
            "幅值数据",
            "完整点云数据",
            "ROI点云数据",
            "ROI完整深度数据",
            "ROI简单深度数据"});
            this.comboBox1.Location = new System.Drawing.Point(44, 382);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 20);
            this.comboBox1.TabIndex = 24;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label14.Location = new System.Drawing.Point(9, 137);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(88, 16);
            this.label14.TabIndex = 2;
            this.label14.Text = "测量数据：";
            // 
            // clearData
            // 
            this.clearData.Location = new System.Drawing.Point(341, 136);
            this.clearData.Name = "clearData";
            this.clearData.Size = new System.Drawing.Size(75, 23);
            this.clearData.TabIndex = 11;
            this.clearData.Text = "清除";
            this.clearData.UseVisualStyleBackColor = true;
            this.clearData.Click += new System.EventHandler(this.clearData_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(862, 645);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.LabOutput);
            this.Controls.Add(this.BtnSetOutput);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.BtnContinuous);
            this.Controls.Add(this.BtnSingleMeasure);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.BtnSetDeviceConf);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.BtnDisconnect);
            this.Controls.Add(this.BtnConnect);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox TextPort;
        private System.Windows.Forms.TextBox TextIP;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.RichTextBox debugText;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button clearDebugBtn;
        private System.Windows.Forms.Label LabFps;
        private System.Windows.Forms.Label LabDeviceVersion;
        private System.Windows.Forms.Label LabSDKVersion;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button BtnConnect;
        private System.Windows.Forms.Button BtnDisconnect;
        private System.Windows.Forms.Label LabDeviceSN;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button BtnSetDeviceConf;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button BtnSingleMeasure;
        private System.Windows.Forms.Button BtnContinuous;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Button BtnSetOutput;
        private System.Windows.Forms.Label LabOutput;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.RichTextBox TextData;
        private System.Windows.Forms.Button clearData;
        private System.Windows.Forms.Label label14;
    }
}

