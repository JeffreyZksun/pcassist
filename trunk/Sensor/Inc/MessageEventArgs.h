#pragma once

class ConnectionPoint;

class MessageEventArgs
{
public:
	MessageEventArgs(ConnectionPoint* pConnectionPoint, const CString& strData);

	ConnectionPoint* GetConnectionPoint() const;

	const CString&	GetData() const;

private:
	ConnectionPoint*	mpConnectionPoint;
	CString				mData;
};
