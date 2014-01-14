/**
* @file DriverEntry.cpp
* @author created by: Peter Hlavaty
*/

#include "Common.cpp"


//---------------------------
//-----   UNINSTALL   -------
//---------------------------
void OnUnload(
	__in DRIVER_OBJECT* DriverObject
	)
{
	UNREFERENCED_PARAMETER(DriverObject);
	DbgPrint("\n\n************** unloaded! <<<<<<<<<<<<<<<\n\n");
} // end OnUnload

//---------------------------
//------   INSTALL   --------
//---------------------------
NTSTATUS DriverEntry(
	__in DRIVER_OBJECT* driverObject, 
	__in UNICODE_STRING* RegistryPath
	)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	gDriverObject = driverObject;
	EnviromentDependentVariablesInit();

	_cinit(0);

	driverObject->DriverUnload = OnUnload;

	return STATUS_SUCCESS;
} // end DriverEntry()
