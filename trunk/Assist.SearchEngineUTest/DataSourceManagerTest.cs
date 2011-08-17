using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using NUnit.Framework;
using Assist.SearchEngine;

namespace Assist.SearchEngineUTest
{
    [TestFixture]
    class DataSourceManagerTest
    {
        [Test]
        public void Constructor()
        {
            DataSourceManager dsManager = new DataSourceManager();
            Assert.AreEqual(0, dsManager.DataSources.Count);
        }


        [Test]
        public void AddRemoveDataSource()
        {
            DataSourceManager dsManager = new DataSourceManager();
            MemoryDataSource dataSource = new MemoryDataSource();

            dsManager.AddDataSource(dataSource);
            Assert.AreEqual(1, dsManager.DataSources.Count);

            dsManager.AddDataSource(dataSource);
            Assert.AreEqual(1, dsManager.DataSources.Count);

            dsManager.RemoveDataSource(dataSource.Id);
            Assert.AreEqual(0, dsManager.DataSources.Count);
        }
    }
}
