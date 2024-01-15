#pragma once
#include <Windows.h>
#include <stdio.h>
#include <iostream>

#include "../Detours/include/detours.h"
#if _WIN64
#pragma comment(lib,"Detours/lib.X64/detours.lib")
#elif _WIN32
#pragma comment(lib,"Detours/lib.X86/detours.lib")
#endif

#include "SystemApi.h"


class BAC
{
private:

private:
	void MakePePacked(HANDLE hProcess, PBYTE pImageBuff);

public:
	//����Ӧ�ò��hook
	void HideHook();
	//���Ӵ��ڴ�����غ���
	void MonitorCreateWindow();
	//����LdrLoadDllע��
	void MonitorLdrLoadDll();
	//����APCע��
	void MonitorApc();
	//�������뷨ע��
	void MonitorImm();



public:
	BAC();
	~BAC();

};