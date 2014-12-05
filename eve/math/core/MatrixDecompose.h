
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
#ifndef __EVE_MATH_CORE_MATRIX_DECOMPOSE_H__
#define __EVE_MATH_CORE_MATRIX_DECOMPOSE_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_MATH_H__
#include "eve/math/core/Math.h"
#endif

#ifndef __EVE_MATH_CORE_TMATRIX_H__
#include "eve/math/core/TMatrix.h"
#endif

#ifndef __EVE_MATH_CORE_TQUATERNION_H__
#include "eve/math/core/TQuaternion.h"
#endif

#ifndef __EVE_MATH_CORE_TVECTOR_H__
#include "eve/math/core/TVector.h"
#endif

#ifndef __EVE_MATH_CORE_TYPES_H__
#include "eve/math/core/Types.h"
#endif


namespace eve
{
	namespace math
	{
		/** \brief Decompose matrix to extract translation, rotation and scale. */
		void decompose_matrix44(const eve::mat44f & mat, eve::vec3f & t, eve::quatf & r, eve::vec3f & s, eve::quatf & so);
		/** \brief Decompose matrix to extract translation, rotation and scale. */
		void decompose_matrix44(const eve::mat44f & mat, eve::vec3f & t, eve::quatf & r);


		/** \brief Extract Camera view look at properties (eye, target, world up). */
		void get_look_at(const eve::mat44f & mat, eve::vec3f & eye, eve::vec3f & center, eve::vec3f & up, float lookDistance = 1.0f);
		/** \brief Extract camera eye position from model view matrix (that will work with stereo camera as well). */
		void get_eye_point(const eve::mat44f & mat, eve::vec3f & eye);

	} // namespace math

} // namespace eve

#endif // __EVE_MATH_CORE_MATRIX_DECOMPOSE_H__
