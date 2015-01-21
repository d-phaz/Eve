
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


namespace eve
{
	namespace math
	{

		/** 
		* \class eve::math::TCamera
		*
		* \brief Template 3D Camera object math and manipulation.
		*
		* \note extends eve::mem::Pointer
		*/
		template <typename T>
		class TCamera
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			T									m_width;						//!< View width.
			T									m_height;						//!< View height.

		protected:
			eve::math::TVec3<T>					m_eyePoint;						//!< Eye position in 3D world.
			eve::math::TVec3<T>					m_target;						//!< View target in 3D world.
			eve::math::TVec3<T>					m_worldUp;						//!< View UP axis.

		protected:
			eve::math::TVec3<T>					m_viewDirection;				//!< Normalized view direction.
			eve::math::TQuaternion<T>			m_orientation;					//!< Orientation (rotation).
			T									m_centerOfInterest;				//!< Center of interest.

		protected:
			T									m_fov;							//!< Horizontal field of view (aspect).
			T									m_aspectRatio;					//!< Aspect ratio (vertical FOV).
			T									m_nearClip;						//!< Near clipping plane.
			T									m_farClip;						//!< Far clipping plane.
			T									m_frustumDepth;					//!< Frustum depth (near clipping plane - far clipping plane).
			eve::math::TVec2<T>					m_lensShift;					//!< Lens shift on both axis.

		protected:
			mutable eve::math::TVec3<T>			m_U;							//!< Right vector.
			mutable eve::math::TVec3<T>			m_V;							//!< Readjust up-vector.
			mutable eve::math::TVec3<T>			m_W;							//!< Negative view direction.

		protected:
			mutable eve::math::TMatrix44<T>		m_matrixProjection;				//!< Projection matrix.
			mutable eve::math::TMatrix44<T>		m_matrixProjectionInverse;		//!< Inversed projection matrix.
			mutable eve::math::TMatrix44<T>		m_matrixModelView;				//!< Model view matrix.
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
			EVE_PROTECT_DESTRUCTOR(TCamera);

		public:
			/** \brief Create new pointer. */
			static eve::math::TCamera<T> * create_ptr(T p_width = static_cast<T>(800.0), T p_height = static_cast<T>(600.0), T p_near = static_cast<T>(1.0), T p_far = static_cast<T>(1000.0), T p_fov = static_cast<T>(65.0));
			/** \brief Create new pointer. */
			template <typename U>
			static eve::math::TCamera<T> * create_ptr(U p_width, U p_height, T p_near = static_cast<T>(1.0), T p_far = static_cast<T>(1000.0), T p_fov = static_cast<T>(65.0));
			/** \brief Create new pointer, copy of \p_parent. */
			static eve::math::TCamera<T> * create_ptr(const TCamera<T> & p_parent);


		protected:
			/** \brief Class constructor. */
			explicit TCamera(T p_width, T p_height, T p_near, T p_far, T p_fov);
			/** \brief Copy constructor. */
			explicit TCamera(const TCamera<T> & p_parent);


		protected:
			/** \brief Initialize camera with default values. */
			virtual void initDefault(void);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		protected:
			/** \brief Compute matrices. */
			void calcMatrices(void) const;
			/** \brief Compute model view matrix. */
			void calcModelView(void) const;
			/** \brief Compute projection matrix. */
			void calcProjection(void) const;
			/** \brief Compute viewport matrix */
			void calcViewportMatrix(void);


		public:
			/** \brief Look at target point. */
			void lookAt(const eve::math::TVec3<T> & p_target);
			/** \brief Look at target point for given eye position. */
			void lookAt(const eve::math::TVec3<T> & p_eyePoint, const eve::math::TVec3<T> & p_target);
			/** \brief Look at target point for given eye position and world up vector. */
			void lookAt(const eve::math::TVec3<T> & p_eyePoint, const eve::math::TVec3<T> & p_target, const eve::math::TVec3<T> & p_up);


		public:
			/** \brief Calibrate camera by setting projection and model view matrix. */
			void calibrateCamera(const eve::math::TMatrix44<T> & p_matrixProjection, const eve::math::TMatrix44<T> & p_matrixModelView);
			/** \brief Release calibration by computing matrices from RTS values. */
			void releaseCalibration(void);


		public:
			/** \brief Generate ray from point. */
			eve::math::TRay<T> generateRay(T p_uPos, T p_vPos, T p_imagePlaneAspectRatio) const;
			/** \brief Generate ray from point. */
			eve::math::TRay<T> generateRay(T p_uPos, T p_vPos, T p_imagePlaneWidth, T p_imagePlaneHeight) const;
			/** \brief Generate ray from point. */
			eve::math::TRay<T> generateRay(eve::math::TVec2<T> p_pos, T p_imagePlaneWidth, T p_imagePlaneHeight) const;


