
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
		/**
		* \class eve::evt::Callback0<class TReturn>
		*
		* \brief Abstract base callback class.
		*
		* Register any method as a callback.
		* The method must provide the following signature: TReturn method(void)
		*/
		template <class TReturn>
		class Callback0
		{
		public:
			virtual ~Callback0(void) {}
			virtual TReturn execute(void) = 0;
			virtual bool operator == (const Callback0<TReturn> & p_other) const = 0;
			virtual bool operator != (const Callback0<TReturn> & p_other) const { return (*this != p_other); }
		};


		/**
		* \class eve::evt::Callback1<class TReturn>, class TArg1>
		*
		* \brief Abstract base callback class.
		*
		* Register any method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1)
		*/
		template <class TReturn, class TArg1>
		class Callback1
		{
		public:
			virtual ~Callback1(void) {}
			virtual TReturn execute(TArg1) = 0;
			virtual bool operator == (const Callback1<TReturn, TArg1> & p_other) const = 0;
			virtual bool operator != (const Callback1<TReturn, TArg1> & p_other) const { return (*this != p_other); }
		};


		/**
		* \class eve::evt::Callback2<class TReturn>, class TArg1, class TArg2>
		*
		* \brief Abstract base callback class.
		*
		* Register any method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2)
		*/
		template <class TReturn, class TArg1, class TArg2>
		class Callback2
		{
		public:
			virtual ~Callback2(void) {}
			virtual TReturn execute(TArg1, TArg2) = 0;
			virtual bool operator == (const Callback2<TReturn, TArg1, TArg2> & p_other) const = 0;
			virtual bool operator != (const Callback2<TReturn, TArg1, TArg2> & p_other) const { return (*this != p_other); }
		};


		/**
		* \class eve::evt::Callback3<class TReturn>, class TArg1, class TArg2, class TArg3>
		*
		* \brief Abstract base callback class.
		*
		* Register any method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3)
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3>
		class Callback3
		{
		public:
			virtual ~Callback3(void) {}
			virtual TReturn execute(TArg1, TArg2, TArg3) = 0;
			virtual bool operator == (const Callback3<TReturn, TArg1, TArg2, TArg3> &p_other) const = 0;
			virtual bool operator != (const Callback3<TReturn, TArg1, TArg2, TArg3> &p_other) const { return (*this != p_other); }
		};


		/**
		* \class eve::evt::Callback4<class TReturn>, class TArg1, class TArg2, class TArg3, class TArg4>
		*
		* \brief Abstract base callback class.
		*
		* Register any method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		class Callback4
		{
		public:
			virtual ~Callback4(void) {}
			virtual TReturn execute(TArg1, TArg2, TArg3, TArg4) = 0;
			virtual bool operator == (const Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> &p_other) const = 0;
			virtual bool operator != (const Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> &p_other) const { return (*this != p_other); }
		};


		/**
		* \class eve::evt::Callback4<class TReturn>, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		*
		* \brief Abstract base callback class.
		*
		* Register any method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		class Callback5
		{
		public:
			virtual ~Callback5(void) {}
			virtual TReturn execute(TArg1, TArg2, TArg3, TArg4, TArg5) = 0;
			virtual bool operator == (const Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> &p_other) const = 0;
			virtual bool operator != (const Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> &p_other) const { return (*this != p_other); }
		};

	} // namespace evt

} // namespace eve


namespace eve
{
	namespace evt
	{
		/**
		* \class eve::evt::StaticCallback0<class TReturn>
		*
		* \brief Abstract base callback class.
		*
		* Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(void)
		*
		* \note extends eve::evt::Callback0<TReturn>
		*/
		template <class TReturn>
		class StaticCallback0 
			: public Callback0<TReturn>
		{
		public:
			typedef TReturn(*FunctionType)(void);
			typedef StaticCallback0<TReturn> CurrentType;

		private:
			FunctionType func;

		public:
			StaticCallback0(FunctionType function) 
				: func(function) 
			{}

			virtual TReturn execute(void) override
			{ 
				func(); 
			}

			virtual bool operator == (const Callback0<TReturn> &p_other) const override
			{
				const CurrentType *p_callBack = reinterpret_cast<const CurrentType*>(&p_other);
				return (p_callBack != NULL && func == p_callBack->func);
			}
		};


		/**
		* \class eve::evt::StaticCallback1<class TReturn, class TArg1>
		*
		* \brief Abstract base callback class.
		*
		* Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1)
		*
		* \note extends eve::evt::Callback1<TReturn, TArg1>
		*/
		template <class TReturn, class TArg1>
		class StaticCallback1 
			: public Callback1<TReturn, TArg1>
		{
		public:
			typedef TReturn(*FunctionType)(TArg1);
			typedef StaticCallback1<TReturn, TArg1> CurrentType;

		private:
			FunctionType func;

		public:
			StaticCallback1(FunctionType function)
				: func(function)
			{}

			virtual TReturn execute(TArg1 arg1) override
			{
				func(arg1);
			}

			virtual bool operator == (const Callback1<TReturn, TArg1> &p_other) const override
			{
				const CurrentType *p_callBack = reinterpret_cast<const CurrentType*>(&p_other);
				return (p_callBack != NULL && func == p_callBack->func);
			}
		};


		/**
		* \class eve::evt::StaticCallback2<class TReturn, class TArg1, class TArg2>
		*
		* \brief Abstract base callback class.
		*
		* Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2)
		*
		* \note extends eve::evt::Callback2<TReturn, TArg1, TArg2>
		*/
		template <class TReturn, class TArg1, class TArg2>
		class StaticCallback2 
			: public Callback2<TReturn, TArg1, TArg2>
		{
		public:
			typedef TReturn(*FunctionType)(TArg1, TArg2);
			typedef StaticCallback2<TReturn, TArg1, TArg2> CurrentType;

		private:
			FunctionType func;

		public:
			StaticCallback2(FunctionType function)
				: func(function)
			{}

			virtual TReturn execute(TArg1 arg1, TArg2 arg2) override
			{
				func(arg1, arg2);
			}

			virtual bool operator == (const Callback2<TReturn, TArg1, TArg2> &p_other) const override
			{
				const CurrentType *p_callBack = reinterpret_cast<const CurrentType*>(&p_other);
				return (p_callBack != NULL && func == p_callBack->func);
			}
		};


		/**
		* \class eve::evt::StaticCallback3<class TReturn, class TArg1, class TArg2, class TArg3>
		*
		* \brief Abstract base callback class.
		*
		* Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3)
		*
		* \note extends eve::evt::Callback3<TReturn, TArg1, TArg2, TArg3>
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3>
		class StaticCallback3 
			: public Callback3<TReturn, TArg1, TArg2, TArg3>
		{
		public:
			typedef TReturn(*FunctionType)(TArg1, TArg2, TArg3);
			typedef StaticCallback3<TReturn, TArg1, TArg2, TArg3> CurrentType;

		private:
			FunctionType func;

		public:
			StaticCallback3(FunctionType function)
				: func(function)
			{}

			virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3) override
			{
				func(arg1, arg2, arg3);
			}

			virtual bool operator == (const Callback3<TReturn, TArg1, TArg2, TArg3> &p_other) const override
			{
				const CurrentType *p_callBack = reinterpret_cast<const CurrentType*>(&p_other);
				return (p_callBack != NULL && func == p_callBack->func);
			}
		};


		/**
		* \class eve::evt::StaticCallback3<class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		*
		* \brief Abstract base callback class.
		*
		* Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		*
		* \note extends eve::evt::Callback4<TReturn, TArg1, TArg2, TArg3, TArg4>
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		class StaticCallback4 
			: public Callback4<TReturn, TArg1, TArg2, TArg3, TArg4>
		{
		public:
			typedef TReturn(*FunctionType)(TArg1, TArg2, TArg3, TArg4);
			typedef StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4> CurrentType;

		private:
			FunctionType func;

		public:
			StaticCallback4(FunctionType function)
				: func(function)
			{}

			virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) override
			{
				func(arg1, arg2, arg3, arg4);
			}

			virtual bool operator == (const Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> &p_other) const override
			{
				const CurrentType *p_callBack = reinterpret_cast<const CurrentType*>(&p_other);
				return (p_callBack != NULL && func == p_callBack->func);
			}
		};


		/**
		* \class eve::evt::StaticCallback5<class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		*
		* \brief Abstract base callback class.
		*
		* Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
		*
		* \note extends eve::evt::Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		class StaticCallback5 
			: public Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
		{
		public:
			typedef TReturn(*FunctionType)(TArg1, TArg2, TArg3, TArg4, TArg5);
			typedef StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> CurrentType;

		private:
			FunctionType func;

		public:
			StaticCallback5(FunctionType function)
				: func(function)
			{}

			virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5) override
			{
				func(arg1, arg2, arg3, arg4, arg5);
			}

			virtual bool operator == (const Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> &p_other) const override
			{
				const CurrentType *p_callBack = reinterpret_cast<const CurrentType*>(&p_other);
				return (p_callBack != NULL && func == p_callBack->func);
			}
		};


		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(void)
		*/
		template <class TReturn>
		inline Callback0<TReturn> * create_callback(TReturn(*func)());
		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1)
		*/
		template <class TReturn, class TArg1>
		inline Callback1<TReturn, TArg1> * create_callback(TReturn(*func)(TArg1));
		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2)
		*/
		template <class TReturn, class TArg1, class TArg2>
		inline Callback2<TReturn, TArg1, TArg2> * create_callback(TReturn(*func)(TArg1, TArg2));
		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3)
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3>
		inline Callback3<TReturn, TArg1, TArg2, TArg3> * create_callback(TReturn(*func)(TArg1, TArg2, TArg3));
		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		inline Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> * create_callback(TReturn(*func)(TArg1, TArg2, TArg3, TArg4));
		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		inline Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> * create_callback(TReturn(*func)(TArg1, TArg2, TArg3, TArg4, TArg5));

	} // namespace evt

} // namespace eve


