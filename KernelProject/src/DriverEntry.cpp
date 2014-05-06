/**
* @file DriverEntry.cpp
* @author created by: Peter Hlavaty
*/

#include "drv_common.h"
#include <memory>

#include <boost/shared_ptr.hpp>
#include <boost/intrusive/avltree.hpp>

#include <Common/utils/VadScanner.hpp>

#include <Common/auto/AutoPtr.hpp>

void custom_deler(
		__in int* mem
		)
{
	DbgPrint("\ncustom_deler to action\n");
	delete mem;
}

class xyz
{
public:
	xyz()
	{
		DbgPrint("\nctor %p\n", this);
	}
	~xyz()
	{
		DbgPrint("\ndtor %p\n", this);
	}
};

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

__checkReturn
NTSTATUS 
CCppDriver::Main(
	__in DRIVER_OBJECT* driverObject, 
	__in UNICODE_STRING* registryPath
	)
{
	UNREFERENCED_PARAMETER(registryPath);
	//EnviromentDependentVariablesInit();
		
	auto superfetch_info = new std::unique_ptr<int, void(*)(int*)>(
		(int*)malloc(0x100),
		custom_deler);
	
	CAutoMem sup_ft(malloc(0x100));
	
	auto superfetch_info_shared = std::shared_ptr< std::unique_ptr<int, void(*)(int*)> >(
		superfetch_info);

	auto test_shared = std::shared_ptr<xyz>(new xyz());

	DbgBreakPoint();
	//NEW USAGE!!
	CRange<void*> mem(nullptr);
	if (CVAdScanner::GetMemory((void*)0x77000000, &mem))
	{
		DbgPrint("\nfound memory : %p %p\n", mem.Begin(), mem.End());

		std::shared_ptr<CVadNode> sp_vad_node;
		if (!CVAdScanner::Find(mem, &sp_vad_node))
			return STATUS_UNSUCCESSFUL;

		for (int i = 0; i < 0x10; i++)
		{
			++(*sp_vad_node.get());
			DbgPrint("\nXX. %p ITERATE : %p %p\n", sp_vad_node.get(), sp_vad_node->Begin(), sp_vad_node->End());
		}
	}

	return STATUS_SUCCESS;
} // end DriverEntry()
