/*
 version file compare
*/
#pragma once
class  __declspec(dllexport) CChVerCompare
{
public:
	CChVerCompare();
	virtual ~CChVerCompare();
private:
	int mMajorVersion;
	int mMinorVersion;
public:
	// major version 
	int getMajorVersion();
	// minor version
	int getMinorVersion();
};