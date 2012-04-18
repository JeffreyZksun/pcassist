#pragma once

enum TextColor {
	COLOR_DEFAULT,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW
};


//void LogOut(const CString& message, TextColor color = COLOR_DEFAULT);
void LogOut(const WString& message, TextColor color = COLOR_DEFAULT);

class Logger
{
public:
	Logger();

	static Logger*	Get();

	bool			DoesOuputParameter() const;
	void			SetDoesOutputParameter( bool bOutput);

	bool			GetEnable() const;
	void			SetEnable(bool bEnable);

private:
	bool			mDoesOutputParameter;
	bool			mbEnable;

};

