
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
#ifndef __EVE_MATH_TMESH_H__
#define __EVE_MATH_TMESH_H__

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
		* \class eve::math::TMesh
		*
		* \brief Template 3D object math and manipulation, using RTS matrix order.
		*
		* \note extends eve::mem::Pointer
		*/
		template <typename T>
		class TMesh
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			mutable eve::math::TVec3<T>			m_rotation;						//!< Specifies Rotation (radians).
			mutable eve::math::TVec3<T>			m_translation;					//!< Specifies translation.
			mutable eve::math::TVec3<T>			m_scale;						//!< Specifies scale.

			mutable eve::math::TMatrix44<T>		m_matrixRotation;				//!< Specifies rotation matrix.
			mutable eve::math::TMatrix44<T>		m_matrixTranslation;			//!< Specifies translation matrix.
			mutable eve::math::TMatrix44<T>		m_matrixScale;					//!< Specifies scale matrix.
			mutable eve::math::TMatrix44<T>		m_matrixModelView;				//!< Specifies model view matrix.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_ASSIGNATION(TMesh);
			EVE_PROTECT_DESTRUCTOR(TMesh);

		public:
			/** \brief Create new pointer, copy of \p_parent. */
			static eve::math::TMesh<T> * create_ptr(const TMesh<T> & p_parent);

			
		protected:
			/** \brief Class constructor. */
			explicit TMesh(void);
			/** \brief Copy constructor. */
			explicit TMesh(const TMesh<T> & p_parent);


		protected:
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
			void updateMatrixModelView(void);


		public:
			/** \brief Rotate object. */
			virtual void rotate(const eve::math::TVec3<T> & p_rotation);
			/** \brief Rotate object on X-axis. */
			virtual void rotateX(float p_rotationX);
			/** \brief Rotate object on Y-axis. */
			virtual void rotateY(float p_rotationY);
			/** \brief Rotate object on Z-axis. */
			virtual void rotateZ(float p_rotationZ);


		public:
			/** \brief Translate object. */
			virtual void translate(const eve::math::TVec3<T> & p_translation);
			/** \brief Translate object on X-axis. */
			virtual void translateX(float p_translationX);
			/** \brief Translate object on Y-axis. */
			virtual void translateY(float p_translationY);
			/** \brief Translate object on Z-axis. */
			virtual void translateZ(float p_translationZ);


		public:
			/** \brief Scale object. */
			virtual void scale(const eve::math::TVec3<T> & p_scale);
			/** \brief Scale object on X-axis. */
			virtual void scaleX(float p_scaleX);
			/** \brief Scale object on Y-axis. */
			virtual void scaleY(float p_scaleY);
			/** \brief Scale object on Z-axis. */
			virtual void scaleZ(float p_scaleZ);


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get rotation. */
			const eve::math::TVec3<T> & getRotation(void) const;
			/** \brief Get rotation on X-axis. */
			const float getRotationX(void) const;
			/** \brief Get rotation on Y-axis. */
			const float getRotationY(void) const;
			/** \brief Get rotation on Z-axis. */
			const float getRotationZ(void) const;

			/** \brief Set rotation. */
			virtual void setRotation(const eve::math::TVec3<T> & p_value);
			/** \brief Set rotation on X-axis. */
			virtual void setRotationX(float p_value);
			/** \brief Set rotation on Y-axis. */
			virtual void setRotationY(float p_value);
			/** \brief Set rotation on Z-axis. */
			virtual void setRotationZ(float p_value);


		public:
			/** \brief Get translation. */
			const eve::math::TVec3<T> & getTranslation(void) const;
			/** \brief Get translation on X-axis. */
			const float getTranslationX(void) const;
			/** \brief Get translation on Y-axis. */
			const float getTranslationY(void) const;
			/** \brief Get translation on Z-axis. */
			const float getTranslationZ(void) const;

			/** \brief Set translation. */
			virtual void setTranslation(const eve::math::TVec3<T> & p_value);
			/** \brief Set translation on X-axis. */
			virtual void setTranslationX(float p_value);
			/** \brief Set translation on Y-axis. */
			virtual void setTranslationY(float p_value);
			/** \brief Set translation on Z-axis. */
			virtual void setTranslationZ(float p_value);


		public:
			/** \brief Get scale. */
			const eve::math::TVec3<T> & getScale(void) const;
			/** \brief Get scale on X-axis. */
			const float getScaleX(void) const;
			/** \brief Get scale on Y-axis. */
			const float getScaleY(void) const;
			/** \brief Get scale on Z-axis. */
			const float getScaleZ(void) const;

			/** \brief Set scale. */
			virtual void setScale(const eve::math::TVec3<T> & p_value);
			/** \brief Set scale on X-axis. */
			virtual void setScaleX(float p_value);
			/** \brief Set scale on Y-axis. */
			virtual void setScaleY(float p_value);
			/** \brief Set scale on Z-axis. */
			virtual void setScaleZ(float p_value);


		public:
			/** \brief Get rotation matrix. */
			const eve::math::TMatrix44<T> & getMatrixRotation(void) const;
			/** \brief Get translation matrix. */
			const eve::math::TMatrix44<T> & getMatrixTranslation(void) const;
			/** \brief Get scale matrix. */
			const eve::math::TMatrix44<T> & getMatrixScale(void) const;
			/** \brief Get model view matrix. */
			const eve::math::TMatrix44<T> & getMatrixModelView(void) const;

		}; // class TMesh

	} // namespace math

} // namespace eve


