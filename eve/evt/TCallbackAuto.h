
#pragma once
#ifndef __EVE_EVT_TCALLBACK_AUTO_H__
#define __EVE_EVT_TCALLBACK_AUTO_H__

#ifndef __EVE_EVT_TCALLBACK_H__
#include "eve/evt/TCallback.h"
#endif


namespace eve
{
	namespace evt
	{
		/**
		* \class eve::evt::CallbackAuto
		*
		* \brief Abstract base auto callback class.
		* Auto callback class stocks callback method argument(s).
		* Register any method as a callback.
		*/
		class CallbackAuto
		{
		public:
			virtual ~CallbackAuto(void) {}
			virtual void execute(void) = 0;
			virtual bool operator == (const CallbackAuto &p_other) const = 0;
			virtual bool operator != (const CallbackAuto &p_other) const { return (*this != p_other); }
		};

	} // namespace evt

} // namespace eve


namespace eve
{
	namespace evt
	{
		/**
		* \class eve::evt::CallbackAutoStatic0<class TReturn>
		*
		* \brief Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(void)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::StaticCallback0<TReturn>
		*/
		template <class TReturn>
		class CallbackAutoStatic0
			: public eve::evt::CallbackAuto
			, public eve::evt::StaticCallback0<TReturn>
		{
		public:
			typedef eve::evt::StaticCallback0<TReturn> ParentType;

			CallbackAutoStatic0(typename ParentType::FunctionType p_fn)
				: eve::evt::CallbackAuto()
				, eve::evt::StaticCallback0<TReturn>(p_fn)
			{}

			virtual void execute(void) override
			{
				eve::evt::StaticCallback0<TReturn>::execute();
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};


		/**
		* \class eve::evt::CallbackAutoStatic1<class TReturn, class TArg1>
		*
		* \brief Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::StaticCallback1<TReturn, TArg1>
		*/
		template <class TReturn, class TArg1>
		class CallbackAutoStatic1 
			: public eve::evt::CallbackAuto
			, public eve::evt::StaticCallback1<TReturn, TArg1>
		{
		private:
			TArg1 a1;

		public:
			typedef eve::evt::StaticCallback1<TReturn, TArg1> ParentType;

			CallbackAutoStatic1(typename ParentType::FunctionType p_fn, TArg1 arg1)
				: eve::evt::CallbackAuto()
				, eve::evt::StaticCallback1<TReturn, TArg1>(p_fn)
				, a1(arg1)
			{}

			virtual void execute(void) override
			{
				eve::evt::StaticCallback1<TReturn, TArg1>::execute(a1);
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};


		/**
		* \class eve::evt::CallbackAutoStatic2<class TReturn, class TArg1, class TArg2>
		*
		* \brief Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::StaticCallback2<TReturn, TArg1, TArg2>
		*/
		template <class TReturn, class TArg1, class TArg2>
		class CallbackAutoStatic2 
			: public eve::evt::CallbackAuto
			, public eve::evt::StaticCallback2<TReturn, TArg1, TArg2>
		{
		private:
			TArg1 a1;
			TArg2 a2;

		public:
			typedef eve::evt::StaticCallback2<TReturn, TArg1, TArg2> ParentType;

			CallbackAutoStatic2(typename ParentType::FunctionType p_fn, TArg1 arg1, TArg2 arg2)
				: eve::evt::CallbackAuto()
				, eve::evt::StaticCallback2<TReturn, TArg1, TArg2>(p_fn)
				, a1(arg1)
				, a2(arg2)
			{}

			virtual void execute(void) override
			{
				eve::evt::StaticCallback2<TReturn, TArg1, TArg2>::execute(a1, a2);
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};


		/**
		* \class eve::evt::CallbackAutoStatic3<class TReturn, class TArg1, class TArg2, class TArg3>
		*
		* \brief Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::StaticCallback3<TReturn, TArg1, TArg2, TArg3>
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3>
		class CallbackAutoStatic3 
			: public eve::evt::CallbackAuto
			, public eve::evt::StaticCallback3<TReturn, TArg1, TArg2, TArg3>
		{
		private:
			TArg1 a1;
			TArg2 a2;
			TArg3 a3;

		public:
			typedef eve::evt::StaticCallback3<TReturn, TArg1, TArg2, TArg3> ParentType;

			CallbackAutoStatic3(typename ParentType::FunctionType p_fn, TArg1 arg1, TArg2 arg2, TArg3 arg3)
				: eve::evt::CallbackAuto()
				, eve::evt::StaticCallback3<TReturn, TArg1, TArg2, TArg3>(p_fn)
				, a1(arg1)
				, a2(arg2)
				, a3(arg3)
			{}

			virtual void execute(void) override
			{
				eve::evt::StaticCallback3<TReturn, TArg1, TArg2, TArg3>::execute(a1, a2, a3);
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};


		/**
		* \class eve::evt::CallbackAutoStatic4<class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		*
		* \brief Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		class CallbackAutoStatic4 
			: public eve::evt::CallbackAuto
			, public eve::evt::StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>
		{
		private:
			TArg1 a1;
			TArg2 a2;
			TArg3 a3;
			TArg4 a4;

		public:
			typedef eve::evt::StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4> ParentType;

			CallbackAutoStatic4(typename ParentType::FunctionType p_fn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
				: eve::evt::CallbackAuto()
				, eve::evt::StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>(p_fn)
				, a1(arg1)
				, a2(arg2)
				, a3(arg3)
				, a4(arg4)
			{}

			virtual void execute(void) override
			{
				eve::evt::StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>::execute(a1, a2, a3, a4);
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};


		/**
		* \class eve::evt::CallbackAutoStatic4<class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		*
		* \brief Register any global or static method as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::StaticCallback4<TReturn, TArg1, TArg2, TArg3, TArg4>
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		class CallbackAutoStatic5 
			: public eve::evt::CallbackAuto
			, public eve::evt::StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
		{
		private:
			TArg1 a1;
			TArg2 a2;
			TArg3 a3;
			TArg4 a4;
			TArg5 a5;

		public:
			typedef eve::evt::StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> ParentType;

			CallbackAutoStatic5(typename ParentType::FunctionType p_fn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
				: eve::evt::CallbackAuto()
				, eve::evt::StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>(p_fn)
				, a1(arg1)
				, a2(arg2)
				, a3(arg3)
				, a4(arg4)
				, a5(arg5)
			{}

			virtual void execute(void) override
			{
				eve::evt::StaticCallback5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>::execute(a1, a2, a3, a4, a5);
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};


		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(void)
		*/
		template <class TReturn>
		inline CallbackAuto * create_callback_auto(TReturn(*func)());
		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1)
		*/
		template <class TReturn, class TArg1>
		inline CallbackAuto * create_callback_auto(TReturn(*func)(TArg1), TArg1 arg1);
		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2)
		*/
		template <class TReturn, class TArg1, class TArg2>
		inline CallbackAuto * create_callback_auto(TReturn(*func)(TArg1, TArg2), TArg1 arg1, TArg2 arg2);
		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3)
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3>
		inline CallbackAuto * create_callback_auto(TReturn(*func)(TArg1, TArg2, TArg3), TArg1 arg1, TArg2 arg2, TArg3 arg3);
		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		inline CallbackAuto * create_callback_auto(TReturn(*func)(TArg1, TArg2, TArg3, TArg4), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4);
		/**
		* \brief Create and return a new static or global method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
		*/
		template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		inline CallbackAuto * create_callback_auto(TReturn(*func)(TArg1, TArg2, TArg3, TArg4, TArg5), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5);

	} // namespace evt

} // namespace eve

