using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assist.SearchEngine
{
    class SearchUtil
    {
        public static bool DoesContainStringIngoreCase(String str, String substr)
        {
            if (str == null || substr == null)
                return false;

            String tempStr = str.ToUpper();
            String tempSubstr = substr.ToUpper();
            return tempStr.Contains(tempSubstr);
        }
    }
}
