#pragma once

#include "CmdOption.h"

namespace Ts
{
    class CmdOption;

    class CmdOptionImp
    {
    public:
        CmdOptionImp(CmdOption* pSelf, const NString& name, const NString& description, CmdOption::EValueType eType);
        CmdOptionImp(CmdOption* pSelf, const NString& name, char shortName, const NString& description,  CmdOption::EValueType eType);
        ~CmdOptionImp();

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

		CmdOption::EValueType GetValueType() const;
		void SetValueType(CmdOption::EValueType eType);

    private:
        CmdOption*					m_pSelf;

        NString						m_Name;
        char						m_ShortName;
        NString						m_Description;
        NString						m_Value;
		CmdOption::EValueType		m_eType;
    };
}