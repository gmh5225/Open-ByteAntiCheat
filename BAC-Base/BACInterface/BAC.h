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
#include "BACKernelApi/BACKernel.h"

using namespace std;


class BAC
{
private:
	BACKernel* bac_kernel = nullptr;

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
	//�����ڴ��д����
	void MonitorMemoryOption();
	
	//����ѭ���¼�
	void LoopEvent();

public:
	//���ڴ�������CRC32Ч��
	unsigned int CRC32(void* pdata, size_t data_len);

public:
	//BAC�ں˽ӿڳ�ʼ��
	bool InitializeBACKernel();
	bool UnInitializeBACKernel();

public:
	BAC();
	~BAC();

};