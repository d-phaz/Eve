
// Main header
#include "SystemCursor.h"

namespace cursor
{
	//--------------------------------------------------------------------------------------------
	Vec2i getCursorPosition( void )
	{
		POINT pt;
		::GetCursorPos( &pt );

		return Vec2i( pt.x, pt.y );
	}


	//--------------------------------------------------------------------------------------------
	void setCursorPosition( const Vec2i & p_targetPosition )
	{
		::SetCursorPos( p_targetPosition.x, p_targetPosition.y );
	}
	
		//=============================================================================================
	void setCursor( const cursor::State & p_cursorType )
	{
		// Grab current window
		POINT point;
		::GetCursorPos( &point );
		HWND handle = ::WindowFromPoint( point );

		switch( p_cursorType )
		{
			MAP_CURSOR( cursor::CURSOR_INHERIT,             IDC_CROSS     , handle ); // Define as MWM param -> ToDo
			MAP_CURSOR( cursor::CURSOR_WAIT,                IDC_WAIT      , handle );

			MAP_CURSOR( cursor::CURSOR_RIGHT_ARROW,         IDC_ARROW     , handle );
			MAP_CURSOR( cursor::CURSOR_LEFT_ARROW,          IDC_ARROW     , handle );
			MAP_CURSOR( cursor::CURSOR_INFO,                IDC_HELP      , handle );
			MAP_CURSOR( cursor::CURSOR_DESTROY,             IDC_CROSS     , handle );
			MAP_CURSOR( cursor::CURSOR_HELP,                IDC_HELP      , handle );
			MAP_CURSOR( cursor::CURSOR_CYCLE,               IDC_SIZEALL   , handle );
			MAP_CURSOR( cursor::CURSOR_SPRAY,               IDC_CROSS     , handle );
			MAP_CURSOR( cursor::CURSOR_TEXT,                IDC_IBEAM     , handle );
			MAP_CURSOR( cursor::CURSOR_CROSSHAIR,           IDC_CROSS     , handle );
			MAP_CURSOR( cursor::CURSOR_UP_DOWN,             IDC_SIZENS    , handle );
			MAP_CURSOR( cursor::CURSOR_LEFT_RIGHT,          IDC_SIZEWE    , handle );
			MAP_CURSOR( cursor::CURSOR_TOP_SIDE,            IDC_ARROW     , handle ); // XXX ToDo 
			MAP_CURSOR( cursor::CURSOR_BOTTOM_SIDE,         IDC_ARROW     , handle ); // XXX ToDo 
			MAP_CURSOR( cursor::CURSOR_LEFT_SIDE,           IDC_ARROW     , handle ); // XXX ToDo 
			MAP_CURSOR( cursor::CURSOR_RIGHT_SIDE,          IDC_ARROW     , handle ); // XXX ToDo 
			MAP_CURSOR( cursor::CURSOR_TOP_LEFT_CORNER,     IDC_SIZENWSE  , handle );
			MAP_CURSOR( cursor::CURSOR_TOP_RIGHT_CORNER,    IDC_SIZENESW  , handle );
			MAP_CURSOR( cursor::CURSOR_BOTTOM_RIGHT_CORNER, IDC_SIZENWSE  , handle );
			MAP_CURSOR( cursor::CURSOR_BOTTOM_LEFT_CORNER,  IDC_SIZENESW  , handle );
			ZAP_CURSOR( cursor::CURSOR_NONE,                NULL          , handle );
			MAP_CURSOR( cursor::CURSOR_FULL_CROSSHAIR,      IDC_CROSS     , handle ); // XXX ToDo 

		default:
			break;
		}
	}
	
}