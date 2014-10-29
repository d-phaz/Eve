#pragma once
#ifndef __EVE_DIRECTX11_MACROS_H__
#define __EVE_DIRECTX11_MACROS_H__

#define MAX_DX11_SRV_SLOTS 128 //Common to all feature levels
#define MAX_DX11_UAV_SLOTS 64 //Current absolute maximum, but depends on feature set

#define EVE_SAFE_RELEASE(obj) if(obj) { obj->Release(); obj = NULL; }

#endif // __EVE_DIRECTX11_MACROS_H__