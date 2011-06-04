#pragma once

#ifdef BRAIN_EXPORTS
#define BRAINEXPORT __declspec(dllexport) 
#else
#define BRAINEXPORT __declspec(dllimport)
#endif

