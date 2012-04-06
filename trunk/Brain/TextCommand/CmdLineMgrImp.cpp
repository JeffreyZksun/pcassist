#include "stdafx.h"

#include "CmdLineMgrImp.h"
#include "CmdOption.h"
#include <boost/program_options.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <iostream>

namespace po = boost::program_options;

using namespace Ts;


CmdLineMgrImp::CmdLineMgrImp(CmdLineMgr* pSelf) : m_pSelf(pSelf), m_SupportedOptionsList()
{

}

CmdLineMgrImp::~CmdLineMgrImp()
{
    for(CmdOptionList::iterator it = m_SupportedOptionsList.begin(); it != m_SupportedOptionsList.end(); ++it)
    {
        delete (*it);
        *it = NULL;
    }
    m_SupportedOptionsList.clear();

    RemovedRecognizedOptions();
}

bool CmdLineMgrImp::Parse(int argc, const char* const argv[])
{
    // Skip the program name in argv[0]
    std::vector<NString> options = po::detail::make_vector<char, const char* const*>(argv+1, argv+argc+!argc);

    return Parse(options);
}

bool CmdLineMgrImp::Parse(NString optionString)
{
    std::vector<NString> options = po::split_unix(optionString);
    return Parse(options);
}

bool CmdLineMgrImp::Parse(const std::vector<NString>& options)
{
    try
    {
        RemovedRecognizedOptions();
        m_UnrecognizedOptions.clear();

        po::options_description optionDesc("Allowed options");

        for(CmdOptionList::const_iterator it = m_SupportedOptionsList.begin(); it != m_SupportedOptionsList.end(); ++it)
        {
			switch((*it)->GetValueType())
			{
			case CmdOption::eNoValue:
				optionDesc.add_options()((*it)->GetLongAndShortName().c_str(), (*it)->GetDescription().c_str());
				break;
			case CmdOption::eString:
				optionDesc.add_options()((*it)->GetLongAndShortName().c_str(), po::value<NString>(), (*it)->GetDescription().c_str());
				break;
			default:
				optionDesc.add_options()((*it)->GetLongAndShortName().c_str(), po::value<NString>(), (*it)->GetDescription().c_str());
				break;				
			}
        }

        po::variables_map vm;
        int style = po::command_line_style::unix_style 
            | po::command_line_style::case_insensitive 
            | po::command_line_style::allow_slash_for_short;  // Allow "/" in short options

        po::parsed_options parsedOptions = po::command_line_parser(options).style(style)
            .options(optionDesc).allow_unregistered().run();

        po::store(parsedOptions, vm);
        po::notify(vm);

        for (po::variables_map::iterator it = vm.begin(); it != vm.end(); ++it)
        {
            CmdOption * pCmdOption = GetSupportedOptionByName(it->first.c_str());

            if(pCmdOption != NULL)
            {
                pCmdOption->SetValue(it->second.as<NString>());
                m_RecognizedOptionsList.push_back(pCmdOption);
            }
        }

        bool bFirst = true;
        std::vector<NString> vecUnrecognizedOptions;
        vecUnrecognizedOptions = po::collect_unrecognized(parsedOptions.options, po::include_positional);
        bool bFirstOne = true;
        for (std::vector<NString>::iterator itrV = vecUnrecognizedOptions.begin(); 
            itrV != vecUnrecognizedOptions.end(); itrV++)
        {
            if(!bFirst)
                m_UnrecognizedOptions.push_back(' '); // And space.
			else
				bFirst = false;

            // Handle the space or add quotes
            if(boost::icontains(itrV->c_str(), " "))
            {
                m_UnrecognizedOptions.push_back('\"');
                m_UnrecognizedOptions.append(itrV->c_str());
                m_UnrecognizedOptions.push_back('\"');
            }
            else
                m_UnrecognizedOptions.append(itrV->c_str());
        }

    }
    catch (std::exception& e)
    {
        // ToDo - Log it.
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CmdLineMgrImp::AddSupportedOption(CmdOption* pOption)
{
    if(NULL == pOption)
        return false;

    for(CmdOptionList::iterator it = m_SupportedOptionsList.begin(); it != m_SupportedOptionsList.end(); ++it)
    {
        if (boost::iequals((*it)->GetName(), pOption->GetName())) // Case-insensitive
            return false; // Avoid to add the duplicated option.
    } 

    m_SupportedOptionsList.push_back(pOption);

    return true;
}

CmdOption* CmdLineMgrImp::GetRecognizedOptionByName(const NString& name) const
{
    for(CmdOptionList::const_iterator it = m_RecognizedOptionsList.begin(); it != m_RecognizedOptionsList.end(); ++it)
    {
        if (boost::iequals((*it)->GetName(), name)) // Case-insensitive
            return *it;
    } 

    return NULL;
}

bool CmdLineMgrImp::HasUnrecognizedOption() const
{
    return (m_UnrecognizedOptions.size() != 0);
}

void CmdLineMgrImp::RemovedRecognizedOptions() 
{
    m_RecognizedOptionsList.clear();
}

CmdOption* CmdLineMgrImp::GetSupportedOptionByName(const NString& name) const
{
    for(CmdOptionList::const_iterator it = m_SupportedOptionsList.begin(); it != m_SupportedOptionsList.end(); ++it)
    {
        if (boost::iequals((*it)->GetName(), name)) // Case-insensitive
            return *it;
    } 

    return NULL;
}

const NString& CmdLineMgrImp::GetUnrecongnizedOption() const
{
    return m_UnrecognizedOptions;
}