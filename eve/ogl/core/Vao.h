
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
#ifndef __EVE_OPENGL_CORE_VAO_H__
#define __EVE_OPENGL_CORE_VAO_H__

#ifndef __EVE_OPENGL_CORE_OBJECT_H__
#include "eve/ogl/core/Object.h"
#endif


namespace eve
{
	namespace ogl
	{
		/**
		* \class eve::ogl::FormatVao
		*
		* \brief OpenGL vertex array object format class.
		* Used to create OpenGL vertex array object based on properties.
		*
		* \note extends eve::ogl::Format
		*/
		class FormatVao final
			: public eve::ogl::Format
		{
		public:
			GLint						numVertices;				//<! Specifies number of vertices.
			GLint						numIndices;					//<! Specifies number of indices.

			GLsizei						perVertexNumPosition;		//<! Specifies per vertex position values amount (should be 2 in 2D scene, 3 in 3D scene).
			GLsizei						perVertexNumDiffuse;		//<! Specifies per vertex diffuse coordinates values amount (should be 2 is using texture coordinates, 4 if using color).
			GLsizei						perVertexNumNormal;			//<! Specifies per vertex normals values amount (should be 3).

			std::shared_ptr<float>		vertices;					//!< Specifies a pointer to vertices data in memory (used as std::shared_ptr).
			std::shared_ptr<GLuint>		indices;					//!< Specifies a pointer to indices data in memory (used as std::shared_ptr).

		public:
			/** \brief Class constructor. */
			FormatVao(void);
			/** \brief Class destructor. */
			virtual ~FormatVao(void);

			/** \brief Copy constructor. */
			FormatVao(const eve::ogl::FormatVao & p_other);
			/** \brief Assignment operator. */
			const eve::ogl::FormatVao & operator = (const eve::ogl::FormatVao & p_other);

		}; // class FormatVao


