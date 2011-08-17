using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assist.SearchEngine
{
    public class ContentFilter : IFilter
    {
        #region Data Members
        public String Content { get; set; }
        #endregion

        public ContentFilter(String content)
        {
            Content = content;
        }

        #region Overrides IFilter
        public UInt32 GetMatchingFactor(DataItem item)
        {
            if (Content == null)
                return 100;

            if (item.Key.Equals(Content, StringComparison.CurrentCultureIgnoreCase))
                return 100;

            UInt32 matchingFactor = 0;
            if (SearchUtil.DoesContainStringIngoreCase(item.Key, Content))
                matchingFactor += 20;

            if (SearchUtil.DoesContainStringIngoreCase(item.Title, Content))
                matchingFactor += 20;

            if (SearchUtil.DoesContainStringIngoreCase(item.Value, Content))
                matchingFactor += 20;

            if (SearchUtil.DoesContainStringIngoreCase(item.Comments, Content))
                matchingFactor += 20;

            return matchingFactor;
        }
        #endregion
    }
}
