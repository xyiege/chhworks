// chVersion.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "chVersion.h"


// ���ǵ���������һ��ʾ��
CHVERSION_API int nchVersion=0;

// ���ǵ���������һ��ʾ����
CHVERSION_API int fnchVersion(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� chVersion.h
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
