using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using NUnit.Framework;
using Assist.SearchEngine;

namespace Assist.SearchEngineUTest
{
    [TestFixture]
    class SimpleSearchEngineTest
    {
        [Test]
        public void Search()
        {
            SimpleSearchEngine simpleSearchEngin = new SimpleSearchEngine();
            DataSourceManager dsManager = new DataSourceManager();
            MemoryDataSource dataSource = new MemoryDataSource();
            dsManager.AddDataSource(dataSource);

            // Item 1
            {
                DataItem dataItem = new DataItem();
                dataItem.Id = "dummyId";

                dataItem.Key = "mk";
                dataItem.Title = "mailTitle";
                dataItem.Value = "this is the value of the mail item";
                dataItem.Comments = "the comments for the mail is added here";

                dataItem.Labels = "mail;dummy";
                dataItem.AccessCounter = 2;

                dataSource.AddDataItem(dataItem);
            }

        }
    }
}
