////////////////////////////////////////////////////////////////
//						ʵ�ֶ�����õĽӿ�
////////////////////////////////////////////////////////////////
#include "BAC-Base.h"

BAC* bac = nullptr;
BACLog* baclog = nullptr;


bool BACBaseInitialize()
{
	//ʵ����BAC��־����
	baclog = new BACLog();
	//ʵ����BAC����
	bac = new BAC();

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

	printf("BAC Initialize Over...\n");
	return true;
}

bool BACBaseUnInitialize()
{
	//�ͷ�BAC����
	if (bac)
		delete bac;
	//�ͷ�BAC��־����
	if (baclog)
		delete baclog;

	return true;
}