//=================================================================================================
template <class TReturn>
inline eve::evt::Callback0<TReturn> * eve::evt::create_callback(TReturn(*func)())
{
	return new eve::evt::StaticCallback0<TReturn>(func);
}

//=================================================================================================
template <class TReturn, class TArg1>
inline eve::evt::Callback1<TReturn, TArg1> * eve::evt::create_callback(TReturn(*func)(TArg1))
{
	return new eve::evt::StaticCallback1<TReturn, TArg1>(func);
}

//=================================================================================================
template <class TReturn, class TArg1, class TArg2>
inline eve::evt::Callback2<TReturn, TArg1, TArg2> * eve::evt::create_callback(TReturn(*func)(TArg1, TArg2))
{
	return new eve::evt::StaticCallback2<TReturn, TArg1, TArg2>(func);
}

//=================================================================================================
template <class TReturn, class TArg1, class TArg2, class TArg3>
inline eve::evt::Callback3<TReturn, TArg1, TArg2, TArg3> * eve::evt::create_callback(TReturn(*func)(TArg1, TArg2, TArg3))
{
	return new eve::evt::StaticCallback3<TReturn, TArg1, TArg2, TArg3>(func);
}

//=================================================================================================
template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
inline eve::evt::Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> * eve::evt::create_callback(TReturn(*func)(TArg1, TArg2, TArg3, TArg4))
{
	return new eve::evt::StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>(func);
}

