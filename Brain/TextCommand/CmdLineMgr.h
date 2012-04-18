#pragma once
#include "BrainSystem.h"
#include "ICmdLineMgr.h"

namespace Ts
{
    class CmdLineMgrImp;

    class BRAINEXPORT CmdLineMgr : public ICmdLineMgr
    {
	public: 
		typedef boost::shared_ptr<CmdLineMgr>		pointer;
		typedef boost::shared_ptr<CmdLineMgrImp>	imp_pointer;

    public:
        virtual ~CmdLineMgr();

		static pointer Create();

	protected:
		CmdLineMgr();

    public:
        virtual bool			Parse(int argc, const char* const argv[]);
        virtual bool			Parse(const NString& optionString);
        virtual bool			AddSupportedOption(CmdOptionPtr pOption);

        virtual CmdOptionPtr	GetRecognizedOptionByName(const NString& name) const;
        virtual CmdOptionPtr	GetSupportedOptionByName(const NString& name) const;

		virtual bool			HasRecognizedOption() const;
        virtual bool			HasUnrecognizedOption() const;
        virtual const NString&  GetUnrecongnizedOption() const;
		virtual NString			GetOptionDescription() const;

    private:
        imp_pointer				m_pImp;

    };
}