
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
#include "eve/ogl/win32/Context.h"

#ifndef __EVE_OPENGL_DEBUG_H__
#include "eve/ogl/Debug.h"
#endif

#ifndef __EVE_SYSTEM_WINDOW_H__
#include "eve/sys/win32/Window.h"
#endif

#ifndef __EVE_SYSTEM_NOTIFICATION_H__
#include "eve/sys/win32/Notification.h"
#endif

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 



//=================================================================================================
bool logEq(bool a, bool b) { return (((!a) && (!b)) || (a && b)); }



eve::ogl::Context * eve::ogl::Context::m_p_instance	= nullptr;
eve::thr::SpinLock * eve::ogl::Context::m_p_fence	= nullptr;

//=================================================================================================
eve::ogl::Context * eve::ogl::Context::create_instance(void)
{
	EVE_ASSERT(!m_p_instance);
	EVE_ASSERT(!m_p_fence);

	m_p_fence = EVE_CREATE_PTR(eve::thr::SpinLock);

	m_p_instance = new eve::ogl::Context();
	m_p_instance->init();
	return m_p_instance;
}

//=================================================================================================
void eve::ogl::Context::release_instance(void)
{
	EVE_ASSERT(m_p_instance);
	EVE_RELEASE_PTR(m_p_instance);

	EVE_ASSERT(m_p_fence);
	EVE_RELEASE_PTR(m_p_fence);
}



//=================================================================================================
eve::ogl::Context::Context(void)
	// Members init
	: m_hGLRC(0)
	, m_hDC(0)
	, m_pixelFormat()
	, m_pixelFormatDecriptor()
	, m_pixelFormatId(0)
{}