//=================================================================================================
template <class TReturn>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TReturn(*func)(void))
{
	return new eve::evt::CallbackAutoStatic0<TReturn>(func);
}

//=================================================================================================
template <class TReturn, class TArg1>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TReturn(*func)(TArg1), TArg1 arg1)
{
	return new eve::evt::CallbackAutoStatic1<TReturn, TArg1>(func, arg1);
}

//=================================================================================================
template <class TReturn, class TArg1, class TArg2>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TReturn(*func)(TArg1, TArg2), TArg1 arg1, TArg2 arg2)
{
	return new eve::evt::CallbackAutoStatic2<TReturn, TArg1, TArg2>(func, arg1, arg2);
}

//=================================================================================================
template <class TReturn, class TArg1, class TArg2, class TArg3>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TReturn(*func)(TArg1, TArg2, TArg3), TArg1 arg1, TArg2 arg2, TArg3 arg3)
{
	return new eve::evt::CallbackAutoStatic3<TReturn, TArg1, TArg2, TArg3>(func, arg1, arg2, arg3);
}

//=================================================================================================
template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TReturn(*func)(TArg1, TArg2, TArg3, TArg4), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
{
	return new eve::evt::CallbackAutoStatic4<TReturn, TArg1, TArg2, TArg3, TArg4>(func, arg1, arg2, arg3, arg4);
}

