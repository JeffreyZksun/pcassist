using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using NUnit.Framework;
using Assist.SearchEngine;

namespace Assist.SearchEngineUTest
{
    [TestFixture]
    class ContentFilterTest
    {
        [Test]
        public void Constructor()
        {
            ContentFilter filter = new ContentFilter("mail");

            Assert.AreEqual("mail", filter.Content);
        }

        [Test]
        public void GetMatchingFactor_100()
        {
            DataItem dataItem = new DataItem();
            dataItem.Id = "dummyId";

            dataItem.Key = "mk";
            dataItem.Title = "mailTitle";
            dataItem.Value = "this is the value of the mail item";
            dataItem.Comments = "the comments for the mail is added here";

            dataItem.Labels = "mail;dummy";
            dataItem.AccessCounter = 2;


            ContentFilter filter = new ContentFilter("mk");

            UInt32 matchingFactor = filter.GetMatchingFactor(dataItem);

            Assert.AreEqual(100, matchingFactor);
        }

        [Test]
        public void GetMatchingFactor_0()
        {
            DataItem dataItem = new DataItem();
            dataItem.Id = "dummyId";

            dataItem.Key = "mk";
            dataItem.Title = "mailTitle";
            dataItem.Value = "this is the value of the mail item";
            dataItem.Comments = "the comments for the mail is added here";

            dataItem.Labels = "mail;dummy";
            dataItem.AccessCounter = 2;


            ContentFilter filter = new ContentFilter("job");

            UInt32 matchingFactor = filter.GetMatchingFactor(dataItem);

            Assert.AreEqual(0, matchingFactor);
        }

        [Test]
        public void GetMatchingFactor_60()
        {
            DataItem dataItem = new DataItem();
            dataItem.Id = "dummyId";

            dataItem.Key = "mk";
            dataItem.Title = "mailTitle"; //mail
            dataItem.Value = "this is the value of the mail item"; //mail
            dataItem.Comments = "the comments for the mail is added here"; //mail

            dataItem.Labels = "mail;dummy";
            dataItem.AccessCounter = 2;


            ContentFilter filter = new ContentFilter("mail");

            UInt32 matchingFactor = filter.GetMatchingFactor(dataItem);

            Assert.AreEqual(60, matchingFactor);
        }

        [Test]
        public void GetMatchingFactor_20()
        {
            DataItem dataItem = new DataItem();
            dataItem.Id = "dummyId";

            dataItem.Key = "mk";
            dataItem.Title = "mailTitle";
            dataItem.Value = "this is the value of the mail item";
            dataItem.Comments = "the comments for the mail is added here";

            dataItem.Labels = "mail;dummy";
            dataItem.AccessCounter = 2;


            ContentFilter filter = new ContentFilter("title");

            UInt32 matchingFactor = filter.GetMatchingFactor(dataItem);

            Assert.AreEqual(20, matchingFactor);
        }
    }
}
