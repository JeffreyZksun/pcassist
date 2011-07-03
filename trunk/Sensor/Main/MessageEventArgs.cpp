#include "StdAfx.h"
#include "MessageEventArgs.h"
#include "ConnectionPoint.h"

MessageEventArgs::MessageEventArgs(ConnectionPoint* pConnectionPoint, const CString& strData)
	: mpConnectionPoint(pConnectionPoint), mData(strData)
{
}

ConnectionPoint* MessageEventArgs::GetConnectionPoint() const
{
	return mpConnectionPoint;
}

const CString& MessageEventArgs::GetData() const
{
	return mData;
}

