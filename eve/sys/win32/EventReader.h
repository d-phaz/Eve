//
//#pragma once
//#ifndef __EVE_SYSTEM_EVENT_READER_H__
//#define __EVE_SYSTEM_EVENT_READER_H__
//
//#ifndef __EVE_CORE_INCLUDES_H__
//#include "eve/core/Includes.h"
//#endif
//
//#ifndef __EVE_MEMORY_INCLUDES_H__
//#include "eve/mem/Includes.h"
//#endif
//
//#ifndef __EVE_MESSAGING_INCLUDES_H__
//#include "eve/mess/Includes.h"
//#endif
//
//
//namespace eve
//{
//	namespace sys
//	{
//		/**
//		* \class eve::sys::EventReader
//		*
//		* \brief Interpret eve::sys::MessagePump received events and translate them to eve readable ones.
//		*
//		* \note extends eve::mem::Pointer
//		*/
//		class EventReader final
//			: public eve::mem::Pointer
//		{
//
//			friend class eve::mem::Pointer;
//
//			//////////////////////////////////////
//			//				DATAS				//
//			//////////////////////////////////////
//
//
//			//////////////////////////////////////
//			//				METHOD				//
//			//////////////////////////////////////
//
//			EVE_DISABLE_COPY(EventReader);
//			EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(EventReader);
//
//
//		private:
//			/** \brief Class constructor. */
//			EventReader(void);
//
//
//		private:
//			/** \brief Alloc and init class members. (pure virtual) */
//			virtual void init(void) override;
//			/** \brief Release and delete class members. (pure virtual) */
//			virtual void release(void) override;
//
//		};
//
//	} // namespace sys
//
//} // namespace eve
//
//
//
//
//
//
//class SystemEventListener;
//
//
///**
//* @class SystemEventReader
//*
//* @brief read and dispatch events from system message pump
//* @note abstract base event reader class
//*/
//class SystemEventReader
//{
//
//	//////////////////////////////////////
//	//			FRIEND CLASS			//
//	//////////////////////////////////////
//
//	friend class SystemEventHandler;
//
//
//
//	//////////////////////////////////////
//	//				DATAS				//
//	//////////////////////////////////////
//
//protected:
//    bool				m_bSizeMove;	// win32 size-move state
//	bool				m_bResizing;	// win32 size-move state
//	bool				m_bDirty;		// win32 size-move state
//
//    uint32_t			m_width;
//	uint32_t			m_height;
//
//    bool				m_bMouseinitialized;
//	bool				m_bMouseInside;
//    bool				m_bMouseHidden;
//	bool				m_bMouseDown;
//	
//	// Mouse double click utilities
//	int32_t				m_prevClick;
//	timeb				m_prevTime;
//	
//
//
//	//////////////////////////////////////
//	//				METHOD				//
//	//////////////////////////////////////
//
//	NATIVE_DISABLE_COPY(SystemEventReader)
//
//public:
//	/** SystemEventReader class constructor. */
//    SystemEventReader( void );
//
//	/** SystemEventReader class destructor. */
//	virtual ~SystemEventReader( void );
//
//
//	/** System event message parser. */
//	virtual std::pair<LRESULT,bool> handleEvent( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//
//
//protected:
//	/** Convert wparam to unicode value. */
//	static uint32_t wparam2unicode( WPARAM wparam );
//
//
//    virtual LRESULT handleEnterSizeMove		( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handleExitSizeMove		( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//	virtual LRESULT handleSizing			( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handleSize				( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handlePaint				( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handleEraseBkgnd		( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handleKey				( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//	virtual LRESULT handleChar				( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handleMouseDown			( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handleMouseUp			( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handleMotion			( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handleFocus				( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handleLeave				( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//    virtual LRESULT handleGetMinMaxInfo		( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//	virtual LRESULT handleDrop				( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//	virtual LRESULT handleClose				( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//	virtual LRESULT handleIdle				( SystemEventListener & p_listener, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
//
//};
//
//#endif // __EVE_SYSTEM_EVENT_READER_H__
