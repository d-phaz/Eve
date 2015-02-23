
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
#ifndef __EVE_OPENGL_CORE_VAO_STAGED_H__
#define __EVE_OPENGL_CORE_VAO_STAGED_H__

#ifndef __EVE_OPENGL_CORE_OBJECT_H__
#include "eve/ogl/core/Object.h"
#endif


namespace eve
{
	namespace ogl
	{
		/**
		* \class eve::ogl::FormatVaoStaged
		*
		* \brief OpenGL vertex array object using per data array buffer format class.
		* Used to create OpenGL vertex array object  using per data array buffer based on properties.
		*
		* \note extends eve::ogl::Format
		*/
		class FormatVaoStaged final
			: public eve::ogl::Format
		{
		public:
			GLint						numVertices;				//<! Specifies number of vertices.
			GLint						numIndices;					//<! Specifies number of indices.

			GLsizei						perVertexNumPosition;		//<! Specifies per vertex position values amount (should be 2 in 2D scene, 3 in 3D scene).
			GLsizei						perVertexNumDiffuse;		//<! Specifies per vertex diffuse coordinates values amount (should be 2 is using texture coordinates, 4 if using color).
			GLsizei						perVertexNumNormal;			//<! Specifies per vertex normals values amount (should be 3).

			std::shared_ptr<float>		positions;					//!< Specifies a pointer to position data in memory (used as std::shared_ptr).
			bool						isPositionDynamic;			//!< Specifies position buffer dynamic drawing activation. Dynamic drawing is used when data are updated at each frame (driver hint), default is false.
			std::shared_ptr<float>		diffuses;					//!< Specifies a pointer to position data in memory (used as std::shared_ptr).
			bool						isDiffuseDynamic;			//!< Specifies diffuse buffer dynamic drawing activation. Dynamic drawing is used when data are updated at each frame (driver hint), default is false.
			std::shared_ptr<float>		normals;					//!< Specifies a pointer to position data in memory (used as std::shared_ptr).
			bool						isNormalDynamic;			//!< Specifies normal buffer dynamic drawing activation. Dynamic drawing is used when data are updated at each frame (driver hint), default is false.
			std::shared_ptr<GLuint>		indices;					//!< Specifies a pointer to indices data in memory (used as std::shared_ptr).
			bool						isIndiceDynamic;			//!< Specifies indice buffer dynamic drawing activation. Dynamic drawing is used when data are updated at each frame (driver hint), default is false.

			GLenum						primitiveType;				//!< Specifies OpenGL drawn primitive type (GL_TRIANGLES, GL_LINES, ...), default is GL_TRIANGLES.

		public:
			/** \brief Class constructor. */
			FormatVaoStaged(void);
			/** \brief Class destructor. */
			virtual ~FormatVaoStaged(void);

			/** \brief Copy constructor. */
			FormatVaoStaged(const eve::ogl::FormatVaoStaged & p_other);
			/** \brief Assignment operator. */
			const eve::ogl::FormatVaoStaged & operator = (const eve::ogl::FormatVaoStaged & p_other);

		}; // class FormatVaoStaged


