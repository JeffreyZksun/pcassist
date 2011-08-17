using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assist.SearchEngine
{
    public interface IFilter
    {
        /// <summary>
        /// Detect whether the passed in item meet the condition. 
        /// Return a number between 0 and 100 to indicate the matching factor.
        /// 0 means it is totally not matched. 100 means exact match.
        /// </summary>
        /// <param name="item">The items to be matched</param>
        /// <returns>The factor between 0 and 100</returns>
        UInt32 GetMatchingFactor(DataItem item);
    }
}
