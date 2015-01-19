
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
#ifndef __EVE_SCENE_MATERIAL_H__
#define __EVE_SCENE_MATERIAL_H__


#ifndef __EVE_SCENE_OBJECT_H__
#include "eve/scene/Object.h"
#endif

#ifndef __EVE_SCENE_EVENT_LISTENER_H__
#include "eve/scene/EventListener.h"
#endif

#ifndef __EVE_MATH_INCLUDES_H__
#include "eve/math/Includes.h"
#endif


namespace eve { namespace ogl { class Texture; } }


namespace eve
{
	namespace scene
	{
		/** 
		* \class eve::scene::Material
		* \brief Mesh object material using multiple texture types 
		* (diffuse, normal, emissive, opacity) and light computation values.
		* \note extends eve::scene::Object, eve::scene::EventListenerSceneMaterial
		*/
		class Material
			: public eve::scene::Object
			, public eve::scene::EventListenerSceneMaterial
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			float					m_diffuse;				//!< Specifies diffuse factor.
			float					m_specular;				//!< Specifies specular factor.
			float					m_shininess;			//!< Specifies shininess factor.
			float					m_fresnelExponent;		//!< Specifies fresnel exponent.

			eve::ogl::Texture *		m_pTexDiffuse;			//!< Specifies diffuse texture.
			eve::ogl::Texture *		m_pTexNormal;			//!< Specifies normal texture.
			eve::ogl::Texture *		m_pTexEmissive;			//!< Specifies emissive texture.
			eve::ogl::Texture *		m_pTexOpacity;			//!< Specifies opacity texture.

			const aiMaterial *		m_pAiMaterial;			//!< Specifies Assimp material (shared pointer).


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Material);
			EVE_PROTECT_DESTRUCTOR(Material);

		public:
			/** \brief Create, init and return new pointer based on ASSIMP aiMaterial \a p_pMaterial. */
			static eve::scene::Material * create_ptr(eve::scene::Scene *	p_pParentScene
												   , eve::scene::Object *	p_pParent
												   , const aiMaterial *		p_pMaterial
												   , const std::string &	p_fullPath);


		protected:
			/** \brief Class constructor. */
			explicit Material(eve::scene::Scene * p_pParentScene, eve::scene::Object * p_pParent);


		protected:
			/** \brief Allocate and init class members based on ASSIMP aiMaterial \a p_pMaterial. */
			void initFromAssimpMaterial(const aiMaterial * p_pMaterial, const std::string & p_fullPath);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneMaterial(eve::scene::EventArgsSceneMaterial & p_args);


		public:
			/** \brief Bind (activate) textures.
			* 1 Diffuse
			* 2 Normal
			* 3 Emissive
			* 4 Opacity
			*/
			void bind(void);
			/** \brief Unbind (deactivate) textures. */
			void unbind(void);


			///////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Set diffuse texture from file path. */
			bool setTexDiffuse(const std::string & p_path);
			/** \brief Set normal texture from file path. */
			bool setTexNormal(const std::string & p_path);
			/** \brief Set emissive texture from file path. */
			bool setTexEmissive(const std::string & p_path);
			/** \brief Set opacity texture from file path. */
			bool setTexOpacity(const std::string & p_path);


		public:
			/** \brief Set diffuse coefficient. */
			void setDiffuse(float p_coeff);
			/** \brief Set specular coefficient. */
			void setSpecular(float p_coeff);
			/** \brief Set shininess coefficient. */
			void setShininess(float p_coeff);
			/** \brief Set Fresnel exponent coefficient. */
			void setFresnelExponent(float p_coeff);

		public:
			/** \brief Get diffuse coefficient. */
			const float getDiffuse(void) const;
			/** \brief Get specular coefficient. */
			const float getShininess(void) const;
			/** \brief Get shininess coefficient. */
			const float getSpecular(void) const;
			/** \brief Get Fresnel exponent coefficient. */
			const float getFresnelExponent(void) const;

		}; // class Material

	} // namespace scene

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
EVE_FORCE_INLINE void eve::scene::Material::setDiffuse(float p_coeff)				{ m_diffuse			= p_coeff; }
EVE_FORCE_INLINE void eve::scene::Material::setSpecular(float p_coeff)				{ m_specular		= p_coeff; }
EVE_FORCE_INLINE void eve::scene::Material::setShininess(float p_coeff)				{ m_shininess		= p_coeff; }
EVE_FORCE_INLINE void eve::scene::Material::setFresnelExponent(float p_coeff)		{ m_fresnelExponent = p_coeff; }

//=================================================================================================
EVE_FORCE_INLINE const float eve::scene::Material::getDiffuse(void) const			{ return m_diffuse; }
EVE_FORCE_INLINE const float eve::scene::Material::getSpecular(void) const			{ return m_specular; }
EVE_FORCE_INLINE const float eve::scene::Material::getShininess(void) const			{ return m_shininess; }
EVE_FORCE_INLINE const float eve::scene::Material::getFresnelExponent(void) const	{ return m_fresnelExponent; }

#endif // __EVE_SCENE_MATERIAL_H__
