using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using NUnit.Framework;
using Assist.SearchEngine;

namespace Assist.SearchEngineUTest
{
    [TestFixture]
    class MemoryDataSourceTest
    {
        [Test]
        public void Constructor()
        {
            MemoryDataSource dataSource = new MemoryDataSource();

            Assert.AreEqual(0, dataSource.GetDataItems().Count);
        }

        [Test]
        public void AddDeleteDataItem()
        {
            MemoryDataSource dataSource = new MemoryDataSource();

            // Item 1
            DataItem dataItem1 = new DataItem();
            dataItem1.Id = "dummyId";

            dataItem1.Key = "mk";
            dataItem1.Title = "mailTitle";
            dataItem1.Value = "this is the value of the mail item";
            dataItem1.Comments = "the comments for the mail is added here";

            dataItem1.Labels = "mail;dummy";
            dataItem1.AccessCounter = 2;

            dataSource.AddDataItem(dataItem1);

            Assert.AreEqual(1, dataSource.GetDataItems().Count);

            // Item 2
            DataItem dataItem2 = new DataItem();
            dataItem2.Id = "dummyId";

            dataItem2.Key = "mk";
            dataItem2.Title = "mailTitle";
            dataItem2.Value = "this is the value of the mail item";
            dataItem2.Comments = "the comments for the mail is added here";

            dataItem2.Labels = "mail;dummy";
            dataItem2.AccessCounter = 2;

            dataSource.AddDataItem(dataItem2);

            Assert.AreEqual(2, dataSource.GetDataItems().Count);


            bool bSucc = dataSource.DeleteDataItem(dataSource.GetDataItems()[0].Id);

            Assert.AreEqual(true, bSucc);
            Assert.AreEqual(1, dataSource.GetDataItems().Count);
        }

        [Test]
        public void AddDataItem()
        {
            MemoryDataSource dataSource = new MemoryDataSource();

            // Item 1
            DataItem dataItem1 = new DataItem();
            dataItem1.Id = "dummyId";

            dataItem1.Key = "mk";
            dataItem1.Title = "mailTitle";
            dataItem1.Value = "this is the value of the mail item";
            dataItem1.Comments = "the comments for the mail is added here";

            dataItem1.Labels = "mail;dummy";
            dataItem1.AccessCounter = 2;

            bool bSucc = dataSource.AddDataItem(dataItem1);

            Assert.AreEqual(true, bSucc);

            dataItem1.Key = "newKey";

            // Verify the data isn't changed.
            Assert.AreEqual("mk", dataSource.GetDataItems()[0].Key);
        }

        [Test]
        public void UpdateDataItem()
        {
            MemoryDataSource dataSource = new MemoryDataSource();

            // Item 1
            DataItem dataItem1 = new DataItem();
            dataItem1.Id = "dummyId";

            dataItem1.Key = "mk";
            dataItem1.Title = "mailTitle";
            dataItem1.Value = "this is the value of the mail item";
            dataItem1.Comments = "the comments for the mail is added here";

            dataItem1.Labels = "mail;dummy";
            dataItem1.AccessCounter = 2;

            dataSource.AddDataItem(dataItem1);

            dataItem1.Key = "newKey";

            bool bSucc = dataSource.UpdateDataItem(dataItem1);

            Assert.AreEqual(true, bSucc);

            Assert.AreEqual("newKey", dataSource.GetDataItems()[0].Key);
        }

        [Test]
        public void GetDataItems()
        {
            MemoryDataSource dataSource = new MemoryDataSource();

            // Item 1
            DataItem dataItem1 = new DataItem();
            dataItem1.Id = "dummyId";

            dataItem1.Key = "mk";
            dataItem1.Title = "mailTitle";
            dataItem1.Value = "this is the value of the mail item";
            dataItem1.Comments = "the comments for the mail is added here";

            dataItem1.Labels = "mail;dummy";
            dataItem1.AccessCounter = 2;

            dataSource.AddDataItem(dataItem1);

            List<DataItem> itemList = dataSource.GetDataItems();
            Assert.AreEqual(1, itemList.Count);

            itemList[0].Key = "newKey";

            // Verify the data isn't changed.
            Assert.AreEqual("mk", dataSource.GetDataItems()[0].Key);
        }

        [Test]
        public void Id()
        {
            MemoryDataSource dataSource = new MemoryDataSource();

            Assert.AreEqual("MemoryDataSource", dataSource.Id);

            dataSource.Id = "Changed";

            Assert.AreEqual("Changed", dataSource.Id);

        }
    }
}