//=================================================================================================
void eve::ogl::Context::init(void)
{
	m_pixelFormat = eve::ogl::PixelFormat::default_format();

	// Create dummy window.
	eve::sys::Window * win = eve::sys::Window::create_ptr(0, 0, 1, 1);

	// Initialize OpenGL drawing device.
	m_hDC = ::GetDC(win->getHandle());
	if (m_hDC == 0)
	{
		EVE_LOG_ERROR("Paint device cannot be null. GetDC() failed: %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	// Initialize and choose best fitting Pixel Format.
	m_pixelFormatId = this->choosePixelFormat();
	if (m_pixelFormatId == 0)
	{
		EVE_LOG_ERROR("Unable to get pixel format for device.");
		EVE_ASSERT_FAILURE;
	}


	// Apply pixel format to DC.
	if (::SetPixelFormat(m_hDC, m_pixelFormatId, &m_pixelFormatDecriptor) == FALSE)
	{
		EVE_LOG_ERROR("Unable to link pixel format to DC, SetPixelFormat() failed %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}


	// Create context (GLRC).
	m_hGLRC = ::wglCreateContext(m_hDC);
	if (m_hGLRC == 0)
	{
		EVE_LOG_ERROR("Unable to create rendering context, wglCreateContext() failed %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}


	// Make context current (has to be activated here to enforce DC bound).
	if (::wglMakeCurrent(m_hDC, m_hGLRC) == 0)
	{
		EVE_LOG_ERROR("Unable to attach context, wglMakeCurrent() failed %s.", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	// Init OpenGL extension for this context
	eve::ogl::Context::init_OpenGL();
	// Stock DC auto updated format.
	this->updateFormatVersion();

	// Release context.
	if (::wglMakeCurrent(0, 0) == 0)
	{
		EVE_LOG_ERROR("Unable to detach context, wglMakeCurrent(0, 0) failed %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	// Release dummy window.
	EVE_RELEASE_PTR(win);
}

//=================================================================================================
void eve::ogl::Context::release(void)
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
void eve::ogl::Context::init_OpenGL(void)
{
	glewInit();

	static bool firstLaunch = true;
	if (firstLaunch)
	{
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{
			// Log error
			EVE_LOG_ERROR("OpenGL extensions initialization failed (GLEW).");
			// Create fatal error window and exit app
			eve::sys::notify_fatal_error(EVE_TXT("OpenGL initialization failed.\n \n Please check your hardware and drivers capabilities."));
		}

		// Retrieve OpenGL version
		GLint majorVersion;
		GLint minorVersion;
		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
		EVE_LOG_INFO("Detected OpenGL version %d.%d.", majorVersion, minorVersion);

		// Test OpenGL version
		if (majorVersion < EVE_WINDOWS_OPENGL_MAJOR_VERSION)
		{
			// Create fatal error window and exit app
			eve::sys::notify_fatal_error(EVE_TXT("OpenGL initialization failed.\n \n Please check your hardware and drivers capabilities."));
		}
		else
		{
			if (minorVersion < EVE_WINDOWS_OPENGL_MINOR_VERSION)
			{
				// Create fatal error window and exit app
				eve::sys::notify_fatal_error(EVE_TXT("OpenGL initialization failed.\n \n Please check your hardware and drivers capabilities."));
			}
		}

		eve::ogl::init_debug_stream();

		firstLaunch = false;
	}
}



//=================================================================================================
int32_t eve::ogl::Context::choosePixelFormat(void)
{
	BYTE pmDepth = 0;

	// Pixel format descriptor
	m_pixelFormatDecriptor = eve::ogl::PixelFormat::pixelFormatToPfd(&m_pixelFormat);
	// Choose pixel format
	int32_t chosenPfi = ::ChoosePixelFormat(m_hDC, &m_pixelFormatDecriptor);
	if (chosenPfi == 0) 
	{
		EVE_LOG_ERROR("Unable to retrieve pixel format, ChoosePixelFormat() failed %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	// GDI function ChoosePixelFormat() does not handle overlay and direct-rendering requests
	bool doSearch = (chosenPfi <= 0);
	PIXELFORMATDESCRIPTOR pfd;
	eve::ogl::PixelFormat fmt;
	if (!doSearch)
	{
		::DescribePixelFormat(m_hDC, chosenPfi, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
		fmt = eve::ogl::PixelFormat::pfdToPixelFormat(&pfd);

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

			fmt = eve::ogl::PixelFormat::pfdToPixelFormat(&pfd);
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
void eve::ogl::Context::updateFormatVersion(void)
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

eve::ogl::SubContext * eve::ogl::SubContext::m_p_context_current = nullptr;

//=================================================================================================
eve::ogl::SubContext * eve::ogl::SubContext::create_ptr(HWND p_hWnd)
{
	eve::ogl::SubContext * ptr = new eve::ogl::SubContext(p_hWnd);
	ptr->init();
	return ptr;
}



//=================================================================================================
eve::ogl::SubContext::SubContext(HWND p_hWnd)
	// Members init
	: m_hDC(0)
	, m_hWnd(p_hWnd)
{}



//=================================================================================================
void eve::ogl::SubContext::init(void)
{
	// Get DC from window handle.
	m_hDC = ::GetDC(m_hWnd);
	if (m_hDC == 0)
	{
		EVE_LOG_ERROR("Paint device cannot be null. GetDC() failed %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}


	// Apply pixel format to DC.
	if (::SetPixelFormat(m_hDC, eve::ogl::Context::get_pixel_format_ID(), &eve::ogl::Context::get_pixel_format_descriptor()) == 0)
	{
		EVE_LOG_ERROR("Unable to link pixel format to DC, SetPixelFormat() failed %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}


	// Make context current (has to be activated here to enforce DC bound).
	if (::wglMakeCurrent(m_hDC, eve::ogl::Context::get_handle()) == 0)
	{
		EVE_LOG_ERROR("Unable to attach context, wglMakeCurrent() failed %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}

	// Init OpenGL extensions for this context.
	eve::ogl::Context::init_OpenGL();

	// Release context.
	if (::wglMakeCurrent(0, 0) == 0)
	{
		EVE_LOG_ERROR("Unable to detach context, wglMakeCurrent(0, 0) failed %s", eve::mess::get_error_msg().c_str());
		EVE_ASSERT_FAILURE;
	}
}

//=================================================================================================
void eve::ogl::SubContext::release(void)
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
void eve::ogl::SubContext::set_current_context(eve::ogl::SubContext * p_pContext)
{
	m_p_context_current = p_pContext;
}


//=================================================================================================
bool eve::ogl::SubContext::makeCurrent(void)
{
	eve::ogl::Context::get_fence()->lock();

	bool ret = true;

	if (eve::ogl::Context::get_handle() == ::wglGetCurrentContext())
	{
		EVE_LOG_ERROR("Context already current.", (uintptr_t)eve::ogl::Context::get_handle());
		ret = false;
	}

	if (ret && (::wglMakeCurrent(m_hDC, eve::ogl::Context::get_handle()) == TRUE))
	{
		eve::ogl::SubContext::set_current_context(this);
	}
	else
	{
		EVE_LOG_ERROR("Unable to attach context, wglMakeCurrent() failed %s", eve::mess::get_error_msg().c_str());
		ret = false;
	}

	return ret;
}

//=================================================================================================
bool eve::ogl::SubContext::doneCurrent(void)
{
	bool ret = true;

	if (::wglMakeCurrent(0, 0) == TRUE)
	{
		eve::ogl::SubContext::set_current_context(nullptr);
	}
	else
	{
		EVE_LOG_ERROR("Unable to detach context, wglMakeCurrent(0, 0) failed %s", eve::mess::get_error_msg().c_str());
		ret = false;
	}

	eve::ogl::Context::get_fence()->unlock();

	return ret;
}

//=================================================================================================
void eve::ogl::SubContext::swapBuffers(void)
{
	// Multiple rendering buffers
	if (eve::ogl::Context::get_pixel_format().doubleBuffer())
	{
		if (!eve::ogl::Context::get_pixel_format().plane())
		{
			if (!eve::ogl::Context::get_pixel_format().hasOverlay())
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
