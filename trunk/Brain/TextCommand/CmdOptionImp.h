#pragma once

namespace Ts
{
    class CmdOption;

    class CmdOptionImp
    {
    public:
        CmdOptionImp(CmdOption* pSelf, const NString& name, const NString& description);
        CmdOptionImp(CmdOption* pSelf, const NString& name, char shortName, const NString& description);
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

    private:
        CmdOption*     m_pSelf;

        NString         m_Name;
        char            m_ShortName;
        NString         m_Description;
        NString         m_Value;
    };
}