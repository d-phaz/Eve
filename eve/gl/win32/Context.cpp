
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

// Main class header
#include "eve/gl/win32/Context.h"

#ifndef __EVE_OPENGL_EXTERNAL_H__
#include "eve/gl/External.h"
#endif

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 



//=================================================================================================
bool logEq(bool a, bool b) { return (((!a) && (!b)) || (a && b)); }



eve::gl::Context * eve::gl::Context::m_p_instance	= nullptr;
eve::thr::SpinLock * eve::gl::Context::m_p_fence	= nullptr;

//=================================================================================================
eve::gl::Context * eve::gl::Context::create_instance(void)
{
	EVE_ASSERT(!m_p_instance);
	EVE_ASSERT(!m_p_fence);

	m_p_fence = EVE_CREATE_PTR(eve::thr::SpinLock);

	m_p_instance = new eve::gl::Context();
	m_p_instance->init();
	return m_p_instance;
}

//=================================================================================================
void eve::gl::Context::release_instance(void)
{
	EVE_ASSERT(m_p_instance);
	EVE_RELEASE_PTR(m_p_instance);

	EVE_ASSERT(m_p_fence);
	EVE_RELEASE_PTR(m_p_fence);
}



//=================================================================================================
eve::gl::Context::Context(void)
	// Members init
	: m_hGLRC(0)
	, m_hDC(0)
	, m_pixelFormat()
	, m_pixelFormatDecriptor()
	, m_pixelFormatId(0)
{}



//=================================================================================================
void eve::gl::Context::init(void)
{
	m_pixelFormat = eve::gl::PixelFormat::default_format();

	this->chooseContext();
}

//=================================================================================================
void eve::gl::Context::release(void)
{
	// Rendering context handle.
	if (m_hGLRC)
	{
		::wglDeleteContext(m_hGLRC);
		m_hGLRC = 0;
	}
	// Draw context.
	if (m_hDC)
	{
		::ReleaseDC(0, m_hDC);
		m_hDC = 0;
	}

	m_pixelFormatId = 0;
}



