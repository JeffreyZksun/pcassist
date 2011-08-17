using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using NUnit.Framework;
using Assist.SearchEngine;

namespace Assist.SearchEngineUTest
{
    [TestFixture]
    class DataItemTest
    {
        [Test]
        public void Constructor()
        {
            DataItem item = new DataItem();
            Assert.AreEqual("", item.Id);
            Assert.AreEqual("", item.Key);
            Assert.AreEqual("", item.Title);
            Assert.AreEqual("", item.Value);
            Assert.AreEqual("", item.Comments);
            Assert.AreEqual("", item.Labels);
            Assert.AreEqual(0, item.AccessCounter);
        }

        [Test]
        public void CopyConstructor()
        {
            DataItem dataItem = new DataItem();
            dataItem.Id = "dummyId";

            dataItem.Key = "mk";
            dataItem.Title = "mailTitle";
            dataItem.Value = "mailValue";
            dataItem.Comments = "mailComments";

            dataItem.Labels = "mail;dummy";
            dataItem.AccessCounter = 2;

            DataItem newItem = new DataItem(dataItem);

            // Change the original one.
            dataItem.Id = "changed";
            dataItem.Key = "changed";
            dataItem.Title = "changed";
            dataItem.Value = "changed";
            dataItem.Comments = "changed";
            dataItem.Labels = "changed";
            dataItem.AccessCounter = 10;

            // Verify the clone item isn't changed
            Assert.AreEqual("dummyId", newItem.Id);
            Assert.AreEqual("mk", newItem.Key);
            Assert.AreEqual("mailTitle", newItem.Title);
            Assert.AreEqual("mailValue", newItem.Value);
            Assert.AreEqual("mailComments", newItem.Comments);
            Assert.AreEqual("mail;dummy", newItem.Labels);
            Assert.AreEqual(2, newItem.AccessCounter);
        }

        [Test]
        public void CloneFrom()
        {
            DataItem dataItem = new DataItem();
            dataItem.Id = "dummyId";

            dataItem.Key = "mk";
            dataItem.Title = "mailTitle";
            dataItem.Value = "mailValue";
            dataItem.Comments = "mailComments";

            dataItem.Labels = "mail;dummy";
            dataItem.AccessCounter = 2;

            DataItem newItem = new DataItem();
            newItem.CloneFrom(dataItem);

            // Change the original one.
            dataItem.Id = "changed";
            dataItem.Key = "changed";
            dataItem.Title = "changed";
            dataItem.Value = "changed";
            dataItem.Comments = "changed";
            dataItem.Labels = "changed";
            dataItem.AccessCounter = 10;

            // Verify the clone item isn't changed
            Assert.AreEqual("dummyId", newItem.Id);
            Assert.AreEqual("mk", newItem.Key);
            Assert.AreEqual("mailTitle", newItem.Title);
            Assert.AreEqual("mailValue", newItem.Value);
            Assert.AreEqual("mailComments", newItem.Comments);
            Assert.AreEqual("mail;dummy", newItem.Labels);
            Assert.AreEqual(2, newItem.AccessCounter);
        }

        [Test]
        public void Properties()
        {
            DataItem dataItem = new DataItem();
            dataItem.Id = "dummyId";

            dataItem.Key = "mk";
            dataItem.Title = "mailTitle";
            dataItem.Value = "mailValue";
            dataItem.Comments = "mailComments";

            dataItem.Labels = "mail;dummy";
            dataItem.AccessCounter = 2;

            // Change the original one.
            dataItem.Id = "changed";
            dataItem.Key = "changed";
            dataItem.Title = "changed";
            dataItem.Value = "changed";
            dataItem.Comments = "changed";
            dataItem.Labels = "changed";
            dataItem.AccessCounter = 10;

            // Verify the changes
            Assert.AreEqual("changed", dataItem.Id);
            Assert.AreEqual("changed", dataItem.Key);
            Assert.AreEqual("changed", dataItem.Title);
            Assert.AreEqual("changed", dataItem.Value);
            Assert.AreEqual("changed", dataItem.Comments);
            Assert.AreEqual("changed", dataItem.Labels);
            Assert.AreEqual(10, dataItem.AccessCounter);
        }
    }
}
