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

	//����Ӧ�ò��hook
public:
	void HideHook();
private:
	void MakePePacked(HANDLE hProcess, PBYTE pImageBuff);

	//���Ӵ��ڴ�����غ���
public:
	void MonitorCreateWindow();
private:


	//Hook���ܵĻص�����
public:
	//static 

public:
	BAC();
	~BAC();

};