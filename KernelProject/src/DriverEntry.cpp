/**
* @file DriverEntry.cpp
* @author created by: Peter Hlavaty
* @author \n
* @author Copyright (c) 2013 ESET, spol. s r. o.
* @note current owner: Peter Hlavaty (peter.hlavaty@eset.sk)
* @note IMPORTANT: Before doing any significant change to this file check your plan with the current owner to avoid unexpected behaviour.
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
