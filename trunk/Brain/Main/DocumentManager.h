#pragma once

class DocumentManager
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