		public:
			/** \brief Convert world-space coordinate to screen coordinates. */
			eve::math::TVec2<T> worldToScreen(const eve::math::TVec3<T> & p_worldCoord, T p_screenWidth, T p_screenHeight) const;
			/** \brief Convert world-space coordinate to eye-space (camera-space, -Z is along the view direction). */
			eve::math::TVec3<T> worldToEye(const eve::math::TVec3<T> & p_worldCoord);
			/** \brief Convert world-space coordinate to the z axis of eye-space (camera-space, -Z is along the view direction, suitable for depth sorting). */
			T worldToEyeDepth(const eve::math::TVec3<T> & p_worldCoord) const;
			/** \brief Convert world-space coordinate to normalized device coordinates. */
			eve::math::TVec3<T> worldToNdc(const eve::math::TVec3<T> & p_worldCoord);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		MATRIX
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Translate object. */
			virtual void translate(const eve::math::TVec3<T> & p_translation);
			/** \brief Translate object on X-axis. */
			virtual void translateX(T p_translationX);
			/** \brief Translate object on Y-axis. */
			virtual void translateY(T p_translationY);
			/** \brief Translate object on Z-axis. */
			virtual void translateZ(T p_translationZ);


		public:
			/** \brief Rotate object. */
			virtual void rotate(const eve::math::TVec3<T> & p_rotation);
			/** \brief Rotate object on X-axis. */
			virtual void rotateX(T p_rotationX);
			/** \brief Rotate object on Y-axis. */
			virtual void rotateY(T p_rotationY);
			/** \brief Rotate object on Z-axis. */
			virtual void rotateZ(T p_rotationZ);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get eye point. */
			const eve::math::TVec3<T> getEyePoint(void) const;
			/** \brief Get eye point position on X-axis. */
			const T getEyePointX(void) const;
			/** \brief Get eye point position on Y-axis. */
			const T getEyePointY(void) const;
			/** \brief Get eye point position on Z-axis. */
			const T getEyePointZ(void) const;

			/** \brief Set eye point. */
			void setEyePoint(const eve::math::TVec3<T> & p_eyePoint);
			/** \brief Set eye point X value. */
			void setEyePointX(T p_eyePointX);
			/** \brief Set eye point Y value. */
			void setEyePointY(T p_eyePointY);
			/** \brief Set eye point Z value. */
			void setEyePointZ(T p_eyePointZ);


		public:
			/** \brief Get translation. */
			const eve::math::TVec3<T> getTranslation(void) const;
			/** \brief Get translation on X-axis. */
			const T getTranslationX(void) const;
			/** \brief Get translation on Y-axis. */
			const T getTranslationY(void) const;
			/** \brief Get translation on Z-axis. */
			const T getTranslationZ(void) const;


		public:
			/** \brief Get center of interest. */
			const T getCenterOfInterest(void) const;
			/** \brief Set center of interest. */
			void setCenterOfInterest(T p_centerOfInterest);


		public:
			/** \brief Get center of interest point. */
			const eve::math::TVec3<T> getCenterOfInterestPoint(void) const;
			/** \brief Set center of interest point. */
			void setCenterOfInterestPoint(const eve::math::TVec3<T> & p_centerOfInterestPoint);


		public:
			/** \brief Get world up. */
			const eve::math::TVec3<T> getWorldUp(void) const;
			/** \brief Set world up. */
			void setWorldUp(const eve::math::TVec3<T> & p_worldUp);


		public:
            /** \brief Get Rigth Vector. */
			const eve::math::TVec3<T> getRightVector(void) const;


		public:
			/** \brief Get view direction. */
			const eve::math::TVec3<T> getViewDirection(void) const;
			/** \brief Set view direction. */
			void setViewDirection(const eve::math::TVec3<T> & p_viewDirection);


		public:
			/** \brief Get camera orientation. */
			const eve::math::TQuaternion<T> getOrientation(void) const;
			/** \brief Set camera orientation. */
			void setOrientation(const eve::math::TQuaternion<T> & p_orientation);


		public:
			/** \brief Get camera horizontal FOV.*/
			const T getFov(void) const;
			/** \brief Set camera horizontal FOV. */
			void setFov(T p_fov);


		public:
			/** \brief Get camera aspect ratio (4/3, 16/9, ...), basically : display width / display height. */
			const T getAspectRatio(void) const;
			/** \brief Set camera aspect ratio (4/3, 16/9, ...), basically : display width / display height.*/
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
			/** \brief Get near clipping plane coordinates. */
			void getNearClipCoordinates(eve::math::TVec3<T> * p_pTopLeft, eve::math::TVec3<T> * p_pTopRight, eve::math::TVec3<T> * p_pBottomLeft, eve::math::TVec3<T> * p_pBottomRight) const;
			/** \brief Get far clipping plane coordinates. */
			void getFarClipCoordinates(eve::math::TVec3<T> * p_pTopLeft, eve::math::TVec3<T> * p_pTopRight, eve::math::TVec3<T> * p_pBottomLeft, eve::math::TVec3<T> * p_pBottomRight) const;


		public:
			/** \brief Get camera frustum coordinates. */
			void getFrustum(T * p_pLeft, T * p_pTop, T * p_pRight, T * p_pBottom, T * p_pNear, T * p_pFar) const;


		public:
			/** \brief Get projection matrix. */
			eve::math::TMatrix44<T> & getMatrixProjection(void) const;
			/** \brief Get model view matrix. */
			virtual eve::math::TMatrix44<T> & getMatrixModelView(void) const;
			/** \brief Get model view projection matrix (MVP). */
			eve::math::TMatrix44<T> & getMatrixModelViewProjection(void) const;
			/** \brief Get inverse projection matrix. */
			eve::math::TMatrix44<T> & getMatrixInverseProjection(void) const;
			/** \brief Get inverse model view matrix. */
			eve::math::TMatrix44<T> & getMatrixInverseModelView(void) const;
			/** \brief Get viewport matrix. */
			eve::math::TMatrix44<T> & getMatrixViewport(void) const;