//=================================================================================================
template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
inline eve::evt::Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> * eve::evt::create_callback(TReturn(*func)(TArg1, TArg2, TArg3, TArg4, TArg5))
{
	return new eve::evt::StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>(func);
}





namespace eve
{
	namespace evt
	{
		/**
		* \class eve::evt::ClassCallback0<class TClass, class TReturn>
		*
		* \brief Abstract base callback class.
		*
		* Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(void)
		*
		* \note extends eve::evt::Callback0<TReturn>
		*/
		template <class TClass, class TReturn>
		class ClassCallback0 
			: public Callback0<TReturn>
		{
		public:
			typedef TReturn(TClass::*FunctionType)();
			typedef ClassCallback0<TClass, TReturn> CurrentType;

		private:
			TClass *	 obj;
			FunctionType func;

		public:
			ClassCallback0(TClass *object, FunctionType function)
				: obj(object)
				, func(function)
			{}

			virtual TReturn execute(void) override
			{
				(obj->*func)();
			}

			virtual bool operator == (const Callback0<TReturn> &p_other) const override
			{
				const CurrentType *cb = reinterpret_cast<const CurrentType*>(&p_other);
				return (cb != NULL && func == cb->func && obj == cb->obj);
			}
		};


		/**
		* \class eve::evt::ClassCallback1<class TClass, class TReturn, class TArg1>
		*
		* \brief Abstract base callback class.
		*
		* Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1)
		*
		* \note extends eve::evt::Callback1<TReturn, TArg1>
		*/
		template <class TClass, class TReturn, class TArg1>
		class ClassCallback1 
			: public Callback1<TReturn, TArg1>
		{
		public:
			typedef TReturn(TClass::*FunctionType)(TArg1);
			typedef ClassCallback1<TClass, TReturn, TArg1> CurrentType;

		private:
			TClass *	 obj;
			FunctionType func;

		public:
			ClassCallback1(TClass *object, FunctionType function)
				: obj(object)
				, func(function)
			{}

			virtual TReturn execute(TArg1 arg1) override
			{
				(obj->*func)(arg1);
			}

			virtual bool operator == (const Callback1<TReturn, TArg1> &p_other) const override
			{
				const CurrentType *cb = reinterpret_cast<const CurrentType*>(&p_other);
				return (cb != NULL && func == cb->func && obj == cb->obj);
			}
		};


