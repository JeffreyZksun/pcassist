#pragma once

class XmlIOStream;

class BRAINEXPORT IDataBaseObject
{
public:
	virtual bool XmlIn(XmlIOStream* pXmlIOStream) = 0;
	virtual bool XmlOut(XmlIOStream* pXmlIOStream) const = 0;

	virtual ~IDataBaseObject() {}
};