		public:
			/** \brief Get billboard vectors. */
			void getBillboardVectors(eve::math::TVec3<T> * p_pRight, eve::math::TVec3<T> * p_pUp) const;


		public:
			/** \brief Get point in scene distance from eye. */
			T getDistanceInScene(const eve::math::TVec3<T> & p_target);


		public:
			/** \brief Set perspective. */
			void setPerspective(T p_horizFovDegrees, T p_aspectRatio, T p_nearPlane, T p_farPlane);


		public:
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
eve::math::TCamera<T>::TCamera(T p_width, T p_height, T p_near, T p_far, T p_fov)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_width(p_width)
	, m_height(p_height)

	, m_eyePoint(eve::math::TVec3<T>::zero())
	, m_target(eve::math::TVec3<T>::zero())
	, m_worldUp(eve::math::TVec3<T>::zero())

	, m_viewDirection(eve::math::TVec3<T>::zero())
	, m_orientation(eve::math::TQuaternion<T>::identity())
	, m_centerOfInterest(static_cast<T>(0.0))

	, m_fov(p_fov)
	, m_aspectRatio(static_cast<T>(0.0))
	, m_nearClip(p_near)
	, m_farClip(p_far)
	, m_frustumDepth(static_cast<T>(0.0))
	, m_lensShift(eve::math::TVec2<T>::zero())

	, m_U(eve::math::TVec3<T>::xAxis())
	, m_V(eve::math::TVec3<T>::yAxis())
	, m_W(eve::math::TVec3<T>::zero())

	, m_matrixProjection(eve::math::TMatrix44<T>::zero())
	, m_matrixProjectionInverse(eve::math::TMatrix44<T>::zero())
	, m_matrixModelView(eve::math::TMatrix44<T>::zero())
	, m_matrixModelViewInverse(eve::math::TMatrix44<T>::zero())
	, m_matrixModelViewProjection(eve::math::TMatrix44<T>::zero())
	, m_matrixViewport(eve::math::TMatrix44<T>::zero())

	, m_frustumLeft(static_cast<T>(0.0))
	, m_frustumRight(static_cast<T>(0.0))
	, m_frustumTop(static_cast<T>(0.0))
	, m_frustumBottom(static_cast<T>(0.0))
{}

//=================================================================================================
template <typename T>
eve::math::TCamera<T>::TCamera(const eve::math::TCamera<T> & p_parent)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_width(p_parent.m_width)
	, m_height(p_parent.m_height)

	, m_eyePoint(p_parent.m_eyePoint)
	, m_target(p_parent.m_target)
	, m_worldUp(p_parent.m_worldUp)

	, m_viewDirection(p_parent.m_viewDirection)
	, m_orientation(p_parent.m_orientation)
	, m_centerOfInterest(p_parent.m_centerOfInterest)

	, m_fov(p_parent.m_fov)
	, m_aspectRatio(p_parent.m_aspectRatio)
	, m_nearClip(p_parent.m_nearClip)
	, m_farClip(p_parent.m_farClip)
	, m_frustumDepth(p_parent.m_frustumDepth)
	, m_lensShift(p_parent.m_lensShift)

	, m_U(p_parent.m_U)
	, m_V(p_parent.m_V)
	, m_W(p_parent.m_W)

	, m_matrixProjection(p_parent.m_matrixProjection)
	, m_matrixProjectionInverse(p_parent.m_matrixProjectionInverse)
	, m_matrixModelView(p_parent.m_matrixModelView)
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
	m_aspectRatio		= m_width/m_height;
	m_frustumDepth		= m_farClip - m_nearClip;

	m_eyePoint.x		= static_cast<T>(10.0);
	m_eyePoint.y		= static_cast<T>(10.0);
	m_eyePoint.z		= static_cast<T>(10.0);

	m_worldUp.x			= static_cast<T>(0.0);
	m_worldUp.y			= static_cast<T>(1.0);
	m_worldUp.z			= static_cast<T>(0.0);	

	m_target.x			= static_cast<T>(0.0);
	m_target.y			= static_cast<T>(0.0);
	m_target.z			= static_cast<T>(0.0);

	m_viewDirection		= (m_target - m_eyePoint).normalized();
	m_orientation		= eve::math::TQuaternion<T>( eve::math::TMatrix44<T>::alignZAxisWithTarget(-m_viewDirection, m_worldUp) ).normalized();
	m_centerOfInterest	= m_eyePoint.distance( m_target );

