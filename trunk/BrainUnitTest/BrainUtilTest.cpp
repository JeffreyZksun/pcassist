#include "StdAfx.h"
#include "BrainUtil.h"

TEST(BrainUtilTest, DoesFileorFolderExist_1)
{
	bool bExist = BrainUtil::DoesFileorFolderExist(_T("C:\\"));
	EXPECT_EQ(true, bExist);
}

TEST(BrainUtilTest, DoesFileorFolderExist_2)
{
	bool bExist = BrainUtil::DoesFileorFolderExist(_T("CB:\\"));
	EXPECT_EQ(false, bExist);
}
