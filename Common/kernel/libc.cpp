#include <ntifs.h>
#include <libc/src/cpp.h>

#include <Common/kernel/KernelModule.hpp>

//---------------------------
//------   INSTALL   --------
//---------------------------

extern
__checkReturn
bool
drv_main();

void
NTAPI
ExitKernelEntry(
	__in DRIVER_OBJECT*
	)
{
	cc_doexit(0, 0, 0);//call dtors
}

extern "C"
__declspec(dllexport)
NTSTATUS
NTAPI
DriverEntry(
	__in DRIVER_OBJECT* driverObject,
	__in void* param
	)
{
	driverObject->DriverUnload = reinterpret_cast<DRIVER_UNLOAD*>(ExitKernelEntry);

	CKernelModule::GetInstance().SetParams(driverObject, param);

	if (drv_main())
		return STATUS_SUCCESS;

	return STATUS_UNSUCCESSFUL;
}
