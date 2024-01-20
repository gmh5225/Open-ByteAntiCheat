#include "BACKernel.h"
#include "../../BAC-Base.h"


BACKernel::BACKernel()
{
	//��ȡģ��·��
	TCHAR module_path[MAX_PATH] = { 0 };
	GetModuleFileNameW(self_module, module_path, _countof(module_path));
	PathRemoveFileSpecW(module_path);
	_stprintf_s(this->_driver_full_path, _countof(this->_driver_full_path), _T("%s\\%s"), module_path, DRIVER_FILE_NAME);

}

BACKernel::~BACKernel()
{
}

bool BACKernel::InstiallDriver()
{
//#if NDEBUG
//	VMProtectBegin("BACKernel::InstallDriver");
//#endif
#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Enter");
#endif

	//����ǰ�ȳ���ж������
	this->UnInstallDriver();

	SC_HANDLE h_service_mgr = NULL;
	SC_HANDLE h_service_ddk = NULL;
	BOOL b_ret = FALSE;

	h_service_mgr = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL == h_service_mgr)
	{
		if (NULL != h_service_mgr)
			CloseServiceHandle(h_service_mgr);
		if (NULL != h_service_ddk)
			CloseServiceHandle(h_service_ddk);
#if _DEBUG
		baclog->FileLog("OpenSCManager error");
		baclog->FunctionLog(__FUNCTION__, "Leave");
#endif
		return FALSE;
	}

	TCHAR driver_name[MAX_PATH] = { 0 };
	_tcscpy_s(driver_name, _countof(driver_name), this->_driver_full_path);
	PathStripPath(driver_name);

	h_service_ddk = CreateService(h_service_mgr,
		driver_name,					// �����������ע����е�����    
		driver_name,					// ע������������ DisplayName ֵ    
		SERVICE_ALL_ACCESS,				// ������������ķ���Ȩ��    
		SERVICE_KERNEL_DRIVER,			// ��ʾ���صķ�������������    
		SERVICE_DEMAND_START,			// ע������������ Start ֵ    
		SERVICE_ERROR_IGNORE,			// ע������������ ErrorControl ֵ    
		this->_driver_full_path,		// ע������������ ImagePath ֵ    
		NULL,							// GroupOrder HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\GroupOrderList
		NULL,
		NULL,
		NULL,
		NULL);

	//�򿪷���
	h_service_ddk = OpenService(h_service_mgr, driver_name, SERVICE_ALL_ACCESS);

	//��������
	b_ret = StartService(h_service_ddk, NULL, NULL);

	if (NULL != h_service_mgr)
		CloseServiceHandle(h_service_mgr);
	if (NULL != h_service_ddk)
		CloseServiceHandle(h_service_ddk);

#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Leave");
#endif
	return b_ret;
//#if NDEBUG
//	VMProtectEnd();
//#endif
}

bool BACKernel::UnInstallDriver()
{
#if NDEBUG
	VMProtectBegin("BACKernel::UnInstallDriver");
#endif
#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Enter");
#endif

	//��ʽִ��ж��
	SC_HANDLE h_service_mgr = NULL;
	SC_HANDLE h_service_ddk = NULL;
	SERVICE_STATUS svr_sta;
	BOOL bRet = TRUE;
	//��SCM������  
	h_service_mgr = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (h_service_mgr == NULL)
	{
#if _DEBUG
		baclog->FileLog("OpenSCManager error");
		baclog->FunctionLog(__FUNCTION__, "Leave");
#endif
		if (NULL != h_service_mgr)
			CloseServiceHandle(h_service_mgr);
		if (NULL != h_service_ddk)
			CloseServiceHandle(h_service_ddk);
		return FALSE;
	}

	//����������Ӧ�ķ���  
	TCHAR driver_name[MAX_PATH] = { 0 };
	_tcscpy_s(driver_name, _countof(driver_name), this->_driver_full_path);
	PathStripPath(driver_name);

	h_service_ddk = OpenService(h_service_mgr, driver_name, SERVICE_ALL_ACCESS);
	if (NULL == h_service_ddk)
	{
#if _DEBUG
		baclog->FileLog("OpenService error");
		baclog->FunctionLog(__FUNCTION__, "Leave");
#endif
		if (NULL != h_service_mgr)
			CloseServiceHandle(h_service_mgr);
		if (NULL != h_service_ddk)
			CloseServiceHandle(h_service_ddk);
		return FALSE;
	}

	if (!ControlService(h_service_ddk, SERVICE_CONTROL_STOP, &svr_sta))
	{
#if _DEBUG
		baclog->FileLog("ControlService error");
		baclog->FunctionLog(__FUNCTION__, "Leave");
#endif
		if (NULL != h_service_mgr)
			CloseServiceHandle(h_service_mgr);
		if (NULL != h_service_ddk)
			CloseServiceHandle(h_service_ddk);
		return FALSE;
	}

	//��̬ж����������
	DeleteService(h_service_ddk);

#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Leave");
#endif
	if (NULL != h_service_mgr)
		CloseServiceHandle(h_service_mgr);
	if (NULL != h_service_ddk)
		CloseServiceHandle(h_service_ddk);
	return TRUE;

#if NDEBUG
	VMProtectEnd();
#endif
}

bool BACKernel::OpenDriverHandle()
{
//#if NDEBUG
//	VMProtectBegin("BACKernel::OpenDriverHandle");
//#endif
#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Enter");
#endif

	//read_able_event = CreateEvent(NULL, FALSE, FALSE, NULL);
	this->_driver_handle = CreateFileW(
		DRIVER_LINKER_NAME,
		GENERIC_ALL,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (NULL == this->_driver_handle || INVALID_HANDLE_VALUE == this->_driver_handle)
	{
#if _DEBUG
		baclog->FileLog("driver handle open fialed");
		baclog->FunctionLog(__FUNCTION__, "Leave");
#endif
		return FALSE;
	}

#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Leave");
#endif
	return TRUE;
//#if NDEBUG
//	VMProtectEnd();
//#endif
}



