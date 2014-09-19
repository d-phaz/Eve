
#pragma once
#ifndef __System_KEYMAP_HPP__
#define __System_KEYMAP_HPP__

#include <Windows.h>

#ifndef __NATIVE_TYPES_H__
#include "Native_types.h"
#endif

#ifndef __SYSTEM_KEYBOARD_H__
#include "system/win32/SystemKeyboard.h"
#endif

#ifndef __SYSTEM_MOUSE_H__
#include "system/shared/SystemMouse.h"
#endif


namespace keymap
{
    keyboard::Symbol mapVirtualKeyCode(WPARAM vCode);

    // NOTE: translateKeyEvent must be called from the Window Procedure
    keyboard::Symbol translateKeyEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, bool &filter);

    keyboard::KeyMod getKeyModState();

    keyboard::KeyMod mapKeyMod(WPARAM wparam);
    mouse::ButtonMask mapButtons(WPARAM wparam);

    mouse::Button mapButton(UINT message, WPARAM wparam);
    bool mapButtonState(UINT message);
}

#endif /* ---- __System_KEYMAP_HPP__ ---- */
