// chMservice.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>

#include "chMservice.h"

//����ȫ�ֺ�������  
void Init();
BOOL IsInstalled();
BOOL Install();
BOOL Uninstall();
void LogEvent(LPCTSTR pszFormat, ...);
void WINAPI ServiceMain();
void WINAPI ServiceStrl(DWORD dwOpcode);

//��������
TCHAR szServiceName[] = _T("chLicenseService");
//��������
TCHAR szServiceDesc[] = _T("�������֤�������ڼ��ϵͳ�Ƿ���");
BOOL bInstall;
SERVICE_STATUS_HANDLE hServiceStatus;
SERVICE_STATUS status;
DWORD dwThreadID;

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	Init();
	dwThreadID = ::GetCurrentThreadId();
	SERVICE_TABLE_ENTRY st[] =
	{
		{ szServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
		{ NULL, NULL }
	};

	if (_stricmp(lpCmdLine, "/install") == 0)
	{
		Install();
	}
	else if (stricmp((LPCTSTR)lpCmdLine, "/uninstall") == 0)
	{
		Uninstall();
	}
	else
	{
		if (!::StartServiceCtrlDispatcher(st))
		{
			LogEvent(_T("Register Service Main Function Error!"));
		}
	}

	return 0;
}

//��ʼ��
void Init()
{
	hServiceStatus = NULL;
	status.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
	status.dwCurrentState = SERVICE_START_PENDING;
	status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	status.dwWin32ExitCode = 0;
	status.dwServiceSpecificExitCode = 0;
	status.dwCheckPoint = 0;
	status.dwWaitHint = 0;
}

//��������������������п��ƶԷ�����Ƶ�ע��
void WINAPI ServiceMain()
{
	status.dwCurrentState = SERVICE_START_PENDING;
	status.dwControlsAccepted = SERVICE_ACCEPT_STOP;

	//ע��������  
	hServiceStatus = RegisterServiceCtrlHandler(szServiceName, ServiceStrl);
	if (hServiceStatus == NULL)
	{
		LogEvent(_T("Handler not installed"));
		return;
	}
	SetServiceStatus(hServiceStatus, &status);

	status.dwWin32ExitCode = S_OK;
	status.dwCheckPoint = 0;
	status.dwWaitHint = 0;
	status.dwCurrentState = SERVICE_RUNNING;
	SetServiceStatus(hServiceStatus, &status);

	//ģ���������С�Ӧ��ʱ����Ҫ������ڴ˼���  
	//���ڴ�д�Ϸ�����Ҫִ�еĴ��룬һ��Ϊ��ѭ��  
	while (1)
	{
		FILE *p;
		p = fopen("c:\\log.txt", "ab+");
		SYSTEMTIME st;
		//utc ʱ��
		//GetSystemTime(&st);
		GetLocalTime(&st);
		char time[100] = { 0 };
		_sntprintf(time, 100, "%4d-%02d-%02d %02d:%02d:%02d\r\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		fwrite(time, strlen(time), 1, p);
		fclose(p);

		Sleep(1000);
	}
	status.dwCurrentState = SERVICE_STOPPED;
	SetServiceStatus(hServiceStatus, &status);
}

//Description:          �������������������ʵ�ֶԷ���Ŀ��ƣ�  
//                      ���ڷ����������ֹͣ����������ʱ���������д˴�����  
void WINAPI ServiceStrl(DWORD dwOpcode)
{
	switch (dwOpcode)
	{
	case SERVICE_CONTROL_STOP:
		status.dwCheckPoint = 1;
		status.dwCurrentState = SERVICE_STOP_PENDING;
		SetServiceStatus(hServiceStatus, &status);
		Sleep(500);
		status.dwCheckPoint = 0;
		status.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(hServiceStatus, &status);

		PostThreadMessage(dwThreadID, WM_CLOSE, 0, 0);
		break;
	case SERVICE_CONTROL_PAUSE:
		break;
	case SERVICE_CONTROL_CONTINUE:
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		exit(0);
		break;
	default:
		LogEvent(_T("Bad service request"));
	}
}

//�жϷ����Ƿ��Ѿ�����װ
BOOL IsInstalled()
{
	BOOL bResult = FALSE;

	//�򿪷�����ƹ�����  
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (hSCM != NULL)
	{
		//�򿪷���  
		SC_HANDLE hService = ::OpenService(hSCM, szServiceName, SERVICE_QUERY_CONFIG);
		if (hService != NULL)
		{
			bResult = TRUE;
			::CloseServiceHandle(hService);
		}
		::CloseServiceHandle(hSCM);
	}
	return bResult;
}

//��װ������
BOOL Install()
{
	//����Ƿ�װ��
	if (IsInstalled())
		return TRUE;

	//�򿪷�����ƹ�����  
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		MessageBox(NULL, _T("Couldn't open service manager"), szServiceName, MB_OK);
		return FALSE;
	}

	//��ȡ����Ŀ¼
	TCHAR szFilePath[MAX_PATH];
	::GetModuleFileName(NULL, szFilePath, MAX_PATH);

	//��������  
	SC_HANDLE hService = ::CreateService(hSCM, szServiceName, szServiceName,
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
		szFilePath, NULL, NULL, _T(""), NULL, NULL);

	//��ⴴ���Ƿ�ɹ�
	if (hService == NULL)
	{
		::CloseServiceHandle(hSCM);
		MessageBox(NULL, _T("Couldn't create service"), szServiceName, MB_OK);
		return FALSE;
	}

	//�ͷ���Դ
	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);
	return TRUE;
}

//ɾ��������
BOOL Uninstall()
{
	//����Ƿ�װ��
	if (!IsInstalled())
		return TRUE;

	//�򿪷�����ƹ�����
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		MessageBox(NULL, _T("Couldn't open service manager"), szServiceName, MB_OK);
		return FALSE;
	}

	//�򿪾������
	SC_HANDLE hService = ::OpenService(hSCM, szServiceName, SERVICE_STOP | DELETE);
	if (hService == NULL)
	{
		::CloseServiceHandle(hSCM);
		MessageBox(NULL, _T("Couldn't open service"), szServiceName, MB_OK);
		return FALSE;
	}

	//��ֹͣ����
	SERVICE_STATUS status;
	::ControlService(hService, SERVICE_CONTROL_STOP, &status);

	//ɾ������  
	BOOL bDelete = ::DeleteService(hService);
	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);

	if (bDelete)  return TRUE;
	LogEvent(_T("Service could not be deleted"));
	return FALSE;
}

//��¼�����¼�
void LogEvent(LPCTSTR pFormat, ...)
{
	TCHAR    chMsg[256];
	HANDLE  hEventSource;
	LPTSTR  lpszStrings[1];
	va_list pArg;

	va_start(pArg, pFormat);
	_vstprintf(chMsg, pFormat, pArg);
	va_end(pArg);

	lpszStrings[0] = chMsg;

	hEventSource = RegisterEventSource(NULL, szServiceName);
	if (hEventSource != NULL)
	{
		ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR*)&lpszStrings[0], NULL);
		DeregisterEventSource(hEventSource);
	}
}
