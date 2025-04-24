
namespace AHT20_Monitor
{
    partial class Form1
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置受控資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
        /// 這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.txt_StopBits = new System.Windows.Forms.TextBox();
            this.txt_DataBits = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.cb_Port = new System.Windows.Forms.ComboBox();
            this.cb_parity = new System.Windows.Forms.ComboBox();
            this.cb_buadRate = new System.Windows.Forms.ComboBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.TempChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.HumChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.btn_Start = new Sunny.UI.UIButton();
            this.btn_Stop = new Sunny.UI.UIButton();
            this.txt_TempData = new Sunny.UI.UITextBox();
            this.txt_HumData = new Sunny.UI.UITextBox();
            this.uiSymbolLabel1 = new Sunny.UI.UISymbolLabel();
            this.uiSymbolLabel2 = new Sunny.UI.UISymbolLabel();
            ((System.ComponentModel.ISupportInitialize)(this.TempChart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.HumChart)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label1.Location = new System.Drawing.Point(12, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(48, 19);
            this.label1.TabIndex = 1;
            this.label1.Text = "PORT";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label2.Location = new System.Drawing.Point(12, 54);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 19);
            this.label2.TabIndex = 2;
            this.label2.Text = "鮑率";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label3.Location = new System.Drawing.Point(12, 95);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(54, 19);
            this.label3.TabIndex = 3;
            this.label3.Text = "數據位";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label4.Location = new System.Drawing.Point(12, 144);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(54, 19);
            this.label4.TabIndex = 4;
            this.label4.Text = "校驗位";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label5.Location = new System.Drawing.Point(12, 187);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(54, 19);
            this.label5.TabIndex = 5;
            this.label5.Text = "停止位";
            // 
            // txt_StopBits
            // 
            this.txt_StopBits.Location = new System.Drawing.Point(79, 184);
            this.txt_StopBits.Name = "txt_StopBits";
            this.txt_StopBits.Size = new System.Drawing.Size(121, 22);
            this.txt_StopBits.TabIndex = 7;
            this.txt_StopBits.Text = "1";
            // 
            // txt_DataBits
            // 
            this.txt_DataBits.Location = new System.Drawing.Point(79, 92);
            this.txt_DataBits.Name = "txt_DataBits";
            this.txt_DataBits.Size = new System.Drawing.Size(121, 22);
            this.txt_DataBits.TabIndex = 9;
            this.txt_DataBits.Text = "8";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(217, 290);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(32, 12);
            this.label7.TabIndex = 11;
            this.label7.Text = "Temp";
            // 
            // cb_Port
            // 
            this.cb_Port.FormattingEnabled = true;
            this.cb_Port.Location = new System.Drawing.Point(80, 18);
            this.cb_Port.Name = "cb_Port";
            this.cb_Port.Size = new System.Drawing.Size(121, 20);
            this.cb_Port.TabIndex = 22;
            // 
            // cb_parity
            // 
            this.cb_parity.FormattingEnabled = true;
            this.cb_parity.Items.AddRange(new object[] {
            "None",
            "Odd",
            "Even"});
            this.cb_parity.Location = new System.Drawing.Point(80, 142);
            this.cb_parity.Name = "cb_parity";
            this.cb_parity.Size = new System.Drawing.Size(121, 20);
            this.cb_parity.TabIndex = 23;
            this.cb_parity.Text = "None";
            // 
            // cb_buadRate
            // 
            this.cb_buadRate.FormattingEnabled = true;
            this.cb_buadRate.Items.AddRange(new object[] {
            "9600",
            "57600",
            "115200"});
            this.cb_buadRate.Location = new System.Drawing.Point(80, 52);
            this.cb_buadRate.Name = "cb_buadRate";
            this.cb_buadRate.Size = new System.Drawing.Size(121, 20);
            this.cb_buadRate.TabIndex = 24;
            this.cb_buadRate.Text = "115200";
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // TempChart
            // 
            this.TempChart.BackColor = System.Drawing.Color.DarkGray;
            chartArea1.Name = "ChartArea1";
            this.TempChart.ChartAreas.Add(chartArea1);
            legend1.Enabled = false;
            legend1.Name = "Legend1";
            this.TempChart.Legends.Add(legend1);
            this.TempChart.Location = new System.Drawing.Point(190, 18);
            this.TempChart.Name = "TempChart";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series1.Color = System.Drawing.Color.Blue;
            series1.Legend = "Legend1";
            series1.Name = "Series1";
            series1.YValuesPerPoint = 4;
            this.TempChart.Series.Add(series1);
            this.TempChart.Size = new System.Drawing.Size(642, 207);
            this.TempChart.TabIndex = 25;
            this.TempChart.Text = "chart1";
            // 
            // HumChart
            // 
            this.HumChart.BackColor = System.Drawing.Color.DarkGray;
            chartArea2.Name = "ChartArea1";
            this.HumChart.ChartAreas.Add(chartArea2);
            legend2.Enabled = false;
            legend2.Name = "Legend1";
            this.HumChart.Legends.Add(legend2);
            this.HumChart.Location = new System.Drawing.Point(221, 231);
            this.HumChart.Name = "HumChart";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series2.Color = System.Drawing.Color.Blue;
            series2.Legend = "Legend1";
            series2.Name = "Series1";
            this.HumChart.Series.Add(series2);
            this.HumChart.Size = new System.Drawing.Size(642, 207);
            this.HumChart.TabIndex = 26;
            this.HumChart.Text = "chart1";
            // 
            // btn_Start
            // 
            this.btn_Start.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btn_Start.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_Start.Location = new System.Drawing.Point(36, 232);
            this.btn_Start.MinimumSize = new System.Drawing.Size(1, 1);
            this.btn_Start.Name = "btn_Start";
            this.btn_Start.Radius = 20;
            this.btn_Start.Size = new System.Drawing.Size(151, 25);
            this.btn_Start.TabIndex = 27;
            this.btn_Start.Text = "START";
            this.btn_Start.TipsFont = new System.Drawing.Font("新細明體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_Start.Click += new System.EventHandler(this.btn_Start_Click);
            // 
            // btn_Stop
            // 
            this.btn_Stop.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btn_Stop.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_Stop.Location = new System.Drawing.Point(36, 277);
            this.btn_Stop.MinimumSize = new System.Drawing.Size(1, 1);
            this.btn_Stop.Name = "btn_Stop";
            this.btn_Stop.Radius = 20;
            this.btn_Stop.Size = new System.Drawing.Size(151, 25);
            this.btn_Stop.TabIndex = 28;
            this.btn_Stop.Text = "STOP";
            this.btn_Stop.TipsFont = new System.Drawing.Font("新細明體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_Stop.Click += new System.EventHandler(this.btn_Stop_Click);
            // 
            // txt_TempData
            // 
            this.txt_TempData.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.txt_TempData.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.txt_TempData.Location = new System.Drawing.Point(80, 346);
            this.txt_TempData.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txt_TempData.MinimumSize = new System.Drawing.Size(1, 16);
            this.txt_TempData.Name = "txt_TempData";
            this.txt_TempData.Padding = new System.Windows.Forms.Padding(5);
            this.txt_TempData.Radius = 20;
            this.txt_TempData.ShowText = false;
            this.txt_TempData.Size = new System.Drawing.Size(150, 29);
            this.txt_TempData.TabIndex = 29;
            this.txt_TempData.TextAlignment = System.Drawing.ContentAlignment.MiddleLeft;
            this.txt_TempData.Watermark = "";
            // 
            // txt_HumData
            // 
            this.txt_HumData.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.txt_HumData.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.txt_HumData.Location = new System.Drawing.Point(79, 385);
            this.txt_HumData.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txt_HumData.MinimumSize = new System.Drawing.Size(1, 16);
            this.txt_HumData.Name = "txt_HumData";
            this.txt_HumData.Padding = new System.Windows.Forms.Padding(5);
            this.txt_HumData.Radius = 20;
            this.txt_HumData.ShowText = false;
            this.txt_HumData.Size = new System.Drawing.Size(150, 29);
            this.txt_HumData.TabIndex = 30;
            this.txt_HumData.TextAlignment = System.Drawing.ContentAlignment.MiddleLeft;
            this.txt_HumData.Watermark = "";
            // 
            // uiSymbolLabel1
            // 
            this.uiSymbolLabel1.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.uiSymbolLabel1.Location = new System.Drawing.Point(0, 343);
            this.uiSymbolLabel1.MinimumSize = new System.Drawing.Size(1, 1);
            this.uiSymbolLabel1.Name = "uiSymbolLabel1";
            this.uiSymbolLabel1.Size = new System.Drawing.Size(74, 35);
            this.uiSymbolLabel1.Symbol = 362151;
            this.uiSymbolLabel1.TabIndex = 31;
            this.uiSymbolLabel1.Text = "Temp";
            // 
            // uiSymbolLabel2
            // 
            this.uiSymbolLabel2.Font = new System.Drawing.Font("新細明體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.uiSymbolLabel2.Location = new System.Drawing.Point(0, 379);
            this.uiSymbolLabel2.MinimumSize = new System.Drawing.Size(1, 1);
            this.uiSymbolLabel2.Name = "uiSymbolLabel2";
            this.uiSymbolLabel2.Size = new System.Drawing.Size(74, 35);
            this.uiSymbolLabel2.Symbol = 363293;
            this.uiSymbolLabel2.TabIndex = 32;
            this.uiSymbolLabel2.Text = "Hum  ";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.ClientSize = new System.Drawing.Size(875, 462);
            this.Controls.Add(this.uiSymbolLabel2);
            this.Controls.Add(this.uiSymbolLabel1);
            this.Controls.Add(this.txt_HumData);
            this.Controls.Add(this.txt_TempData);
            this.Controls.Add(this.btn_Stop);
            this.Controls.Add(this.btn_Start);
            this.Controls.Add(this.HumChart);
            this.Controls.Add(this.TempChart);
            this.Controls.Add(this.cb_buadRate);
            this.Controls.Add(this.cb_parity);
            this.Controls.Add(this.cb_Port);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.txt_DataBits);
            this.Controls.Add(this.txt_StopBits);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "SHT20 Monitor";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.TempChart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.HumChart)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txt_StopBits;
        private System.Windows.Forms.TextBox txt_DataBits;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox cb_Port;
        private System.Windows.Forms.ComboBox cb_parity;
        protected System.Windows.Forms.ComboBox cb_buadRate;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.DataVisualization.Charting.Chart HumChart;
        private System.Windows.Forms.DataVisualization.Charting.Chart TempChart;
        private Sunny.UI.UIButton btn_Start;
        private Sunny.UI.UIButton btn_Stop;
        private Sunny.UI.UITextBox txt_TempData;
        private Sunny.UI.UITextBox txt_HumData;
        private Sunny.UI.UISymbolLabel uiSymbolLabel1;
        private Sunny.UI.UISymbolLabel uiSymbolLabel2;
    }
}

