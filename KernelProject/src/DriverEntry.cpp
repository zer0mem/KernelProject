#include <Common/drv_common.h>

#include <memory>
#include "CapstoneCppBindingsTest.hpp"

//---------------------------
//----   ENTRY PIONT   ------
//---------------------------

extern
int
main();

__checkReturn
bool
drv_main()
{
	main();

	CapstoneBindingsTest::X64Disasm(main, 0x50);
	CapstoneBindingsTest::X64DisasmCallback(main, 0x50);
	CapstoneBindingsTest::X64DisasmCallback(main, 0x50, true);
	CapstoneBindingsTest::X64DisasmCallback(RANDOM_CODE, sizeof(RANDOM_CODE)-1);

	return true;
}
