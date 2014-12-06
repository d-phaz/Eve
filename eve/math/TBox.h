
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
#ifndef __EVE_MATH_TBOX_H__
#define __EVE_MATH_TBOX_H__

#ifndef __EVE_MATH_CORE_TMATRIX_H__
#include "eve/math/core/TMatrix.h"
#endif

#ifndef __EVE_MATH_CORE_TVECTOR_H__
#include "eve/math/core/TVector.h"
#endif

#ifndef __EVE_MATH_TRAY_H__
#include "eve/math/TRay.h"
#endif


namespace eve
{
	namespace math
	{
		/**
		* \class eve::math::TBox
		*
		* \brief Template 3D box.
		*/
		template< typename T >
		class TBox
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			eve::math::TVec3<T> m_extends[2];
			eve::math::TVec3<T> m_verts[8];


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			TBox(void);
			TBox(const eve::math::TVec3<T> & p_min, const eve::math::TVec3<T> & p_max);


		protected:
			void set(const eve::math::TVec3<T> & p_min, const eve::math::TVec3<T> & p_max);


		public:
			bool intersects(const eve::math::TRay<T> & p_ray);
			int32_t	intersect(const eve::math::TRay<T> & p_ray, T p_intersections[2]);

			//! Expands the box so that it contains \a p_box
			virtual void include(const TBox<T> & p_box);

			//! for use in frustum culling
			eve::math::TVec3<T> getNegative(const eve::math::TVec3<T> & p_normal) const;
			eve::math::TVec3<T> getPositive(const eve::math::TVec3<T> & p_normal) const;

			//! converts axis-aligned box to another coordinate space
			TBox<T> transformed(const eve::math::TMatrix44<T> & p_transform) const;

			eve::math::TVec3<T> getCenter(void) const;
			eve::math::TVec3<T> getSize(void) const;

