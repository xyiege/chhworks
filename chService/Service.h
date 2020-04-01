#pragma once
class CService
{
public:
	CService();
	virtual ~CService();
	bool IsInstalled();
	bool Install();
	bool Uninstall();
	void LogEvent(char pszFormat);
	bool bInstall;
	int dwThreadID;
};

