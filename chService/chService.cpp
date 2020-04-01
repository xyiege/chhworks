// chService.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "chService.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum chs{
	install= 11,
	status=10,
	uninstall=12,
} chopt;

// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����:  MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			//default status
			//argv[1] = _T("default");
			/*
			TCHAR xstr = (TCHAR)argv[1];
	
			switch (chopt)
			{
			case install:
				_tprintf(_T("chservice will be install\n"));
				nRetCode = 1;
				break;
			case status:
				_tprintf(_T("check chservice status\n"));
				nRetCode = 1;
				break;
			default:
				break;
			}
			*/
			
			if (wcscmp(_T("cal"), argv[1]) == 0){
				typedef float (*CHV)(float,float,int);
				HINSTANCE hins = LoadLibrary(_T("chVersion.dll"));
				if (hins !=NULL){
					CHV xxfnc = (CHV)GetProcAddress(hins, "floatcalculate");
					float ret = xxfnc(40, 55.89f, 0);
					_tprintf(_T("floatcalculate: %.2f\n"), ret);
				}

				FreeLibrary(hins);
				nRetCode = 1;
			}else{
				_tprintf(_T("chService has been running!\n"));
				nRetCode = 1;
			}
			

			

				//typedef int* (*CHVERSION_API)();
				//HINSTANCE hins = LoadLibrary(_T("chVersion.dll"));
				//int *ret = (int*)GetProcAddress(hins,"nchVersion");//get var
				//_tprintf(_T("nchVersion: %d\n"), ret);
				//FreeLibrary(hins);
				//nRetCode = 1;
		}
	}
	else
	{
		// TODO:  ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����:  GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
