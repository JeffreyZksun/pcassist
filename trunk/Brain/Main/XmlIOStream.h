#pragma once

class XmlIOStream
{
public:
	XmlIOStream(bool bIsRead);
	~XmlIOStream(void);

public:

public:
	void		Clear();
	bool		Load(const CString& docName);
	bool		Save(const CString& docName);

private:
	bool	mbIsRead;
};
