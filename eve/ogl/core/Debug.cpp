
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

// Main header.
#include "eve/ogl/core/Debug.h"

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


//=================================================================================================
void eve::ogl::init_debug_stream(void)
{
#if defined(GL_ARB_debug_output)
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	glDebugMessageCallbackARB(&eve::mess::Server::ogl_debug_output, 0);
	EVE_OGL_CHECK_ERROR;
#endif
}



//=================================================================================================
void eve::ogl::check_error(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line)
{
	int32_t Error = glGetError();
	if (Error != GL_NO_ERROR)
	{
		std::wstring mess;
		switch (Error)
		{
		case GL_INVALID_ENUM:					mess = EVE_TXT("GL_INVALID_ENUM");					break;
		case GL_INVALID_VALUE:					mess = EVE_TXT("GL_INVALID_VALUE");					break;
		case GL_INVALID_OPERATION:				mess = EVE_TXT("GL_INVALID_OPERATION");				break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:	mess = EVE_TXT("GL_INVALID_FRAMEBUFFER_OPERATION");	break;
		case GL_STACK_OVERFLOW:					mess = EVE_TXT("GL_STACK_OVERFLOW");				break;
		case GL_STACK_UNDERFLOW:				mess = EVE_TXT("GL_STACK_UNDERFLOW");				break;
		case GL_OUT_OF_MEMORY:					mess = EVE_TXT("GL_OUT_OF_MEMORY");					break;
		default:								mess = EVE_TXT("UNKNOWN");							break;
		}

		EVE_LOG_ERROR("OpenGL Error: %s in function %s in file %s at line %d.", mess.c_str(), p_pFunction, p_pFile, p_line);
		EVE_ASSERT_FAILURE;
	}
}



//=================================================================================================
void eve::ogl::check_frame_buffer(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, GLuint p_framebufferId)
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::wstring mess;
		switch (status)
		{
		case GL_FRAMEBUFFER_UNDEFINED:						mess = EVE_TXT("GL_FRAMEBUFFER_UNDEFINED");							break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:			mess = EVE_TXT("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");				break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:  mess = EVE_TXT("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");		break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:			mess = EVE_TXT("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:			mess = EVE_TXT("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:					mess = EVE_TXT("GL_FRAMEBUFFER_UNSUPPORTED");						break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:			mess = EVE_TXT("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");			break;

#if !defined(EVE_OS_DARWIN)
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:		mess = EVE_TXT("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");			break;
#endif
		}

		EVE_LOG_ERROR("OpenGL Error: %s in function %s in file %s at line %d.", mess.c_str(), p_pFunction, p_pFile, p_line);
		EVE_ASSERT_FAILURE;
	}
}



//=================================================================================================
void eve::ogl::check_shader_program(wchar_t * p_pFunction, wchar_t * p_pFile, int32_t p_line, GLuint p_programId)
{
	EVE_ASSERT(p_programId != 0);

	GLint link = GL_FALSE;
	glGetProgramiv(p_programId, GL_LINK_STATUS, &link);

	if (link != GL_TRUE)
	{
		int32_t logLength;
		glGetProgramiv(p_programId, GL_INFO_LOG_LENGTH, &logLength);

		size_t size = std::max(logLength, 1);
		char * buf = (char*)malloc(size *sizeof(char));
		glGetProgramInfoLog(p_programId, logLength, NULL, buf);

		wchar_t * wbuf = (wchar_t*)malloc(size * sizeof(wchar_t));
		mbstowcs(wbuf, buf, size);

		EVE_LOG_ERROR("OpenGL Error: in function %s in file %s at line %d Shader program link failed: %s.", p_pFunction, p_pFile, p_line, wbuf);

		free(wbuf);
		free(buf);

		EVE_ASSERT_FAILURE;
	}
}
