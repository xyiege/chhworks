// chConsole.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "chConsole.h"

#include "../chVersion/chVersion.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
			//argv[1]?argv[1]: _T("tips");
			argv[1] = _T("default");
			//����1
			//if (argv[1] ==_T("version")){ //test version dynamic
				//_tprintf(_T("yes,it is equals"));
				//����2
			if (wcscmp(_T("version"), argv[1]) == 0){
				_tprintf(_T("yes,it is equals\n"));
				int vret = fnchVersion();
				_tprintf(_T("version dll ret:%d\n"), vret);
				/*
				typedef int* (*CHVERSION_API)();
				HINSTANCE hins = ::LoadLibrary(_T("chVersion.dll"));
				CHVERSION_API fnxchVersion = (CHVERSION_API)GetProcAddress(hins,"fnchVersion");
				//CHVERSION_API fnxchVersion = (CHVERSION_API)GetProcAddress(hins, "CchVersion");
				
				int *xx=fnxchVersion();
				//fnxchVersion();
				//CHVERSION_API mfun = (CHVERSION_API)GetProcAddress(hins, "nchVersion");
				//int xx = mfun();
				_tprintf(_T("version dll ret:%s\n"),xx);
				_tprintf(_T("load dll success!\n"));
				FreeLibrary(hins);
				*/
			}
			//calculate
			else if (wcscmp(_T("cal"), argv[1]) == 0){
				_tprintf(_T("calculate function demo,see anther application. Visit chService.exe cal\n"));
				//get function from dll
				//float ret = floatcalculate(4, 6, 0);
				//_tprintf(_T("version dll ret:%0.2f\n"), ret);
				/*
				_tprintf(_T("now,it is floatcalculat\n"));
				//calculate
				typedef float (*chcal)(float,float,int);
				HINSTANCE xchins;
				chcal chc;
				xchins = ::LoadLibrary(_T("chVersion.dll"));
				if (xchins != NULL){
					chc = (chcal)GetProcAddress(xchins, "floatcalculate");
					float ret = chc(4,6,0); //add
					_tprintf(_T("floatcalculate result :%s\n"), ret);
				}
				FreeLibrary(xchins);
				*/
			}
			else{
				_tprintf(_T("Kunming Chuhong Technolgy LTD.\n"));
			}
			//ZeroMemory(argv, sizeof(argv+1));
			nRetCode = 1;
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
