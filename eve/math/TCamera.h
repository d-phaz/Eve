
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
#ifndef __EVE_MATH_TCAMERA_H__
#define __EVE_MATH_TCAMERA_H__

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_INCLUDES_H__
#include "eve/math/core/Includes.h"
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

#ifndef __EVE_MATH_TRAY_H__
#include "eve/math/TRay.h"
#endif

#ifndef __EVE_MATH_TTRANSFORM_H__
#include "eve/math/TTransform.h"
#endif


namespace eve
{
	namespace math
	{

		/** 
		* \class eve::math::TCamera
		*
		* \brief Template 3D Camera object math and manipulation.
		*
		* \note extends TTransform
		*/
		template <typename T>
		class TCamera
			: public eve::math::TTransform<T>
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			T									m_cam_view_width;				//!< View width.
			T									m_cam_view_height;				//!< View height.

		protected:
			T									m_fov;							//!< Horizontal field of view (aspect).
			T									m_aspectRatio;					//!< Aspect ratio (vertical FOV).
			T									m_nearClip;						//!< Near clipping plane.
			T									m_farClip;						//!< Far clipping plane.
			T									m_frustumDepth;					//!< Frustum depth (near clipping plane - far clipping plane).
			eve::math::TVec2<T>					m_lensShift;					//!< Lens shift on both axis.

		protected:
			mutable eve::math::TMatrix44<T>		m_matrixProjection;				//!< Projection matrix.
			mutable eve::math::TMatrix44<T>		m_matrixProjectionInverse;		//!< Inversed projection matrix.
			mutable eve::math::TMatrix44<T>		m_matrixModelViewInverse;		//!< Inversed model view matrix.
			mutable eve::math::TMatrix44<T>		m_matrixModelViewProjection;	//!< Projection matrix * Model view matrix.
			mutable eve::math::TMatrix44<T>		m_matrixViewport;				//!< Viewport matrix.

		protected:
			mutable T							m_frustumLeft;					//!< Left frustum border.
			mutable T							m_frustumRight;					//!< Right frustum border.
			mutable T							m_frustumTop;					//!< Top frustum border.
			mutable T							m_frustumBottom;				//!< Bottom frustum border.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_ASSIGNATION(TCamera);
			EVE_PUBLIC_DESTRUCTOR(TCamera);

		public:
			/** \brief Create new pointer. */
			static eve::math::TCamera<T> * create_ptr(T p_width = static_cast<T>(800.0), T p_height = static_cast<T>(600.0), T p_near = static_cast<T>(1.0), T p_far = static_cast<T>(1000.0), T p_fov = static_cast<T>(65.0));
			/** \brief Create new pointer. */
			template <typename U>
			static eve::math::TCamera<T> * create_ptr(U p_width, U p_height, T p_near = static_cast<T>(1.0), T p_far = static_cast<T>(1000.0), T p_fov = static_cast<T>(65.0));
			/** \brief Create new pointer, copy of \p_parent. */
			static eve::math::TCamera<T> * create_ptr(const TCamera<T> & p_parent);


		public:
			/** \brief Class constructor. */
			explicit TCamera(void);
			/** \brief Class constructor. */
			explicit TCamera(T p_width, T p_height, T p_near, T p_far, T p_fov);
			/** \brief Copy constructor. */
			explicit TCamera(const TCamera<T> & p_parent);


		protected:
			/** \brief Initialize camera with default values. */
			virtual void initDefault(void);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		protected:
			/** \brief Update all matrices. */
			void updateMatrices(void);

			/** \brief Update model view matrix based on rot/trans/scale matrices concatenation. */
			virtual void updateMatrixModelView(void) override;
			/** \brief Update projection matrix. */
			virtual void updateMatrixProjection(void);
			/** \brief Compute viewport matrix */
			void updateMatrixViewport(void);


