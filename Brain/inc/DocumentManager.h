#pragma once

#include "BrainSystem.h"
#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class BRAINEXPORT DocumentManager
{
public:
	DocumentManager(void);
	~DocumentManager(void);

	void SetDocumentName(const CString&);

public:
	bool		XmlIn();
	bool		XmlOut();

private:
	CString		mDocumentName;
};

#pragma warning( pop ) 
