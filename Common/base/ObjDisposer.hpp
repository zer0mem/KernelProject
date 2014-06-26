#pragma once

template<typename OBJ>
struct CObjDisposer
{
	void
	operator()(
		__in OBJ* obj
		)
	{
		delete obj;
	}
};

template<typename TYPE>
struct CRefObjDisposer
{
	static
	void
	ReleaseRef(
		__in_opt TYPE* obj
		)
	{
		if (!obj->DecreaseReferenceHolders())
			CObjDisposer<TYPE>()(obj);
	}
	void
	operator()(
		__in TYPE* obj
		)
	{
		ReleaseRef(obj);
	}
};
