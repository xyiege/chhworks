#include "stdafx.h"
#include "ChVerCompare.h"


CChVerCompare::CChVerCompare()
{
	mMajorVersion = 0;
	mMinorVersion = 0;
}


CChVerCompare::~CChVerCompare()
{
}


// major version 
int CChVerCompare::getMajorVersion()
{
	return 1;
}


// minor version
int CChVerCompare::getMinorVersion()
{
	return 0;
}
