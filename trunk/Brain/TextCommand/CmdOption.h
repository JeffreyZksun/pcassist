#pragma once

#include "BrainSystem.h"

namespace Ts
{
    class CmdOptionImp;

    class BRAINEXPORT CmdOption
    {
    public:
        CmdOption(const NString& name, const NString& description);
        CmdOption(const NString& name, char shortName, const NString& description);
        ~CmdOption();

    public:
        NString GetLongAndShortName() const;

        const NString& GetName() const;
        void SetName(const NString& name);

        char GetShortName() const;
        void SetShortName(char shortName);

        const NString& GetDescription() const;
        void SetDescription(const NString& description);

        const NString& GetValue() const;
        void SetValue(const NString& value);

    private:
        CmdOptionImp*  m_pImp;
    };
}