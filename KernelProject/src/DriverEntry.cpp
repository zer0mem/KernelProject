/**
* @file DriverEntry.cpp
* @author created by: Peter Hlavaty
*/

#include "drv_common.h"
#include <memory>

//---------------------------
//-----   UNINSTALL   -------
//---------------------------

CCppDriver::~CCppDriver()
{
	DbgPrint("\n\n************** unloaded! %p <<<<<<<<<<<<<<<\n\n", nullptr);
} // end OnUnload

//---------------------------
//------   INSTALL   --------
//---------------------------

void test();

__checkReturn
NTSTATUS 
CCppDriver::Main(
	__in DRIVER_OBJECT* driverObject, 
	__in UNICODE_STRING* registryPath
	)
{
	test();
	return STATUS_SUCCESS;
} // end DriverEntry()