//=================================================================================================
template <class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TReturn(*func)(TArg1, TArg2, TArg3, TArg4, TArg5), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
{
	return new eve::evt::CallbackAutoStatic5<TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>(func, arg1, arg2, arg3, arg4, arg5);
}


namespace eve
{
	namespace evt
	{
		/**
		* \class eve::evt::CallbackAutoClass0<class TClass, class TReturn>
		*
		* \brief Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(void)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::ClassCallback0<TClass, TReturn>
		*/
		template <class TClass, class TReturn>
		class CallbackAutoClass0 
			: public eve::evt::CallbackAuto
			, public eve::evt::ClassCallback0<TClass, TReturn>
		{
		public:
			typedef eve::evt::ClassCallback0<TClass, TReturn> ParentType;

			CallbackAutoClass0(TClass *object, typename ParentType::FunctionType p_fn)
				: eve::evt::CallbackAuto()
				, eve::evt::ClassCallback0<TClass, TReturn>(object, p_fn)
			{}

			virtual void execute(void) override
			{
				eve::evt::ClassCallback0<TClass, TReturn>::execute();
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (*(ParentType*)this == *cb);
			}
		};


		/**
		* \class eve::evt::CallbackAutoClass1<class TClass, class TReturn, class TArg1>
		*
		* \brief Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::ClassCallback1<TClass, TReturn, TArg1>
		*/
		template <class TClass, class TReturn, class TArg1>
		class CallbackAutoClass1 
			: public eve::evt::CallbackAuto
			, public eve::evt::ClassCallback1<TClass, TReturn, TArg1>
		{
		private:
			TArg1 a1;

		public:
			typedef eve::evt::ClassCallback1<TClass, TReturn, TArg1> ParentType;

			CallbackAutoClass1(TClass *object, typename ParentType::FunctionType p_fn, TArg1 arg1)
				: eve::evt::CallbackAuto()
				, eve::evt::ClassCallback1<TClass, TReturn, TArg1>(object, p_fn)
				, a1(arg1)
			{}

			virtual void execute(void) override
			{
				eve::evt::ClassCallback1<TClass, TReturn, TArg1>::execute(a1);
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};


		/**
		* \class eve::evt::CallbackAutoClass2<class TClass, class TReturn, class TArg1, class TArg2>
		*
		* \brief Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::ClassCallback2<TClass, TReturn, TArg1, TArg2>
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2>
		class CallbackAutoClass2
			: public eve::evt::CallbackAuto
			, public eve::evt::ClassCallback2<TClass, TReturn, TArg1, TArg2>
		{
		private:
			TArg1 a1;
			TArg2 a2;

		public:
			typedef eve::evt::ClassCallback2<TClass, TReturn, TArg1, TArg2> ParentType;

			CallbackAutoClass2(TClass *object, typename ParentType::FunctionType p_fn, TArg1 arg1, TArg2 arg2)
				: eve::evt::CallbackAuto()
				, eve::evt::ClassCallback2<TClass, TReturn, TArg1, TArg2>(object, p_fn)
				, a1(arg1)
				, a2(arg2)
			{}

			virtual void execute(void) override
			{
				eve::evt::ClassCallback2<TClass, TReturn, TArg1, TArg2>::execute(a1, a2);
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};


		/**
		* \class eve::evt::CallbackAutoClass3<class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
		*
		* \brief Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3>
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
		class CallbackAutoClass3
			: public eve::evt::CallbackAuto
			, public eve::evt::ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3>
		{
		private:
			TArg1 a1;
			TArg2 a2;
			TArg3 a3;

		public:
			typedef eve::evt::ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3> ParentType;

			CallbackAutoClass3(TClass *object, typename ParentType::FunctionType p_fn, TArg1 arg1, TArg2 arg2, TArg3 arg3)
				: eve::evt::CallbackAuto()
				, eve::evt::ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3>(object, p_fn)
				, a1(arg1)
				, a2(arg2)
				, a3(arg3)
			{}

			virtual void execute(void) override
			{
				eve::evt::ClassCallback3<TClass, TReturn, TArg1, TArg2, TArg3>::execute(a1, a2, a3);
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};


		/**
		* \class eve::evt::CallbackAutoClass4<class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		*
		* \brief Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		class CallbackAutoClass4
			: public eve::evt::CallbackAuto
			, public eve::evt::ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>
		{
		private:
			TArg1 a1;
			TArg2 a2;
			TArg3 a3;
			TArg4 a4;

		public:
			typedef eve::evt::ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4> ParentType;

			CallbackAutoClass4(TClass *object, typename ParentType::FunctionType p_fn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
				: eve::evt::CallbackAuto()
				, eve::evt::ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>(object, p_fn)
				, a1(arg1)
				, a2(arg2)
				, a3(arg3)
				, a4(arg4)
			{}

			virtual void execute(void) override
			{
				eve::evt::ClassCallback4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>::execute(a1, a2, a3, a4);
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};


		/**
		* \class eve::evt::CallbackAutoClass5<class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		*
		* \brief Register any method of any class as a callback.
		* The method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5arg5)
		*
		* \note extends eve::evt::CallbackAuto, eve::evt::ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		class CallbackAutoClass5
			: public eve::evt::CallbackAuto
			, public eve::evt::ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>
		{
		private:
			TArg1 a1;
			TArg2 a2;
			TArg3 a3;
			TArg4 a4;
			TArg5 a5;

		public:
			typedef eve::evt::ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5> ParentType;

			CallbackAutoClass5(TClass *object, typename ParentType::FunctionType p_fn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
				: eve::evt::CallbackAuto()
				, eve::evt::ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>(object, p_fn)
				, a1(arg1)
				, a2(arg2)
				, a3(arg3)
				, a4(arg4)
				, a5(arg5)
			{}

			virtual void execute(void) override
			{
				eve::evt::ClassCallback5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>::execute(a1, a2, a3, a4, a5);
			}

			virtual bool operator == (const eve::evt::CallbackAuto &p_other) const override
			{
				const ParentType *cb = dynamic_cast<const ParentType*>(&p_other);
				return (cb != NULL && *(ParentType*)this == *cb);
			}
		};

		
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(void)
		*/
		template <class TClass, class TReturn>
		inline CallbackAuto * create_callback_auto(TClass *obj, TReturn(TClass::*func)());
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1)
		*/
		template <class TClass, class TReturn, class TArg1>
		inline CallbackAuto * create_callback_auto(TClass *obj, TReturn(TClass::*func)(TArg1), TArg1 arg1);
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2)
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2>
		inline CallbackAuto * create_callback_auto(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2), TArg1 arg1, TArg2 arg2);
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3)
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
		inline CallbackAuto * create_callback_auto(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3), TArg1 arg1, TArg2 arg2, TArg3 arg3);
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
		inline CallbackAuto * create_callback_auto(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3, TArg4), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4);
		/**
		* \brief Create and return a new class method callback.
		* Method must provide the following signature: TReturn method(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
		*/
		template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
		inline CallbackAuto * create_callback_auto(TClass * obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3, TArg4, TArg5), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5);

	} // namespace evt

} // namespace eve

