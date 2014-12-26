
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
#ifndef __EVE_MATH_MATRIX_DECOMPOSE_H__
#define __EVE_MATH_MATRIX_DECOMPOSE_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_INCLUDES_H__
#include "eve/math/core/Includes.h"
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
		template <typename T> 
		void get_look_at(const eve::math::TMatrix44<T> & mat, eve::math::TVec3<T> & eye, eve::math::TVec3<T> & center, eve::math::TVec3<T> & up, float lookDistance = 1.0f);
		/** \brief Extract camera eye position from model view matrix (that will work with stereo camera as well). */
		template <typename T> 
		void get_eye_point(const eve::math::TMatrix44<T> & mat, eve::math::TVec3<T> & eye);

	} // namespace math

} // namespace eve

//=================================================================================================
template <typename T> EVE_FORCE_INLINE static eve::math::TVec3<T> transform3x3(const eve::math::TMatrix44<T> & m, const eve::math::TVec3<T> & v)
{
	return eve::math::TVec3<T>( (m.m[0] * v.x + m.m[4] * v.y + m.m[8]  * v.z),
								(m.m[1] * v.x + m.m[5] * v.y + m.m[9]  * v.z),
								(m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z));
}

//=================================================================================================
template <typename T> EVE_FORCE_INLINE void eve::math::get_look_at(const eve::math::TMatrix44<T> & mat, eve::math::TVec3<T> & eye, eve::math::TVec3<T> & center, eve::math::TVec3<T> & up, float lookDistance)
{
	eve::math::TMatrix44<T> inv = mat.inverted();

	eye		= inv * eve::math::TVec3<T>::zero();
	up		= transform3x3(mat, eve::math::TVec3<T>::world_up());
	center	= transform3x3(mat, eve::math::TVec3<T>::view_direction());
	center.normalize();
	center = eye + center*lookDistance;
}

//=================================================================================================
template <typename T> EVE_FORCE_INLINE void eve::math::get_eye_point(const eve::math::TMatrix44<T> & mat, eve::math::TVec3<T> & eye)
{
	eye.x = -(mat.at(0, 0) * mat.at(0, 3)
			+ mat.at(1, 0) * mat.at(1, 3)
			+ mat.at(2, 0) * mat.at(2, 3));

	eye.y = -(mat.at(0, 1) * mat.at(0, 3)
			+ mat.at(1, 1) * mat.at(1, 3)
			+ mat.at(2, 1) * mat.at(2, 3));

	eye.z = -(mat.at(0, 2) * mat.at(0, 3)
			+ mat.at(1, 2) * mat.at(1, 3)
			+ mat.at(2, 2) * mat.at(2, 3));
}

#endif // __EVE_MATH_MATRIX_DECOMPOSE_H__
