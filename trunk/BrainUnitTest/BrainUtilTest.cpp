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

// Test the basic group
TEST(BrainUtilTest, ExtractSubItems_1)
{
    CString strGroup = _T(" {item 1} {item 2} {item 3} ");
    std::vector<CString> subItems;
    
    BrainUtil::ExtractSubItems(strGroup, subItems);

    EXPECT_EQ(3, subItems.size());

    bool bMatch = subItems[1].Compare(_T("item 2")) == 0;
    EXPECT_EQ(true, bMatch);
}

// Test dummy chars outside {}
TEST(BrainUtilTest, ExtractSubItems_2)
{
    CString strGroup = _T(" {}-{  item 2  } x {item 3} dummy");
    std::vector<CString> subItems;

    BrainUtil::ExtractSubItems(strGroup, subItems);

    EXPECT_EQ(3, subItems.size());

    bool bMatch = subItems[1].Compare(_T("  item 2  ")) == 0;
    EXPECT_EQ(true, bMatch);

    bMatch = subItems[0].Compare(_T("")) == 0;
    EXPECT_EQ(true, bMatch);
}

// Test the control chars \t \r \n
TEST(BrainUtilTest, ExtractSubItems_3)
{
    CString strGroup = _T(" {item 1} \t {item 2} \r\n {item 3} ");
    std::vector<CString> subItems;

    BrainUtil::ExtractSubItems(strGroup, subItems);

    EXPECT_EQ(3, subItems.size());

    bool bMatch = subItems[0].Compare(_T("item 1")) == 0;
    EXPECT_EQ(true, bMatch);

    bMatch = subItems[1].Compare(_T("item 2")) == 0;
    EXPECT_EQ(true, bMatch);

    bMatch = subItems[2].Compare(_T("item 3")) == 0;
    EXPECT_EQ(true, bMatch);

}