		public:
			/** \brief Look at target point. */
			void lookAt(const eve::math::TVec3<T> & p_target);
			/** \brief Look at target point for given eye position. */
			void lookAt(const eve::math::TVec3<T> & p_eyePoint, const eve::math::TVec3<T> & p_target);
			/** \brief Look at target point for given eye position and world up vector. */
			void lookAt(const eve::math::TVec3<T> & p_eyePoint, const eve::math::TVec3<T> & p_target, const eve::math::TVec3<T> & p_up);


		public:
			/** \brief Calibrate camera by setting projection and model view matrix. */
			void calibrate(const eve::math::TMatrix44<T> & p_matrixProjection, const eve::math::TMatrix44<T> & p_matrixModelView);


		public:
			/** \brief Convert world-space coordinate to screen coordinates. */
			eve::math::TVec2<T> worldToScreen(const eve::math::TVec3<T> & p_worldCoord) const;
			/** \brief Convert world-space coordinate to screen coordinates. */
			eve::math::TVec2<T> worldToScreen(const eve::math::TVec3<T> & p_worldCoord, T p_screenWidth, T p_screenHeight) const;
			/** \brief Convert world-space coordinate to eye-space (camera-space, -Z is along the view direction). */
			eve::math::TVec3<T> worldToEye(const eve::math::TVec3<T> & p_worldCoord);
			/** \brief Convert world-space coordinate to the z axis of eye-space (camera-space, -Z is along the view direction, suitable for depth sorting). */
			T worldToEyeDepth(const eve::math::TVec3<T> & p_worldCoord) const;
			/** \brief Convert world-space coordinate to normalized device coordinates. */
			eve::math::TVec3<T> worldToNdc(const eve::math::TVec3<T> & p_worldCoord);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get Right axis. */
			eve::math::TVec3<T> getRight(void) const;
			/** \brief Get world up axis. */
			eve::math::TVec3<T> getUp(void) const;
			/** \brief Get direction axis. */
			eve::math::TVec3<T> getDirection(void) const;


		public:
			/** \brief Get camera horizontal FOV.*/
			const T getFov(void) const;
			/** \brief Set camera horizontal FOV. */
			void setFov(T p_fov);


		public:
			/** \brief Get camera aspect ratio (4/3, 16/9, ...), basically (display width / display height). */
			const T getAspectRatio(void) const;							   
			/** \brief Set camera aspect ratio (4/3, 16/9, ...), basically (display width / display height).*/
			void setAspectRatio(T p_aspectRatio);


		public:
			/** \brief Get near clipping plane distance. */
			const T getNearClip(void) const;
			/** \brief Set near clipping plane distance. */
			void setNearClip(T p_nearClip);


		public:
			/** \brief Get frustum depth (far-near). */
			const T getFrustumDepth(void) const;


		public:
			/** \brief Get far clipping plane distance. */
			const T getFarClip(void) const;
			/** \brief Set near clipping plane distance. */
			void setFarClip(T p_farClip);


		public:
			/** \brief Get camera frustum coordinates. */
			void getFrustum(T * p_pLeft, T * p_pTop, T * p_pRight, T * p_pBottom, T * p_pNear, T * p_pFar) const;


		public:
			/** \brief Get projection matrix. */
			eve::math::TMatrix44<T> & getMatrixProjection(void) const;
			/** \brief Get model view projection matrix (MVP). */
			eve::math::TMatrix44<T> & getMatrixModelViewProjection(void) const;
			/** \brief Get inverse projection matrix. */
			eve::math::TMatrix44<T> & getMatrixInverseProjection(void) const;
			/** \brief Get inverse model view matrix. */
			eve::math::TMatrix44<T> & getMatrixInverseModelView(void) const;
			/** \brief Get viewport matrix. */
			eve::math::TMatrix44<T> & getMatrixViewport(void) const;


		public:
			/** \brief Get point in scene distance from eye. */
			T getDistanceInScene(const eve::math::TVec3<T> & p_target);


		public:
			/** \brief Set perspective. */
			void setPerspective(T p_horizFovDegrees, T p_aspectRatio, T p_nearPlane, T p_farPlane);


		public:
			/** \brief Get display width. */
			const T getDisplayWidth(void) const;
			/** \brief Get display height. */
			const T getDisplayHeight(void) const;

