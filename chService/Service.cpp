#include "stdafx.h"
#include "Service.h"


CService::CService()
{
	dwThreadID = 0;
}


CService::~CService()
{
}


bool CService::IsInstalled()
{
	return false;
}


bool CService::Install()
{
	return false;
}


bool CService::Uninstall()
{
	return false;
}


void CService::LogEvent(char pszFormat)
{
}
