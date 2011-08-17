using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assist.SearchEngine
{
    public interface ISearchEngine
    {
        /// <summary>
        /// Get the candidate data items from the data source manager.
        /// Return the data items meet the specified condition.
        /// </summary>
        /// <param name="dataSourceMgr"></param>
        /// <param name="filter"></param>
        /// <returns></returns>
        List<DataItem> Search(DataSourceManager dataSourceMgr, List<IFilter> filterList);
    }
}
