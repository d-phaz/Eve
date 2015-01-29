
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
#ifndef __EVE_OPENGL_CORE_UNIFORM_H__
#define __EVE_OPENGL_CORE_UNIFORM_H__

#ifndef __EVE_OPENGL_CORE_OBJECT_H__
#include "eve/ogl/core/Object.h"
#endif

#ifndef __EVE_MATH_TYPES_H__
#include "eve/math/Types.h"
#endif


namespace eve
{
	namespace ogl
	{
		/** \brief Get in byte, GLSL compliant, aligned size of target size. */
		size_t align_size_of(size_t p_originalSize);


		/**
		* \class eve::ogl::FormatUniform
		*
		* \brief OpenGL uniform buffer format class.
		* Used to create OpenGL uniform buffer based on properties.
		*
		* \note extends eve::ogl::Format
		*/
		class FormatUniform final
			: public eve::ogl::Format
		{
		public:
			GLint					blockSize;			//!< Specifies uniform block size.
			bool					dynamic;			//!< Specifies whether the buffer use dynamic draw (per draw call update).

		public:
			/** \brief Class constructor. */
			FormatUniform(void);
			/** \brief Class destructor. */
			virtual ~FormatUniform(void);

			/** \brief Copy constructor. */
			FormatUniform(const eve::ogl::FormatUniform & p_other);
			/** \brief Assignment operator. */
			const eve::ogl::FormatUniform & operator = (const eve::ogl::FormatUniform & p_other);

		}; // class FormatUniform


