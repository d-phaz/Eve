
#pragma once
#ifndef __EVE_EVT_CALLBACK_AUTO_H__
#define __EVE_EVT_CALLBACK_AUTO_H__

#ifndef __EVE_EVT_CALLBACK_H__
#include "eve/evt/Callback.h"
#endif


/*****************************************************************************
* AUTO CALLBACK ABSTRACT CLASS
*/
class AutoCallback
{
public:
	virtual ~AutoCallback( void ) {}
	virtual void execute( void ) = 0;
	virtual bool operator == (const AutoCallback &other) const = 0;
	virtual bool operator != (const AutoCallback &other) const
	{ return !(*this == other); }
};

/*****************************************************************************
* AUTO STATIC FUNCTION CALLBACKS
*/
template <class TReturn>
class AutoStaticCallback0 : public AutoCallback, public StaticCallback0<TReturn>
{
public:
	typedef StaticCallback0<TReturn> ParentType;

	AutoStaticCallback0(typename ParentType::FunctionType function)
		: StaticCallback0<TReturn>(function)
	{}

	virtual void execute()
	{ StaticCallback0<TReturn>::execute(); }

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
};


template <class TReturn, class TArg1>
class AutoStaticCallback1 : public AutoCallback, public StaticCallback1<TReturn, TArg1>
{
public:
	typedef StaticCallback1<TReturn, TArg1> ParentType;

	AutoStaticCallback1(typename ParentType::FunctionType function, TArg1 arg1)
		: StaticCallback1<TReturn, TArg1>(function), a1(arg1)
	{}

	virtual void execute()
	{ StaticCallback1<TReturn, TArg1>::execute(a1); }

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
	TArg1 a1;
};

template <class TReturn, class TArg1, class TArg2>
class AutoStaticCallback2 : public AutoCallback, public StaticCallback2<TReturn, TArg1, TArg2>
{
public:
	typedef StaticCallback2<TReturn, TArg1, TArg2> ParentType;

	AutoStaticCallback2(typename ParentType::FunctionType function, TArg1 arg1, TArg2 arg2)
		: StaticCallback2<TReturn, TArg1, TArg2>(function), a1(arg1), a2(arg2)
	{}

	virtual void execute()
	{ StaticCallback2<TReturn, TArg1, TArg2>::execute(a1, a2); }

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
	TArg1 a1;
	TArg2 a2;
};

template <class TReturn, class TArg1, class TArg2, class TArg3>
class AutoStaticCallback3 : public AutoCallback, public StaticCallback3<TReturn, TArg1, TArg2, TArg3>
{
public:
	typedef StaticCallback3<TReturn, TArg1, TArg2, TArg3> ParentType;

	AutoStaticCallback3(typename ParentType::FunctionType function, TArg1 arg1, TArg2 arg2, TArg3 arg3)
		: StaticCallback3<TReturn, TArg1, TArg2, TArg3>(function), a1(arg1), a2(arg2), a3(arg3)
	{}

	virtual void execute()
	{ StaticCallback3<TReturn, TArg1, TArg2, TArg3>::execute(a1, a2, a3); }

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
	TArg1 a1;
	TArg2 a2;
	TArg3 a3;
};

template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
class AutoStaticCallback4 : public AutoCallback, public StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>
{
public:
	typedef StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4> ParentType;

	AutoStaticCallback4(typename ParentType::FunctionType function, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		: StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>(function), a1(arg1), a2(arg2), a3(arg3), a4(arg4)
	{}

	virtual void execute()
	{ StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>::execute(a1, a2, a3, a4); }

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
	TArg1 a1;
	TArg2 a2;
	TArg3 a3;
	TArg4 a4;
};

template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
class AutoStaticCallback5 : public AutoCallback, public StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
{
public:
	typedef StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> ParentType;

	AutoStaticCallback5(typename ParentType::FunctionType function, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
		: StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>(function), a1(arg1), a2(arg2), a3(arg3), a4(arg4), a5(arg5)
	{}

	virtual void execute()
	{ StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>::execute(a1, a2, a3, a4, a5); }

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
	TArg1 a1;
	TArg2 a2;
	TArg3 a3;
	TArg4 a4;
	TArg5 a5;
};

/*****************************************************************************
* AUTO CLASS FUNCTION CALLBACKS
*/
template <class TClass, class TReturn>
class AutoClassCallback0 : public AutoCallback, public ClassCallback0<TClass, TReturn>
{
public:
	typedef ClassCallback0<TClass, TReturn> ParentType;

