
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
#ifndef __EVE_MATH_CAMERA_H__
#define __EVE_MATH_CAMERA_H__

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_INCLUDES_H__
#include "eve/math/core/Includes.h"
#endif

#ifndef __EVE_MATH_TYPES_H__
#include "eve/math/Types.h"
#endif


namespace eve
{
	namespace math
	{

		/** 
		* \class eve::math::Camera
		*
		* \brief 3D Camera object math and manipulation.
		*
		* \note extends eve::mem::Pointer
		*/
		class Camera
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			float							m_width;						//!< View width.
			float							m_height;						//!< View height.

		protected:
			eve::vec3f						m_eyePoint;						//!< Eye position in 3D world.
			eve::vec3f						m_target;						//!< View target in 3D world.
			eve::vec3f						m_worldUp;						//!< View UP axis.

		protected:
			eve::vec3f						m_viewDirection;				//!< Normalized view direction.
			eve::quatf						m_orientation;					//!< Orientation (rotation).
			float							m_centerOfInterest;				//!< Center of interest.

		protected:
			float							m_fov;							//!< Horizontal field of view (aspect).
			float							m_aspectRatio;					//!< Aspect ratio (vertical FOV).
			float							m_nearClip;						//!< Near clipping plane.
			float							m_farClip;						//!< Far clipping plane.
			float							m_frustumDepth;					//!< Frustum depth (near clipping plane - far clipping plane).
			eve::vec2f						m_lensShift;					//!< Lens shift on both axis.

		protected:
			mutable eve::vec3f				m_U;							//!< Right vector.
			mutable eve::vec3f				m_V;							//!< Readjust up-vector.
			mutable eve::vec3f				m_W;							//!< Negative view direction.

		protected:
			mutable eve::mat44f				m_matrixProjection;				//!< Projection matrix.
			mutable eve::mat44f				m_matrixProjectionInverse;		//!< Inversed projection matrix.
			mutable eve::mat44f				m_matrixModelView;				//!< Model view matrix.
			mutable eve::mat44f				m_matrixModelViewInverse;		//!< Inversed model view matrix.
			mutable eve::mat44f				m_matrixModelViewProjection;	//!< Projection matrix * Model view matrix.
			mutable eve::mat44f				m_matrixViewport;				//!< Viewport matrix.

		protected:
			mutable float					m_frustumLeft;					//!< Left frustum border.
			mutable float					m_frustumRight;					//!< Right frustum border.
			mutable float					m_frustumTop;					//!< Top frustum border.
			mutable float					m_frustumBottom;				//!< Bottom frustum border.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_ASSIGNATION(Camera);
			EVE_PROTECT_DESTRUCTOR(Camera);

		public:
			/** \brief Create new pointer. */
			static eve::math::Camera * create_ptr(float p_width = 800.0f, float p_height = 600.0f, float p_near = 1.0f, float p_far = 1000.0f, float p_fov = 65.0f);
			/** \brief Create new pointer, copy of \p_parent. */
			static eve::math::Camera * create_ptr(const Camera & p_parent);


		protected:
			/** \brief Class constructor. */
			explicit Camera(float p_width, float p_height, float p_near, float p_far, float p_fov);
			/** \brief Copy constructor. */
			explicit Camera(const Camera & p_parent);