		/**
		* \class eve::evt::ClassCallback2<class TClass, class TReturn, class TArg1, class TArg2>
		*
		* \brief Abstract base callback class.
		*
		* Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2)
		*
		* \note extends eve::evt::Callback2<TReturn, TArg1, TArg2>
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2>
		class ClassCallback2 
			: public Callback2<TReturn, TArg1, TArg2>
		{
		public:
			typedef TReturn(TClass::*FunctionType)(TArg1, TArg2);
			typedef ClassCallback2<TClass, TReturn, TArg1, TArg2> CurrentType;

		private:
			TClass *	 obj;
			FunctionType func;

		public:
			ClassCallback2(TClass *object, FunctionType function)
				: obj(object)
				, func(function)
			{}

			virtual TReturn execute(TArg1 arg1, TArg2 arg2) override
			{
				return (obj->*func)(arg1, arg2);
			}

			virtual bool operator == (const Callback2<TReturn, TArg1, TArg2> &p_other) const override
			{
				const CurrentType *cb = reinterpret_cast<const CurrentType*>(&p_other);
				return (cb != NULL && func == cb->func && obj == cb->obj);
			}
		};


		/**
		* \class eve::evt::ClassCallback3<class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
		*
		* \brief Abstract base callback class.
		*
		* Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3)
		*
		* \note extends eve::evt::Callback3<TReturn, TArg1, TArg2, TArg3>
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
		class ClassCallback3 
			: public Callback3<TReturn, TArg1, TArg2, TArg3>
		{
		public:
			typedef TReturn(TClass::*FunctionType)(TArg1, TArg2, TArg3);
			typedef ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3> CurrentType;

		private:
			TClass *	 obj;
			FunctionType func;

		public:
			ClassCallback3(TClass *object, FunctionType function)
				: obj(object)
				, func(function)
			{}

			virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3) override
			{
				(obj->*func)(arg1, arg2, arg3);
			}

			virtual bool operator == (const Callback3<TReturn, TArg1, TArg2, TArg3> &p_other) const override
			{
				const CurrentType *cb = reinterpret_cast<const CurrentType*>(&p_other);
				return (cb != NULL && func == cb->func && obj == cb->obj);
			}
		};


		/**
		* \class eve::evt::ClassCallback4<class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		*
		* \brief Abstract base callback class.
		*
		* Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		*
		* \note extends eve::evt::Callback4<TReturn, TArg1, TArg2, TArg3, TArg4>
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		class ClassCallback4 
			: public Callback4<TReturn, TArg1, TArg2, TArg3, TArg4>
		{
		public:
			typedef TReturn(TClass::*FunctionType)(TArg1, TArg2, TArg3, TArg4);
			typedef ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4> CurrentType;

		private:
			TClass *	 obj;
			FunctionType func;

		public:
			ClassCallback4(TClass *object, FunctionType function)
				: obj(object)
				, func(function)
			{}

			virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) override
			{
				(obj->*func)(arg1, arg2, arg3, arg4);
			}

			virtual bool operator == (const Callback4<TReturn, TArg1, TArg2, TArg3, TArg4> &p_other) const override
			{
				const CurrentType *cb = reinterpret_cast<const CurrentType*>(&p_other);
				return (cb != NULL && func == cb->func && obj == cb->obj);
			}
		};


		/**
		* \class eve::evt::ClassCallback5<class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		*
		* \brief Abstract base callback class.
		*
		* Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
		*
		* \note extends eve::evt::Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		class ClassCallback5 
			: public Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
		{
		public:
			typedef TReturn(TClass::*FunctionType)(TArg1, TArg2, TArg3, TArg4, TArg5);
			typedef ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> CurrentType;

		private:
			TClass *obj;
			FunctionType func;

		public:
			ClassCallback5(TClass *object, FunctionType function)
				: obj(object)
				, func(function)
			{}

			virtual TReturn execute(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5) override
			{
				(obj->*func)(arg1, arg2, arg3, arg4, arg5);
			}

			virtual bool operator == (const Callback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> &p_other) const override
			{
				const CurrentType *cb = reinterpret_cast<const CurrentType*>(&p_other);
				return (cb != NULL && func == cb->func && obj == cb->obj);
			}
		};
		

		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(void)
		*/
		template <class TClass, class TReturn>
		inline ClassCallback0<TClass, TReturn> * create_callback(TClass *obj, TReturn(TClass::*func)());
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1)
		*/
		template <class TClass, class TReturn, class TArg1>
		inline ClassCallback1<TClass, TReturn, TArg1> * create_callback(TClass *obj, TReturn(TClass::*func)(TArg1));
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2)
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2>
		inline ClassCallback2<TClass, TReturn, TArg1, TArg2> * create_callback(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2));
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3)
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
		inline ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3> * create_callback(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3));
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		inline ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4> * create_callback(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3, TArg4));
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		inline ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> * create_callback(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3, TArg4, TArg5));

	} // namespace evt

} // namespace eve


