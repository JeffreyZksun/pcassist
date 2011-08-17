using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Assist.SearchEngine;

namespace Assist.DataSource
{
    public class DBDataSource : IDataSource
    {
        #region Data members
        private SharedDbTableDataContext mDbContext = new SharedDbTableDataContext();
        #endregion

        #region Implement IDataSource
        public List<DataItem> GetDataItems()
        {
            List<DataItem> dataItemList = new List<DataItem>();

            var myNotes = from item in mDbContext.TBL_Informations
                          where item.Visible == true
                          select new DataItem()
                          {
                              Id = this.Id + ";" + item.ID.ToString()
                              ,
                              Key = Decode(item._Key)
                              ,
                              Title = Decode(item.Title)
                              ,
                              Value = Decode(item.Link)
                              ,
                              Comments = Decode(item.Comments)
                              ,
                              Labels = Decode(item.Category)
                              ,
                              AccessCounter = (UInt32)item.AccessCount
                          };

            try
            {
                dataItemList.AddRange(myNotes);
            }
            catch (System.Exception)
            {
            }

            return dataItemList;
        }

        public bool AddDataItem(DataItem item)
        {
            return false;
        }

        public bool UpdateDataItem(DataItem item)
        {
            return false;
        }

        public bool DeleteDataItem(String itemId)
        {
            return false;
        }

        public String Id
        {
            get
            { 
                return "DBDataSource"; 
            }
            set
            { 
                ; // Do nothing
            }
        }

        #endregion

        #region Encode/Decode - Avoid SQL injection
        // % -- &37;
        private String Encode(String str)
        {
            if (str == null)
                return "";

            String EncodedStr = str.Replace("%", "&37;"); // Replace with the ASCII code.

            return EncodedStr;
        }

        private String Decode(String str)
        {
            if (str == null)
                return "";

            String DecodedStr = str.Replace("&37;", "%"); // Replace with the ASCII code.

            return DecodedStr;
        }

        #endregion


    }
}