			/** \brief Set display size. */
			void setDisplaySize(T p_width, T p_height, bool p_bUpdateAspectRatio = true);
			/** \brief Set display size. */
			template <typename U>
			void setDisplaySize(U p_width, U p_height, bool p_bUpdateAspectRatio = true);


		public:
			/** 
			* \brief Return both the horizontal and vertical lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			void getLensShift(T * p_pHorizontal, T * p_pVertical) const;
			/** 
			* \brief Return both the horizontal and vertical lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			const eve::math::TVec2<T> getLensShift(void) const;


			/** 
			* \brief Set both the horizontal and vertical lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			void setLensShift(T p_horizontal, T p_vertical);
			/** 
			* \brief Set both the horizontal and vertical lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			void setLensShift(const eve::math::TVec2<T> & p_shift);


			/** 
			* \brief Get horizontal lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			*/
			const T getLensShiftHorizontal(void) const;
			/** 
			* \brief Set horizontal lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			*/
			void setLensShiftHorizontal(T p_horizontal);


			/** 
			* \brief Get vertical lens shift
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			const T getLensShiftVertical(void) const;
			/** 
			* \brief Set vertical lens shift
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			void setLensShiftVertical(T p_vertical);


		public:
			/** \brief Get half view size. */
			const eve::math::TVec2<T> getHalfSize(void) const;

		}; // class TCamera

	} // namespace math

} // namespace eve


//=================================================================================================
template <typename T>
eve::math::TCamera<T> * eve::math::TCamera<T>::create_ptr(T p_width, T p_height, T p_near, T p_far, T p_fov)
{
	eve::math::TCamera<T> * ptr = new eve::math::TCamera<T>(p_width, p_height, p_near, p_far, p_fov);
	ptr->initDefault();
	return ptr;
}

//=================================================================================================
template <typename T>
template <typename U>
eve::math::TCamera<T> * eve::math::TCamera<T>::create_ptr(U p_width, U p_height, T p_near, T p_far, T p_fov)
{
	return eve::math::TCamera<T>::create_ptr(static_cast<T>(p_width), static_cast<T>(p_height), p_near, p_far, p_fov);
}

//=================================================================================================
template <typename T>
eve::math::TCamera<T> * eve::math::TCamera<T>::create_ptr(const eve::math::TCamera<T> & p_parent)
{
	eve::math::TCamera<T> * ptr = new eve::math::TCamera<T>(p_parent);
	return ptr;
}



//=================================================================================================
template <typename T>
eve::math::TCamera<T>::TCamera(void)
	// Inheritance
	: eve::math::TTransform<T>()

	// Members init
	, m_cam_view_width(static_cast<T>(800.0))
	, m_cam_view_height(static_cast<T>(600.0))

	, m_fov(static_cast<T>(65.0))
	, m_aspectRatio(static_cast<T>(4.0/3.0))
	, m_nearClip(static_cast<T>(1.0))
	, m_farClip(static_cast<T>(1000.0))
	, m_frustumDepth(static_cast<T>(0.0))
	, m_lensShift(eve::math::TVec2<T>::zero())

	, m_matrixProjection(eve::math::TMatrix44<T>::zero())
	, m_matrixProjectionInverse(eve::math::TMatrix44<T>::zero())
	, m_matrixModelViewInverse(eve::math::TMatrix44<T>::zero())
	, m_matrixModelViewProjection(eve::math::TMatrix44<T>::zero())
	, m_matrixViewport(eve::math::TMatrix44<T>::identity())

	, m_frustumLeft(static_cast<T>(0.0))
	, m_frustumRight(static_cast<T>(0.0))
	, m_frustumTop(static_cast<T>(0.0))
	, m_frustumBottom(static_cast<T>(0.0))
{}