		protected:
			/** \brief Initialize camera with default values. */
			virtual void initDefault(void);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void);
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void);


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
			void lookAt(const eve::vec3f & p_target);
			/** \brief Look at target point for given eye position. */
			void lookAt(const eve::vec3f & p_eyePoint, const eve::vec3f & p_target);
			/** \brief Look at target point for given eye position and world up vector. */
			void lookAt(const eve::vec3f & p_eyePoint, const eve::vec3f & p_target, const eve::vec3f & p_up);


		public:
			/** \brief Calibrate camera by setting projection and model view matrix. */
			void calibrateCamera(const eve::mat44f & p_matrixProjection, const eve::mat44f & p_matrixModelView);
			/** \brief Release calibration by computing matrices from RTS values. */
			void releaseCalibration(void);


		public:
			/** \brief Generate ray from point. */
			eve::rayf generateRay(float p_uPos, float p_vPos, float p_imagePlaneAspectRatio) const;
			/** \brief Generate ray from point. */
			eve::rayf generateRay(float p_uPos, float p_vPos, float p_imagePlaneWidth, float p_imagePlaneHeight) const;
			/** \brief Generate ray from point. */
			eve::rayf generateRay(eve::vec2f p_pos, float p_imagePlaneWidth, float p_imagePlaneHeight) const;


		public:
			/** \brief Convert world-space coordinate to screen coordinates. */
			eve::vec2f worldToScreen(const eve::vec3f & p_worldCoord, float p_screenWidth, float p_screenHeight) const;
			/** \brief Convert world-space coordinate to eye-space (camera-space, -Z is along the view direction). */
			eve::vec3f worldToEye(const eve::vec3f & p_worldCoord);
			/** \brief Convert world-space coordinate to the z axis of eye-space (camera-space, -Z is along the view direction, suitable for depth sorting). */
			float worldToEyeDepth(const eve::vec3f & p_worldCoord) const;
			/** \brief Convert world-space coordinate to normalized device coordinates. */
			eve::vec3f worldToNdc(const eve::vec3f & p_worldCoord);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		MATRIX
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** Translate object. */
			virtual void translate(const eve::vec3f & p_translation);
			/** Translate object on X-axis. */
			virtual void translateX(float p_translationX);
			/** Translate object on Y-axis. */
			virtual void translateY(float p_translationY);
			/** Translate object on Z-axis. */
			virtual void translateZ(float p_translationZ);


		public:
			/** Rotate object. */
			virtual void rotate(const eve::vec3f & p_rotation);
			/** Rotate object on X-axis. */
			virtual void rotateX(float p_rotationX);
			/** Rotate object on Y-axis. */
			virtual void rotateY(float p_rotationY);
			/** Rotate object on Z-axis. */
			virtual void rotateZ(float p_rotationZ);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get eye point. */
			const eve::vec3f getEyePoint(void) const;
			/** \brief Set eye point. */
			void setEyePoint(const eve::vec3f & p_eyePoint);
			/** \brief Set eye point X value. */
			void setEyePointX(float p_eyePointX);
			/** \brief Set eye point Y value. */
			void setEyePointY(float p_eyePointY);
			/** \brief Set eye point Z value. */
			void setEyePointZ(float p_eyePointZ);


		public:
			/** Get translation. */
			const eve::vec3f getTranslation(void) const;
			/** Get translation on X-axis. */
			const float getTranslationX(void) const;
			/** Get translation on Y-axis. */
			const float getTranslationY(void) const;
			/** Get translation on Z-axis. */
			const float getTranslationZ(void) const;


		public:
			/** \brief Get center of interest. */
			const float getCenterOfInterest(void) const;
			/** \brief Set center of interest. */
			void setCenterOfInterest(float p_centerOfInterest);


		public:
			/** \brief Get center of interest point. */
			const eve::vec3f getCenterOfInterestPoint(void) const;
			/** \brief Set center of interest point. */
			void setCenterOfInterestPoint(const eve::vec3f & p_centerOfInterestPoint);


		public:
			/** \brief Get world up. */
			const eve::vec3f getWorldUp(void) const;
			/** \brief Set world up. */
			void setWorldUp(const eve::vec3f & p_worldUp);


		public:
			/** \brief Get view direction. */
			const eve::vec3f getViewDirection(void) const;
			/** \brief Set view direction. */
			void setViewDirection(const eve::vec3f & p_viewDirection);


		public:
			/** \brief Get camera orientation. */
			const eve::quatf getOrientation(void) const;
			/** \brief Set camera orientation. */
			void setOrientation(const eve::quatf & p_orientation);


		public:
			/** \brief Get camera horizontal FOV.*/
			const float getFov(void) const;
			/** \brief Set camera horizontal FOV. */
			void setFov(float p_fov);


		public:
			/** \brief Get camera aspect ratio (4/3, 16/9, ...), basically : display width / display height. */
			const float getAspectRatio(void) const;
			/** \brief Set camera aspect ratio (4/3, 16/9, ...), basically : display width / display height.*/
			void setAspectRatio(float p_aspectRatio);


		public:
			/** \brief Get near clipping plane distance. */
			const float getNearClip(void) const;
			/** \brief Set near clipping plane distance. */
			void setNearClip(float p_nearClip);


		public:
			/** \brief Get frustum depth (far-near). */
			const float getFrustumDepth(void) const;


		public:
			/** \brief Get far clipping plane distance. */
			const float getFarClip(void) const;
			/** \brief Set near clipping plane distance. */
			void setFarClip(float p_farClip);


		public:
			/** \brief Get near clipping plane coordinates. */
			void getNearClipCoordinates(eve::vec3f * p_pTopLeft, eve::vec3f * p_pTopRight, eve::vec3f * p_pBottomLeft, eve::vec3f * p_pBottomRight) const;
			/** \brief Get far clipping plane coordinates. */
			void getFarClipCoordinates(eve::vec3f * p_pTopLeft, eve::vec3f * p_pTopRight, eve::vec3f * p_pBottomLeft, eve::vec3f * p_pBottomRight) const;


		public:
			/** \brief Get camera frustum coordinates. */
			void getFrustum(float * p_pLeft, float * p_pTop, float * p_pRight, float * p_pBottom, float * p_pNear, float * p_pFar) const;


		public:
			/** \brief Get projection matrix. */
			const eve::mat44f & getMatrixProjection(void) const;
			/** \brief Get model view matrix. */
			virtual const eve::mat44f & getMatrixModelView(void) const;
			/** \brief Get model view projection matrix (MVP). */
			const eve::mat44f & getMatrixModelViewProjection(void) const;
			/** \brief Get inverse projection matrix. */
			const eve::mat44f & getMatrixInverseProjection(void) const;
			/** \brief Get inverse model view matrix. */
			const eve::mat44f & getMatrixInverseModelView(void) const;
			/** \brief Get viewport matrix. */
			const eve::mat44f & getMatrixViewport(void) const;


		public:
			/** \brief Get billboard vectors. */
			void getBillboardVectors(eve::vec3f * p_pRight, eve::vec3f * p_pUp) const;


		public:
			/** \brief Get point in scene distance from eye. */
			float getDistanceInScene(const eve::vec3f & p_target);


		public:
			/** \brief Set perspective. */
			void setPerspective(float p_horizFovDegrees, float p_aspectRatio, float p_nearPlane, float p_farPlane);


		public:
			/** \brief Set display size. */
			virtual void setDisplaySize(float p_width, float p_height, bool p_bUpdateAspectRatio = true);


		public:
			/** 
			* \brief Return both the horizontal and vertical lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			void getLensShift(float * p_pHorizontal, float * p_pVertical) const;
			/** 
			* \brief Return both the horizontal and vertical lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			const eve::vec2f getLensShift(void) const;


			/** 
			* \brief Set both the horizontal and vertical lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			void setLensShift(float p_horizontal, float p_vertical);
			/** 
			* \brief Set both the horizontal and vertical lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			void setLensShift(const eve::vec2f & p_shift);


			/** 
			* \brief Get horizontal lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			*/
			const float getLensShiftHorizontal(void) const;
			/** 
			* \brief Set horizontal lens shift.
			* Horizontal lens shift of 1 (-1) will shift the view right (left) by half the width of the viewport.
			*/
			void setLensShiftHorizontal(float p_horizontal);


			/** 
			* \brief Get vertical lens shift
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			const float getLensShiftVertical(void) const;
			/** 
			* \brief Set vertical lens shift
			* Vertical lens shift of 1 (-1) will shift the view up (down) by half the height of the viewport.
			*/
			void setLensShiftVertical(float p_vertical);


		public:
			/** \brief Get half view size. */
			const eve::vec2f getHalfSize(void) const;

		}; // class Camera

	} // namespace math

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
inline const eve::vec3f		eve::math::Camera::getEyePoint(void) const						{ return m_eyePoint;			}

