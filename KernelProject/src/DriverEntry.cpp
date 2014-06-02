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
	printf("\n\n************** unloaded! %p <<<<<<<<<<<<<<<\n\n", nullptr);
} // end OnUnload

//---------------------------
//------   INSTALL   --------
//---------------------------

EXTERN_C
int main();

#include <Common/3rdparty/Disasm.hpp>

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

	CDisasmbler64 dis;
	auto insn = dis.Disasm(main, 0x30);

	if (!insn.get())
		return STATUS_SUCCESS;

	printf("\n\nDISASM :\n\n");
	for (size_t i = 0; i < insn->Count; i++)
	{
		printf("-> 0x%p:\t%s\t%s\n", insn->Instructions[i].address, insn->Instructions[i].mnemonic, insn->Instructions[i].op_str);
		dis.PrintInstDetail(insn->Instructions[i]);
	}

	return STATUS_SUCCESS;
} // end DriverEntry()
