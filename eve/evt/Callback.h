
#pragma once
#ifndef __EVE_EVT_CALLBACK_H__
#define __EVE_EVT_CALLBACK_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif


namespace eve
{
	namespace evt
	{



	} // namespace evt

} // namespace eve


/**
* \class eve::evt::Callback0
* \brief
*/
template <class TReturn>
class Callback0
{
public:
	virtual ~Callback0() {}
	virtual TReturn execute() = 0;
	virtual bool operator == (const Callback0<TReturn> &other) const = 0;
	virtual bool operator != (const Callback0<TReturn> &other) const
	{
		return !(*this == other);
	}
};




/*****************************************************************************
* ABSTRACT CALLBACKS
*/


template <class TReturn, class TArg1>
class Callback1
{
public:
	virtual ~Callback1() {}
	virtual TReturn execute(TArg1) = 0;
	virtual bool operator == (const Callback1<TReturn, TArg1> &other) const = 0;
	virtual bool operator != (const Callback1<TReturn, TArg1> &other) const
	{ 
		return !(*this == other);
	}
};

template <class TReturn, class TArg1, class TArg2>
class Callback2
{
public:
	virtual ~Callback2() {}
	virtual TReturn execute(TArg1, TArg2) = 0;
	virtual bool operator == (const Callback2<TReturn, TArg1, TArg2> &other) const = 0;
	virtual bool operator != (const Callback2<TReturn, TArg1, TArg2> &other) const
	{ 
		return !(*this == other);
	}
};

template <class TReturn, class TArg1, class TArg2, class TArg3>
class Callback3
{
public:
	virtual ~Callback3() {}
	virtual TReturn execute(TArg1, TArg2, TArg3) = 0;
	virtual bool operator == (const Callback3<TReturn, TArg1, TArg2, TArg3> &other) const = 0;
	virtual bool operator != (const Callback3<TReturn, TArg1, TArg2, TArg3> &other) const
	{
		return !(*this == other);
	}
};

template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
class Callback4
{
public:
	virtual ~Callback4() {}
	virtual TReturn execute(TArg1, TArg2, TArg3, TArg4) = 0;
	virtual bool operator == (const Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> &other) const = 0;
	virtual bool operator != (const Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> &other) const
	{ 
		return !(*this == other);
	}
};

template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
class Callback5
{
public:
	virtual ~Callback5() {}
	virtual TReturn execute(TArg1, TArg2, TArg3, TArg4, TArg5) = 0;
	virtual bool operator == (const Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> &other) const = 0;
	virtual bool operator != (const Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> &other) const
	{
		return !(*this == other);
	}
};

/*****************************************************************************
* STATIC FUNCTION CALLBACKS
*/
template <class TReturn>
class StaticCallback0 : public Callback0<TReturn>
{
public:
	typedef TReturn (*FunctionType)();
	typedef StaticCallback0<TReturn> CurrentType;

	StaticCallback0(FunctionType function)
		: func(function)
	{

	}

	virtual TReturn execute()
	{
		func(); 
	}

	virtual bool operator == (const Callback0<TReturn> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func);
	}

private:
	FunctionType func;
};

template <class TReturn, class TArg1>
class StaticCallback1 : public Callback1<TReturn, TArg1>
{
public:
	typedef TReturn (*FunctionType)(TArg1);
	typedef StaticCallback1<TReturn, TArg1> CurrentType;

	StaticCallback1(FunctionType function)
		: func(function)
	{

	}

	virtual TReturn execute(TArg1 arg1)
	{
		func(arg1);
	}

	virtual bool operator == (const Callback1<TReturn, TArg1> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func);
	}

private:
	FunctionType func;
};

template <class TReturn, class TArg1, class TArg2>
class StaticCallback2 : public Callback2<TReturn, TArg1, TArg2>
{
public:
	typedef TReturn (*FunctionType)(TArg1, TArg2);
	typedef StaticCallback2<TReturn, TArg1, TArg2> CurrentType;

	StaticCallback2(FunctionType function)
		: func(function)
	{

	}

	virtual TReturn execute(TArg1 arg1, TArg2 arg2)
	{
		func(arg1, arg2); 
	}

	virtual bool operator == (const Callback2<TReturn, TArg1, TArg2> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func);
	}

private:
	FunctionType func;
};

template <class TReturn, class TArg1, class TArg2, class TArg3>
class StaticCallback3 : public Callback3<TReturn, TArg1, TArg2, TArg3>
{
public:
	typedef TReturn (*FunctionType)(TArg1, TArg2, TArg3);
	typedef StaticCallback3<TReturn, TArg1, TArg2, TArg3> CurrentType;