		/** 
		* \class eve::ogl::Uniform
		*
		* \brief Create and manage OpenGL uniform buffer.
		*
		* \note extends eve::ogl::Object
		*/
		class Uniform final
			: public eve::ogl::Object
		{

			friend class eve::ogl::Renderer;
			friend class eve::ogl::Object;


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			GLuint						m_id;					//!< Specifies OpenGL unique uniform buffer ID.
			GLint						m_blockSize;			//!< Specifies uniform block size.
			GLenum						m_usage;				//!< Specifies whether the buffer use GL_STATIC_DRAW or GL_DYNAMIC_DRAW.
			bool						m_bDynamic;				//!< Specifies whether the buffer use dynamic draw (per draw call update).

			float *						m_pData;				//!< Specifies host data to send to buffer.
			float *						m_pOglData;				//!< Specifies device buffer data address.


		private:
			// OpenGL documentation:

			// Each shader stage has a limit on the number of separate uniform buffer binding locations.
			// These are queried using glGetIntegerv with GL_MAX_VERTEX_UNIFORM_BLOCKS, GL_MAX_GEOMETRY_UNIFORM_BLOCKS, GL_MAX_FRAGMENT_UNIFORM_BLOCKS. 

			// There is also a limitation on the available storage per uniform buffer. 
			// This is queried through GL_MAX_UNIFORM_BLOCK_SIZE.
			// This is in basic machine units (bytes).

			// If you bind a uniform buffer with glBindBufferRange, the offset field of that parameter must be a multiple of GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT.
			// This is a global value, not a per-program or per-block one.
			// Thus, if you want to put the data for multiple uniform blocks in a single buffer object, 
			// you must make sure that the data for each within that block matches this alignment.

			static int32_t				m_max_vertex_uniform_blocks;			//!< Specifies OpenGL maximum vertex uniform blocks.
			static int32_t				m_max_control_uniform_blocks;			//!< Specifies OpenGL maximum control uniform blocks.
			static int32_t				m_max_evaluation_uniform_blocks;		//!< Specifies OpenGL maximum control uniform blocks.
			static int32_t				m_max_geometry_uniform_blocks;			//!< Specifies OpenGL maximum geometry uniform blocks.
			static int32_t				m_max_fragment_uniform_blocks;			//!< Specifies OpenGL maximum fragment uniform blocks.

			static int32_t				m_max_uniform_buffer_binding;			//!< Specifies OpenGl maximum buffer binding amount.
			static int32_t				m_max_uniform_block_size;				//!< Specifies OpenGL maximum uniform blocks size.

			static int32_t				m_uniform_buffer_offset_alignment;		//!< Specifies OpenGL uniform buffer offset alignment.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Uniform);
			EVE_PUBLIC_DESTRUCTOR(Uniform);
			
		public:
			/** \brief Class constructor. */
			explicit Uniform(void);


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
			/** \brief Set buffer data immediately (needs active OpenGL context). */
			void oglUpdateData(float * p_data);


		public:
			/** \brief Push data in uniform buffer data using memory position padding and request update. */
			void pushData(float * p_data, size_t p_num, size_t p_padding);


			/** \brief Push vector in uniform buffer data using memory position padding and request update. */
			void pushData(const eve::math::TVec2<float> & p_data, size_t p_padding);
			/** \brief Push vector in uniform buffer data using memory position padding and request update. */
			void pushData(const eve::math::TVec3<float> & p_data, size_t p_padding);
			/** \brief Push vector in uniform buffer data using memory position padding and request update. */
			void pushData(const eve::math::TVec4<float> & p_data, size_t p_padding);


			/** \brief Push matrix in uniform buffer data using memory position padding and request update. */
			void pushData(const eve::math::TMatrix22<float> & p_data, size_t p_padding);
			/** \brief Push matrix in uniform buffer data using memory position padding and request update. */
			void pushData(const eve::math::TMatrix33<float> & p_data, size_t p_padding);
			/** \brief Push matrix in uniform buffer data using memory position padding and request update. */
			void pushData(const eve::math::TMatrix44<float> & p_data, size_t p_padding);


		public:
			/** \brief Bind (activate). */
			void bind(GLuint p_binding);
			/** \brief Bind to camera transform buffer. */
			void bindCamera(void);
			/** \brief Bind to model transform buffer. */
			void bindModel(void);
			/** \brief Bind to skeleton transform buffer. */
			void bindSkeleton(void);


			/** \brief Unbind (deactivate). */
			static void unbind(GLuint p_binding);
			/** \brief Unbind (deactivate) from camera buffer. */
			static void unbind_camera(void);
			/** \brief Unbind (deactivate) from model buffer. */
			static void unbind_model(void);
			/** \brief Unbind (deactivate) from skeleton buffer. */
			static void unbind_skeleton(void);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief get OpenGL maximum vertex uniform blocks. */
			static const int32_t get_max_vertex_uniform_blocks(void);
			/** \brief Get OpenGL maximum control uniform blocks. */
			static const int32_t get_max_control_uniform_blocks(void);
			/** \brief Get OpenGL maximum evaluation uniform blocks. */
			static const int32_t get_max_evaluation_uniform_blocks(void);
			/** \brief Get OpenGL maximum geometry uniform blocks. */
			static const int32_t get_max_geometry_uniform_blocks(void);	
			/** \brief Get OpenGL maximum fragment uniform blocks. */
			static const int32_t get_max_fragment_uniform_blocks(void);

			/** \brief Get OpenGL maximum uniform buffer binding. */
			static const int32_t get_max_uniform_buffer_binding(void);
			/** \brief Get OpenGL maximum uniform blocks size. */
			static const int32_t get_max_uniform_block_size(void);				

			/** \brief Get OpenGL uniform buffer offset alignment. */
			static const int32_t get_uniform_buffer_offset_alignment(void);		
			
		public:
			/** \brief Get OpenGL texture unique id. (pure virtual) */
			virtual const GLuint getId(void) const override;
			
		}; // class Fbo

	} // namespace ogl

} // namespace eve


//=================================================================================================
EVE_FORCE_INLINE size_t eve::ogl::align_size_of(size_t p_originalSize)
{
	size_t ret = p_originalSize;

	// Align on 4 bytes.
	if (ret > 2)	{ ret += ret % 4; }
	// Align on 2 bytes.
	else			{ ret += ret % 2; }

	return ret;
}

