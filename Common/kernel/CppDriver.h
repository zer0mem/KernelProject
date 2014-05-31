#pragma once

#include <ntifs.h>
#include "../base/Singleton.hpp"

//global accessible UNIQUE instance!
class CCppDriver :
	public CSingleton<CCppDriver>
{
	friend class CSingleton<CCppDriver>;
	//---------------------------
	//-- default implementation!
	//---------------------------
	CCppDriver()
	{
		DbgPrint("\nCCppDriver ctor\n");
	}
public:
	__forceinline
	DRIVER_OBJECT*&
	DriverObject()
	{
		return g_pDriverObject;
	}
	
//---------------------------
//----- do - implement!!
//---------------------------
	//unload
	~CCppDriver();

	//entry point
	__checkReturn
	NTSTATUS
	Main(
		__in DRIVER_OBJECT* driverObject,
		__in UNICODE_STRING* registryPath
		);

protected:
	static DRIVER_OBJECT* g_pDriverObject;
};
