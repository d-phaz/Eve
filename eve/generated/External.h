
#pragma once
#ifndef __EVE_EXTERNAL_H__
#define __EVE_EXTERNAL_H__

#define OPTION_BUILD_USE_VLD
#ifdef OPTION_BUILD_USE_VLD
#include "vld.h"
#endif

/* #undef OPENCL_FOUND */
#ifdef OPENCL_FOUND
#define EVE_ENABLE_OPENCL
#endif

#endif 	// __EVE_EXTERNAL_H__