	StaticCallback3(FunctionType function)
		: func(function)
	{
	}

	virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3)
	{ 
		func(arg1, arg2, arg3); 
	}

	virtual bool operator == (const Callback3<TReturn, TArg1, TArg2, TArg3> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func);
	}

private:
	FunctionType func;
};

template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
class StaticCallback4 : public Callback4<TReturn, TArg1, TArg2, TArg3, TArg4>
{
public:
	typedef TReturn (*FunctionType)(TArg1, TArg2, TArg3, TArg4);
	typedef StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4> CurrentType;

	StaticCallback4(FunctionType function)
		: func(function)
	{
	}

	virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
	{ 
		func(arg1, arg2, arg3, arg4);
	}

	virtual bool operator == (const Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func);
	}

private:
	FunctionType func;
};

template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
class StaticCallback5 : public Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
{
public:
	typedef TReturn (*FunctionType)(TArg1, TArg2, TArg3, TArg4, TArg5);
	typedef StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> CurrentType;

	StaticCallback5(FunctionType function)
		: func(function)
	{
	}

	virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
	{ 
		func(arg1, arg2, arg3, arg4, arg5);
	}

	virtual bool operator == (const Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func);
	}

private:
	FunctionType func;
};

/*****************************************************************************
* CLASS FUNCTION CALLBACKS
*/
template <class TClass, class TReturn>
class ClassCallback0 : public Callback0<TReturn>
{
public:
	typedef TReturn (TClass::*FunctionType)();
	typedef ClassCallback0<TClass, TReturn> CurrentType;

	ClassCallback0(TClass *object, FunctionType function)
		: obj(object), func(function)
	{
	}

	virtual TReturn execute()
	{ 
		(obj->*func)(); 
	}

	virtual bool operator == (const Callback0<TReturn> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func && obj == p_callBack->obj);
	}

private:
	TClass *obj;
	FunctionType func;
};

template <class TClass, class TReturn, class TArg1>
class ClassCallback1 : public Callback1<TReturn, TArg1>
{
public:
	typedef TReturn (TClass::*FunctionType)(TArg1);
	typedef ClassCallback1<TClass, TReturn, TArg1> CurrentType;

	ClassCallback1(TClass *object, FunctionType function)
		: obj(object), func(function)
	{

	}

	virtual TReturn execute(TArg1 arg1)
	{
		(obj->*func)(arg1);
	}

	virtual bool operator == (const Callback1<TReturn, TArg1> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func && obj == p_callBack->obj);
	}

private:
	TClass *obj;
	FunctionType func;
};

template <class TClass, class TReturn, class TArg1, class TArg2>
class ClassCallback2 : public Callback2<TReturn, TArg1, TArg2>
{
public:
	typedef TReturn (TClass::*FunctionType)(TArg1, TArg2);
	typedef ClassCallback2<TClass, TReturn, TArg1, TArg2> CurrentType;

	ClassCallback2(TClass *object, FunctionType function)
		: obj(object), func(function)
	{

	}

	virtual TReturn execute(TArg1 arg1, TArg2 arg2)
	{
		return (obj->*func)(arg1, arg2);
	}

	virtual bool operator == (const Callback2<TReturn, TArg1, TArg2> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func && obj == p_callBack->obj);
	}

private:
	TClass *obj;
	FunctionType func;
};

template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
class ClassCallback3 : public Callback3<TReturn, TArg1, TArg2, TArg3>
{
public:
	typedef TReturn (TClass::*FunctionType)(TArg1, TArg2, TArg3);
	typedef ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3> CurrentType;

	ClassCallback3(TClass *object, FunctionType function)
		: obj(object), func(function)
	{

	}

	virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3)
	{
		(obj->*func)(arg1, arg2, arg3);
	}

	virtual bool operator == (const Callback3<TReturn, TArg1, TArg2, TArg3> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func && obj == p_callBack->obj);
	}

private:
	TClass *obj;
	FunctionType func;
};

template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
class ClassCallback4 : public Callback4<TReturn, TArg1, TArg2, TArg3, TArg4>
{
public:
	typedef TReturn (TClass::*FunctionType)(TArg1, TArg2, TArg3, TArg4);
	typedef ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4> CurrentType;

	ClassCallback4(TClass *object, FunctionType function)
		: obj(object), func(function)
	{

	}

	virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
	{
		(obj->*func)(arg1, arg2, arg3, arg4);
	}

	virtual bool operator == (const Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func && obj == p_callBack->obj);
	}

private:
	TClass *obj;
	FunctionType func;
};

