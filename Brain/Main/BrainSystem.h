#pragma once

#ifdef BRAIN_EXPORTS
	#define BRAINEXPORT __declspec(dllexport) 
#elif defined(NO_BRAIN_EXPORTS)
	#define BRAINEXPORT
#else
	#define BRAINEXPORT __declspec(dllimport)
#endif


//#define BEHAVIOR_FUNCTION_IMP(BehaviorName) \
//bool BehaviorName##Function(BehaviorNode* pSelf);\
//BehaviorFunctionHelper g##BehaviorName(_T(#BehaviorName), BehaviorName##Function);\
//bool BehaviorName##Function(BehaviorNode* pSelf)

#define BEHAVIOR_FUNCTION_IMP(BehaviorName) \
bool BehaviorName(BehaviorNode* pSelf);\
BehaviorFunctionHelper g##BehaviorName(_T(#BehaviorName), BehaviorName);\
bool BehaviorName(BehaviorNode* pSelf)