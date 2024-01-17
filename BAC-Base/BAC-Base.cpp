////////////////////////////////////////////////////////////////
//						ʵ�ֶ�����õĽӿ�
////////////////////////////////////////////////////////////////
#include "BAC-Base.h"

BAC* bac = nullptr;
BACLog* baclog = nullptr;


bool BACBaseInitialize()
{
#if NDEBUG
	VMProtectBegin("BACBaseInitialize");
#endif

	//ʵ����BAC��־����
	baclog = new BACLog();
	//ʵ����BAC����
	bac = new BAC();

#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Enter");
#endif

	//����CRC32
	printf("old hash:%d\n", bac->CRC32(::GetModuleHandleA("ntdll.dll"), 0x10000));

	//Ӧ�ò�����hook
	bac->HideHook();
	//����LdrLoadDllע��
	bac->MonitorLdrLoadDll();
	//�������뷨ע��
	bac->MonitorImm();
	//�����ڴ��д����
	bac->MonitorMemoryOption();
	//����ѭ���¼�
	bac->LoopEvent();



	//���Ӵ��ڴ�������غ���
	bac->MonitorCreateWindow();

	//����CRC32
	printf("after hook hash:%d\n", bac->CRC32(::GetModuleHandleA("ntdll.dll"), 0x10000));

#if _DEBUG
	baclog->FileLogf("%s-> %s: %s", "[BAC]", __FUNCTION__, "Leave");
#endif
	return true;
#if NDEBUG
	VMProtectEnd();
#endif
}

bool BACBaseUnInitialize()
{
#if NDEBUG
	VMProtectBegin("BACBaseUnInitialize");
#endif
#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Enter");
#endif

	//�ͷ�BAC����
	if (bac)
		delete bac;

#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Leave");
#endif

	//�ͷ�BAC��־����
	if (baclog)
		delete baclog;

	return true;
#if NDEBUG
	VMProtectEnd();
#endif
}

