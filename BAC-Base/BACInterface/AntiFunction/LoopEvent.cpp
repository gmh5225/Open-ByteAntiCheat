////////////////////////////////////////////////////////////////
//						�ڴ˴���ѭ���¼�
////////////////////////////////////////////////////////////////
#include "../BAC.h"
#include "../../BAC-Base.h"


void BAC::LoopEvent()
{
#if NDEBUG
	VMProtectBegin("BAC::LoopEvent");
#endif
#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Enter");
#endif



#if _DEBUG
	baclog->FunctionLog(__FUNCTION__, "Leave");
#endif
#if NDEBUG
	VMProtectEnd();
#endif
}

