using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assist.SearchEngine
{
    public class MemoryDataSource : IDataSource
    {
        #region Data members
        private List<DataItem> mDataItemList = new List<DataItem>();
        private UInt32 mItemIndex = 0;
        private String mId = "MemoryDataSource";
        #endregion

        #region Implement IDataSource
        public List<DataItem> GetDataItems()
        {
            List<DataItem> clonedItemList = new List<DataItem>();

            foreach (DataItem tempItem in mDataItemList)
            {
                DataItem newItem = new DataItem(tempItem);
                clonedItemList.Add(newItem);
            }

            return clonedItemList;
        }

        public bool AddDataItem(DataItem item)
        {
            item.Id = Id + mItemIndex.ToString();
            DataItem newItem = new DataItem(item);

            mDataItemList.Add(newItem);
            mItemIndex++;

            return true;
        }

        public bool UpdateDataItem(DataItem item)
        {
            foreach (DataItem tempItem in mDataItemList)
            {
                if (tempItem.Id.Equals(item.Id, StringComparison.CurrentCultureIgnoreCase))
                {
                    tempItem.CloneFrom(item);
                    return true;
                }
            }

            return false;
        }

        public bool DeleteDataItem(String itemId)
        {
            foreach (DataItem tempItem in mDataItemList)
            {
                if (tempItem.Id.Equals(itemId, StringComparison.CurrentCultureIgnoreCase))
                {
                    mDataItemList.Remove(tempItem);
                    return true;
                }
            }

            return false;
        }

        public String Id
        {
            get
            {
                return mId;
            }
            set
            {
                mId = value;
            }
        }
        #endregion
    }
}
