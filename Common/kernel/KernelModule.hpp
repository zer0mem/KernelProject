#pragma once

#include <ntifs.h>
#include "../base/Module.hpp"

class CKernelModule
{
public:
	static
	CModule&
	GetInstance()
	{
		return CModule::GetInstance();
	}

	static
	DRIVER_OBJECT*
	DriverObject()
	{
		return static_cast<DRIVER_OBJECT*>(CModule::GetInstance().m_module);
	}

	static
	const UNICODE_STRING*
	RegistryPath()
	{
		return static_cast<const UNICODE_STRING*>(CModule::GetInstance().m_param);
	}

	static
	const void*
	Param()
	{
		return CModule::GetInstance().m_param;
	}
};
