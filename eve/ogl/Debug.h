
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
#ifndef __EVE_OPENGL_DEBUG_H__
#define __EVE_OPENGL_DEBUG_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_OPENGL_EXTERNAL_H__
#include "eve/ogl/External.h"
#endif

#ifndef __EVE_OPENGL_MACRO_H__
#include "eve/ogl/Macro.h"
#endif


namespace eve
{
	namespace ogl
	{
		/** \brief Initialize OpenGL debug stream. */
		void init_debug_stream(void);

		/** \brief Test OpenGL error, log it and create error assertion. */
		void check_error(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line);

		/** \brief Test frame buffer integrity, log and create assertion if frame buffer is not complete. */
		void check_frame_buffer(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, GLuint p_framebufferId);

		/** \brief Test shader program and log state if required. */
		void check_shader_program(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, GLuint p_programId);

	} // namespace ogl

} // namespace eve

/** 
* \def EVE_OGL_CHECK_ERROR
* \brief Convenience macro to check OpenGL errors.
*/
#ifndef NDEBUG
#define EVE_OGL_CHECK_ERROR		eve::ogl::check_error(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__)
#else
#define EVE_OGL_CHECK_ERROR 
#endif

/**
* \def EVE_OGL_CHECK_FBO
* \brief Convenience macro to check OpenGL Frame buffer object.
*/
#ifndef NDEBUG
#define EVE_OGL_CHECK_FBO(ID)		eve::ogl::check_frame_buffer(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__, ID)
#else
#define EVE_OGL_CHECK_FBO(ID)
#endif

/**
* \def EVE_OGL_CHECK_SHADER
* \brief Convenience macro to check OpenGL shader program.
*/
#ifndef NDEBUG
#define EVE_OGL_CHECK_SHADER(ID)		eve::ogl::check_shader_program(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT_ENFORCE(__FILE__), __LINE__, ID)
#else
#define EVE_OGL_CHECK_SHADER(ID)
#endif

#endif // __EVE_OPENGL_RENDER_H__
