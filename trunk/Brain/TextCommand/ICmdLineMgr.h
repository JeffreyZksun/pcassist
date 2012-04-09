#pragma once
#include "BrainSystem.h"

namespace Ts
{
    class CmdOption;

    class BRAINEXPORT ICmdLineMgr
    {
    public:
        virtual ~ICmdLineMgr(){}

    public:
        virtual bool			Parse(int argc, const char* const argv[]) = 0;
        virtual bool			Parse(NString optionString) = 0;
        virtual bool			AddSupportedOption(CmdOption* pOption) = 0;

        virtual CmdOption*		GetRecognizedOptionByName(const NString& name) const = 0;
        virtual CmdOption*		GetSupportedOptionByName(const NString& name) const = 0;

		virtual bool			HasRecognizedOption() const = 0;
        virtual bool			HasUnrecognizedOption() const = 0;
		virtual const NString&	GetUnrecongnizedOption() const = 0;

        virtual NString			GetOptionDescription() const = 0;
    };
}