/**
* \def EVE_OGL_SIZEOF_VEC2
* \brief Convenience macro to retrieve GLSL convenient size of GLSL vec2 type.
*/
#define EVE_OGL_SIZEOF_VEC2 (sizeof(float) * 2)
/**
* \def EVE_OGL_SIZEOF_VEC3
* \brief Convenience macro to retrieve GLSL convenient size of GLSL vec3 type.
*/
#define EVE_OGL_SIZEOF_VEC3 (sizeof(float) * 4)
/**
* \def EVE_OGL_SIZEOF_VEC4
* \brief Convenience macro to retrieve GLSL convenient size of GLSL vec4 type.
*/
#define EVE_OGL_SIZEOF_VEC4 (sizeof(float) * 4)


/**
* \def EVE_OGL_SIZEOF_MAT2
* \brief Convenience macro to retrieve GLSL convenient size of GLSL mat2 type.
*/
#define EVE_OGL_SIZEOF_MAT2 (sizeof(float) * 4)
/**
* \def EVE_OGL_SIZEOF_MAT3
* \brief Convenience macro to retrieve GLSL convenient size of GLSL mat3 type.
*/
#define EVE_OGL_SIZEOF_MAT3 (sizeof(float) * 16)
/**
* \def EVE_OGL_SIZEOF_MAT4
* \brief Convenience macro to retrieve GLSL convenient size of GLSL mat4 type.
*/
#define EVE_OGL_SIZEOF_MAT4 (sizeof(float) * 16)



/**
* \def EVE_OGL_PADDING_VEC2
* \brief Convenience macro to retrieve GLSL convenient padding of GLSL vec2 type.
*/
#define EVE_OGL_PADDING_VEC2 2
/**
* \def EVE_OGL_PADDING_VEC3
* \brief Convenience macro to retrieve GLSL convenient padding of GLSL vec3 type.
*/
#define EVE_OGL_PADDING_VEC3 4
/**
* \def EVE_OGL_PADDING_VEC4
* \brief Convenience macro to retrieve GLSL convenient padding of GLSL vec4 type.
*/
#define EVE_OGL_PADDING_VEC4 4


/**
* \def EVE_OGL_PADDING_MAT2
* \brief Convenience macro to retrieve GLSL convenient padding of GLSL mat2 type.
*/
#define EVE_OGL_PADDING_MAT2 4
/**
* \def EVE_OGL_PADDING_MAT3
* \brief Convenience macro to retrieve GLSL convenient padding of GLSL mat3 type.
*/
#define EVE_OGL_PADDING_MAT3 16
/**
* \def EVE_OGL_PADDING_MAT4
* \brief Convenience macro to retrieve GLSL convenient padding of GLSL mat4 type.
*/
#define EVE_OGL_PADDING_MAT4 16


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
EVE_FORCE_INLINE const int32_t eve::ogl::Uniform::get_max_vertex_uniform_blocks(void)		{ return m_max_vertex_uniform_blocks;			}
EVE_FORCE_INLINE const int32_t eve::ogl::Uniform::get_max_control_uniform_blocks(void)		{ return m_max_control_uniform_blocks;			}
EVE_FORCE_INLINE const int32_t eve::ogl::Uniform::get_max_evaluation_uniform_blocks(void)	{ return m_max_evaluation_uniform_blocks;		}
EVE_FORCE_INLINE const int32_t eve::ogl::Uniform::get_max_geometry_uniform_blocks(void)		{ return m_max_geometry_uniform_blocks;			}
EVE_FORCE_INLINE const int32_t eve::ogl::Uniform::get_max_fragment_uniform_blocks(void)		{ return m_max_fragment_uniform_blocks;			}	

//=================================================================================================
EVE_FORCE_INLINE const int32_t eve::ogl::Uniform::get_max_uniform_buffer_binding(void)		{ return m_max_uniform_buffer_binding;			}
EVE_FORCE_INLINE const int32_t eve::ogl::Uniform::get_max_uniform_block_size(void)			{ return m_max_uniform_block_size;				}

//=================================================================================================
EVE_FORCE_INLINE const int32_t eve::ogl::Uniform::get_uniform_buffer_offset_alignment(void)	{ return m_uniform_buffer_offset_alignment;		}



//=================================================================================================
EVE_FORCE_INLINE const GLuint eve::ogl::Uniform::getId(void) const	{ return m_id; }

#endif // __EVE_OPENGL_CORE_UNIFORM_H__
