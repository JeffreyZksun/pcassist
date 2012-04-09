#pragma once

#include <list>
#include <vector>

namespace boost
{ 
	namespace program_options
	{
		class options_description;
	}
}

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
        bool			Parse(int argc, const char* const argv[]);
        bool			Parse(NString optionString);
        bool			AddSupportedOption(CmdOption* pOption);

        CmdOption*		GetRecognizedOptionByName(const NString& name) const;
        CmdOption*		GetSupportedOptionByName(const NString& name) const;

		bool			HasRecognizedOption() const;
        bool			HasUnrecognizedOption() const ;
        const NString&  GetUnrecongnizedOption() const;

		NString			GetOptionDescription() const;

    private:
        void			RemovedRecognizedOptions();
        bool			Parse(const std::vector<NString>& options);

		void			PopulateOptionsDescription(boost::program_options::options_description& optionDesc) const;

    private:
        typedef std::list<CmdOption*> CmdOptionList;

    private:
        CmdLineMgr*     m_pSelf;

        CmdOptionList   m_SupportedOptionsList;
        CmdOptionList   m_RecognizedOptionsList;

        NString         m_UnrecognizedOptions;
    };
}