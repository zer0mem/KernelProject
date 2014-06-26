#pragma once

#include <sal.h>
#include <Common/base/Singleton.hpp>
#include <Common/base/ObjDisposer.hpp>
#include <boost/intrusive/list.hpp>

#include "../base/DynamicClass.h"

using namespace boost::intrusive;

struct PARAM_PACKET
{
	void* Packet;
	size_t Size;
};

class CModule :
	public CSingleton<CModule>
{
	friend class CSingleton<CModule>;

	CModule()
	{
	}

protected:
	friend class CKernelModule;
	friend class CExeModule;
	friend class CDllModule;

	void* m_module;
	const void* m_param;

	list<IExitCallback> m_defer;

public:
	void
	SetParams(
		__in void* module,
		__in const void* param
		)
	{
		m_module = module;
		m_param = param;
	}

	~CModule()
	{
		//CObjDisposer call delete for selected object
		m_defer.clear_and_dispose(CObjDisposer<IExitCallback>());
	}

	void
	RegisterRuntimeClass(
		__in IExitCallback& callback
		)
	{
		m_defer.push_back(callback);
	}
};
