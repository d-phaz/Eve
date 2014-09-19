
#pragma once
#ifndef __SYSTEM_CURSOR_H__
#define __SYSTEM_CURSOR_H__



#ifndef __NATIVE_SYSTEM_H__
#include "Native_System.h"
#endif

#ifndef __TVECTOR_H__
#include "math/TVector.h"
#endif

#ifndef __SYSTEM_CURSOR_H__
#include "system/shared/SystemCursor.h"
#endif

namespace cursor
{
	enum State
	{
		CURSOR_RIGHT_ARROW              = 0x0000,
		CURSOR_LEFT_ARROW               = 0x0001,
		CURSOR_INFO                     = 0x0002,
		CURSOR_DESTROY                  = 0x0003,
		CURSOR_HELP                     = 0x0004,
		CURSOR_CYCLE                    = 0x0005,
		CURSOR_SPRAY                    = 0x0006,
		CURSOR_WAIT                     = 0x0007,
		CURSOR_TEXT                     = 0x0008,
		CURSOR_CROSSHAIR                = 0x0009,
		CURSOR_UP_DOWN                  = 0x000A,
		CURSOR_LEFT_RIGHT               = 0x000B,
		CURSOR_TOP_SIDE                 = 0x000C,
		CURSOR_BOTTOM_SIDE              = 0x000D,
		CURSOR_LEFT_SIDE                = 0x000E,
		CURSOR_RIGHT_SIDE               = 0x000F,
		CURSOR_TOP_LEFT_CORNER          = 0x0010,
		CURSOR_TOP_RIGHT_CORNER         = 0x0011,
		CURSOR_BOTTOM_RIGHT_CORNER      = 0x0012,
		CURSOR_BOTTOM_LEFT_CORNER       = 0x0013,
		CURSOR_INHERIT                  = 0x0064,
		CURSOR_NONE                     = 0x0065,
		CURSOR_FULL_CROSSHAIR           = 0x0066
	};

	/**
	* @brief get cursor position in screen coordinates
	* @return cursor position as glm::ivec2
	*/
	Vec2i getCursorPosition(void);
	/**
	* @brief set cursor position
	* @param p_targetPosition cursor position as glm::vec2
	*/
	void setCursorPosition(const Vec2i & p_targetPosition);

	/** \! Set under cursor window cursor. */
	void setCursor( const cursor::State & p_cursorType );
}



#if defined( NATIVE_OS_WIN32)
/* Set the cursor AND change it for this window class. */
#define MAP_CURSOR(a, b, c) \
    case a: \
	SetCursor( (HCURSOR)LoadImage(NULL, b, IMAGE_CURSOR, 0, 0, LR_SHARED) );  \
	SetClassLongPtr( c, GCLP_HCURSOR, ( LONG )( LONG_PTR )LoadImage(NULL, b, IMAGE_CURSOR, 0, 0, LR_SHARED) ); \
	break;

/* Nuke the cursor AND change it for this window class. */
#define ZAP_CURSOR(a, b, c) \
	case a: \
	SetCursor( NULL ); \
	SetClassLongPtr( c, GCLP_HCURSOR, ( LONG )( LONG_PTR )NULL ); \
	break;
#endif

#endif // __SYSTEM_CURSOR_H__