template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
class ClassCallback5 : public Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
{
public:
	typedef TReturn (TClass::*FunctionType)(TArg1, TArg2, TArg3, TArg4, TArg5);
	typedef ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> CurrentType;

	ClassCallback5(TClass *object, FunctionType function)
		: obj(object), func(function)
	{

	}

	virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
	{ 
		(obj->*func)(arg1, arg2, arg3, arg4, arg5);
	}

	virtual bool operator == (const Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> &other) const
	{
		const CurrentType *p_callBack = static_cast<const CurrentType*>(&other);
		return (p_callBack != NULL && func == p_callBack->func && obj == p_callBack->obj);
	}

private:
	TClass *obj;
	FunctionType func;
};

/*****************************************************************************
* CALLBACK SETS
*/
template <class TCallback>
inline void insertCallbackIntoSet(TCallback *p_callBack, std::set<TCallback*> *cb_set)
{
	typename std::set<TCallback*>::iterator it;
	it = cb_set->begin();
	while (it != cb_set->end() && *it != p_callBack && **it != *p_callBack) ++it;
	if (it != cb_set->end())
	{
		if (*it != p_callBack)
		{
			delete *it;
		}
		cb_set->erase(it);
	}

	cb_set->insert(p_callBack);
}

template <class TCallback>
inline void removeCallbackFromSet(TCallback *p_callBack, std::set<TCallback*> *cb_set)
{
	typename std::set<TCallback*>::iterator it;
	it = cb_set->begin();
	while (it != cb_set->end() && *it != p_callBack && **it != *p_callBack) ++it;
	if (it != cb_set->end())
	{
		if (*it != p_callBack)
		{
			delete *it;
			delete p_callBack;
		}
		cb_set->erase(it);
	}
	else
		delete p_callBack;
}

template <class TCallback>
inline void clearCallbackSet(std::set<TCallback*> *cb_set)
{
	typename std::set<TCallback*>::iterator it;
	for (it = cb_set->begin(); it != cb_set->end(); ++it)
		delete *it;
	cb_set->clear();
}

template <class TReturn>
class Callback0Set
{
public:
	typedef Callback0<TReturn> CallbackType;

	void add    (CallbackType *p_callBack) { insertCallbackIntoSet(p_callBack, &callbacks); }
	void remove (CallbackType *p_callBack) { removeCallbackFromSet(p_callBack, &callbacks); }
	void clear  ()                 { clearCallbackSet(&callbacks); }

	void execute()
	{
		typename std::set<CallbackType*>::iterator it;
		for (it = callbacks.begin(); it != callbacks.end(); ++it)
			(*it)->execute();
	}

private:
	std::set<CallbackType*> callbacks;
};

template <class TReturn, class TArg1>
class Callback1Set
{
public:
	typedef Callback1<TReturn, TArg1> CallbackType;

	void add    (CallbackType *p_callBack) { insertCallbackIntoSet(p_callBack, &callbacks); }
	void remove (CallbackType *p_callBack) { removeCallbackFromSet(p_callBack, &callbacks); }
	void clear  ()                 { clearCallbackSet(&callbacks); }

	void execute(TArg1 arg1)
	{
		typename std::set<CallbackType*>::iterator it;
		for (it = callbacks.begin(); it != callbacks.end(); ++it)
			(*it)->execute(arg1);
	}

private:
	std::set<CallbackType*> callbacks;
};

template <class TReturn, class TArg1, class TArg2>
class Callback2Set
{
public:
	typedef Callback2<TReturn, TArg1, TArg2> CallbackType;

	void add    (CallbackType *p_callBack) { insertCallbackIntoSet(p_callBack, &callbacks); }
	void remove (CallbackType *p_callBack) { removeCallbackFromSet(p_callBack, &callbacks); }
	void clear  ()                 { clearCallbackSet(&callbacks); }

	void execute(TArg1 arg1, TArg2 arg2)
	{
		typename std::set<CallbackType*>::iterator it;
		for (it = callbacks.begin(); it != callbacks.end(); ++it)
			(*it)->execute(arg1, arg2);
	}

private:
	std::set<CallbackType*> callbacks;
};

template <class TReturn, class TArg1, class TArg2, class TArg3>
class Callback3Set
{
public:
	typedef Callback3<TReturn, TArg1, TArg2, TArg3> CallbackType;

	void add    (CallbackType *p_callBack) { insertCallbackIntoSet(p_callBack, &callbacks); }
	void remove (CallbackType *p_callBack) { removeCallbackFromSet(p_callBack, &callbacks); }
	void clear  ()                 { clearCallbackSet(&callbacks); }

