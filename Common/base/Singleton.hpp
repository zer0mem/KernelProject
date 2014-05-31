#pragma once

/*
# CSingleton usage : 

class CClass :
	public CSingleton<CClass>
{
	friend class CSingleton<CClass>;
	CClass(...)
	{
	}
public:
}

CClass CClass::m_instance;
*/

template<typename TYPE>
class CSingleton
{
	CSingleton(const CSingleton&) = delete;
	void operator=(CSingleton const&) = delete;
protected:
	static TYPE m_instance;
	CSingleton()
	{
	}
public:
	static
	TYPE& GetInstance()
	{
		return m_instance;
	}
};

template<typename TYPE>
TYPE CSingleton<TYPE>::m_instance;