	AutoClassCallback0(TClass *object, typename ParentType::FunctionType function)
		: ClassCallback0<TClass, TReturn>(object, function)
	{

	}

	virtual void execute()
	{ 
		ClassCallback0<TClass, TReturn>::execute(); 
	}

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (*(ParentType*)this == *p_callBack);
	}

private:
};

template <class TClass, class TReturn, class TArg1>
class AutoClassCallback1 : public AutoCallback, public ClassCallback1<TClass, TReturn, TArg1>
{
public:
	typedef ClassCallback1<TClass, TReturn, TArg1> ParentType;

	AutoClassCallback1(TClass *object, typename ParentType::FunctionType function, TArg1 arg1)
		: ClassCallback1<TClass, TReturn, TArg1>(object, function), a1(arg1)
	{

	}

	virtual void execute()
	{ 
		ClassCallback1<TClass, TReturn, TArg1>::execute(a1);
	}

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
	TArg1 a1;
};

template <class TClass, class TReturn, class TArg1, class TArg2>
class AutoClassCallback2 : public AutoCallback, public ClassCallback2<TClass, TReturn, TArg1, TArg2>
{
public:
	typedef ClassCallback2<TClass, TReturn, TArg1, TArg2> ParentType;

	AutoClassCallback2(TClass *object, typename ParentType::FunctionType function, TArg1 arg1, TArg2 arg2)
		: ClassCallback2<TClass, TReturn, TArg1, TArg2>(object, function), a1(arg1), a2(arg2)
	{

	}

	virtual void execute()
	{ 
		ClassCallback2<TClass, TReturn, TArg1, TArg2>::execute(a1, a2);
	}

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
	TArg1 a1;
	TArg2 a2;
};

template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
class AutoClassCallback3 : public AutoCallback, public ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3>
{
public:
	typedef ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3> ParentType;

	AutoClassCallback3(TClass *object, typename ParentType::FunctionType function, TArg1 arg1, TArg2 arg2, TArg3 arg3)
		: ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3>(object, function), a1(arg1), a2(arg2), a3(arg3)
	{

	}

	virtual void execute()
	{ 
		ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3>::execute(a1, a2, a3); 
	}

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
	TArg1 a1;
	TArg2 a2;
	TArg3 a3;
};

template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
class AutoClassCallback4 : public AutoCallback, public ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>
{
public:
	typedef ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4> ParentType;

	AutoClassCallback4(TClass *object, typename ParentType::FunctionType function, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		: ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>(object, function), a1(arg1), a2(arg2), a3(arg3), a4(arg4)
	{

	}

	virtual void execute()
	{
		ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>::execute(a1, a2, a3, a4);
	}

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
	TArg1 a1;
	TArg2 a2;
	TArg3 a3;
	TArg4 a4;
};

template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
class AutoClassCallback5 : public AutoCallback, public ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
{
public:
	typedef ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> ParentType;

	AutoClassCallback5(TClass *object, typename ParentType::FunctionType function, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
		: ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>(object, function), a1(arg1), a2(arg2), a3(arg3), a4(arg4), a5(arg5)
	{}

	virtual void execute()
	{
		ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>::execute(a1, a2, a3, a4, a5);
	}

	virtual bool operator == (const AutoCallback &other) const
	{
		const ParentType *p_callBack = dynamic_cast<const ParentType*>(&other);
		return (p_callBack != NULL && *(ParentType*)this == *p_callBack);
	}

private:
	TArg1 a1;
	TArg2 a2;
	TArg3 a3;
	TArg4 a4;
	TArg5 a5;
};

/*****************************************************************************
* AUTO CALLBACK SET
*/
class AutoCallbackSet
{
public:
	void add    (AutoCallback *p_callBack) { insertCallbackIntoSet(p_callBack, &callbacks); }
	void clear  ()                 {	clearCallbackSet(&callbacks); }
	bool empty	()                 {	return callbacks.empty(); }
	template <class TCallback>
	void remove(TCallback *p_callBack)
	{
		typename std::set<AutoCallback*>::iterator it;
		TCallback *tmp;
		it = callbacks.begin();
		while (it != callbacks.end() && *it != p_callBack)
		{
			tmp = dynamic_cast<TCallback*>(*it);
			if (tmp != NULL && *tmp == *p_callBack) break;
			++it;
		}
		if (it != callbacks.end())
		{
			if (*it != p_callBack)
			{
				delete *it;
				delete p_callBack;
			}
			callbacks.erase(it);
		}
		else 
		{
			delete p_callBack;
		}
	}