	// Members init.
	this->init();
}



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::init(void)
{
// 	// Test values.
// 	if (m_aspectRatio < static_cast<T>(0.000001)) {
// 		m_aspectRatio = m_width / m_height;
// 	}

// 	// Init matrices.
// 	m_matrixProjection.setToNull();
// 	m_matrixProjectionInverse.setToNull();
// 	m_matrixModelView.setToNull();
// 	m_matrixModelViewInverse.setToNull();
// 	m_matrixModelViewProjection.setToNull();
// 	m_matrixViewport.setToIdentity();


	// Compute matrices.
	this->calcMatrices();
	this->calcViewportMatrix();
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::release(void)
{
	// Nothing to do for now.
}



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::calcMatrices(void) const
{
	this->calcProjection();
	this->calcModelView();
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::calcModelView(void) const
{
	m_W = -m_viewDirection.normalized();
	m_U = m_orientation * eve::math::TVec3<T>::xAxis();
	m_V = m_orientation * eve::math::TVec3<T>::yAxis();

	eve::math::TVec3<T> d(-m_eyePoint.dot(m_U), -m_eyePoint.dot(m_V), -m_eyePoint.dot(m_W));
	T * m = m_matrixModelView.m;
	m[0] = m_U.x;		m[4] = m_U.y;		m[8] = m_U.z;		m[12] = d.x;
	m[1] = m_V.x;		m[5] = m_V.y;		m[9] = m_V.z;		m[13] = d.y;
	m[2] = m_W.x;		m[6] = m_W.y;		m[10] = m_W.z;		m[14] = d.z;
	/*m[ 3] = 0.0f;		m[ 7] = 0.0f;		m[11] = 0.0f;*/		m[15] = static_cast<T>(1.0);

	// Update inverse model view matrix
	m_matrixModelViewInverse = m_matrixModelView.inverted();

	// Update MVP
	m_matrixModelViewProjection = m_matrixProjection * m_matrixModelView;
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::calcProjection(void) const
{
	m_frustumTop	= m_nearClip * eve::math::tan(static_cast<T>(M_PI) / static_cast<T>(180.0) * m_fov * static_cast<T>(0.5));
	m_frustumBottom = -m_frustumTop;
	m_frustumRight	= m_frustumTop * m_aspectRatio;
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
	m[0] = static_cast<T>(2.0) * m_nearClip / (m_frustumRight - m_frustumLeft);
	//m[ 4] =  static_cast<T>(0.0);
	m[8] = (m_frustumRight + m_frustumLeft) / (m_frustumRight - m_frustumLeft);
	//m[12] =  static_cast<T>(0.0);

	//m[ 1] =  static_cast<T>(0.0);
	m[5] = static_cast<T>(2.0) * m_nearClip / (m_frustumTop - m_frustumBottom);
	m[9] = (m_frustumTop + m_frustumBottom) / (m_frustumTop - m_frustumBottom);
	//m[13] =  static_cast<T>(0.0);

	//m[ 2] =  static_cast<T>(0.0);
	//m[ 6] =  static_cast<T>(0.0);
	m[10] = -(m_farClip + m_nearClip) / (m_farClip - m_nearClip);
	m[14] = -(static_cast<T>(2.0) * m_farClip * m_nearClip) / (m_farClip - m_nearClip);

	//m[ 3] = static_cast<T>(0.0);
	//m[ 7] = static_cast<T>(0.0);
	m[11] = static_cast<T>(-1.0);
	//m[15] = static_cast<T>(0.0);


	m = m_matrixProjectionInverse.m;
	m[0] = (m_frustumRight - m_frustumLeft) / (static_cast<T>(2.0) * m_nearClip);
	//m[ 4] = static_cast<T>(0.0);
	//m[ 8] = static_cast<T>(0.0);
	m[12] = (m_frustumRight + m_frustumLeft) / (static_cast<T>(2.0) * m_nearClip);

	//m[ 1] = static_cast<T>(0.0);
	m[5] = (m_frustumTop - m_frustumBottom) / (static_cast<T>(2.0) * m_nearClip);
	//m[ 9] = static_cast<T>(0.0);
	m[13] = (m_frustumTop + m_frustumBottom) / (static_cast<T>(2.0) * m_nearClip);

	//m[ 2] = static_cast<T>(0.0);
	//m[ 6] = static_cast<T>(0.0);
	//m[10] = static_cast<T>(0.0);
	m[14] = static_cast<T>(-1.0);

	//m[ 3] = static_cast<T>(0.0);
	//m[ 7] = static_cast<T>(0.0);
	m[11] = -(m_farClip - m_nearClip) / (static_cast<T>(2.0) * m_farClip*m_nearClip);
	m[15] =  (m_farClip + m_nearClip) / (static_cast<T>(2.0) * m_farClip*m_nearClip);
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::calcViewportMatrix(void)
{
	//T halfWidth  = m_width / static_cast<T>(2.0);
	//T halfHeight = m_height / static_cast<T>(2.0);

	//eve::math::TMatrix44<T> * m = &m_matrixViewport;
	////m[ 0] = halfWidth;				m[ 4] = static_cast<T>(0.0);	m[ 8] = static_cast<T>(0.0);		m[12] = static_cast<T>(0.0);
	////m[ 1] = static_cast<T>(0.0);	m[ 5] = halfHeight;				m[ 9] = static_cast<T>(0.0);		m[13] = static_cast<T>(0.0);
	////m[ 2] = static_cast<T>(0.0);	m[ 6] = static_cast<T>(0.0);	m[10] = static_cast<T>(1.0);		m[14] = static_cast<T>(0.0);
	////m[ 3] = halfWidth;				m[ 7] = halfHeight;				m[11] = static_cast<T>(0.0);		m[15] = static_cast<T>(1.0);

	//m[ 0] = halfWidth;		
	//m[ 5] = halfHeight;
	//m[ 3] = halfWidth;		
	//m[ 7] = halfHeight;

	m_matrixViewport = eve::math::TMatrix44<T>::ortho(static_cast<T>(0.0), m_width, m_height, static_cast<T>(0.0));
}



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::lookAt(const eve::math::TVec3<T> & p_target)
{
	m_viewDirection = (p_target - m_eyePoint).normalized();
	m_orientation	= eve::math::TQuaternion<T>(eve::math::TMatrix44<T>::alignZAxisWithTarget(-m_viewDirection, m_worldUp)).normalized();

	this->calcModelView();
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::lookAt(const eve::math::TVec3<T> & p_eyePoint, const eve::math::TVec3<T> & p_target)
{
	m_eyePoint		= p_eyePoint;
	m_viewDirection = (p_target - m_eyePoint).normalized();
	m_orientation	= eve::math::TQuaternion<T>(eve::math::TMatrix44<T>::alignZAxisWithTarget(-m_viewDirection, m_worldUp)).normalized();

	this->calcModelView();
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::lookAt(const eve::math::TVec3<T> & p_eyePoint, const eve::math::TVec3<T> & p_target, const eve::math::TVec3<T> & p_up)
{
	m_eyePoint		= p_eyePoint;
	m_worldUp		= p_up.normalized();
	m_viewDirection = (p_target - m_eyePoint).normalized();
	m_orientation	= eve::math::TQuaternion<T>(eve::math::TMatrix44<T>::alignZAxisWithTarget(-m_viewDirection, m_worldUp)).normalized();

	this->calcModelView();
}



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::calibrateCamera(const eve::math::TMatrix44<T> & p_matrixProjection, const eve::math::TMatrix44<T> & p_matrixModelView)
{
	m_matrixProjection			= p_matrixProjection;
	m_matrixProjectionInverse	= m_matrixProjection.inverted();

	m_matrixModelView			= p_matrixModelView;
	m_matrixModelViewInverse	= m_matrixModelView.inverted();

	m_matrixModelViewProjection = m_matrixProjection * m_matrixModelView;
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::releaseCalibration(void)
{
	this->calcMatrices();
}



//=================================================================================================
template <typename T>
eve::math::TRay<T> eve::math::TCamera<T>::generateRay(T p_uPos, T p_vPos, T p_imagePlaneAspectRatio) const
{
	T s = (p_uPos - static_cast<T>(0.5)) * p_imagePlaneAspectRatio;
	T t = (p_vPos - static_cast<T>(0.5));
	T viewDistance = p_imagePlaneAspectRatio / eve::math::abs(m_frustumRight - m_frustumLeft) * m_nearClip;

	return eve::math::TRay<T>(m_eyePoint, (m_U * s + m_V * t - (m_W * viewDistance)).normalized());
}

//=================================================================================================
template <typename T>
eve::math::TRay<T> eve::math::TCamera<T>::generateRay(T p_uPos, T p_vPos, T p_imagePlaneWidth, T p_imagePlaneHeight) const
{
	return this->generateRay(p_uPos, p_vPos, p_imagePlaneWidth / p_imagePlaneHeight);
}

//=================================================================================================
template <typename T>
eve::math::TRay<T> eve::math::TCamera<T>::generateRay(eve::math::TVec2<T> p_pos, T p_imagePlaneWidth, T p_imagePlaneHeight) const
{
	return this->generateRay(p_pos.x, p_pos.y, p_imagePlaneWidth / p_imagePlaneHeight);
}



//=================================================================================================
template <typename T>
eve::math::TVec2<T> eve::math::TCamera<T>::worldToScreen(const eve::math::TVec3<T> & p_worldCoord, T p_screenWidth, T p_screenHeight) const
{
	eve::math::TVec3<T> eyeCoord = m_matrixModelView.transformPointAffine(p_worldCoord);
	eve::math::TVec3<T> ndc		 = m_matrixProjection.transformPoint(eyeCoord);

	return eve::math::TVec2<T>((ndc.x + static_cast<T>(1.0)) / static_cast<T>(2.0) * p_screenWidth, (static_cast<T>(1.0) - (ndc.y + static_cast<T>(1.0)) / static_cast<T>(2.0))*p_screenHeight);
}

//=================================================================================================
template <typename T>
eve::math::TVec3<T> eve::math::TCamera<T>::worldToEye(const eve::math::TVec3<T> & p_worldCoord)
{
	return m_matrixModelView.transformPointAffine(p_worldCoord);
}

//=================================================================================================
template <typename T>
T eve::math::TCamera<T>::worldToEyeDepth(const eve::math::TVec3<T> & p_worldCoord) const
{
	return (m_matrixModelView.m[2] * p_worldCoord.x + m_matrixModelView.m[6] * p_worldCoord.y + m_matrixModelView.m[10] * p_worldCoord.z + m_matrixModelView.m[14]);
}

//=================================================================================================
template <typename T>
eve::math::TVec3<T> eve::math::TCamera<T>::worldToNdc(const eve::math::TVec3<T> & p_worldCoord)
{
	eve::math::TVec3<T> eye = m_matrixModelView.transformPointAffine(p_worldCoord);

	return m_matrixProjection.transformPoint(eye);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		MATRIX
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::translate(const eve::math::TVec3<T> & p_translation)
{
	this->setEyePoint(m_eyePoint + p_translation);
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::translateX(T p_translationX)
{
	this->setEyePointX(m_eyePoint.x + p_translationX);
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::translateY(T p_translationY)
{
	this->setEyePointY(m_eyePoint.y + p_translationY);
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::translateZ(T p_translationZ)
{
	this->setEyePointZ(m_eyePoint.z + p_translationZ);
}



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::rotate(const eve::math::TVec3<T> & p_rotation)
{
	eve::math::TVec3<T> coi = getCenterOfInterestPoint() + p_rotation;
	this->lookAt(coi);
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::rotateX(T p_rotationX)
{
	eve::math::TVec3<T> coi = getCenterOfInterestPoint();
	coi.x += p_rotationX;
	this->lookAt(coi);
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::rotateY(T p_rotationY)
{
	eve::math::TVec3<T> coi = getCenterOfInterestPoint();
	coi.y += p_rotationY;
	this->lookAt(coi);
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::rotateZ(T p_rotationZ)
{
	eve::math::TVec3<T> coi = getCenterOfInterestPoint();
	coi.z += p_rotationZ;
	this->lookAt(coi);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TCamera<T>::getEyePoint(void) const	{ return m_eyePoint;   }
template<typename T>
EVE_FORCE_INLINE const T					eve::math::TCamera<T>::getEyePointX(void) const { return m_eyePoint.x; }
template<typename T>
EVE_FORCE_INLINE const T					eve::math::TCamera<T>::getEyePointY(void) const { return m_eyePoint.y; }
template<typename T>
EVE_FORCE_INLINE const T					eve::math::TCamera<T>::getEyePointZ(void) const { return m_eyePoint.z; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setEyePoint(const eve::math::TVec3<T> & p_eyePoint)
{
	m_eyePoint = p_eyePoint;
	this->calcModelView();
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setEyePointX(T p_eyePointX)
{
	m_eyePoint.x = p_eyePointX;
	this->calcModelView();
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setEyePointY(T p_eyePointY)
{
	m_eyePoint.y = p_eyePointY;
	this->calcModelView();
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setEyePointZ(T p_eyePointZ)
{
	m_eyePoint.z = p_eyePointZ;
	this->calcModelView();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TCamera<T>::getTranslation(void) const	{ return m_eyePoint;   }
template<typename T>
EVE_FORCE_INLINE const T					eve::math::TCamera<T>::getTranslationX(void) const	{ return m_eyePoint.x; }
template<typename T>
EVE_FORCE_INLINE const T					eve::math::TCamera<T>::getTranslationY(void) const	{ return m_eyePoint.y; }
template<typename T>
EVE_FORCE_INLINE const T					eve::math::TCamera<T>::getTranslationZ(void) const	{ return m_eyePoint.z; }





//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getCenterOfInterest(void) const	{ return m_centerOfInterest; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setCenterOfInterest(T p_centerOfInterest)
{
	m_centerOfInterest = p_centerOfInterest;
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TCamera<T>::getCenterOfInterestPoint(void) const	{ return (m_eyePoint + m_viewDirection * m_centerOfInterest); }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setCenterOfInterestPoint(const eve::math::TVec3<T> & p_centerOfInterestPoint)
{
	m_centerOfInterest = m_eyePoint.distance(p_centerOfInterestPoint);
	this->lookAt(p_centerOfInterestPoint);
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T> eve::math::TCamera<T>::getWorldUp(void) const { return m_worldUp; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setWorldUp(const eve::math::TVec3<T> & p_worldUp)
{
	m_worldUp = p_worldUp.normalized();
	m_orientation = eve::math::TQuaternion<T>(eve::math::TMatrix44<T>::alignZAxisWithTarget(-m_viewDirection, m_worldUp)).normalized();

	this->calcModelView();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T> eve::math::TCamera<T>::getRightVector(void) const { return m_U; }



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T> eve::math::TCamera<T>::getViewDirection(void) const { return m_viewDirection; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setViewDirection(const eve::math::TVec3<T> & p_viewDirection)
{
	m_viewDirection = p_viewDirection.normalized();
	m_orientation	= eve::math::TQuaternion<T>(eve::math::TVec3<T>(static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(-1.0)), m_viewDirection);

	this->calcModelView();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TQuaternion<T> eve::math::TCamera<T>::getOrientation(void) const { return m_orientation; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setOrientation(const eve::math::TQuaternion<T> & p_orientation)
{
	m_orientation = p_orientation.normalized();
	m_viewDirection = m_orientation * eve::math::TVec3<T>(static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(-1.0));

	this->calcModelView();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getFov(void) const { return m_fov; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setFov(T p_fov)
{
	m_fov = p_fov;
	this->calcProjection();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getAspectRatio(void) const { return m_aspectRatio; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setAspectRatio(T p_aspectRatio)
{
	m_aspectRatio = p_aspectRatio;
	this->calcProjection();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getNearClip(void) const { return m_nearClip; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setNearClip(T p_nearClip)
{
	m_nearClip = p_nearClip;
	this->calcProjection();
}

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getFarClip(void) const { return m_farClip; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setFarClip(T p_farClip)
{
	m_farClip = p_farClip;
	this->calcProjection();
}

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getFrustumDepth(void) const { return m_frustumDepth; }



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::getNearClipCoordinates(eve::math::TVec3<T> * p_pTopLeft, eve::math::TVec3<T> * p_pTopRight, eve::math::TVec3<T> * p_pBottomLeft, eve::math::TVec3<T> * p_pBottomRight) const
{
	eve::math::TVec3<T> viewDirection(m_viewDirection.normalized());

	*p_pTopLeft		= m_eyePoint + (m_nearClip * viewDirection) + (m_frustumTop    * m_V) + (m_frustumLeft  * m_U);
	*p_pTopRight	= m_eyePoint + (m_nearClip * viewDirection) + (m_frustumTop    * m_V) + (m_frustumRight * m_U);
	*p_pBottomLeft	= m_eyePoint + (m_nearClip * viewDirection) + (m_frustumBottom * m_V) + (m_frustumLeft  * m_U);
	*p_pBottomRight = m_eyePoint + (m_nearClip * viewDirection) + (m_frustumBottom * m_V) + (m_frustumRight * m_U);
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::getFarClipCoordinates(eve::math::TVec3<T> * p_pTopLeft, eve::math::TVec3<T> * p_pTopRight, eve::math::TVec3<T> * p_pBottomLeft, eve::math::TVec3<T> * p_pBottomRight) const
{
	eve::math::TVec3<T> viewDirection(m_viewDirection.normalized());

	T ratio = m_farClip / m_nearClip;

	*p_pTopLeft		= m_eyePoint + (m_farClip * viewDirection) + (ratio * m_frustumTop    * m_V) + (ratio * m_frustumLeft  * m_U);
	*p_pTopRight	= m_eyePoint + (m_farClip * viewDirection) + (ratio * m_frustumTop    * m_V) + (ratio * m_frustumRight * m_U);
	*p_pBottomLeft	= m_eyePoint + (m_farClip * viewDirection) + (ratio * m_frustumBottom * m_V) + (ratio * m_frustumLeft  * m_U);
	*p_pBottomRight = m_eyePoint + (m_farClip * viewDirection) + (ratio * m_frustumBottom * m_V) + (ratio * m_frustumRight * m_U);
}



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::getFrustum(T * p_pLeft, T * p_pTop, T * p_pRight, T * p_pBottom, T * p_pNear, T * p_pFar) const
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
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixProjection(void) const				{ return m_matrixProjection; }
template<typename T>								
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixModelView(void) const				{ return m_matrixModelView; }
template<typename T>								
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixModelViewProjection(void) const		{ return m_matrixModelViewProjection; }
template<typename T>								
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixInverseProjection(void) const		{ return m_matrixProjectionInverse; }
template<typename T>								
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixInverseModelView(void) const		{ return m_matrixModelViewInverse; }
template<typename T>								
EVE_FORCE_INLINE eve::math::TMatrix44<T> &	eve::math::TCamera<T>::getMatrixViewport(void) const				{ return m_matrixViewport; }



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::getBillboardVectors(eve::math::TVec3<T> * p_pRight, eve::math::TVec3<T> * p_pUp) const
{
	p_pRight->set(m_matrixModelView.m[0], m_matrixModelView.m[4], m_matrixModelView.m[8]);
	p_pUp->set(m_matrixModelView.m[1], m_matrixModelView.m[5], m_matrixModelView.m[9]);
}



//=================================================================================================
template <typename T>
T eve::math::TCamera<T>::getDistanceInScene(const eve::math::TVec3<T> & p_target)
{
	eve::vec4f temp = m_matrixModelView * eve::vec4f(p_target.x, p_target.y, p_target.z, static_cast<T>(1.0));

	T distance = eve::math::TVec3<T>(temp.x, temp.y, temp.z).length();

	return distance;
}



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setPerspective(T p_horizFovDegrees, T p_aspectRatio, T p_nearPlane, T p_farPlane)
{
	m_fov			= p_horizFovDegrees;
	m_aspectRatio	= p_aspectRatio;
	m_nearClip		= p_nearPlane;
	m_farClip		= p_farPlane;

	this->calcProjection();
}



//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setDisplaySize(T p_width, T p_height, bool p_bUpdateAspectRatio)
{
	m_width		= p_width;
	m_height	= p_height;

	if (p_bUpdateAspectRatio) 
	{
		this->setAspectRatio(m_width / m_height);
	}

	this->calcViewportMatrix();
}

//=================================================================================================
template <typename T>
template <typename U>
void eve::math::TCamera<T>::setDisplaySize(U p_width, U p_height, bool p_bUpdateAspectRatio)
{
	this->setDisplaySize(static_cast<T>(p_width), static_cast<T>(p_height), p_bUpdateAspectRatio);
}


//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T> eve::math::TCamera<T>::getLensShift(void) const { return m_lensShift; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::getLensShift(T * p_pHorizontal, T * p_pVertical) const
{
	*p_pHorizontal	= m_lensShift.x;
	*p_pVertical	= m_lensShift.y;
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setLensShift(T p_horizontal, T p_vertical)
{
	m_lensShift.x = p_horizontal;
	m_lensShift.y = p_vertical;

	this->calcProjection();
}

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setLensShift(const eve::math::TVec2<T> & p_shift)
{
	m_lensShift.x = p_shift.x;
	m_lensShift.y = p_shift.y;

	this->calcProjection();
}

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getLensShiftHorizontal(void) const { return m_lensShift.x; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setLensShiftHorizontal(T p_horizontal)
{
	m_lensShift.x = p_horizontal;
	this->calcProjection();
}

//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const T eve::math::TCamera<T>::getLensShiftVertical(void) const { return m_lensShift.y; }

//=================================================================================================
template <typename T>
void eve::math::TCamera<T>::setLensShiftVertical(T p_vertical)
{
	m_lensShift.y = p_vertical;
	this->calcProjection();
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T> eve::math::TCamera<T>::getHalfSize(void) const { return eve::math::TVec2<T>(m_width*static_cast<T>(0.5), m_height*static_cast<T>(0.5)); }





//=================================================================================================
//template <typename T>
// bool eve::math::TCamera<T>::initFromImport( const aiCamera * pCamera, const aiScene * pScene, const eve::math::TVec3<T> & p_upAxis )
// {
// #ifndef NDEBUG
// 	NATIVE_ASSERT( (pCamera!=NULL)	);
// 	NATIVE_ASSERT( (pScene!=NULL)	);
// #endif
// 
// 	// Create return value.
// 	bool breturn = (pCamera!=NULL) && (pScene!=NULL);
// 
// 	if( breturn )
// 	{
// 		// Stock item type.
// 		m_itemType		= Item_Camera;
// 		m_itemSubType	= Item_Camera_Simple;
// 
// 		// Stock ASSIMP pointer.
// 		m_pAiScene	= pScene;
// 		m_pAiCamera = pCamera;
// 
// 		// Loaded camera data copy.
// 		m_name				= std::string( m_pAiCamera->mName.data );
// 
// 		m_aspectRatio		= m_pAiCamera->mAspect;
// 		m_nearClip			= m_pAiCamera->mClipPlaneNear;
// 		m_farClip			= m_pAiCamera->mClipPlaneFar;
// 		m_frustumDepth		= m_farClip - m_nearClip;
// 		m_fov				= toDegrees( m_pAiCamera->mHorizontalFOV );
// 
// 		m_eyePoint.x		= m_pAiCamera->mPosition.x;
// 		m_eyePoint.y		= m_pAiCamera->mPosition.y;
// 		m_eyePoint.z		= m_pAiCamera->mPosition.z;
// 
// 		m_target.x			= m_pAiCamera->mLookAt.x;
// 		m_target.y			= m_pAiCamera->mLookAt.y;
// 		m_target.z			= m_pAiCamera->mLookAt.z;
// 
// 		m_worldUp.x			= m_pAiCamera->mUp.x;
// 		m_worldUp.y			= m_pAiCamera->mUp.y;
// 		m_worldUp.z			= m_pAiCamera->mUp.z;
// 
// 		// Find scene node 
// 		aiNode * pRoot = m_pAiScene->mRootNode;
// 		aiNode * pNode = pRoot->FindNode( m_name.c_str() );
// 		breturn = pNode!=NULL;
// 
// #ifndef NDEBUG
// 		NATIVE_ASSERT( breturn );
// #else
// 		if( breturn )
// #endif
// 		{
// 			// Compute scene node matrix 
// 			aiMatrix4x4 mat;
// 			while( pNode != pRoot )
// 			{
// 				mat = pNode->mTransformation * mat;
// 				pNode = pNode->mParent;
// 			}
// 
// 			//if( p_upAxis.z > static_cast<T>(0.0) )
// 			//{
// 			//	aiMatrix4x4 aim;
// 			//	m_pAiCamera->GetCameraMatrix(aim);
// 			//	mat = aim * mat;
// 			//}
// 
// 			eve::math::TMatrix44<T> matrix( mat.a1, mat.b1, mat.c1, mat.d1
// 							, mat.a2, mat.b2, mat.c2, mat.d2
// 							, mat.a3, mat.b3, mat.c3, mat.d3
// 							, mat.a4, mat.b4, mat.c4, mat.d4 );
// 
// 			// Correct Up Axis if needed.
// 			if( p_upAxis.z > static_cast<T>(0.0) )
// 			{
// 				matrix.fromZupToYup();
// 			}
// 
// 			// Invert matrix to retrieve camera view coordinates.
// 			matrix.invert();
// 			
// 			// Extract camera data from model view matrix.
// 			eve::math::get_look_at( matrix, m_eyePoint, m_target, m_worldUp );
// 
// 			// Compute camera matrix required data.
// 			m_viewDirection		= (m_target - m_eyePoint).normalized();
// 			m_orientation		= eve::math::TQuaternion<T>( eve::math::TMatrix44<T>::alignZAxisWithTarget(-m_viewDirection, m_worldUp) ).normalized();
// 			m_centerOfInterest	= m_eyePoint.distance( m_target );
// 			
// 		}
// 
// 		// Init all data.
// 		this->init();
// 	}
// 
// 	return breturn;
// }

#endif // __EVE_MATH_TCAMERA_H__
