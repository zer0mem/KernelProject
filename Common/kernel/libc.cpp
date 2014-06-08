#include <libc/src/libc.h>
#include <libc/src/cpp.h>
#include <libc/src/pool.h>

#include "CppDriver.h"

void 
set_kernel_libc()
{
	cc_alloc = PoolAlloc;
	cc_free = PoolFree;
	cc_realloc = PoolReAlloc;
}

CCppDriver CCppDriver::m_instance;
DRIVER_OBJECT* CCppDriver::g_pDriverObject = nullptr;

//---------------------------
//-----   UNINSTALL   -------
//---------------------------
void
OnUnload(
	__in DRIVER_OBJECT* driverObject
	)
{
	UNREFERENCED_PARAMETER(driverObject);
	cc_doexit(0, 0, 0);//call dtors including CCppDiver one!
}

//---------------------------
//------   INSTALL   --------
//---------------------------
EXTERN_C
__declspec(dllexport)
NTSTATUS
DriverEntry(
	__in DRIVER_OBJECT* driverObject,
	__in UNICODE_STRING* registryPath
	)
{
	set_kernel_libc();
	cc_init(0);//call ctors

	driverObject->DriverUnload = OnUnload;
	CCppDriver::GetInstance().DriverObject() = driverObject;
	return CCppDriver::GetInstance().Main(driverObject, registryPath);
}