			const eve::math::TVec3<T> & getMin(void) const;
			const eve::math::TVec3<T> & getMax(void) const;

		}; // class TBox

	} // namespace math

} // namespace eve

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TBox<T>::TBox(void)
{}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TBox<T>::TBox(const eve::math::TVec3<T> & p_min, const eve::math::TVec3<T> & p_max)
{
	m_extends[0] = eve::math::TVec3<T>(p_min.x, p_min.y, p_min.z);
	m_extends[1] = eve::math::TVec3<T>(p_max.x, p_max.y, p_max.z);

	eve::math::TVec3<T> extent(p_max.x - p_min.x, p_max.y - p_min.y, p_max.z - p_min.z);
	eve::math::TVec3<T> mid((p_min.x + p_max.x) * static_cast<T>(0.5), (p_min.y + p_max.y) * static_cast<T>(0.5), (p_min.z + p_max.z) * static_cast<T>(0.5));

	m_verts[0] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>(-0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[1] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>(-0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[2] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>( 0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[3] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>( 0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[4] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>( 0.5), static_cast<T>(-0.5)) * extent + mid;
	m_verts[5] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>( 0.5), static_cast<T>(-0.5)) * extent + mid;
	m_verts[6] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>(-0.5), static_cast<T>(-0.5)) * extent + mid;
	m_verts[7] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>(-0.5), static_cast<T>(-0.5)) * extent + mid;
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE void eve::math::TBox<T>::set(const eve::math::TVec3<T> & p_min, const eve::math::TVec3<T> & p_max)
{
	m_extends[0] = eve::math::TVec3<T>(p_min.x, p_min.y, p_min.z);
	m_extends[1] = eve::math::TVec3<T>(p_max.x, p_max.y, p_max.z);

	eve::math::TVec3<T> extent(p_max.x - p_min.x, p_max.y - p_min.y, p_max.z - p_min.z);
	eve::math::TVec3<T> mid((p_min.x + p_max.x) * static_cast<T>(0.5), (p_min.y + p_max.y) * static_cast<T>(0.5), (p_min.z + p_max.z) * static_cast<T>(0.5));

	m_verts[0] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>(-0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[1] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>(-0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[2] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>( 0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[3] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>( 0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[4] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>( 0.5), static_cast<T>(-0.5)) * extent + mid;
	m_verts[5] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>( 0.5), static_cast<T>(-0.5)) * extent + mid;
	m_verts[6] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>(-0.5), static_cast<T>(-0.5)) * extent + mid;
	m_verts[7] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>(-0.5), static_cast<T>(-0.5)) * extent + mid;
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE bool eve::math::TBox<T>::intersects(const eve::math::TRay<T> & p_ray)
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	tmin  = (m_extends[p_ray.getSignX()].x - p_ray.getOrigin().x) * p_ray.getInverseDirection().x;
	tmax  = (m_extends[1 - p_ray.getSignX()].x - p_ray.getOrigin().x) * p_ray.getInverseDirection().x;
	tymin = (m_extends[p_ray.getSignY()].y - p_ray.getOrigin().y) * p_ray.getInverseDirection().y;
	tymax = (m_extends[1 - p_ray.getSignY()].y - p_ray.getOrigin().y) * p_ray.getInverseDirection().y;

	if ((tmin > tymax) || (tymin > tmax))
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	tzmin = (m_extends[p_ray.getSignZ()].z - p_ray.getOrigin().z) * p_ray.getInverseDirection().z;
	tzmax = (m_extends[1 - p_ray.getSignZ()].z - p_ray.getOrigin().z) * p_ray.getInverseDirection().z;

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;

	return tmin > 0;
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE int32_t eve::math::TBox<T>::intersect(const eve::math::TRay<T> & p_ray, T intersections[2])
{
	int32_t i = 0;

	if (p_ray.calcTriangleIntersection(m_verts[2], m_verts[0], m_verts[1], &intersections[i])) { // +Z
		i++;
	}
	else if (p_ray.calcTriangleIntersection(m_verts[1], m_verts[3], m_verts[2], &intersections[i])) { // +Z
		i++;
	}

	if (p_ray.calcTriangleIntersection(m_verts[7], m_verts[5], m_verts[3], &intersections[i])) { // +X
		i++; if (i > 2) return i;
	}
	else if (p_ray.calcTriangleIntersection(m_verts[1], m_verts[7], m_verts[3], &intersections[i])) { // +X
		i++; if (i > 2) return i;
	}

	if (p_ray.calcTriangleIntersection(m_verts[3], m_verts[5], m_verts[4], &intersections[i])) { // +Y
		i++; if (i > 2) return i;
	}
	else if (p_ray.calcTriangleIntersection(m_verts[2], m_verts[3], m_verts[4], &intersections[i])) { // +Y
		i++; if (i > 2) return i;
	}

	if (p_ray.calcTriangleIntersection(m_verts[1], m_verts[0], m_verts[7], &intersections[i])) { // -Y
		i++; if (i > 2) return i;
	}
	else if (p_ray.calcTriangleIntersection(m_verts[0], m_verts[6], m_verts[7], &intersections[i])) { // -Y
		i++; if (i > 2) return i;
	}

	if (p_ray.calcTriangleIntersection(m_verts[4], m_verts[0], m_verts[2], &intersections[i])) { // -X
		i++; if (i > 2) return i;
	}
	else if (p_ray.calcTriangleIntersection(m_verts[4], m_verts[6], m_verts[0], &intersections[i])) { // -X
		i++; if (i > 2) return i;
	}

	if (p_ray.calcTriangleIntersection(m_verts[6], m_verts[4], m_verts[5], &intersections[i])) { // -Z
		i++;
	}
	else if (p_ray.calcTriangleIntersection(m_verts[7], m_verts[6], m_verts[5], &intersections[i])) { // -Z
		i++;
	}

	return i;
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE void eve::math::TBox<T>::include(const eve::math::TBox<T> & p_box)
{
	eve::math::TVec3<T> minB = p_box.getMin();
	if (minB.x < m_extends[0].x) m_extends[0].x = minB.x;
	if (minB.y < m_extends[0].y) m_extends[0].y = minB.y;
	if (minB.z < m_extends[0].z) m_extends[0].z = minB.z;

	eve::math::TVec3<T> maxB = p_box.getMax();
	if (maxB.x > m_extends[1].x) m_extends[1].x = maxB.x;
	if (maxB.y > m_extends[1].y) m_extends[1].y = maxB.y;
	if (maxB.z > m_extends[1].z) m_extends[1].z = maxB.z;

	// update vertices
	eve::math::TVec3<T> extent(m_extends[1].x - m_extends[0].x, m_extends[1].y - m_extends[0].y, m_extends[1].z - m_extends[0].z);
	eve::math::TVec3<T> mid((m_extends[0].x + m_extends[1].x) * static_cast<T>(0.5), (m_extends[0].y + m_extends[1].y) * static_cast<T>(0.5), (m_extends[0].z + m_extends[1].z) * static_cast<T>(0.5));

	m_verts[0] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>(-0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[1] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>(-0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[2] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>( 0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[3] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>( 0.5), static_cast<T>( 0.5)) * extent + mid;
	m_verts[4] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>( 0.5), static_cast<T>(-0.5)) * extent + mid;
	m_verts[5] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>( 0.5), static_cast<T>(-0.5)) * extent + mid;
	m_verts[6] = eve::math::TVec3<T>(static_cast<T>(-0.5), static_cast<T>(-0.5), static_cast<T>(-0.5)) * extent + mid;
	m_verts[7] = eve::math::TVec3<T>(static_cast<T>( 0.5), static_cast<T>(-0.5), static_cast<T>(-0.5)) * extent + mid;
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TBox<T>::getPositive(const eve::math::TVec3<T> & p_normal) const
{
	eve::math::TVec3<T> result = getMin();
	eve::math::TVec3<T> size   = getSize();

	if (p_normal.x > 0)
		result.x += size.x;

	if (p_normal.y > 0)
		result.y += size.y;

	if (p_normal.z > 0)
		result.z += size.z;

	return(result);
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TBox<T>::getNegative(const eve::math::TVec3<T> & p_normal) const
{
	eve::math::TVec3<T> result = getMin();
	eve::math::TVec3<T> size   = getSize();

	if (p_normal.x < 0)
		result.x += size.x;

	if (p_normal.y < 0)
		result.y += size.y;

	if (p_normal.z < 0)
		result.z += size.z;

	return(result);
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TBox<T> eve::math::TBox<T>::transformed(const eve::math::TMatrix44<T> & p_transform) const
{
	eve::math::TVec3<T> verts[8];

	for (size_t i = 0; i < 8; i++)
		verts[i] = p_transform.transformPointAffine(m_verts[i]);

	eve::math::TVec3<T> min = verts[0];
	eve::math::TVec3<T> max = verts[0];

	for (size_t i = 1; i < 8; i++) 
	{
		if (verts[i].x < min.x) min.x = verts[i].x;
		if (verts[i].y < min.y) min.y = verts[i].y;
		if (verts[i].z < min.z) min.z = verts[i].z;

		if (verts[i].x > max.x) max.x = verts[i].x;
		if (verts[i].y > max.y) max.y = verts[i].y;
		if (verts[i].z > max.z) max.z = verts[i].z;
	}

	return TBox<T>(min, max);
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TBox<T>::getCenter(void) const
{
	return (m_extends[1] + m_extends[0]) * static_cast<T>(0.5);
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TBox<T>::getSize(void) const
{
	return m_extends[1] - m_extends[0];
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE const eve::math::TVec3<T> & eve::math::TBox<T>::getMin(void) const
{
	return m_extends[0];
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE const eve::math::TVec3<T> & eve::math::TBox<T>::getMax(void) const
{
	return m_extends[1];
}

#endif // __EVE_MATH_TBOX_H__
