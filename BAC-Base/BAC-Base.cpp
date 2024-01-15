#include "BAC-Base.h"

BAC* bac = nullptr;


bool BACBaseInitialize()
{
	//ʵ����BAC����
	bac = new BAC();

	//Ӧ�ò�����hook
	bac->HideHook();
	//����LdrLoadDllע��
	bac->MonitorLdrLoadDll();
	//�������뷨ע��
	bac->MonitorImm();


	//���Ӵ��ڴ�������غ���
	bac->MonitorCreateWindow();

	printf("BAC Initialize Over...\n");

	return true;
}

bool BACBaseUnInitialize()
{
	//�ͷ�BAC����
	if (bac)
		delete bac;

	return true;
}

