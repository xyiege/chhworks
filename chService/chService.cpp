// chService.cpp : 定义控制台应用程序的入口点。
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

// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  更改错误代码以符合您的需要
			_tprintf(_T("错误:  MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  在此处为应用程序的行为编写代码。
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
		// TODO:  更改错误代码以符合您的需要
		_tprintf(_T("错误:  GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
