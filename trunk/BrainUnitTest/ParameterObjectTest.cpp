#include "StdAfx.h"
#include "ParameterObject.h"

TEST(ParameterObject, GetParameter_index)
{
	ParameterObject paraObj;
	Parameter para0(_T("para0"), _T("value0"));
	Parameter para1(_T("para1"), _T("value1"));
	paraObj.AddParameter(para0);
	paraObj.AddParameter(para1);

	Parameter para3;
	bool bExist = paraObj.GetParameter(0, para3);
	EXPECT_EQ(true, bExist);

	bool bmatch = para0.GetName().Compare(para3.GetName()) == 0;
	EXPECT_EQ(true, bmatch);
	bmatch = para0.GetRawValue().Compare(para3.GetRawValue()) == 0;
	EXPECT_EQ(true, bmatch);
}