//=================================================================================================
inline const eve::vec3f		eve::math::Camera::getTranslation(void) const					{ return m_eyePoint;			}
inline const float			eve::math::Camera::getTranslationX(void) const					{ return m_eyePoint.x;			}
inline const float			eve::math::Camera::getTranslationY(void) const					{ return m_eyePoint.y;			}
inline const float			eve::math::Camera::getTranslationZ(void) const					{ return m_eyePoint.z;			}

//=================================================================================================
inline const float			eve::math::Camera::getCenterOfInterest(void) const				{ return m_centerOfInterest;	}
inline const eve::vec3f		eve::math::Camera::getCenterOfInterestPoint(void) const			{ return (m_eyePoint + m_viewDirection * m_centerOfInterest); }

//=================================================================================================
inline const eve::vec3f		eve::math::Camera::getWorldUp(void) const						{ return m_worldUp;				}
inline const eve::vec3f		eve::math::Camera::getViewDirection(void) const					{ return m_viewDirection;		}
inline const eve::quatf		eve::math::Camera::getOrientation(void) const					{ return m_orientation;			}
inline const float			eve::math::Camera::getFov(void) const							{ return m_fov;					}
inline const float			eve::math::Camera::getAspectRatio(void) const					{ return m_aspectRatio;			}

//=================================================================================================
inline const float			eve::math::Camera::getNearClip(void) const						{ return m_nearClip;			}
inline const float			eve::math::Camera::getFarClip(void) const						{ return m_farClip;				}
inline const float			eve::math::Camera::getFrustumDepth(void) const					{ return m_frustumDepth;		}

//=================================================================================================
inline const eve::mat44f &	eve::math::Camera::getMatrixProjection(void) const				{ return m_matrixProjection;	}
inline const eve::mat44f &	eve::math::Camera::getMatrixModelView(void) const				{ return m_matrixModelView;		}
inline const eve::mat44f &	eve::math::Camera::getMatrixModelViewProjection(void) const		{ return m_matrixModelViewProjection;	}
inline const eve::mat44f &	eve::math::Camera::getMatrixInverseProjection(void) const		{ return m_matrixProjectionInverse;		}
inline const eve::mat44f &	eve::math::Camera::getMatrixInverseModelView(void) const		{ return m_matrixModelViewInverse;		}
inline const eve::mat44f &	eve::math::Camera::getMatrixViewport(void) const				{ return m_matrixViewport;		}

//=================================================================================================
inline const eve::vec2f		eve::math::Camera::getLensShift(void) const						{ return m_lensShift;			}
inline const float			eve::math::Camera::getLensShiftHorizontal(void) const			{ return m_lensShift.x;			}
inline const float			eve::math::Camera::getLensShiftVertical(void) const				{ return m_lensShift.y;			}

//=================================================================================================
inline const eve::vec2f		eve::math::Camera::getHalfSize(void) const						{ return eve::vec2f(m_width*0.5f, m_height*0.5f); }

#endif // __EVE_MATH_CAMERA_H__
