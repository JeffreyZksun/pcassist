using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assist.SearchEngine
{
    public class DataSourceManager
    {
        #region Data members
        public List<IDataSource> DataSources { get; set; }
        #endregion

        public DataSourceManager()
        {
            DataSources = new List<IDataSource>();
        }

        /// <summary>
        /// Add the data source if it has a different id with the existing ones.
        /// </summary>
        /// <param name="dataSource"></param>
        public void AddDataSource(IDataSource dataSource)
        {
            if(!DoesDataSourceExist(dataSource.Id))
                DataSources.Add(dataSource);
        }

        /// <summary>
        /// Remove the data source with the specified id.
        /// </summary>
        /// <param name="dataSourceId"></param>
        public void RemoveDataSource(String dataSourceId)
        {
            foreach (IDataSource item in DataSources)
            {
                if (item.Id.Equals(dataSourceId, StringComparison.CurrentCultureIgnoreCase))
                {
                    DataSources.Remove(item);
                    return;
                }
            }
        }

        #region Private helpers
        /// <summary>
        /// Check if there is the data source with the same id.
        /// </summary>
        /// <param name="dataSourceId"></param>
        /// <returns></returns>
        private bool DoesDataSourceExist(String dataSourceId)
        {
            foreach (IDataSource item in DataSources)
            {
                if (item.Id.Equals(dataSourceId, StringComparison.CurrentCultureIgnoreCase))
                    return true;
            }

            return false;
        }
        #endregion
    }
}
