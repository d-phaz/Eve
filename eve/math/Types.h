
/*
 Copyright (c) 2014, The eve Project
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the {organization} nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#ifndef __EVE_MATH_TYPES_H__
#define __EVE_MATH_TYPES_H__

#ifndef __EVE_MATH_CORE_TYPES_H__
#include "eve/math/core/Types.h"
#endif

#ifndef __EVE_MATH_TBOX_H__
#include "eve/math/TBox.h"
#endif 

#ifndef __EVE_MATH_TCAMERA_H__
#include "eve/math/TCamera.h"
#endif 

#ifndef __EVE_MATH_TMESH_H__
#include "eve/math/TMesh.h"
#endif

#ifndef __EVE_MATH_TRAY_H__
#include "eve/math/TRay.h"
#endif


namespace eve
{

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		Typedefs
	///////////////////////////////////////////////////////////////////////////////////////////////////

	namespace math
	{
		typedef eve::math::TBox<double>			Boxd;
		typedef eve::math::TBox<float>			Boxf;
#if defined(EVE_PRECISION_DOUBLE)
		typedef eve::math::TBox<double>			Box;
#else
		typedef eve::math::TBox<float>			Box;
#endif

		typedef eve::math::TRay<double>			Rayd;
		typedef eve::math::TRay<float>			Rayf;
#if defined(EVE_PRECISION_DOUBLE)
		typedef eve::math::TRay<double>			Ray;
#else
		typedef eve::math::TRay<float>			Ray;
#endif


		typedef eve::math::TCamera<double>		Camerad;
		typedef eve::math::TCamera<float>		Cameraf;
#if defined(EVE_PRECISION_DOUBLE)
		typedef eve::math::TCamera<double>		Camera;
#else
		typedef eve::math::TCamera<float>		Camera;
#endif


		typedef eve::math::TMesh<double>		Meshd;
		typedef eve::math::TMesh<float>			Meshf;
#if defined(EVE_PRECISION_DOUBLE)
		typedef eve::math::TMesh<double>		Mesh;
#else
		typedef eve::math::TMesh<float>			Mesh;
#endif

	} // namespace math



	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		Enumeration
	///////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	* \def eve::Axis
	* \brief 3D axis enumeration.
	*/
	enum Axis
	{
		Axis_X,
		Axis_Y,
		Axis_Z,

		//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
		_Axis_Force32Bit = INT_MAX

	}; // enum Axis

} // namespace eve

#endif // __EVE_MATH_TYPES_H__
