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
	typedef boost::shared_ptr<CmdOption>	CmdOptionPtr;
	typedef boost::weak_ptr<CmdLineMgr>     CmdLineMgrBackPtr;

    class CmdLineMgrImp
    {
    public:
		CmdLineMgrImp(CmdLineMgrBackPtr pSelf);
        ~CmdLineMgrImp();

    public:
        bool			Parse(int argc, const char* const argv[]);
        bool			Parse(const NString& optionString);
        bool			AddSupportedOption(CmdOptionPtr pOption);

        CmdOptionPtr	GetRecognizedOptionByName(const NString& name) const;
        CmdOptionPtr	GetSupportedOptionByName(const NString& name) const;

		bool			HasRecognizedOption() const;
        bool			HasUnrecognizedOption() const ;
        const NString&  GetUnrecongnizedOption() const;

		NString			GetOptionDescription() const;

    private:
        void			RemovedRecognizedOptions();
        bool			Parse(const std::vector<NString>& options);

		void			PopulateOptionsDescription(boost::program_options::options_description& optionDesc) const;

    private:
        typedef std::list<CmdOptionPtr> CmdOptionList;

    private:
        CmdLineMgrBackPtr m_pSelf;

        CmdOptionList   m_SupportedOptionsList;
        CmdOptionList   m_RecognizedOptionsList;

        NString         m_UnrecognizedOptions;
    };
}