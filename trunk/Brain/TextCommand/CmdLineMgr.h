#pragma once
#include "BrainSystem.h"
#include "ICmdLineMgr.h"

namespace Ts
{
    class CmdLineMgrImp;

    class BRAINEXPORT CmdLineMgr : public ICmdLineMgr
    {
    public:
        CmdLineMgr();
        virtual ~CmdLineMgr();

    public:
        virtual bool			Parse(int argc, const char* const argv[]);
        virtual bool			Parse(NString optionString);
        virtual bool			AddSupportedOption(CmdOption* pOption);

        virtual CmdOption*		GetRecognizedOptionByName(const NString& name) const;
        virtual CmdOption*		GetSupportedOptionByName(const NString& name) const;

		virtual bool			HasRecognizedOption() const;
        virtual bool			HasUnrecognizedOption() const;
        virtual const NString&  GetUnrecongnizedOption() const;
		virtual NString			GetOptionDescription() const;

    private:
        CmdLineMgrImp*  m_pImp;

    };
}