
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
#ifndef __EVE_MATH_TTRANSFORM_H__
#define __EVE_MATH_TTRANSFORM_H__

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_INCLUDES_H__
#include "eve/math/core/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_TMATRIX_H__
#include "eve/math/core/TMatrix.h"
#endif

#ifndef __EVE_MATH_CORE_TVECTOR_H__
#include "eve/math/core/TVector.h"
#endif


namespace eve
{
	namespace math
	{

		/** 
		* \class eve::math::TTransform
		*
		* \brief Template 3D object math and manipulation, using RTS matrix order.
		*
		* \note extends eve::mem::Pointer
		*/
		template <typename T>
		class TTransform
			: public eve::mem::Pointer
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			mutable eve::math::TVec3<T>			m_rotation;						//!< Specifies Rotation (radians).
			mutable eve::math::TVec3<T>			m_translation;					//!< Specifies translation.
			mutable eve::math::TVec3<T>			m_scale;						//!< Specifies scale.

			mutable eve::math::TVec3<T>			m_pivot;						//!< Specifies pivot point (rotation origin), default to vec3(0, 0, 0).

			mutable eve::math::TMatrix44<T>		m_matrixRotation;				//!< Specifies rotation matrix.
			mutable eve::math::TMatrix44<T>		m_matrixScale;					//!< Specifies scale matrix.
			mutable eve::math::TMatrix44<T>		m_matrixModelView;				//!< Specifies model view matrix.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_ASSIGNATION(TTransform);
			EVE_PUBLIC_DESTRUCTOR(TTransform);

		public:
			/** \brief Create new pointer, copy of \p_parent. */
			static eve::math::TTransform<T> * create_ptr(const TTransform<T> & p_parent);

			
		public:
			/** \brief Class constructor. */
			explicit TTransform(void);
			/** \brief Copy constructor. */
			explicit TTransform(const TTransform<T> & p_parent);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		protected:
			/** \brief Update rotation matrix.*/
			void updateMatrixRotation(void);
			/** \brief Update translation matrix. */
			void updateMatrixTranslation(void);
			/** \brief Update scale matrix. */
			void updateMatrixScale(void);
			/** \brief Update model view matrix based on rot/trans/scale matrices concatenation. */
			virtual void updateMatrixModelView(void);


		public:
			/** \brief Rotate object (radians). */
			void rotate(const eve::math::TVec3<T> & p_rotation);
			/** \brief Rotate object (radians). */
			void rotate(T p_x, T p_y, T p_z);
			/** \brief Rotate object on X-axis (radians). */
			void rotateX(T p_rotationX);
			/** \brief Rotate object on Y-axis (radians). */
			void rotateY(T p_rotationY);
			/** \brief Rotate object on Z-axis (radians). */
			void rotateZ(T p_rotationZ);


		public:
			/** \brief Rotate object using pivot point as origin (radians). */
			void rotatePivot(const eve::math::TVec3<T> & p_rotation);
			/** \brief Rotate object using pivot point as origin (radians). */
			void rotatePivot(T p_x, T p_y, T p_z);
			/** \brief Rotate object using pivot point as origin on X-axis (radians). */
			void rotatePivotX(T p_rotationX);
			/** \brief Rotate object using pivot point as origin on Y-axis (radians). */
			void rotatePivotY(T p_rotationY);
			/** \brief Rotate object using pivot point as origin on Z-axis (radians). */
			void rotatePivotZ(T p_rotationZ);


		public:
			/** \brief Translate object. */
			void translate(const eve::math::TVec3<T> & p_translation);
			/** \brief Translate object. */
			void translate(T p_x, T p_y, T p_z);
			/** \brief Translate object on X-axis. */
			void translateX(T p_translationX);
			/** \brief Translate object on Y-axis. */
			void translateY(T p_translationY);
			/** \brief Translate object on Z-axis. */
			void translateZ(T p_translationZ);


