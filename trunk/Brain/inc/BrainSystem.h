#pragma once

#ifdef BRAIN_EXPORTS
	#define BRAINEXPORT __declspec(dllexport) 
#elif defined(NO_BRAIN_EXPORTS)
	#define BRAINEXPORT
#else
	#define BRAINEXPORT __declspec(dllimport)
#endif
