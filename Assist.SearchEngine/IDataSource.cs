using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assist.SearchEngine
{
    public interface IDataSource
    {
        /// <summary>
        /// Get all the data items provided by this data source.
        /// The returned data items are cloned from the data source.
        /// The changes made to them won't change the underlying data source.
        /// </summary>
        /// <returns>The cloned data items</returns>
        List<DataItem> GetDataItems();

        /// <summary>
        /// Add a new data item to this data source.
        /// The data source will make a clone from the passed in data item and
        /// generate a new Id.
        /// The generated id will be assigned to the passed in data item.
        /// </summary>
        /// <param name="item">The item to be added</param>
        /// <returns>True if success. Otherwise, false.</returns>
        bool AddDataItem(DataItem item);

        /// <summary>
        /// Update the data item. The passed in data item contains the new data.
        /// </summary>
        /// <param name="item">True if success. Otherwise, false.</param>
        /// <returns>True if success. Otherwise, false.</returns>
        bool UpdateDataItem(DataItem item);

        /// <summary>
        /// Delete the data item specified by the id.
        /// </summary>
        /// <param name="itemId"></param>
        /// <returns>True if success. Otherwise, false.</returns>
        bool DeleteDataItem(String itemId);

        /// <summary>
        /// A unique string to distinguish itself from others.
        /// </summary>
        String Id { get; set; }
    }
}