		public:
			/** \brief Scale object. */
			void scale(const eve::math::TVec3<T> & p_scale);
			/** \brief Scale object. */
			void scale(T p_x, T p_y, T p_z);
			/** \brief Scale object on X-axis. */
			void scaleX(T p_scaleX);
			/** \brief Scale object on Y-axis. */
			void scaleY(T p_scaleY);
			/** \brief Scale object on Z-axis. */
			void scaleZ(T p_scaleZ);


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get rotation (radians). */
			const eve::math::TVec3<T> & getRotation(void) const;
			/** \brief Get rotation on X-axis (radians). */
			const T getRotationX(void) const;
			/** \brief Get rotation on Y-axis (radians). */
			const T getRotationY(void) const;
			/** \brief Get rotation on Z-axis (radians). */
			const T getRotationZ(void) const;

			/** \brief Set rotation (radians). */
			void setRotation(const eve::math::TVec3<T> & p_value);
			/** \brief Set rotation (radians). */
			void setRotation(eve::math::TQuaternion<T> & p_value);
			/** \brief Set rotation (radians). */
			void setRotation(T p_x, T p_y, T p_z);
			/** \brief Set rotation on X-axis (radians). */
			void setRotationX(T p_value);
			/** \brief Set rotation on Y-axis (radians). */
			void setRotationY(T p_value);
			/** \brief Set rotation on Z-axis (radians). */
			void setRotationZ(T p_value);


		public:
			/** \brief Get pivot point (rotation origin) position in 3D view. */
			const eve::math::TVec3<T> & getPivot(void) const;
			/** \brief Set pivot point (rotation origin) position in 3D view. */
			void setPivot(const eve::math::TVec3<T> & p_value);
			/** \brief Set pivot point (rotation origin) position in 3D view. */
			void setPivot(T p_x, T p_y, T p_z);


		public:
			/** \brief Get translation. */
			const eve::math::TVec3<T> & getTranslation(void) const;
			/** \brief Get translation on X-axis. */
			const T getTranslationX(void) const;
			/** \brief Get translation on Y-axis. */
			const T getTranslationY(void) const;
			/** \brief Get translation on Z-axis. */
			const T getTranslationZ(void) const;

			/** \brief Set translation. */
			void setTranslation(const eve::math::TVec3<T> & p_value);
			/** \brief Set translation. */
			void setTranslation(T p_x, T p_y, T p_z);
			/** \brief Set translation on X-axis. */
			void setTranslationX(T p_value);
			/** \brief Set translation on Y-axis. */
			void setTranslationY(T p_value);
			/** \brief Set translation on Z-axis. */
			void setTranslationZ(T p_value);


		public:
			/** \brief Get scale. */
			const eve::math::TVec3<T> & getScale(void) const;
			/** \brief Get scale on X-axis. */
			const T getScaleX(void) const;
			/** \brief Get scale on Y-axis. */
			const T getScaleY(void) const;
			/** \brief Get scale on Z-axis. */
			const T getScaleZ(void) const;

			/** \brief Set scale. */
			void setScale(const eve::math::TVec3<T> & p_value);
			/** \brief Set scale. */
			void setScale(T p_x, T p_y, T p_z);
			/** \brief Set scale on X-axis. */
			void setScaleX(T p_value);
			/** \brief Set scale on Y-axis. */
			void setScaleY(T p_value);
			/** \brief Set scale on Z-axis. */
			void setScaleZ(T p_value);


		public:
			/** \brief Get rotation matrix. */
			eve::math::TMatrix44<T> & getMatrixRotation(void) const;
			/** \brief Get translation matrix. */
			eve::math::TMatrix44<T> & getMatrixTranslation(void) const;
			/** \brief Get scale matrix. */
			eve::math::TMatrix44<T> & getMatrixScale(void) const;
			/** \brief Get model view matrix. */
			eve::math::TMatrix44<T> & getMatrixModelView(void) const;

		}; // class TTransform

	} // namespace math

} // namespace eve


