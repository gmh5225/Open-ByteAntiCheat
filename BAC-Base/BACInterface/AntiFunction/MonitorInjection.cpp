#include "../BAC.h"
#include "../../BAC-Base.h"

typedef NTSTATUS(WINAPI* fpLdrLoadDll)(IN PWCHAR PathToFile OPTIONAL, IN PULONG Flags OPTIONAL,
	IN PUNICODE_STRING ModuleFileName, OUT PHANDLE ModuleHandle);

fpLdrLoadDll pfnLdrLoadDll = NULL;

typedef BOOL(__stdcall* fpImmGetHotKey)(DWORD dwHotKeyID, LPUINT lpuModifiers, LPUINT lpuVKey, LPHKL lphKL);
typedef int(__stdcall* fpImmActivateLayout)(LPARAM);

bool active_flag = false;
fpImmGetHotKey pfnGetHotKey = NULL;
fpImmActivateLayout pfnImmActivateLayout = NULL;


NTSTATUS WINAPI MyLdrLoadDll(IN PWCHAR PathToFile OPTIONAL, IN PULONG Flags OPTIONAL,
	IN PUNICODE_STRING ModuleFileName, OUT PHANDLE ModuleHandle)
{
	bool is_hidemodle = false;
	WCHAR szDllName[MAX_PATH];
	ZeroMemory(szDllName, sizeof(szDllName));
	memcpy(szDllName, ModuleFileName->Buffer, ModuleFileName->Length);

	printf("[LOG]:LdrLoadDll:%S\n", szDllName);

	//�ڼ���֮ǰ�ж��¸�ģ���Ƿ񱻼��ع�
	HMODULE hPreMod = GetModuleHandleW(szDllName);
	NTSTATUS ntStatus = pfnLdrLoadDll(PathToFile, Flags, ModuleFileName, ModuleHandle);
	DWORD dwLastError = GetLastError();

	//���û�б����ع�����ִ����pfnLdrLoadDll�ɹ������Ƿ����������Լ��Ĳ���
	if (STATUS_SUCCESS == ntStatus && NULL == hPreMod)
	{
		//GetModuleHandleW��ʵ�Ƕ�ȡpeb����Ϣ,û��Ҫ�ٱ���һ����
		HMODULE hNowMod = GetModuleHandleW(szDllName);
		if (NULL == hNowMod) 
			is_hidemodle = true;
	}

	//�ָ�������
	SetLastError(dwLastError);
	return ntStatus;
}

void BAC::MonitorLdrLoadDll()
{
#if _DEBUG
	baclog->OutPutCommandLine(__FUNCTION__, "Initialize");
#endif

	HMODULE ntdll = ::GetModuleHandleA("ntdll.dll");
	if (!ntdll)
		ntdll = ::LoadLibraryA("ntdll.dll");

	//��ȡ��غ�����ַ
	pfnLdrLoadDll = (fpLdrLoadDll)::GetProcAddress(ntdll, "LdrLoadDll");

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	DetourAttach((PVOID*)&pfnLdrLoadDll, MyLdrLoadDll);

	DetourTransactionCommit();

#if _DEBUG
	baclog->OutPutCommandLine(__FUNCTION__, "Leave");
#endif
}

void BAC::MonitorApc()
{

}

BOOL WINAPI MyImmGetHotKey(DWORD dwHotKeyID, LPUINT lpuModifiers, LPUINT lpuVKey, LPHKL lphKL)
{
	active_flag = true;
	return pfnGetHotKey(dwHotKeyID, lpuModifiers, lpuVKey, lphKL);
}

int WINAPI MyImmActivateLayout(LPARAM pa)
{
	if (active_flag)
		active_flag = true;
	else
	{
		MessageBoxA(NULL, "��⵽���뷨ע��", "��ʾ", MB_OK);
		ExitProcess(5);
	}
	return pfnImmActivateLayout(pa);
}

void BAC::MonitorImm()
{
#if _DEBUG
	baclog->OutPutCommandLine(__FUNCTION__, "Initialize");
#endif

	HMODULE imm32 = LoadLibraryA("imm32.dll");
	pfnGetHotKey = (fpImmGetHotKey)GetProcAddress(imm32, "ImmGetHotKey");
	pfnImmActivateLayout = (fpImmActivateLayout)GetProcAddress(imm32, "ImmActivateLayout");

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID*)&pfnGetHotKey, MyImmGetHotKey);
	DetourAttach((PVOID*)&pfnImmActivateLayout, MyImmActivateLayout);
	DetourTransactionCommit();

#if _DEBUG
	baclog->OutPutCommandLine(__FUNCTION__, "Leave");
#endif
}