//=================================================================================================
template <class TClass, class TReturn>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TClass *obj, TReturn(TClass::*func)())
{
	return new eve::evt::CallbackAutoClass0<TClass, TReturn>(obj, func);
}

//=================================================================================================
template <class TClass, class TReturn, class TArg1>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TClass *obj, TReturn(TClass::*func)(TArg1), TArg1 arg1)
{
	return new eve::evt::CallbackAutoClass1<TClass, TReturn, TArg1>(obj, func, arg1);
}

//=================================================================================================
template <class TClass, class TReturn, class TArg1, class TArg2>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2), TArg1 arg1, TArg2 arg2)
{
	return new eve::evt::CallbackAutoClass2<TClass, TReturn, TArg1, TArg2>(obj, func, arg1, arg2);
}

//=================================================================================================
template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3), TArg1 arg1, TArg2 arg2, TArg3 arg3)
{
	return new eve::evt::CallbackAutoClass3<TClass, TReturn, TArg1, TArg2, TArg3>(obj, func, arg1, arg2, arg3);
}

//=================================================================================================
template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TClass *obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3, TArg4), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
{
	return new eve::evt::CallbackAutoClass4<TClass, TReturn, TArg1, TArg2, TArg3, TArg4>(obj, func, arg1, arg2, arg3, arg4);
}

//=================================================================================================
template <class TClass, class TReturn, class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
inline eve::evt::CallbackAuto * eve::evt::create_callback_auto(TClass * obj, TReturn(TClass::*func)(TArg1, TArg2, TArg3, TArg4, TArg5), TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
{
	return new eve::evt::CallbackAutoClass5<TClass, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5>(obj, func, arg1, arg2, arg3, arg4, arg5);
}

#endif // __EVE_EVT_TCALLBACK_AUTO_H__