//=================================================================================================
template <typename T>
eve::math::TTransform<T> * eve::math::TTransform<T>::create_ptr(const eve::math::TTransform<T> & p_parent)
{
	eve::math::TTransform<T> * ptr = new eve::math::TTransform<T>(p_parent);
	return ptr;
}



//=================================================================================================
template <typename T>
eve::math::TTransform<T>::TTransform(void)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_rotation(eve::math::TVec3<T>::zero())
	, m_translation(eve::math::TVec3<T>::zero())
	, m_scale(eve::math::TVec3<T>::one())

	, m_pivot(eve::math::TVec3<T>::zero())

	, m_matrixRotation(eve::math::TMatrix44<T>::identity())
	, m_matrixScale(eve::math::TMatrix44<T>::identity())
	, m_matrixModelView(eve::math::TMatrix44<T>::identity())
{}

//=================================================================================================
template <typename T>
eve::math::TTransform<T>::TTransform(const eve::math::TTransform<T> & p_parent)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_rotation(p_parent.m_rotation)
	, m_translation(p_parent.m_translation)
	, m_scale(p_parent.m_scale)

	, m_pivot(p_parent.m_pivot)

	, m_matrixRotation(p_parent.m_matrixRotation)
	, m_matrixScale(p_parent.m_matrixScale)
	, m_matrixModelView(p_parent.m_matrixModelView)
{
	this->init();
}



//=================================================================================================
template <typename T>
void eve::math::TTransform<T>::init(void)
{
	m_matrixRotation.set(		eve::math::TMatrix44<T>::createRotation(m_rotation));
	m_matrixScale.set(			eve::math::TMatrix44<T>::createScale(m_scale));
	this->updateMatrixModelView();
}