//=================================================================================================
bool eve::gl::Context::chooseContext(void)
{
	bool ret = true;

	// Initialize OpenGL drawing device.
	m_hDC = ::GetDC(0);
	if (m_hDC == 0)
	{
		EVE_LOG_ERROR("Paint device cannot be null. GetDC() failed: %s", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
		ret = false;
	}

	// Initialize and choose best fitting Pixel Format.
	m_pixelFormatId = this->choosePixelFormat(&m_pixelFormatDecriptor);
	if (m_pixelFormatId == 0)
	{
		EVE_LOG_ERROR("Unable to get pixel format for device.");
		EVE_ASSERT_FAILURE;
		ret = false;
	}


	// Apply pixel format to DC.
	if (::SetPixelFormat(m_hDC, m_pixelFormatId, &m_pixelFormatDecriptor) == 0)
	{
		EVE_LOG_ERROR("Unable to link pixel format to DC, SetPixelFormat() failed: %s", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
		ret = false;
	}


	// Create context (GLRC).
	m_hGLRC = ::wglCreateContext(m_hDC);
	if (m_hGLRC == 0)
	{
		EVE_LOG_ERROR("Unable to create rendering context, wglCreateContext() failed: %s", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
		ret = false;
	}


	// Make context current (has to be activated here to enforce DC bound).
	if (::wglMakeCurrent(m_hDC, m_hGLRC) == 0)
	{
		EVE_LOG_ERROR("Unable to attach context, wglMakeCurrent() failed: %s.", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
	}

	// Stock DC auto updated format.
	this->updateFormatVersion();

	return ret;
}

//=================================================================================================
int32_t eve::gl::Context::choosePixelFormat(PIXELFORMATDESCRIPTOR * p_pPfd)
{
	BYTE pmDepth = 0;


	// Pixel format descriptor
	PIXELFORMATDESCRIPTOR * p = p_pPfd;
	p = eve::gl::PixelFormat::pixelFormatToPfd(&m_pixelFormat);


	// Choose pixel format
	int32_t chosenPfi = ::ChoosePixelFormat(m_hDC, p);
	if (chosenPfi == 0) 
	{
		EVE_LOG_ERROR("Unable to retrieve pixel format, ChoosePixelFormat() failed: %s", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
	}

	// GDI function ChoosePixelFormat() does not handle overlay and direct-rendering requests
	bool doSearch = (chosenPfi <= 0);
	PIXELFORMATDESCRIPTOR pfd;
	eve::gl::PixelFormat fmt;
	if (!doSearch)
	{
		::DescribePixelFormat(m_hDC, chosenPfi, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
		fmt = eve::gl::PixelFormat::pfdToPixelFormat(&pfd);

		if (m_pixelFormat.hasOverlay() && !fmt.hasOverlay())
			doSearch = true;
		else if (!logEq(m_pixelFormat.directRendering(), fmt.directRendering()))
			doSearch = true;
		else if ((!(pfd.dwFlags & PFD_DRAW_TO_BITMAP) || pfd.cColorBits != pmDepth))
			doSearch = true;
		else if (!(pfd.dwFlags & PFD_DRAW_TO_WINDOW))
			doSearch = true;
		else if (!logEq(m_pixelFormat.rgba(), fmt.rgba()))
			doSearch = true;
	}


	if (doSearch)
	{
		int32_t pfiMax		= ::DescribePixelFormat(m_hDC, 0, 0, NULL);
		int32_t bestScore	= -1;
		int32_t bestPfi		= -1;

		for (int32_t pfi = 1; pfi <= pfiMax; pfi++)
		{
			::DescribePixelFormat(m_hDC, pfi, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
			if (!(pfd.dwFlags & PFD_SUPPORT_OPENGL))
				continue;
			if ((!(pfd.dwFlags & PFD_DRAW_TO_BITMAP) || pfd.cColorBits != pmDepth))
				continue;
			if (!(pfd.dwFlags & PFD_DRAW_TO_WINDOW))
				continue;

			fmt = eve::gl::PixelFormat::pfdToPixelFormat(&pfd);
			if (m_pixelFormat.hasOverlay() && !fmt.hasOverlay())
				continue;

			int32_t score = pfd.cColorBits;
			if (logEq(m_pixelFormat.depth(), fmt.depth()))
				score += pfd.cDepthBits;
			if (logEq(m_pixelFormat.alpha(), fmt.alpha()))
				score += pfd.cAlphaBits;
			if (logEq(m_pixelFormat.accum(), fmt.accum()))
				score += pfd.cAccumBits;
			if (logEq(m_pixelFormat.stencil(), fmt.stencil()))
				score += pfd.cStencilBits;
			if (logEq(m_pixelFormat.doubleBuffer(), fmt.doubleBuffer()))
				score += 1000;
			if (logEq(m_pixelFormat.stereo(), fmt.stereo()))
				score += 2000;
			if (logEq(m_pixelFormat.directRendering(), fmt.directRendering()))
				score += 4000;
			if (logEq(m_pixelFormat.rgba(), fmt.rgba()))
				score += 8000;
			if (score > bestScore)
			{
				bestScore = score;
				bestPfi = pfi;
			}
		}

		if (bestPfi > 0)
		{
			// Stock chosen pfi ID
			chosenPfi = bestPfi;
			// Stock selected pixel format
			m_pixelFormat = fmt;
		}
	}

	return chosenPfi;
}



//=================================================================================================
void eve::gl::Context::updateFormatVersion(void)
{
	const GLubyte *s = glGetString(GL_VERSION);

	if (!(s && s[0] >= '0' && s[0] <= '9' && s[1] == '.' && s[2] >= '0' && s[2] <= '9'))
	{
		if (!s) {
			EVE_LOG_ERROR("OpenGL version string is null.");
		}
		else {
			EVE_LOG_ERROR("Unexpected OpenGL version string format.");
		}
		m_pixelFormat.setVersion(0, 0);
		m_pixelFormat.setProfile(pf_profNoProfile);
		m_pixelFormat.setOption(pf_optDeprecatedFunctions);
		return;
	}

	int32_t major = s[0] - '0';
	int32_t minor = s[2] - '0';
	m_pixelFormat.setVersion(major, minor);

	if (major < 3)
	{
		m_pixelFormat.setProfile(pf_profNoProfile);
		m_pixelFormat.setOption(pf_optDeprecatedFunctions);
	}
	else
	{
		GLint value = 0;
		if (major > 3 || minor >= 2) {
			glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &value);
		}

		switch (value)
		{
		case WGL_CONTEXT_CORE_PROFILE_BIT_ARB:
			m_pixelFormat.setProfile(pf_profCoreProfile);
			break;
		case WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB:
			m_pixelFormat.setProfile(pf_profCompatibilityProfile);
			break;
		default:
			m_pixelFormat.setProfile(pf_profNoProfile);
			break;
		}

		glGetIntegerv(GL_CONTEXT_FLAGS, &value);
		if (value & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT)
			m_pixelFormat.setOption(pf_optNoDeprecatedFunctions);
		else
			m_pixelFormat.setOption(pf_optDeprecatedFunctions);
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////

eve::gl::SubContext * eve::gl::SubContext::m_p_context_current = nullptr;

//=================================================================================================
eve::gl::SubContext * eve::gl::SubContext::create_ptr(HWND p_hWnd)
{
	eve::gl::SubContext * ptr = new eve::gl::SubContext(p_hWnd);
	ptr->init();
	return ptr;
}



//=================================================================================================
eve::gl::SubContext::SubContext(HWND p_hWnd)
	// Members init
	: m_hDC(0)
	, m_hWnd(p_hWnd)
{}



//=================================================================================================
void eve::gl::SubContext::init(void)
{
	// Get DC from window handle.
	m_hDC = ::GetDC(m_hWnd);
	if (m_hDC == 0)
	{
		EVE_LOG_ERROR("Paint device cannot be null. GetDC() failed: %s", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
	}


	// Apply pixel format to DC.
	if (::SetPixelFormat(m_hDC, eve::gl::Context::get_pixel_format_ID(), &eve::gl::Context::get_pixel_format_descriptor()) == 0)
	{
		EVE_LOG_ERROR("Unable to link pixel format to DC, SetPixelFormat() failed: %s", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
	}


	// Make context current (has to be activated here to enforce DC bound).
	if (::wglMakeCurrent(m_hDC, eve::gl::Context::get_handle()) == 0)
	{
		EVE_LOG_ERROR("Unable to attach context, wglMakeCurrent() failed: %s.", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
	}
	// Release context.
	if (::wglMakeCurrent(0, 0) == 0)
	{
		EVE_LOG_ERROR("Unable to detach context, wglMakeCurrent(0, 0) failed: %s.", eve::mess::get_error_msg());
		EVE_ASSERT_FAILURE;
	}
}

//=================================================================================================
void eve::gl::SubContext::release(void)
{
	// Draw context.
	if (m_hWnd && m_hDC)
	{
		::ReleaseDC(m_hWnd, m_hDC);
		m_hDC	= 0;
		m_hWnd	= 0;
	}
}



//=================================================================================================
void eve::gl::SubContext::set_current_context(eve::gl::SubContext * p_pContext)
{
	m_p_context_current = p_pContext;
}


//=================================================================================================
bool eve::gl::SubContext::makeCurrent(void)
{
	eve::gl::Context::get_fence()->lock();

	bool ret = true;

	if (eve::gl::Context::get_handle() == ::wglGetCurrentContext())
	{
		EVE_LOG_ERROR("Context already current.", (uintptr_t)eve::gl::Context::get_handle());
		ret = false;
	}

	if (ret && (::wglMakeCurrent(m_hDC, eve::gl::Context::get_handle()) == TRUE))
	{
		eve::gl::SubContext::set_current_context(this);
	}
	else
	{
		EVE_LOG_ERROR("Unable to attach context, wglMakeCurrent() failed: %s.", eve::mess::get_error_msg());
		ret = false;
	}

	return ret;
}

//=================================================================================================
bool eve::gl::SubContext::doneCurrent(void)
{
	bool ret = true;

	if (::wglMakeCurrent(0, 0) == TRUE)
	{
		eve::gl::SubContext::set_current_context(nullptr);
	}
	else
	{
		EVE_LOG_ERROR("Unable to detach context, wglMakeCurrent(0, 0) failed: %s.", eve::mess::get_error_msg());
		ret = false;
	}

	eve::gl::Context::get_fence()->unlock();

	return ret;
}

//=================================================================================================
void eve::gl::SubContext::swapBuffers(void)
{
	// Multiple rendering buffers
	if (eve::gl::Context::get_pixel_format().doubleBuffer())
	{
		if (!eve::gl::Context::get_pixel_format().plane())
		{
			if (!eve::gl::Context::get_pixel_format().hasOverlay())
			{
				::SwapBuffers(m_hDC);
			}
			else // format has overlay
			{
				::wglSwapLayerBuffers(m_hDC, WGL_SWAP_MAIN_PLANE);
			}
		}
		else // format has plane
		{
			::wglSwapLayerBuffers(m_hDC, WGL_SWAP_OVERLAY1);
		}
	}

	// Single rendering buffers
	else
	{
		// Force OpenGL command termination
		glFlush();
		glFinish();
	}
}
