#include "stdafx.h"
#include "MessageResource.h"

const WString& MessageResource::GetWelcomeMesage()
{
	static WString msg =	
		_T("**********************************************\r\n")
		_T("*                                            *\r\n")
		_T("*     Weclome to Task Automation System      *\r\n")
		_T("*                                            *\r\n")
		_T("**********************************************\r\n");
	return msg;
}
