#pragma once

enum TextColor {
	COLOR_DEFAULT,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW
};


void LogOut(const CString& message, TextColor color = COLOR_DEFAULT);

class Logger
{
public:
	Logger();

	static Logger*	Get();

	bool			DoesOuputParameter();
	bool			SetDoesOutputParameter( bool bOutput);

private:
	bool			mDoesOutputParameter;

};

