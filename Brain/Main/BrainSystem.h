#pragma once

#ifdef BRAIN_EXPORTS
#define BRAINEXPORT __declspec(dllexport) 
#else
#define BRAINEXPORT __declspec(dllimport)
#endif

#define BEHAVIOR_CLASS_DECLARE(ClassName) ClassName();

#define BEHAVIOR_CLASS_IMP(ClassName, BaseClass) \
ClassName::ClassName() \
	: BaseClass(_T("ClassName")) \
{ \
}
