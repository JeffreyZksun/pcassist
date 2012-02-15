#include "HostService.h"
#include "BehaviorBuilder.h"

#if defined(_WINOS) 

#include "OS\Windows\WindowsProvider.h"

#elif defined(_MACOSX) 

#include "OS\Windows\MACOSXProvider.h"

#endif 

HostService::HostService() : mpProvider(NULL), mpBehaviorBuilder(NULL)
{


}

HostService::~HostService()
{
	if(mpProvider)
	{
		delete mpProvider;
		mpProvider = NULL;
	}

	if(mpBehaviorBuilder)
	{
		delete mpBehaviorBuilder;
		mpBehaviorBuilder = NULL;
	}

}

IOSProvider* HostService::GetOSProvider()
{
	if(!mpProvider)
	{
#if defined(_WINOS) 

		mpProvider = new WindowsProvider();

#elif defined(_MACOSX) 


#endif 
	}

	return mpProvider;
}
IBehaviorBuilder* HostService::GetBehaviorBuilder()
{
	if(!mpBehaviorBuilder)
	{
		mpBehaviorBuilder = new BehaviorBuilder();
	}

	return mpBehaviorBuilder;
}




