#include "stdafx.h"
#include "MessageResource.h"

const WString& MessageResource::GetWelcomeMesage()
{
	static WString msg =	
		_T("**********************************************\r\n")
		_T("*                                            *\r\n")
		_T("*     Weclome to Task Automation Server      *\r\n")
		_T("*                                            *\r\n")
		_T("**********************************************\r\n");
	return msg;
}

const WString& MessageResource::GetTaskPromptMesage()
{
	static WString msg =	
		_T("\r\n")
		_T("\r\n")
		_T("Allowed taks:\r\n")
		_T("\t-T dwg -V G037 -N objectdbx_g053.100_2_3_2012\r\n");
	return msg;
}