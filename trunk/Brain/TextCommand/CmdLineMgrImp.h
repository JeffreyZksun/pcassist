#pragma once

#include <list>
#include <vector>

namespace Ts
{
    class CmdLineMgr;
    class CmdOption;

    class CmdLineMgrImp
    {
    public:
        CmdLineMgrImp(CmdLineMgr* pSelf);
        ~CmdLineMgrImp();

    public:
        bool        Parse(int argc, const char* const argv[]);
        bool        Parse(NString optionString);
        bool        AddSupportedOption(CmdOption* pOption);

        CmdOption*  GetRecognizedOptionByName(const NString& name) const;
        CmdOption*  GetSupportedOptionByName(const NString& name) const;

        bool        HasUnrecognizedOption() const ;
        NString     GetUnrecongnizedOption() const;

    private:
        void        RemovedRecognizedOptions();
        bool        Parse(const std::vector<NString>& options);

    private:
        typedef std::list<CmdOption*> CmdOptionList;

    private:
        CmdLineMgr*     m_pSelf;

        CmdOptionList   m_SupportedOptionsList;
        CmdOptionList   m_RecognizedOptionsList;

        NString         m_UnrecognizedOptions;
    };
}