		/** 
		* \class eve::ogl::Vao
		*
		* \brief Create and manage OpenGL vertex array object.
		*
		* \note extends eve::ogl::Object
		*/
		class Vao final
			: public eve::ogl::Object
		{

			friend class eve::mem::Pointer;
			friend class eve::ogl::Renderer;
			friend class eve::ogl::Object;


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			GLuint						m_id;						//!< Specifies OpenGL unique uniform buffer ID.
			GLuint						m_arrayBufferId;			//<! Specifies OpenGL array buffer (vertices) ID.
			GLuint						m_elementBufferId;			//<! Specifies OpenGL element buffer (indices) ID.

		private:
			GLint						m_numVertices;				//<! Specifies number of vertices.
			GLint						m_numIndices;				//<! Specifies number of indices.

			GLsizei						m_perVertexNumPosition;		//<! Specifies per vertex position values amount (should be 2 in 2D scene, 3 in 3D scene).
			GLsizei						m_perVertexNumDiffuse;		//<! Specifies per vertex diffuse coordinates values amount (should be 2 is using texture coordinates, 4 if using color).
			GLsizei						m_perVertexNumNormal;		//<! Specifies per vertex normals values amount (should be 3).

			std::shared_ptr<float>		m_pVertices;				//!< Specifies a pointer to vertices data in memory (used as std::shared_ptr).
			std::shared_ptr<GLuint>		m_pIndices;					//!< Specifies a pointer to indices data in memory (used as std::shared_ptr).
			float *						m_pOglData;					//!< Specifies device buffer data address.

		private:
			GLuint						m_offsetPosition;			//<! Specifies vertices positions data offset in array.
			GLuint						m_offsetDiffuse;			//<! Specifies vertices diffuse coordinates data offset in array.
			GLuint						m_offsetNormals;			//<! Specifies vertices normals data offset in array.

			size_t						m_verticesStrideUnit;		//<! Specifies vertices array unit stride (m_perVertexNumPosition + m_perVertexNumDiffuse + m_perVertexNumNormal).
			GLsizei						m_verticesStride;			//<! Specifies vertices array stride  ((m_perVertexNumPosition + m_perVertexNumDiffuse + m_perVertexNumNormal) * sizeof(float)).
			GLsizeiptr					m_verticesSize;				//<! Specifies size of vertices array in memory.

			GLsizeiptr					m_indicesSize;				//<! Specifies indices array size in memory.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Vao);
			EVE_PROTECT_DESTRUCTOR(Vao);
			
		private:
			/** \brief Class constructor. */
			explicit Vao(void);


		protected:
			/**
			* \brief Get attributes from eve::ogl::Format. (pure virtual)
			* Object attributes MUST be retrieved before init() call.
			*/
			virtual void setAttributes(eve::ogl::Format * p_format);


		protected:
			/** \brief Alloc and init non OpenGL class members. (pure virtual) */
			virtual void init(void);
			/** \brief Release and delete non OpenGL class members. (pure virtual) */
			virtual void release(void);


		protected:
			/** \brief Init OpenGL components. */
			virtual void oglInit(void);
			/** \brief Update OpenGL components. (only FBO size can be updated here) */
			virtual void oglUpdate(void);
			/** \brief Deallocate and release OpenGL components. */
			virtual void oglRelease(void);


		public:
			/** \brief Draw VAO content. */
			void draw(void);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////	
			
		public:
			/** \brief Get OpenGL texture unique id. (pure virtual) */
			virtual const GLuint getId(void) const override;


		public:
			/** \brief Get number of vertices. */
			const GLint getNumVertices(void) const;
			/** \brief Get number of indices. */
			const GLint getNumIndices(void) const;


		public:
			/** \brief Get per vertex position values amount (should be 2 in 2D scene, 3 in 3D scene). */
			const GLsizei getPerVertexNumPosition(void) const;
			/** \brief Get per vertex diffuse coordinates values amount (should be 2 is using texture coordinates, 4 if using color). */
			const GLsizei getPerVertexNumDiffuse(void) const;
			/** \brief Get per vertex normals values amount (should be 3). */
			const GLsizei getPerVertexNumNormal(void) const;


		public:
			/** \brief Get the pointer to vertices data in memory (used as std::shared_ptr). */
			std::shared_ptr<float>	getVertices(void) const;
			/** \brief Set array buffer data (vertices). */
			void setVertices(const std::shared_ptr<float> & p_data);


		public:
			/** \brief Get the pointer to indices data in memory (used as std::shared_ptr). */
			std::shared_ptr<GLuint> getIndices(void) const;
			/** \brief Set element buffer data (indices). */
			void setIndices(const std::shared_ptr<GLuint> & p_data);

			
		}; // class Fbo

	} // namespace ogl

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
EVE_FORCE_INLINE const GLuint eve::ogl::Vao::getId(void) const	{ return m_id; }



//=================================================================================================
EVE_FORCE_INLINE const GLint eve::ogl::Vao::getNumVertices(void) const	{ return m_numVertices; }
EVE_FORCE_INLINE const GLint eve::ogl::Vao::getNumIndices(void) const	{ return m_numIndices;  }


//=================================================================================================
EVE_FORCE_INLINE const GLsizei eve::ogl::Vao::getPerVertexNumPosition(void) const	{ return m_perVertexNumPosition;	}
EVE_FORCE_INLINE const GLsizei eve::ogl::Vao::getPerVertexNumDiffuse(void) const	{ return m_perVertexNumDiffuse;		}
EVE_FORCE_INLINE const GLsizei eve::ogl::Vao::getPerVertexNumNormal(void) const		{ return m_perVertexNumNormal;		}


//=================================================================================================
EVE_FORCE_INLINE std::shared_ptr<float>	eve::ogl::Vao::getVertices(void) const	{ return m_pVertices; }


//=================================================================================================
EVE_FORCE_INLINE std::shared_ptr<GLuint> eve::ogl::Vao::getIndices(void) const	{ return m_pIndices;  }

#endif // __EVE_OPENGL_CORE_VAO_H__
