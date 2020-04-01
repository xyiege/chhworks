// chVersion.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "chVersion.h"


// 这是导出变量的一个示例
CHVERSION_API int nchVersion=0;

// 这是导出函数的一个示例。
CHVERSION_API int fnchVersion(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 chVersion.h
CchVersion::CchVersion()
{
	return;
}


float floatcalculate(float x, float y, int type)
{
	float result = 0;
	switch (type){
	case 0:
	{
			  result = x + y; 
			  break;
	}
	case 1:
	{
			  result = x - y;
			  break;
	}
	case 2:
	{
			  result = x*y;
			  break; 
	}
	case 3:
	{
			  result = x / y;
			  break; 
	}
	default:
		result = 0;
		break;
	}
	return result;

}
