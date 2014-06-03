/**
* @file DriverEntry.cpp
* @author created by: Peter Hlavaty
*/

#include "drv_common.h"

EXTERN_C
int main();

#include "CapstoneCppBindingsTest.hpp"

//---------------------------
//-----   UNINSTALL   -------
//---------------------------

CCppDriver::~CCppDriver()
{
	printf("\n\n************** unloaded! %p <<<<<<<<<<<<<<<\n\n", nullptr);
}

//---------------------------
//------   INSTALL   --------
//---------------------------

__checkReturn
NTSTATUS 
CCppDriver::Main(
	__in DRIVER_OBJECT* driverObject, 
	__in UNICODE_STRING* registryPath
	)
{
	UNREFERENCED_PARAMETER(driverObject);
	UNREFERENCED_PARAMETER(registryPath);

	main();

	CapstoneBindingsTest::X64Disasm(main, 0x50);
	CapstoneBindingsTest::X64DisasmCallback(main, 0x50);
	CapstoneBindingsTest::X64DisasmCallback(main, 0x50, true);
	CapstoneBindingsTest::X64DisasmCallback(RANDOM_CODE, sizeof(RANDOM_CODE) - 1);

	return STATUS_SUCCESS;
}
