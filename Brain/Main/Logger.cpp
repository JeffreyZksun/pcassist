#include "StdAfx.h"
#include "Logger.h"
#include <iostream>
#include <winbase.h> // GetStdHandle
#include <wincon.h> // CONSOLE_SCREEN_BUFFER_INFO

WORD GetColorAttribute(TextColor color);

void LogOut(const CString& message, TextColor color/* = COLOR_DEFAULT*/)
{
	if(!Logger::Get()->GetEnable())
		return;

	if(COLOR_DEFAULT == color)
	{
		std::wcout << (LPCTSTR)message;
		fflush(stdout);
		return;
	}

	// ToDo - set the color
	const HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Gets the current text color.
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(stdout_handle, &buffer_info);
	const WORD old_color_attrs = buffer_info.wAttributes;

	// We need to flush the stream buffers into the console before each
	// SetConsoleTextAttribute call lest it affect the text that is already
	// printed but has not yet reached the console.
	fflush(stdout);
	SetConsoleTextAttribute(stdout_handle,
		GetColorAttribute(color) | FOREGROUND_INTENSITY);

	std::wcout << (LPCTSTR)message;

	fflush(stdout);
	// Restores the text color.
	SetConsoleTextAttribute(stdout_handle, old_color_attrs);	
}

WORD GetColorAttribute(TextColor color) {
	switch (color) {
	case COLOR_RED:    return FOREGROUND_RED;
	case COLOR_GREEN:  return FOREGROUND_GREEN;
	case COLOR_YELLOW: return FOREGROUND_RED | FOREGROUND_GREEN;
	default:           return 0;
	}
}

Logger::Logger() : mDoesOutputParameter(false), mbEnable(true)
{

}

Logger* Logger::Get()
{
	static Logger singleton;
	return &singleton;
}

bool Logger::DoesOuputParameter() const
{
	return mDoesOutputParameter;
}

void Logger::SetDoesOutputParameter( bool bOutput)
{
	mDoesOutputParameter = bOutput;
}

bool Logger::GetEnable() const
{
	return mbEnable;
}

void Logger::SetEnable(bool bEnable)
{
	mbEnable = bEnable;
}