using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace AHT20_Monitor
{
    public partial class Form1 : Form
    {
        private string[] Pc_IO_Port;
        private SerialPort _port;
        private string temp;
        private string hum;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Pc_IO_Port = SerialPort.GetPortNames();
            cb_Port.Items.AddRange(Pc_IO_Port);

            TempChart.ChartAreas[0].AxisY.Minimum = 25;
            HumChart.ChartAreas[0].AxisY.Minimum = 60;

            //TempChart.ChartAreas[0].AxisY.IsStartedFromZero = true;
           //HumChart.ChartAreas[0].AxisY.IsStartedFromZero = true;
            TempChart.Titles.Add("溫度曲線");
            HumChart.Titles.Add("濕度曲線");
        }

        private void OpenPort(string Comport, int Buadrate, StopBits _stopBit, Parity _parity, int DataBits)  //初始化串列埠
        {
            _port = new SerialPort();
            _port.PortName = Comport;
            _port.BaudRate = Buadrate;
            _port.StopBits = _stopBit;
            _port.Parity = _parity;
            _port.DataBits = DataBits;
            _port.Encoding = Encoding.Default;

            _port.DataReceived += new SerialDataReceivedEventHandler(DataRecivedHander);

            try
            {
                _port.Open();
                timer1.Start();
            }
            catch 
            {
                MessageBox.Show("ERROR");
            }
        }

        private void DataRecivedHander(object sender, SerialDataReceivedEventArgs e)     //確認串列埠狀態並把數據填入佔存區
        {
            try
            {
                if (_port.IsOpen)
                {
                    string data = _port.ReadLine();
                    string[] dataSplit = data.Split(',');
                    temp = dataSplit[0];
                    hum = dataSplit[1];
                }
                else
                {
                    MessageBox.Show($"串口未開啟");
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show($"ERROR\r\n{ex.Message}");
                _port.Close();
                timer1.Stop();
            }
        }



        private void timer1_Tick(object sender, EventArgs e)
        {
            txt_TempData.Text = temp;
            txt_HumData.Text = hum;

            if(temp != null && hum != null)
            {
                double d_temp = Convert.ToDouble(txt_TempData.Text);
                double d_hun = Convert.ToDouble(txt_HumData.Text);

                TempChart.Series[0].Points.AddY(d_temp);
                HumChart.Series[0].Points.AddY(d_hun);
            }

        }

        private void btn_Start_Click(object sender, EventArgs e)
        {
            if (cb_Port.Text != string.Empty && cb_buadRate.Text != string.Empty && cb_parity.Text != string.Empty && txt_DataBits.Text != string.Empty && txt_StopBits.Text != string.Empty)
            {
                StopBits stopbit = StopBits.One;
                Parity parity = Parity.None;

                switch (cb_parity.SelectedItem.ToString())
                {
                    case "None":
                        {
                            parity = Parity.None;
                            break;
                        }
                    case "Even":
                        {
                            parity = Parity.Even;
                            break;
                        }
                    case "Odd":
                        {
                            parity = Parity.Odd;
                            break;
                        }
                }

                switch (txt_StopBits.Text)
                {
                    case "1":
                        {
                            stopbit = StopBits.One;
                            break;
                        }
                    case "2":
                        {
                            stopbit = StopBits.Two;
                            break;
                        }
                    case "0":
                        {
                            stopbit = StopBits.None;
                            break;
                        }
                }
                //OpenPort(cb_Port.SelectedItem.ToString(), Convert.ToInt32(cb_buadRate.SelectedItem.ToString()), StopBits.One, Parity.None, 8);
                OpenPort(cb_Port.SelectedItem.ToString(), Convert.ToInt32(cb_buadRate.SelectedItem.ToString()), stopbit, parity, Convert.ToInt32(txt_DataBits.Text.ToString()));
            }
            else
            {
                MessageBox.Show("輸入條件為空，請重新確認..");
            }
        }

        private void btn_Stop_Click(object sender, EventArgs e)
        {
            _port.Close();
            timer1.Stop();
        }

    }
    }

