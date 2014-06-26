#pragma once

#include <sal.h>

#include <boost/intrusive/list.hpp>
using namespace boost::intrusive;

class IExitCallback :
	public list_base_hook<>
{
	friend class CModule;
public:
	virtual
	~IExitCallback()
	{
	}
};
