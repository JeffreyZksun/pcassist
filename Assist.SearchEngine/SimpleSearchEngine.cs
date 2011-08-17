using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assist.SearchEngine
{
    public  class SimpleSearchEngine : ISearchEngine
    {
        #region Implement ISearchEngine
        public List<DataItem> Search(DataSourceManager dataSourceMgr, List<IFilter> filterList)
        {
            if (dataSourceMgr == null || filterList == null)
                return null;

            List<DataItem> results = new List<DataItem>();

            foreach (IDataSource dataSource in dataSourceMgr.DataSources)
            {
                List<DataItem> candidateItems = dataSource.GetDataItems();
                if (candidateItems == null)
                    continue;

                if (filterList.Count == 0)
                    results.AddRange(candidateItems);
                else
                {
                    foreach (IFilter filter in filterList)
                    {
                        if (filter == null)
                            continue;

                        foreach (DataItem dataItem in candidateItems)
                        {
                            if (dataItem == null)
                                continue;

                            UInt32 matchingFactor = filter.GetMatchingFactor(dataItem);
                            if (matchingFactor > 0) // Match
                                results.Add(dataItem);
                        }
                    }
                }
            }

            return results;
        }
        #endregion
    }
}
