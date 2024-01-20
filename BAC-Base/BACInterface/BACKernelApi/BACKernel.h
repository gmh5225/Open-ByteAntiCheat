#pragma once
#include <Windows.h>
#include <tchar.h>
#include <shlwapi.h>

#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib, "user32.lib")

#include "../../../BAC-Base-Kernel/IRPControl/BAC-DataStruct.h"
#include "../../../BAC-Base-Kernel/IRPControl/IRPControlCode.h"

//�����ļ�����
#if _WIN64
#define DRIVER_FILE_NAME _T("BAC-Base64.sys")
#elif _WIN32
#define DRIVER_FILE_NAME _T("BAC-Base.sys")
#else
#error "unsupport"
#endif


class BACKernel
{
private:
	//�����ļ����
	HANDLE _driver_handle = NULL;
	//�����ļ�·��
	TCHAR _driver_full_path[MAX_PATH] = { 0 };

public:
	BACKernel();
	~BACKernel();

public:
	bool InstiallDriver();
	bool UnInstallDriver();
	bool OpenDriverHandle();

};