//=================================================================================================
template <class TClass, class TReturn>
inline eve::evt::ClassCallback0<TClass, TReturn> * eve::evt::create_callback(TClass *obj, TReturn(TClass::*func)())
{
	return new eve::evt::ClassCallback0<TClass, TReturn>(obj, func);
}

//=================================================================================================
template <class TClass, class TReturn, class TArg1>
inline eve::evt::ClassCallback1<TClass, TReturn, TArg1> * create_callback(TClass *obj, TReturn(TClass::*func)(TArg1))
{
	return new ClassCallback1<TClass, TReturn, TArg1>(obj, func);
}

//=================================================================================================
template <class TClass, class TReturn, class TArg1, class TArg2>
inline eve::evt::ClassCallback2<TClass, TReturn, TArg1, TArg2> * eve::evt::create_callback(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2))
{
	return new eve::evt::ClassCallback2<TClass, TReturn, TArg1, TArg2>(obj, func);
}

//=================================================================================================
template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
inline eve::evt::ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3> * eve::evt::create_callback(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3))
{
	return new eve::evt::ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3>(obj, func);
}

//=================================================================================================
template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
inline eve::evt::ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4> * eve::evt::create_callback(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3, TArg4))
{
	return new eve::evt::ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>(obj, func);
}

//=================================================================================================
template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
inline eve::evt::ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> * eve::evt::create_callback(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3, TArg4, TArg5))
{
	return new eve::evt::ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>(obj, func);
}

#endif // __EVE_EVT_CALLBACK_H__