//=================================================================================================
template <typename T>
eve::math::TMesh<T> * eve::math::TMesh<T>::create_ptr(const eve::math::TMesh<T> & p_parent)
{
	eve::math::TMesh<T> * ptr = new eve::math::TMesh<T>(p_parent);
	return ptr;
}



//=================================================================================================
template <typename T>
eve::math::TMesh<T>::TMesh(void)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_rotation(eve::math::TVec3<T>::zero())
	, m_translation(eve::math::TVec3<T>::zero())
	, m_scale(eve::math::TVec3<T>::one())

	, m_matrixRotation(eve::math::TMatrix44<T>::identity())
	, m_matrixTranslation(eve::math::TMatrix44<T>::identity())
	, m_matrixScale(eve::math::TMatrix44<T>::identity())
	, m_matrixModelView(eve::math::TMatrix44<T>::identity())
{}

//=================================================================================================
template <typename T>
eve::math::TMesh<T>::TMesh(const eve::math::TMesh<T> & p_parent)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_rotation(p_parent.m_rotation)
	, m_translation(p_parent.m_translation)
	, m_scale(p_parent.m_scale)

	, m_matrixRotation(p_parent.m_matrixRotation)
	, m_matrixTranslation(p_parent.m_matrixTranslation)
	, m_matrixScale(p_parent.m_matrixScale)
	, m_matrixModelView(p_parent.m_matrixModelView)
{}