//=================================================================================================
template <typename T>
eve::math::TCamera<T>::TCamera(T p_width, T p_height, T p_near, T p_far, T p_fov)
	// Inheritance
	: eve::math::TTransform<T>()

	// Members init
	, m_cam_view_width(p_width)
	, m_cam_view_height(p_height)

	, m_fov(p_fov)
	, m_aspectRatio(static_cast<T>(0.0))
	, m_nearClip(p_near)
	, m_farClip(p_far)
	, m_frustumDepth(static_cast<T>(0.0))
	, m_lensShift(eve::math::TVec2<T>::zero())

	, m_matrixProjection(eve::math::TMatrix44<T>::zero())
	, m_matrixProjectionInverse(eve::math::TMatrix44<T>::zero())
	, m_matrixModelViewInverse(eve::math::TMatrix44<T>::zero())
	, m_matrixModelViewProjection(eve::math::TMatrix44<T>::zero())
	, m_matrixViewport(eve::math::TMatrix44<T>::identity())

	, m_frustumLeft(static_cast<T>(0.0))
	, m_frustumRight(static_cast<T>(0.0))
	, m_frustumTop(static_cast<T>(0.0))
	, m_frustumBottom(static_cast<T>(0.0))
{}

//=================================================================================================
template <typename T>
eve::math::TCamera<T>::TCamera(const eve::math::TCamera<T> & p_parent)
	// Inheritance
	: eve::math::TTransform<T>(p_parent)

	// Members init
	, m_cam_view_width(p_parent.m_cam_view_width)
	, m_cam_view_height(p_parent.m_cam_view_height)

	, m_fov(p_parent.m_fov)
	, m_aspectRatio(p_parent.m_aspectRatio)
	, m_nearClip(p_parent.m_nearClip)
	, m_farClip(p_parent.m_farClip)
	, m_frustumDepth(p_parent.m_frustumDepth)
	, m_lensShift(p_parent.m_lensShift)

	, m_matrixProjection(p_parent.m_matrixProjection)
	, m_matrixProjectionInverse(p_parent.m_matrixProjectionInverse)
	, m_matrixModelViewInverse(p_parent.m_matrixModelViewInverse)
	, m_matrixModelViewProjection(p_parent.m_matrixModelViewProjection)
	, m_matrixViewport(p_parent.m_matrixViewport)

	, m_frustumLeft(p_parent.m_frustumLeft)
	, m_frustumRight(p_parent.m_frustumRight)
	, m_frustumTop(p_parent.m_frustumTop)
	, m_frustumBottom(p_parent.m_frustumBottom)
{}



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::initDefault(void)
{
	// Default values.
	m_aspectRatio		= m_cam_view_width / m_cam_view_height;
	m_frustumDepth		= m_farClip - m_nearClip;

	// Members init.
	this->init();

	// Matrix init.
	eve::math::TVec3<T> tra(static_cast<T>(10.0), static_cast<T>(10.0), static_cast<T>(10.0));
	eve::math::TVec3<T> tar(static_cast<T>( 0.0), static_cast<T>( 0.0), static_cast<T>( 0.0));
	this->lookAt(tra, tar, eve::math::TVec3<T>::world_up());
}



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::init(void)
{
	// Call parent class.
	eve::math::TTransform<T>::init();

	// Test values.
	//if (m_aspectRatio < static_cast<T>(0.000001)) {
		m_aspectRatio = m_cam_view_width / m_cam_view_height;
	//}

	// Compute matrices.
	this->updateMatrices();
	this->updateMatrixViewport();
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::release(void)
{
	// Nothing to do for now.

	// Call parent class.
	eve::math::TTransform<T>::release();
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::updateMatrices(void)
{
	this->updateMatrixModelView();
	this->updateMatrixProjection();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::updateMatrixModelView(void)
{
	// Call parent class.
	eve::math::TTransform<T>::updateMatrixModelView();

	// Update inverse model view matrix.
	m_matrixModelViewInverse.set(m_matrixModelView.inverted());
	// Update MVP.
	m_matrixModelViewProjection.set(m_matrixProjection * m_matrixModelViewInverse);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::updateMatrixProjection(void)
{
	m_frustumTop	=  m_nearClip * eve::math::tan(static_cast<T>(M_PI) / static_cast<T>(180.0) * m_fov * static_cast<T>(0.5));
	m_frustumBottom = -m_frustumTop;
	m_frustumRight	=  m_frustumTop * m_aspectRatio;
	m_frustumLeft	= -m_frustumRight;

	// Perform lens shift
	if (m_lensShift.x != static_cast<T>(0.0))
	{
		m_frustumRight = eve::math::lerp(static_cast<T>(2.0) * m_frustumRight, static_cast<T>(0.0), static_cast<T>(0.5) - static_cast<T>(0.5) * m_lensShift.x);
		m_frustumRight = eve::math::lerp(static_cast<T>(0.0), static_cast<T>(2.0) * m_frustumLeft, static_cast<T>(0.5) - static_cast<T>(0.5) * m_lensShift.x);
	}
	if (m_lensShift.y != static_cast<T>(0.0))
	{
		m_frustumTop	= eve::math::lerp(static_cast<T>(0.0), static_cast<T>(2.0) * m_frustumTop, static_cast<T>(0.5) + static_cast<T>(0.5) * m_lensShift.y);
		m_frustumBottom = eve::math::lerp(static_cast<T>(2.0) * m_frustumBottom, static_cast<T>(0.0), static_cast<T>(0.5) + static_cast<T>(0.5) * m_lensShift.y);
	}

	T *m = m_matrixProjection.m;
	m[ 0] =  static_cast<T>(2.0) * m_nearClip / (m_frustumRight - m_frustumLeft);
	m[ 5] =  static_cast<T>(2.0) * m_nearClip / (m_frustumTop - m_frustumBottom);
	m[ 8] =  (m_frustumRight + m_frustumLeft) / (m_frustumRight - m_frustumLeft);
	m[ 9] =  (m_frustumTop + m_frustumBottom) / (m_frustumTop - m_frustumBottom);
	m[10] = -(m_farClip + m_nearClip) / (m_farClip - m_nearClip);
	m[11] = -static_cast<T>(1.0);
	m[14] = -(static_cast<T>(2.0) * m_farClip * m_nearClip) / (m_farClip - m_nearClip);


	m = m_matrixProjectionInverse.m;
	m[ 0] =  (m_frustumRight - m_frustumLeft) / (static_cast<T>(2.0) * m_nearClip);
	m[ 5] =  (m_frustumTop - m_frustumBottom) / (static_cast<T>(2.0) * m_nearClip);
	m[11] = -(m_farClip - m_nearClip) / (static_cast<T>(2.0) * m_farClip*m_nearClip);
	m[12] =  (m_frustumRight + m_frustumLeft) / (static_cast<T>(2.0) * m_nearClip);
	m[13] =  (m_frustumTop + m_frustumBottom) / (static_cast<T>(2.0) * m_nearClip);
	m[14] = -static_cast<T>(1.0);
	m[15] =  (m_farClip + m_nearClip) / (static_cast<T>(2.0) * m_farClip*m_nearClip);

	// Update MVP.
	m_matrixModelViewProjection.set(m_matrixProjection * m_matrixModelViewInverse);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::updateMatrixViewport(void)
{
	m_matrixViewport.set(eve::math::TMatrix44<T>::ortho(static_cast<T>(0.0), m_cam_view_width, static_cast<T>(0.0), m_cam_view_height));
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::lookAt(const eve::math::TVec3<T> & p_target)
{
	eve::math::TVec3<T>			dir	= (p_target - m_translation).normalized();
	eve::math::TMatrix44<T>		mat = eve::math::TMatrix44<T>::alignZAxisWithTarget(-dir, getUp());
	eve::math::TQuaternion<T>	rot	= eve::math::TQuaternion<T>(mat).normalized();
	this->setRotation(rot);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::lookAt(const eve::math::TVec3<T> & p_eyePoint, const eve::math::TVec3<T> & p_target)
{
	this->setTranslation(p_eyePoint);
	this->lookAt(p_target);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::lookAt(const eve::math::TVec3<T> & p_eyePoint, const eve::math::TVec3<T> & p_target, const eve::math::TVec3<T> & p_up)
{
	this->setTranslation(p_eyePoint);
	eve::math::TVec3<T>			dir = (p_target - m_translation).normalized();
	eve::math::TMatrix44<T>		mat = eve::math::TMatrix44<T>::alignZAxisWithTarget(-dir, p_up);
	eve::math::TQuaternion<T>	rot = eve::math::TQuaternion<T>(mat).normalized();
	this->setRotation(rot);
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::calibrate(const eve::math::TMatrix44<T> & p_matrixProjection, const eve::math::TMatrix44<T> & p_matrixModelView)
{
	m_matrixProjection			= p_matrixProjection;
	m_matrixProjectionInverse	= m_matrixProjection.inverted();

	m_matrixModelView			= p_matrixModelView;
	m_matrixModelViewInverse	= m_matrixModelView.inverted();

	m_matrixModelViewProjection = m_matrixProjection * m_matrixModelViewInverse;

	eve::math::TQuaternion<T> rot;
	eve::math::decompose_matrix44(m_matrixModelView, m_translation, rot);
	m_rotation.set(rot.toVec3());
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TCamera<T>::worldToScreen(const eve::math::TVec3<T> & p_worldCoord) const
{
	eve::math::TVec3<T> eyeCoord = m_matrixModelView.transformPointAffine(p_worldCoord);
	eve::math::TVec3<T> ndc		 = m_matrixProjection.transformPoint(eyeCoord);

	return eve::math::TVec2<T>((ndc.x + static_cast<T>(1.0)) / static_cast<T>(2.0) * m_cam_view_width
							 , (static_cast<T>(1.0) - (ndc.y + static_cast<T>(1.0)) / static_cast<T>(2.0)) * m_cam_view_height);

}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TCamera<T>::worldToScreen(const eve::math::TVec3<T> & p_worldCoord, T p_screenWidth, T p_screenHeight) const
{
	eve::math::TVec3<T> eyeCoord = m_matrixModelView.transformPointAffine(p_worldCoord);
	eve::math::TVec3<T> ndc		 = m_matrixProjection.transformPoint(eyeCoord);

	return eve::math::TVec2<T>((ndc.x + static_cast<T>(1.0)) / static_cast<T>(2.0) * p_screenWidth, (static_cast<T>(1.0) - (ndc.y + static_cast<T>(1.0)) / static_cast<T>(2.0))*p_screenHeight);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TCamera<T>::worldToEye(const eve::math::TVec3<T> & p_worldCoord)
{
	return m_matrixModelView.transformPointAffine(p_worldCoord);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE T eve::math::TCamera<T>::worldToEyeDepth(const eve::math::TVec3<T> & p_worldCoord) const
{
	return (m_matrixModelView.m[2] * p_worldCoord.x + m_matrixModelView.m[6] * p_worldCoord.y + m_matrixModelView.m[10] * p_worldCoord.z + m_matrixModelView.m[14]);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TCamera<T>::worldToNdc(const eve::math::TVec3<T> & p_worldCoord)
{
	eve::math::TVec3<T> eye = m_matrixModelView.transformPointAffine(p_worldCoord);

	return m_matrixProjection.transformPoint(eye);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TCamera<T>::getRight(void) const 
{ 
	return m_matrixModelView.getRight();
}

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TCamera<T>::getUp(void) const
{
	return m_matrixModelView.getUp();
}

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TCamera<T>::getDirection(void) const
{
	return m_matrixModelView.getDirection();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getFov(void) const { return m_fov; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setFov(T p_fov)
{
	m_fov = p_fov;
	this->updateMatrixProjection();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getAspectRatio(void) const { return m_aspectRatio; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setAspectRatio(T p_aspectRatio)
{
	m_aspectRatio = p_aspectRatio;
	this->updateMatrixProjection();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getNearClip(void) const { return m_nearClip; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setNearClip(T p_nearClip)
{
	m_nearClip = p_nearClip;
	this->updateMatrixProjection();
}

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getFarClip(void) const { return m_farClip; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setFarClip(T p_farClip)
{
	m_farClip = p_farClip;
	this->updateMatrixProjection();
}

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getFrustumDepth(void) const 
{ 
	return m_frustumDepth; 
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::getFrustum(T * p_pLeft, T * p_pTop, T * p_pRight, T * p_pBottom, T * p_pNear, T * p_pFar) const
{
	*p_pLeft	= m_frustumLeft;
	*p_pTop		= m_frustumTop;
	*p_pRight	= m_frustumRight;
	*p_pBottom	= m_frustumBottom;
	*p_pNear	= m_nearClip;
	*p_pFar		= m_farClip;
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixProjection(void) const			{ return m_matrixProjection; }
template<typename T>								
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixModelViewProjection(void) const	{ return m_matrixModelViewProjection; }
template<typename T>								
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixInverseProjection(void) const		{ return m_matrixProjectionInverse; }
template<typename T>								
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixInverseModelView(void) const		{ return m_matrixModelViewInverse; }
template<typename T>								
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixViewport(void) const				{ return m_matrixViewport; }



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE T eve::math::TCamera<T>::getDistanceInScene(const eve::math::TVec3<T> & p_target)
{
	eve::vec4f temp = m_matrixModelView * eve::vec4f(p_target.x, p_target.y, p_target.z, static_cast<T>(1.0));
	T distance = eve::math::TVec3<T>(temp.x, temp.y, temp.z).length();
	return distance;
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setPerspective(T p_horizFovDegrees, T p_aspectRatio, T p_nearPlane, T p_farPlane)
{
	m_fov			= p_horizFovDegrees;
	m_aspectRatio	= p_aspectRatio;
	m_nearClip		= p_nearPlane;
	m_farClip		= p_farPlane;

	this->updateMatrixProjection();
}



//=================================================================================================
template <typename T> EVE_FORCE_INLINE const T eve::math::TCamera<T>::getDisplayWidth(void) const  { return m_cam_view_width;  }
template <typename T> EVE_FORCE_INLINE const T eve::math::TCamera<T>::getDisplayHeight(void) const { return m_cam_view_height; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setDisplaySize(T p_width, T p_height, bool p_bUpdateAspectRatio)
{
	m_cam_view_width		= p_width;
	m_cam_view_height	= p_height;

	if (p_bUpdateAspectRatio) 
	{
		this->setAspectRatio(m_cam_view_width / m_cam_view_height);
	}

	this->updateMatrixViewport();
}

//=================================================================================================
template <typename T>
template <typename U>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setDisplaySize(U p_width, U p_height, bool p_bUpdateAspectRatio)
{
	this->setDisplaySize(static_cast<T>(p_width), static_cast<T>(p_height), p_bUpdateAspectRatio);
}


//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T> eve::math::TCamera<T>::getLensShift(void) const { return m_lensShift; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::getLensShift(T * p_pHorizontal, T * p_pVertical) const
{
	*p_pHorizontal	= m_lensShift.x;
	*p_pVertical	= m_lensShift.y;
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setLensShift(T p_horizontal, T p_vertical)
{
	m_lensShift.x = p_horizontal;
	m_lensShift.y = p_vertical;

	this->updateMatrixProjection();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setLensShift(const eve::math::TVec2<T> & p_shift)
{
	m_lensShift.x = p_shift.x;
	m_lensShift.y = p_shift.y;

	this->updateMatrixProjection();
}

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getLensShiftHorizontal(void) const { return m_lensShift.x; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setLensShiftHorizontal(T p_horizontal)
{
	m_lensShift.x = p_horizontal;
	this->updateMatrixProjection();
}

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getLensShiftVertical(void) const { return m_lensShift.y; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TCamera<T>::setLensShiftVertical(T p_vertical)
{
	m_lensShift.y = p_vertical;
	this->updateMatrixProjection();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T> eve::math::TCamera<T>::getHalfSize(void) const 
{ 
	return eve::math::TVec2<T>(m_cam_view_width * static_cast<T>(0.5), m_cam_view_height * static_cast<T>(0.5)); 
}

#endif // __EVE_MATH_TCAMERA_OBJECT_H__