		/** 
		* \class eve::ogl::VaoStaged
		*
		* \brief Create and manage OpenGL vertex array object using per data array buffer.
		*
		* \note extends eve::ogl::Object
		*/
		class VaoStaged
			: public eve::ogl::Object
		{

			friend class eve::ogl::Renderer;
			friend class eve::ogl::Object;


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			enum VaoStages
			{
				Vao_Stage_Position,
				Vao_Stage_Diffuse,
				Vao_Stage_Normal,
			}; // enum VaoStages

		private:
			GLuint						m_id;						//!< Specifies OpenGL unique vertex array object ID.
			GLuint *					m_arrayBufferId;			//<! Specifies OpenGL array buffers (position, diffuse, normal) IDs.
			GLuint						m_elementBufferId;			//<! Specifies OpenGL element buffer (indices) ID.

			GLenum						m_primitiveType;			//!< Specifies OpenGL drawn primitive type (GL_TRIANGLES, GL_LINES, ...), default is GL_TRIANGLES.
			
		private:
			GLint						m_numVertices;				//<! Specifies number of vertices.
			GLint						m_numIndices;				//<! Specifies number of indices.

			GLsizei						m_perVertexNumPosition;		//<! Specifies per vertex position values amount (should be 2 in 2D scene, 3 in 3D scene).
			GLsizei						m_perVertexNumDiffuse;		//<! Specifies per vertex diffuse coordinates values amount (should be 2 if using texture coordinates, 4 if using color).
			GLsizei						m_perVertexNumNormal;		//<! Specifies per vertex normals values amount (should be 3).

			float *						m_pPositionsData;			//!< Specifies position device buffer data address.
			std::shared_ptr<float>		m_pPositions;				//!< Specifies a pointer to position data in memory (used as std::shared_ptr).
			bool						m_bPositionsUpdate;			//!< Specifies whether or not positions must be updated.
			bool						m_bPositionDynamic;			//!< Specifies position buffer dynamic drawing activation. Dynamic drawing is used when data are updated at each frame (driver hint), default is false.

			float *						m_pDiffusesData;			//!< Specifies diffuse device buffer data address.
			std::shared_ptr<float>		m_pDiffuses;				//!< Specifies a pointer to diffuse data in memory (used as std::shared_ptr).
			bool						m_bDiffusesUpdate;			//!< Specifies whether or not diffuses must be updated.
			bool						m_bDiffuseDynamic;			//!< Specifies diffuse buffer dynamic drawing activation. Dynamic drawing is used when data are updated at each frame (driver hint), default is false.

			float *						m_pNormalsData;				//!< Specifies normal device buffer data address.
			std::shared_ptr<float>		m_pNormals;					//!< Specifies a pointer to normal data in memory (used as std::shared_ptr).
			bool						m_bNormalsUpdate;			//!< Specifies whether or not normals must be updated.
			bool						m_bNormalDynamic;			//!< Specifies normal buffer dynamic drawing activation. Dynamic drawing is used when data are updated at each frame (driver hint), default is false.

			GLuint *					m_pIndicesData;				//!< Specifies indices device buffer data address.
			std::shared_ptr<GLuint>		m_pIndices;					//!< Specifies a pointer to indices data in memory (used as std::shared_ptr).
			bool						m_bIndicesUpdate;			//!< Specifies whether or not indices must be updated.
			bool						m_bIndiceDynamic;			//!< Specifies indice buffer dynamic drawing activation. Dynamic drawing is used when data are updated at each frame (driver hint), default is false.

		private:
			GLsizei						m_positionStride;			//<! Specifies position array stride  (m_perVertexNumPosition * sizeof(float)).
			GLsizeiptr					m_positionSize;				//<! Specifies size of position array in memory.
			GLsizei						m_diffuseStride;			//<! Specifies diffuse array stride  (m_perVertexNumDiffuse * sizeof(float)).
			GLsizeiptr					m_diffuseSize;				//<! Specifies size of vertices array in memory.
			GLsizei						m_normalStride;				//<! Specifies vertices array stride  (m_perVertexNumNormal * sizeof(float)).
			GLsizeiptr					m_normalSize;				//<! Specifies size of vertices array in memory.

			GLsizeiptr					m_indicesSize;				//<! Specifies indices array size in memory.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(VaoStaged);
			EVE_PUBLIC_DESTRUCTOR(VaoStaged);
			
		public:
			/** \brief Class constructor. */
			explicit VaoStaged(void);


		protected:
			/**
			* \brief Get attributes from eve::ogl::Format. (pure virtual)
			* Object attributes MUST be retrieved before init() call.
			*/
			virtual void setAttributes(eve::ogl::Format * p_format);


		public:
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


		public:
			/** \brief Add target staged VAO, data structures have to be compatible. */
			void add(eve::ogl::VaoStaged * p_pVao);
			/** \brief Merge target staged VAO and release it, data structures have to be compatible. */
			void merge(eve::ogl::VaoStaged * p_pVao);


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
			/** \brief Get the pointer to position data in memory (used as std::shared_ptr). */
			std::shared_ptr<float> getPositions(void) const;
			/** \brief Set position array buffer data, adds the object as a shared owner, increasing the use_count. */
			void setPositions(const std::shared_ptr<float> & p_data);
			/** \brief Set position array buffer data, transfer ownership without altering the use_count. */
			void setPositions(const std::shared_ptr<float> && p_data);


		public:
			/** \brief Get the pointer to diffuse data in memory (used as std::shared_ptr). */
			std::shared_ptr<float> getDiffuses(void) const;
			/** \brief Set diffuse array buffer data, adds the object as a shared owner, increasing the use_count. */
			void setDiffuses(const std::shared_ptr<float> & p_data);
			/** \brief Set diffuse array buffer data, transfer ownership without altering the use_count. */
			void setDiffuses(const std::shared_ptr<float> && p_data);


		public:
			/** \brief Get the pointer to normal data in memory (used as std::shared_ptr). */
			std::shared_ptr<float> getNormals(void) const;
			/** \brief Set normal array buffer data, adds the object as a shared owner, increasing the use_count. */
			void setNormals(const std::shared_ptr<float> & p_data);
			/** \brief Set normal array buffer data, transfer ownership without altering the use_count. */
			void setNormals(const std::shared_ptr<float> && p_data);


		public:
			/** \brief Set position, diffuse, normal array buffer data, adds the object as a shared owner, increasing the use_count. */
			void setVertices(const std::shared_ptr<float> & p_positions
						   , const std::shared_ptr<float> & p_diffuses
						   , const std::shared_ptr<float> & p_normals);
			/** \brief Set position, diffuse, normal array buffer data, transfer ownership without altering the use_count. */
			void setVertices(const std::shared_ptr<float> && p_positions
						   , const std::shared_ptr<float> && p_diffuses
						   , const std::shared_ptr<float> && p_normals);


		public:
			/** \brief Get the pointer to indices data in memory (used as std::shared_ptr). */
			std::shared_ptr<GLuint> getIndices(void) const;
			/** \brief Set element buffer data (indices), adds the object as a shared owner, increasing the use_count. */
			void setIndices(const std::shared_ptr<GLuint> & p_data);
			/** \brief Set element buffer data (indices), transfer ownership without altering the use_count. */
			void setIndices(const std::shared_ptr<GLuint> && p_data);
						
		}; // class VaoStaged

	} // namespace ogl

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
EVE_FORCE_INLINE const GLuint eve::ogl::VaoStaged::getId(void) const	{ return m_id; }


//=================================================================================================
EVE_FORCE_INLINE const GLint eve::ogl::VaoStaged::getNumVertices(void) const	{ return m_numVertices;	}
EVE_FORCE_INLINE const GLint eve::ogl::VaoStaged::getNumIndices(void) const		{ return m_numIndices;	}


//=================================================================================================
EVE_FORCE_INLINE const GLsizei eve::ogl::VaoStaged::getPerVertexNumPosition(void) const	{ return m_perVertexNumPosition;	}
EVE_FORCE_INLINE const GLsizei eve::ogl::VaoStaged::getPerVertexNumDiffuse(void) const	{ return m_perVertexNumDiffuse;		}
EVE_FORCE_INLINE const GLsizei eve::ogl::VaoStaged::getPerVertexNumNormal(void) const	{ return m_perVertexNumNormal;		}


//=================================================================================================
EVE_FORCE_INLINE std::shared_ptr<float>	eve::ogl::VaoStaged::getPositions(void) const	{ return m_pPositions;	}
EVE_FORCE_INLINE std::shared_ptr<float>	eve::ogl::VaoStaged::getDiffuses(void) const	{ return m_pDiffuses;	}
EVE_FORCE_INLINE std::shared_ptr<float>	eve::ogl::VaoStaged::getNormals(void) const		{ return m_pNormals;	}


//=================================================================================================
EVE_FORCE_INLINE std::shared_ptr<GLuint> eve::ogl::VaoStaged::getIndices(void) const	{ return m_pIndices; }

#endif // __EVE_OPENGL_CORE_VAO_H__