//=================================================================================================
template <typename T>
void eve::math::TTransform<T>::release(void)
{
	// Nothing to do for now.
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::updateMatrixRotation(void)
{
	m_matrixRotation.set(eve::math::TMatrix44<T>::createRotation(m_rotation));
	this->updateMatrixModelView();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::updateMatrixTranslation(void)
{
	this->updateMatrixModelView();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::updateMatrixScale(void)
{
	m_matrixScale.set(eve::math::TMatrix44<T>::createScale(m_scale));
	this->updateMatrixModelView();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::updateMatrixModelView(void)
{
	m_matrixModelView.set(m_matrixRotation * m_matrixScale);
	m_matrixModelView.setTranslate(m_translation);
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::rotate(const eve::math::TVec3<T> & p_rotation)
{
	m_rotation += p_rotation;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::rotate(T p_x, T p_y, T p_z)
{
	m_rotation.x += p_x;
	m_rotation.y += p_y;
	m_rotation.z += p_z;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::rotateX(T p_rotationX)
{
	m_rotation.x += p_rotationX;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::rotateY(T p_rotationY)
{
	m_rotation.y += p_rotationY;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::rotateZ(T p_rotationZ)
{
	m_rotation.z += p_rotationZ;
	this->updateMatrixRotation();
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::rotatePivot(const eve::math::TVec3<T> & p_rotation)
{
	eve::math::TMatrix44<T> matOrigin(m_matrixRotation);
	matOrigin.setTranslate(m_pivot - m_translation);

	eve::math::TMatrix44<T> matRot = eve::math::TMatrix44<T>::createRotation(p_rotation);
	eve::math::TMatrix44<T> mat = matRot * matOrigin;

	m_translation += mat.getTranslate() - (m_pivot - m_translation);

	this->rotate(p_rotation);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::rotatePivot(T p_x, T p_y, T p_z)
{
	eve::math::TMatrix44<T> matOrigin(m_matrixRotation);
	matOrigin.setTranslate(m_pivot - m_translation);

	eve::math::TMatrix44<T> matRot = eve::math::TMatrix44<T>::createRotation(eve::math::TVec3<T>(p_x, p_y, p_z));
	eve::math::TMatrix44<T> mat = matRot * matOrigin;

	m_translation += mat.getTranslate() - (m_pivot - m_translation);

	this->rotate(p_x, p_y, p_z);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::rotatePivotX(T p_rotationX)
{
	eve::math::TMatrix44<T> matOrigin(m_matrixRotation);
	matOrigin.setTranslate(m_pivot - m_translation);

	eve::math::TMatrix44<T> matRot = eve::math::TMatrix44<T>::createRotation(eve::math::TVec3<T>::xAxis(), p_rotationX);
	eve::math::TMatrix44<T> mat = matRot * matOrigin;

	m_translation += mat.getTranslate() - (m_pivot - m_translation);

	this->rotateX(p_rotationX);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::rotatePivotY(T p_rotationY)
{
	eve::math::TMatrix44<T> matOrigin(m_matrixRotation);
	matOrigin.setTranslate(m_pivot - m_translation);

	eve::math::TMatrix44<T> matRot = eve::math::TMatrix44<T>::createRotation(eve::math::TVec3<T>::yAxis(), p_rotationY);
	eve::math::TMatrix44<T> mat = matRot * matOrigin;

	m_translation += mat.getTranslate() - (m_pivot - m_translation);

	this->rotateY(p_rotationY);
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::rotatePivotZ(T p_rotationZ)
{
	eve::math::TMatrix44<T> matOrigin(m_matrixRotation);
	matOrigin.setTranslate(m_pivot - m_translation);

	eve::math::TMatrix44<T> matRot = eve::math::TMatrix44<T>::createRotation(eve::math::TVec3<T>::zAxis(), p_rotationZ);
	eve::math::TMatrix44<T> mat = matRot * matOrigin;

	m_translation += mat.getTranslate() - (m_pivot - m_translation);

	this->rotateZ(p_rotationZ);
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::translate(const eve::math::TVec3<T> & p_translation)
{
	m_translation += p_translation;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::translate(T p_x, T p_y, T p_z)
{
	m_translation.x += p_x;
	m_translation.y += p_y;
	m_translation.z += p_z;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::translateX(T p_translationX)
{
	m_translation.x += p_translationX;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::translateY(T p_translationY)
{
	m_translation.y += p_translationY;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::translateZ(T p_translationZ)
{
	m_translation.z += p_translationZ;
	this->updateMatrixTranslation();
}



//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::scale(const eve::math::TVec3<T> & p_scale)
{
	m_scale += p_scale;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::scale(T p_x, T p_y, T p_z)
{
	m_scale.x += p_x;
	m_scale.y += p_y;
	m_scale.z += p_z;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::scaleX(T p_scaleX)
{
	m_scale.x += p_scaleX;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::scaleY(T p_scaleY)
{
	m_scale.y += p_scaleY;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::scaleZ(T p_scaleZ)
{
	m_scale.z += p_scaleZ;
	this->updateMatrixScale();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template <typename T> EVE_FORCE_INLINE const eve::math::TVec3<T> &  eve::math::TTransform<T>::getRotation(void) const  { return m_rotation;   }
template <typename T> EVE_FORCE_INLINE const T						eve::math::TTransform<T>::getRotationX(void) const { return m_rotation.x; }
template <typename T> EVE_FORCE_INLINE const T						eve::math::TTransform<T>::getRotationY(void) const { return m_rotation.y; }
template <typename T> EVE_FORCE_INLINE const T						eve::math::TTransform<T>::getRotationZ(void) const { return m_rotation.z; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setRotation(const eve::math::TVec3<T> & p_value)
{
	m_rotation = p_value;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setRotation(eve::math::TQuaternion<T> & p_value)
{
	m_rotation.set(p_value.toVec3());
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setRotation(T p_x, T p_y, T p_z)
{
	m_rotation.x = p_x;
	m_rotation.y = p_y;
	m_rotation.z = p_z;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setRotationX(T p_value)
{
	m_rotation.x = p_value;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setRotationY(T p_value)
{
	m_rotation.y = p_value;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setRotationZ(T p_value)
{
	m_rotation.z = p_value;
	this->updateMatrixRotation();
}



//=================================================================================================
template <typename T> EVE_FORCE_INLINE const eve::math::TVec3<T> & eve::math::TTransform<T>::getPivot(void) const { return m_pivot; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setPivot(const eve::math::TVec3<T> & p_value)
{
	m_pivot = p_value;
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setPivot(T p_x, T p_y, T p_z)
{
	m_pivot.x = p_x;
	m_pivot.y = p_y;
	m_pivot.z = p_z;
}



//=================================================================================================
template <typename T> EVE_FORCE_INLINE const eve::math::TVec3<T> &	eve::math::TTransform<T>::getTranslation(void) const  { return m_translation; }
template <typename T> EVE_FORCE_INLINE const T						eve::math::TTransform<T>::getTranslationX(void) const { return m_translation.x; }
template <typename T> EVE_FORCE_INLINE const T						eve::math::TTransform<T>::getTranslationY(void) const { return m_translation.y; }
template <typename T> EVE_FORCE_INLINE const T						eve::math::TTransform<T>::getTranslationZ(void) const { return m_translation.z; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setTranslation(const eve::math::TVec3<T> & p_value)
{
	m_translation = p_value;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setTranslation(T p_x, T p_y, T p_z)
{
	m_translation.x = p_x;
	m_translation.y = p_y;
	m_translation.z = p_z;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setTranslationX(T p_value)
{
	m_translation.x = p_value;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setTranslationY(T p_value)
{
	m_translation.y = p_value;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setTranslationZ(T p_value)
{
	m_translation.z = p_value;
	this->updateMatrixTranslation();
}



//=================================================================================================
template <typename T> EVE_FORCE_INLINE const eve::math::TVec3<T> &	eve::math::TTransform<T>::getScale(void) const  { return m_scale;   }
template <typename T> EVE_FORCE_INLINE const T						eve::math::TTransform<T>::getScaleX(void) const { return m_scale.x; }
template <typename T> EVE_FORCE_INLINE const T						eve::math::TTransform<T>::getScaleY(void) const { return m_scale.y; }
template <typename T> EVE_FORCE_INLINE const T						eve::math::TTransform<T>::getScaleZ(void) const { return m_scale.z; }

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setScale(const eve::math::TVec3<T> & p_value)
{
	m_scale = p_value;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setScale(T p_x, T p_y, T p_z)
{
	m_scale.x = p_x;
	m_scale.y = p_y;
	m_scale.z = p_z;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setScaleX(T p_value)
{
	m_scale.x = p_value;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setScaleY(T p_value)
{
	m_scale.y = p_value;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
EVE_FORCE_INLINE void eve::math::TTransform<T>::setScaleZ(T p_value)
{
	m_scale.z = p_value;
	this->updateMatrixScale();
}



//=================================================================================================
template <typename T> EVE_FORCE_INLINE eve::math::TMatrix44<T> & eve::math::TTransform<T>::getMatrixRotation(void) const	{ return m_matrixRotation;		}
template <typename T> EVE_FORCE_INLINE eve::math::TMatrix44<T> & eve::math::TTransform<T>::getMatrixTranslation(void) const	{ return m_matrixTranslation;	}
template <typename T> EVE_FORCE_INLINE eve::math::TMatrix44<T> & eve::math::TTransform<T>::getMatrixScale(void) const		{ return m_matrixScale;			}
template <typename T> EVE_FORCE_INLINE eve::math::TMatrix44<T> & eve::math::TTransform<T>::getMatrixModelView(void) const	{ return m_matrixModelView;		}

#endif // __EVE_MATH_TTRANSFORM_H__