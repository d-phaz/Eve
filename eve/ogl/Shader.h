
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
#ifndef __EVE_OPENGL_SHADER_H__
#define __EVE_OPENGL_SHADER_H__

#ifndef __EVE_OPENGL_OBJECT_H__
#include "eve/ogl/Object.h"
#endif


namespace eve
{
	namespace ogl
	{
		/** 
		* \def eve::ogl::PipelineType
		* \brief Defines shader pipeline types.
		*/
		enum PipelineType
		{
			shader_Unknown,
			shader_Pixel,			//!< GL_VERTEX_SHADER | GL_FRAGMENT_SHADER
			shader_Geometry,		//!< GL_VERTEX_SHADER | GL_GEOMETRY_SHADER | GL_FRAGMENT_SHADER
			shader_Tessellation		//!< GL_VERTEX_SHADER | GL_TESS_CONTROL_SHADER | GL_TESS_EVALUATION_SHADER | GL_GEOMETRY_SHADER | GL_FRAGMENT_SHADER
		};

		/**
		* \def eve::ogl::ProgramType
		* \brief convenience enumeration to access in array program id.
		*/
		enum ProgramType
		{
			prgm_Vertex,
			prgm_Control,
			prgm_Evaluation,
			prgm_Geometry,
			prgm_Fragment,

			prgm_Max
		};


		/**
		* \class eve::ogl::FormatShader
		*
		* \brief OpenGL shader format class.
		* Used to create OpenGL shader based on properties.
		*
		* \note extends eve::ogl::Format
		*/
		class FormatShader final
			: public eve::ogl::Format
		{
		public:
			std::string					vertex;			//!< Vertex shader program source.
			std::string					control;		//!< Control shader program source.
			std::string					eval;			//!< Evaluation shader program source.
			std::string					geom;			//!< Geometry shader program source.
			std::string					fragment;		//!< Fragment shader program source.

		public:
			/** \brief Class constructor. */
			FormatShader(void);
			/** \brief Class destructor. */
			virtual ~FormatShader(void);

			/** \brief Copy constructor. */
			FormatShader(const eve::ogl::FormatShader & p_other);
			/** \brief Assignation operator. */
			const eve::ogl::FormatShader & operator = (const eve::ogl::FormatShader & p_other);

		}; // class FormatShader


		/** 
		* \class eve::ogl::Shader
		*
		* \brief Create and manage OpenGL shader pipeline.
		*
		* Program use multiple shader:
		*	GL_VERTEX_SHADER | GL_FRAGMENT_SHADER
		*	GL_VERTEX_SHADER | GL_GEOMETRY_SHADER | GL_FRAGMENT_SHADER
		*	GL_VERTEX_SHADER | GL_TESS_CONTROL_SHADER | GL_TESS_EVALUATION_SHADER | GL_GEOMETRY_SHADER | GL_FRAGMENT_SHADER
		*
		* Use buffer(s) to pass uniform variables.
		*
		* \note extends eve::ogl::Object
		*/
		class Shader final
			: public eve::ogl::Object
		{

			friend class eve::mem::Pointer;
			friend class eve::ogl::Renderer;
			friend class eve::ogl::Object;


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			GLuint						m_id;					//!< Specifies OpenGL unique shader program ID.
			GLuint *					m_prgmId;				//!< Staged programs OpenGL ids.

			std::string					m_vertex;				//!< Vertex shader program source.
			std::string					m_control;				//!< Control shader program source.
			std::string					m_eval;					//!< Evaluation shader program source.
			std::string					m_geom;					//!< Geometry shader program source.
			std::string					m_fragment;				//!< Fragment shader program source.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Shader);
			EVE_PROTECT_DESTRUCTOR(Shader);
			
		private:
			/** \brief Class constructor. */
			explicit Shader(void);


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
			/** \brief Bind (activate). */
			void bind(GLenum p_index);
			/** \brief Unbind (deactivate). */
			static void unbind(GLenum p_index);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////
			
		public:
			/** \brief Get OpenGL shader unique id. (pure virtual) */
			virtual const GLuint getId(void) const override;

			/** \brief Get OpenGL program id depending on target type. */
			const GLuint getProgramId(eve::ogl::ProgramType p_type) const;
			
		}; // class Fbo

	} // namespace ogl

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
inline const GLuint eve::ogl::Shader::getId(void) const	{ return m_id; }

//=================================================================================================
inline const GLuint eve::ogl::Shader::getProgramId(eve::ogl::ProgramType p_type) const { EVE_ASSERT(m_prgmId[p_type] != 0); return m_prgmId[p_type]; }

#endif // __EVE_OPENGL_TEXTURE_H__
