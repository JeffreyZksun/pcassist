#pragma once
#include "BrainSystem.h"

namespace Ts
{
    class CmdOption;

	typedef boost::shared_ptr<CmdOption>	CmdOptionPtr;

    class BRAINEXPORT ICmdLineMgr
    {
    public:
        virtual ~ICmdLineMgr(){}

    public:
        virtual bool			Parse(int argc, const char* const argv[]) = 0;
        virtual bool			Parse(const NString& optionString) = 0;
        virtual bool			AddSupportedOption(CmdOptionPtr pOption) = 0;

        virtual CmdOptionPtr	GetRecognizedOptionByName(const NString& name) const = 0;
        virtual CmdOptionPtr	GetSupportedOptionByName(const NString& name) const = 0;

		virtual bool			HasRecognizedOption() const = 0;
        virtual bool			HasUnrecognizedOption() const = 0;
		virtual const NString&	GetUnrecongnizedOption() const = 0;

        virtual NString			GetOptionDescription() const = 0;
    };
}