//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::init(void)
{
	// Nothing to do for now.
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::release(void)
{
	// Nothing to do for now.
}



//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::updateMatrixRotation(void)
{
	m_matrixRotation = eve::math::TMatrix44<T>::createRotation(m_rotation);
	this->updateMatrixModelView();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::updateMatrixTranslation(void)
{
	m_matrixTranslation = eve::math::TMatrix44<T>::createTranslation(m_translation);
	this->updateMatrixModelView();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::updateMatrixScale(void)
{
	m_matrixScale = eve::math::TMatrix44<T>::createScale(m_scale);
	this->updateMatrixModelView();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::updateMatrixModelView(void)
{
	m_matrixModelView = m_matrixRotation * m_matrixTranslation * m_matrixScale;
}



//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::rotate(const eve::math::TVec3<T> & p_rotation)
{
	m_rotation += p_rotation;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::rotateX(float p_rotationX)
{
	m_rotation.x += p_rotationX;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::rotateY(float p_rotationY)
{
	m_rotation.y += p_rotationY;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::rotateZ(float p_rotationZ)
{
	m_rotation.z += p_rotationZ;
	this->updateMatrixRotation();
}



//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::translate(const eve::math::TVec3<T> & p_translation)
{
	m_translation += p_translation;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::translateX(float p_translationX)
{
	m_translation.x += p_translationX;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::translateY(float p_translationY)
{
	m_translation.y += p_translationY;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::translateZ(float p_translationZ)
{
	m_translation.z += p_translationZ;
	this->updateMatrixTranslation();
}



//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::scale(const eve::math::TVec3<T> & p_scale)
{
	m_scale += p_scale;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::scaleX(float p_scaleX)
{
	m_scale.x += p_scaleX;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::scaleY(float p_scaleY)
{
	m_scale.y += p_scaleY;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::scaleZ(float p_scaleZ)
{
	m_scale.z += p_scaleZ;
	this->updateMatrixScale();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
template <typename T> EVE_FORCE_INLINE const eve::math::TVec3<T> &  eve::math::TMesh<T>::getRotation(void) const  { return m_rotation;   }
template <typename T> EVE_FORCE_INLINE const float					eve::math::TMesh<T>::getRotationX(void) const { return m_rotation.x; }
template <typename T> EVE_FORCE_INLINE const float					eve::math::TMesh<T>::getRotationY(void) const { return m_rotation.y; }
template <typename T> EVE_FORCE_INLINE const float					eve::math::TMesh<T>::getRotationZ(void) const { return m_rotation.z; }

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setRotation(const eve::math::TVec3<T> & p_value)
{
	m_rotation = p_value;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setRotationX(float p_value)
{
	m_rotation.x = p_value;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setRotationY(float p_value)
{
	m_rotation.y = p_value;
	this->updateMatrixRotation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setRotationZ(float p_value)
{
	m_rotation.z = p_value;
	this->updateMatrixRotation();
}



//=================================================================================================
template <typename T> EVE_FORCE_INLINE const eve::math::TVec3<T> &	eve::math::TMesh<T>::getTranslation(void) const  { return m_translation; }
template <typename T> EVE_FORCE_INLINE const float					eve::math::TMesh<T>::getTranslationX(void) const { return m_translation.x; }
template <typename T> EVE_FORCE_INLINE const float					eve::math::TMesh<T>::getTranslationY(void) const { return m_translation.y; }
template <typename T> EVE_FORCE_INLINE const float					eve::math::TMesh<T>::getTranslationZ(void) const { return m_translation.z; }

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setTranslation(const eve::math::TVec3<T> & p_value)
{
	m_translation = p_value;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setTranslationX(float p_value)
{
	m_translation.x = p_value;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setTranslationY(float p_value)
{
	m_translation.y = p_value;
	this->updateMatrixTranslation();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setTranslationZ(float p_value)
{
	m_translation.z = p_value;
	this->updateMatrixTranslation();
}



//=================================================================================================
template <typename T> EVE_FORCE_INLINE const eve::math::TVec3<T> &	eve::math::TMesh<T>::getScale(void) const  { return m_scale;   }
template <typename T> EVE_FORCE_INLINE const float					eve::math::TMesh<T>::getScaleX(void) const { return m_scale.x; }
template <typename T> EVE_FORCE_INLINE const float					eve::math::TMesh<T>::getScaleY(void) const { return m_scale.y; }
template <typename T> EVE_FORCE_INLINE const float					eve::math::TMesh<T>::getScaleZ(void) const { return m_scale.z; }

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setScale(const eve::math::TVec3<T> & p_value)
{
	m_scale = p_value;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setScaleX(float p_value)
{
	m_scale.x = p_value;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setScaleY(float p_value)
{
	m_scale.y = p_value;
	this->updateMatrixScale();
}

//=================================================================================================
template <typename T>
void eve::math::TMesh<T>::setScaleZ(float p_value)
{
	m_scale.z = p_value;
	this->updateMatrixScale();
}



//=================================================================================================
template <typename T> EVE_FORCE_INLINE const eve::math::TMatrix44<T> & eve::math::TMesh<T>::getMatrixRotation(void) const		{ return m_matrixRotation;		}
template <typename T> EVE_FORCE_INLINE const eve::math::TMatrix44<T> & eve::math::TMesh<T>::getMatrixTranslation(void) const	{ return m_matrixTranslation;	}
template <typename T> EVE_FORCE_INLINE const eve::math::TMatrix44<T> & eve::math::TMesh<T>::getMatrixScale(void) const			{ return m_matrixScale;			}
template <typename T> EVE_FORCE_INLINE const eve::math::TMatrix44<T> & eve::math::TMesh<T>::getMatrixModelView(void) const		{ return m_matrixModelView;		}

#endif // __EVE_MATH_TMESH_H__
