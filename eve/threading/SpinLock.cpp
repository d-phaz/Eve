
#include "Native_SpinLock.h"

#ifndef __NATIVE_ATOMIC_H__
#include "Native_Atomic.h"
#endif //__NATIVE_ATOMIC_H__

#ifndef __NATIVE_THREADSIMPLE_H__
#include "Native_ThreadSimple.h"
#endif //__NATIVE_THREADSIMPLE_H__

namespace NativeT
{
	namespace
	{
		static const NATIVE_Sint32_t _writelocked = 0;
		static const NATIVE_Sint32_t _unlocked = 1;
	} // namespace anonymous

	namespace detail
	{
		class SpinLock
		{
		public:
			SpinLock() : _state( _unlocked ) {}
			~SpinLock() { _state = _unlocked; }

			inline void set()
			{
				while( true )
				{
					if( trySet( ))
						return;
					NativeT::ThreadSimple::yield();
				}
			}

			inline void unset()
			{
				NATIVE_ASSERT(_state != _unlocked);
				_state = _unlocked;
			}

			inline bool trySet()
			{
				if( !_state.compareAndSetBool(_writelocked, _unlocked))
					return false;
				NATIVE_ASSERT(_state == _writelocked );
				return true;
			}

			inline void setRead()
			{
				while( true )
				{
					if( trySetRead( ))
						return;
					NativeT::ThreadSimple::yield();
				}
			}

			inline void unsetRead()
			{
				while( true )
				{
					NATIVE_ASSERT( _state > _unlocked );
					memoryBarrier();
					const NATIVE_Sint32_t expected = _state;
					if( _state.compareAndSetBool( expected-1, expected ))
						return;
				}
			}

			inline bool trySetRead()
			{
				memoryBarrier();
				const NATIVE_Sint32_t state = _state;
				// Note: 0 used here since using _locked unexplicably gives
				//       'undefined reference to NativeT::SpinLock::_locked'
				const NATIVE_Sint32_t expected = (state == _writelocked) ? _unlocked : state;

				if( !_state.compareAndSetBool( expected+1, expected ))
					return false;

				NATIVE_ASSERT(_state > _unlocked);
				return true;
			}

			inline bool isSet() { return ( _state != _unlocked ); }
			inline bool isSetWrite() { return ( _state == _writelocked ); }
			inline bool isSetRead() { return ( _state > _unlocked ); }

		private:
			a_uint32_t _state;
		};
	}// namespace detail

	SpinLock::SpinLock()
		: _impl( new detail::SpinLock ) {}

	SpinLock::~SpinLock()
	{
		delete _impl;
	}

	void SpinLock::set()
	{
		_impl->set();
	}

	void SpinLock::unset()
	{
		_impl->unset();
	}

	bool SpinLock::trySet()
	{
		return _impl->trySet();
	}

	void SpinLock::setRead()
	{
		_impl->setRead();
	}

	void SpinLock::unsetRead()
	{
		_impl->unsetRead();
	}

	bool SpinLock::trySetRead()
	{
		return _impl->trySetRead();
	}

	bool SpinLock::isSet()
	{
		return _impl->isSet();
	}

	bool SpinLock::isSetWrite()
	{
		return _impl->isSetWrite();
	}

	bool SpinLock::isSetRead()
	{
		return _impl->isSetRead();
	}

} //namespace NativeT
