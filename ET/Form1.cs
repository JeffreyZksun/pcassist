using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using Assist.SearchEngine;

namespace ET
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            mSearchEngine = new SimpleSearchEngine();
            mDsManager = new DataSourceManager();
            mDataSource = new MemoryDataSource();
            mDsManager.AddDataSource(mDataSource);

            mExtToolMgr = new ExternalToolManager();

            bool bSucc = mExtToolMgr.Load("S:\\Build Tools\\pc\\_ExternalTools.xml");

            if(bSucc)
            {
                List<ExternalTool> extTools = mExtToolMgr.GetAllExternalTools();
                for (int i =0; i < extTools.Count; i++)
                {
                    ExternalTool et = extTools[i];
                    TitleList.Items.Add(et.GetTitle());

                    DataItem dataItem = new DataItem();
                    dataItem.Id = i.ToString();

                    dataItem.Key = et.GetTitle();
                    dataItem.Title = et.GetTitle();
                    dataItem.Value = et.GetCommand() + " " + et.GetParameter();
                    dataItem.Comments = i.ToString(); // save the indes in the comments

                    dataItem.Labels = "";
                    dataItem.AccessCounter = 0;

                    mDataSource.AddDataItem(dataItem);
                }
            }

        }

        ExternalToolManager mExtToolMgr = null;

        SimpleSearchEngine mSearchEngine = null;
        DataSourceManager mDsManager = null;
        MemoryDataSource mDataSource = null;

        List<DataItem> mSearchResult = null;


        private void button1_Click(object sender, EventArgs e)
        {


        }

        private void listBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            outputWindow.Text = "";
            
            ExternalTool et = GetSelectedExternalTool();
            if (et == null)
                return;

            ProcessProxy proxy = new ProcessProxy(et.GetCommand(), et.GetParameter(), et.GetWorkingDirectoty());
            proxy.OutputDataReceived += new DataReceivedEventHandler(proxy_OutputDataReceived);
            proxy.StartProcess();            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Show all
            DoSearch("");

            textSearchBox.Focus();
        }

        private void UpdateList()
        {
            TitleList.Items.Clear();

            foreach (DataItem data in mSearchResult)
            {
                TitleList.Items.Add(data.Title);
            }
        }

        private void TitleList_SelectedIndexChanged(object sender, EventArgs e)
        {
            ExternalTool et = GetSelectedExternalTool();
            if (et == null)
                return;

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

        private ExternalTool GetSelectedExternalTool()
        {
            int iSelectedIndex = TitleList.SelectedIndex;

            if (iSelectedIndex < 0 || iSelectedIndex >= mSearchResult.Count)
                return null;

            Int32 iExternalToolIndex = Int32.Parse(mSearchResult[iSelectedIndex].Comments);
            if (iExternalToolIndex >= 0 && iExternalToolIndex < mExtToolMgr.GetAllExternalTools().Count)
            {
                ExternalTool et = mExtToolMgr.GetAllExternalTools()[iExternalToolIndex];
                return et;
            }

            return null;
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

        private void textSearchBox_TextChanged(object sender, EventArgs e)
        {
            DoSearch(textSearchBox.Text.Trim());
        }

        private void DoSearch(String content)
        {
            ContentFilter filter = new ContentFilter(content);
            List<IFilter> filterList = new List<IFilter>();
            filterList.Add(filter);

            mSearchResult = mSearchEngine.Search(mDsManager, filterList);
            UpdateList();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            Keys k = (Keys)e.KeyValue;

            // Handle "ESC" key
            if (k == Keys.Escape)
            {
                e.Handled = true;

                textSearchBox.Text = "";

                return;
            }

        }

        private void textSearchBox_KeyUp(object sender, KeyEventArgs e)
        {
            Keys k = (Keys)e.KeyValue;

            // Handle "ESC" key
            if (k == Keys.Up || k == Keys.Down)
            {
                //e.Handled = true;

                return;
            }
        }
    }
}
