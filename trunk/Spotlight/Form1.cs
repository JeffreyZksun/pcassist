using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Assist.SearchEngine;
using Assist.DataSource;

namespace Spotlight
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            DataSourceManager dataSourceMgr = new DataSourceManager();
            DBDataSource dbSource = new DBDataSource();
            dataSourceMgr.AddDataSource(dbSource);

            //List<DataItem> dataItemList = dbSource.GetDataItems();

            List<IFilter> filetList = new List<IFilter>();
            ContentFilter contentFilter = new ContentFilter("mail");
            filetList.Add(contentFilter);

            SimpleSearchEngine searchEngine = new SimpleSearchEngine();

            List<DataItem> results = searchEngine.Search(dataSourceMgr, filetList);

            contentFilter.Content = "mail";
        }
    }
}