	void execute()
	{
		std::set<AutoCallback*>::iterator it;
		for (it = callbacks.begin(); it != callbacks.end(); ++it)
			(*it)->execute();
	}

private:
	std::set<AutoCallback*> callbacks;
};

/*****************************************************************************
* AUTO CALLBACKS CONSTRUCTORS
*/
template <class TReturn>
inline AutoCallback * autoCallback( TReturn (*func)() )
{
	return new AutoStaticCallback0<TReturn>(func); 
}


template <class TReturn, class TArg1>
inline AutoCallback * autoCallback(TReturn (*func)(TArg1), TArg1 arg1)
{
	return new AutoStaticCallback1<TReturn, TArg1>(func, arg1);
}


template <class TReturn, class TArg1, class TArg2>
inline AutoCallback * autoCallback(TReturn (*func)(TArg1, TArg2), TArg1 arg1, TArg2 arg2)
{
	return new AutoStaticCallback2<TReturn, TArg1, TArg2>(func, arg1, arg2);
}


template <class TReturn, class TArg1, class TArg2, class TArg3>
inline AutoCallback * autoCallback(TReturn (*func)(TArg1, TArg2, TArg3), TArg1 arg1, TArg2 arg2, TArg3 arg3)
{ 
	return new AutoStaticCallback3<TReturn, TArg1, TArg2, TArg3>(func, arg1, arg2, arg3); 
}


template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
inline AutoCallback * autoCallback(TReturn (*func)(TArg1, TArg2, TArg3, TArg4), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
{ 
	return new AutoStaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>(func, arg1, arg2, arg3, arg4);
}


template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
inline AutoCallback * autoCallback(TReturn (*func)(TArg1, TArg2, TArg3, TArg4, TArg5), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
{ 
	return new AutoStaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>(func, arg1, arg2, arg3, arg4, arg5);
}



template <class TClass, class TReturn>
inline AutoCallback * autoCallback(TClass *obj, TReturn (TClass::*func)())
{ 
	return new AutoClassCallback0<TClass, TReturn>(obj, func);
}


template <class TClass, class TReturn, class TArg1>
inline AutoCallback * autoCallback(TClass *obj, TReturn (TClass::*func)(TArg1), TArg1 arg1)
{
	return new AutoClassCallback1<TClass, TReturn, TArg1>(obj, func, arg1); 
}


template <class TClass, class TReturn, class TArg1, class TArg2>
inline AutoCallback * autoCallback(TClass *obj, TReturn (TClass::*func)(TArg1, TArg2), TArg1 arg1, TArg2 arg2)
{ 
	return new AutoClassCallback2<TClass, TReturn, TArg1, TArg2>(obj, func, arg1, arg2);
}


template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
inline AutoCallback * autoCallback(TClass *obj, TReturn (TClass::*func)(TArg1, TArg2, TArg3), TArg1 arg1, TArg2 arg2, TArg3 arg3)
{
	return new AutoClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3>(obj, func, arg1, arg2, arg3); 
}


template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
inline AutoCallback * autoCallback(TClass *obj, TReturn (TClass::*func)(TArg1, TArg2, TArg3, TArg4), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
{ 
	return new AutoClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>(obj, func, arg1, arg2, arg3, arg4);
}


template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
inline AutoCallback * autoCallback(TClass * obj, TReturn (TClass::*func)(TArg1, TArg2, TArg3, TArg4, TArg5), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
{ 
	return new AutoClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>(obj, func, arg1, arg2, arg3, arg4, arg5);
}


#endif // __EVE_EVT_CALLBACK_AUTO_H__