	void execute(TArg1 arg1, TArg2 arg2, TArg3 arg3)
	{
		typename std::set<CallbackType*>::iterator it;
		for (it = callbacks.begin(); it != callbacks.end(); ++it)
			(*it)->execute(arg1, arg2, arg3);
	}

private:
	std::set<CallbackType*> callbacks;
};

template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
class Callback4Set
{
public:
	typedef Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> CallbackType;

	void add    (CallbackType *p_callBack) { insertCallbackIntoSet(p_callBack, &callbacks); }
	void remove (CallbackType *p_callBack) 
	{
		removeCallbackFromSet(p_callBack, &callbacks); 
	}
	void clear  ()               
	{
		clearCallbackSet(&callbacks);
	}

	void execute(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
	{
		typename std::set<CallbackType*>::iterator it;
		for (it = callbacks.begin(); it != callbacks.end(); ++it)
			(*it)->execute(arg1, arg2, arg3, arg4);
	}

private:
	std::set<CallbackType*> callbacks;
};

template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
class Callback5Set
{
public:
	typedef Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> CallbackType;

	void add    (CallbackType *p_callBack)
	{
		insertCallbackIntoSet(p_callBack, &callbacks);
	}

	void remove (CallbackType *p_callBack)
	{ 
		removeCallbackFromSet(p_callBack, &callbacks);
	}

	void clear  ()                
	{
		clearCallbackSet(&callbacks); 
	}

	void execute(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
	{
		typename std::set<CallbackType*>::iterator it;
		for (it = callbacks.begin(); it != callbacks.end(); ++it)
			(*it)->execute(arg1, arg2, arg3, arg4, arg5);
	}

private:
	std::set<CallbackType*> callbacks;
};

/*****************************************************************************
* CALLBACKS CONSTRUCTORS
*/
template <class TReturn>
inline Callback0<TReturn> * callback(TReturn (*func)())
{ 
	return new StaticCallback0<TReturn>(func);
}


template <class TReturn, class TArg1>
inline Callback1<TReturn, TArg1> * callback(TReturn (*func)(TArg1))
{ 
	return new StaticCallback1<TReturn, TArg1>(func); 
}


template <class TReturn, class TArg1, class TArg2>
inline Callback2<TReturn, TArg1, TArg2> * callback(TReturn (*func)(TArg1, TArg2))
{ 
	return new StaticCallback2<TReturn, TArg1, TArg2>(func); 
}


template <class TReturn, class TArg1, class TArg2, class TArg3>
inline Callback3<TReturn, TArg1, TArg2, TArg3> * callback(TReturn (*func)(TArg1, TArg2, TArg3))
{ 
	return new StaticCallback3<TReturn, TArg1, TArg2, TArg3>(func);
}


template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
inline Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> * callback(TReturn (*func)(TArg1, TArg2, TArg3, TArg4))
{ 
	return new StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>(func);
}


template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
inline Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> * callback(TReturn (*func)(TArg1, TArg2, TArg3, TArg4, TArg5))
{
	return new StaticCallback5<TReturn,TArg1, TArg2, TArg3, TArg4, TArg5>(func); 
}


template <class TClass, class TReturn> 
inline ClassCallback0<TClass, TReturn> * callback(TClass *obj, TReturn (TClass::*func)())
{ 
	return new ClassCallback0<TClass, TReturn>(obj, func);
}


template <class TClass, class TReturn, class TArg1>
inline ClassCallback1<TClass, TReturn, TArg1> * callback(TClass *obj, TReturn (TClass::*func)(TArg1))
{ 
	return new ClassCallback1<TClass, TReturn, TArg1>(obj, func);
}


template <class TClass, class TReturn, class TArg1, class TArg2>
inline ClassCallback2<TClass, TReturn, TArg1, TArg2> * callback(TClass *obj, TReturn (TClass::*func)(TArg1, TArg2))
{ 
	return new ClassCallback2<TClass, TReturn, TArg1, TArg2>(obj, func);
}


template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
inline ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3> * callback(TClass *obj, TReturn (TClass::*func)(TArg1, TArg2, TArg3))
{ 
	return new ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3>(obj, func); 
}


template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
inline ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4> * callback(TClass *obj, TReturn (TClass::*func)(TArg1, TArg2, TArg3, TArg4))
{
	return new ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>(obj, func);
}


template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
inline ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> * callback(TClass *obj, TReturn (TClass::*func)(TArg1, TArg2, TArg3, TArg4, TArg5))
{ 
	return new ClassCallback5<TClass, TReturn,TArg1, TArg2, TArg3, TArg4, TArg5>(obj, func);
}


#endif // __EVE_EVT_CALLBACK_H__
