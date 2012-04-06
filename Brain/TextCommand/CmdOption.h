#pragma once

#include "BrainSystem.h"

namespace Ts
{
    class CmdOptionImp;

    class BRAINEXPORT CmdOption
    {
	public:
		enum EValueType
		{
			eNoValue,
			eString
		};

    public:
        CmdOption(const NString& name, const NString& description, EValueType eType = eString);
        CmdOption(const NString& name, char shortName, const NString& description, EValueType eType = eString);
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

		CmdOption::EValueType GetValueType() const;
		void SetValueType(CmdOption::EValueType eType);

    private:
        CmdOptionImp*  m_pImp;
    };
}