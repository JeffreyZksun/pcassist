using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace ET
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        ExternalToolManager mExtToolMgr = new ExternalToolManager();

        private void button1_Click(object sender, EventArgs e)
        {


        }

        private void listBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            outputWindow.Text = "";
            int iSelectedIndex = TitleList.SelectedIndex;

            if (iSelectedIndex >= 0 && iSelectedIndex < mExtToolMgr.GetAllExternalTools().Count)
            {
                ExternalTool et = mExtToolMgr.GetAllExternalTools()[iSelectedIndex];
                if (et != null)
                {
                    ProcessProxy proxy = new ProcessProxy(et.GetCommand(), et.GetParameter(), et.GetWorkingDirectoty());
                    proxy.OutputDataReceived += new DataReceivedEventHandler(proxy_OutputDataReceived);
                    proxy.StartProcess();
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            bool bSucc = mExtToolMgr.Load("S:\\Build Tools\\pc\\_ExternalTools.xml");
            if (bSucc)
            {
                TitleList.Items.Clear();

                List<ExternalTool> extTools = mExtToolMgr.GetAllExternalTools();
                foreach (ExternalTool et in extTools)
                {
                    TitleList.Items.Add(et.GetTitle());
                }
            }
        }

        private void TitleList_SelectedIndexChanged(object sender, EventArgs e)
        {
            int iSelectedIndex = TitleList.SelectedIndex;

            if (iSelectedIndex >= 0 && iSelectedIndex < mExtToolMgr.GetAllExternalTools().Count)
            {
                ExternalTool et = mExtToolMgr.GetAllExternalTools()[iSelectedIndex];
                if (et != null)
                {
                    exToolContent.Text = "";
                    exToolContent.Text += "Title            : " + et.GetTitle();
                    exToolContent.Text += Environment.NewLine + "Command          : " + et.GetCommand();
                    exToolContent.Text += Environment.NewLine + "Parameter        : " + et.GetParameter();
                    exToolContent.Text += Environment.NewLine + "WorkingDirectoty : " + et.GetWorkingDirectoty();
                    //exToolContent.Items.Clear();
                    //exToolContent.Items.Add("Title            : " + et.GetTitle());
                    //exToolContent.Items.Add("Command          : " + et.GetCommand());
                    //exToolContent.Items.Add("Parameter        : " + et.GetParameter());
                    //exToolContent.Items.Add("WorkingDirectoty : " + et.GetWorkingDirectoty());
                }
            }
        }


        void proxy_OutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            // Collect the sort command output.
            if (!String.IsNullOrEmpty(e.Data))
            {
                // Add the text to the collected output.
                //output.Append(Environment.NewLine + e.Data);
                AppendOutputString(e.Data);
            }
        }

        private delegate void InvokeCallback(string msg);

        private void AppendOutputString(String msg)
        {
            if (outputWindow.InvokeRequired)
            {
                InvokeCallback msgCallback = new InvokeCallback(AppendOutputString);
                // If use Invoke here, program will hang.
                outputWindow.BeginInvoke(msgCallback, new object[] { msg });
            }
            else
            {
                outputWindow.Text += (Environment.NewLine + msg);
            }
        }
    }
}
