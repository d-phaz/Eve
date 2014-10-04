//
///*
// Copyright (c) 2014, The eve Project
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
// 
// * Neither the name of the {organization} nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//*/
//
//// Main class header
//#include "SystemContext.h"
//
//// OpenGL header
//#ifndef __OGL_EXTERNAL_H__
//#include "gl/OGLExternal.h"
//#endif
//
//// Messaging header
//#ifndef __NATIVE_MESSAGING_H__
//#include "Native_Messaging.h"
//#endif
//
//#ifndef __NATIVE_SYSTEM_H__
//#include "Native_System.h"
//#endif
//
//#ifndef __SYSTEM_NODE_H__
//#include "SystemNode.h"
//#endif
//
//#ifndef __SYSTEM_WINDOW_H__
//#include "SystemWindow.h"
//#endif
//
//#ifndef __SYSTEM_ERROR_H__
//#include "SystemError.h"
//#endif
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
////		Static
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//static bool opengl32dll = false;	//<! convenience driver awakening boolean
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
////		SystemContext class
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
////=================================================================================================
//SystemContext::SystemContext( void )
//
//	// Members initialization
//	: m_NodalId					( -1 )
//	, m_pNode					( NULL )
//	, m_SystemContextMaster		( NULL )
//
//	, m_Sharing					( false )
//	, m_bValid					( false )
//
//	, m_pixelFormatId			( 0 )
//	, m_pixelFormat				()
//
//	, m_Hglrc					( NULL )
//	, m_Hdc						( NULL )
//	, m_Hwnd					( NULL )
//{}
//
////=================================================================================================
//SystemContext::~SystemContext( void )
//{
//	// do not delete -> shared pointers
//	m_pNode = NULL;	
//	m_SystemContextMaster = NULL;
//}
//
//
//
////=================================================================================================
//bool SystemContext::init( int32_t p_nodalId, SystemNode * p_pNode, SystemContext * p_pContextMaster )
//{
//	m_NodalId				= p_nodalId;
//	m_pNode					= p_pNode;
//	m_SystemContextMaster	= p_pContextMaster;
//
//	m_Hwnd = m_pNode->getWindow()->m_Hwnd;
//
//	m_pixelFormat = SystemPixelFormat::default_format();
//
//	m_bValid = this->chooseContext( m_SystemContextMaster );
//
//	return m_bValid;
//}
//
//
//
////=================================================================================================
//void SystemContext::release( void )
//{
//	// Workaround for MATROX driver: make a dummy call to OpenGL to force DLL loading.
//	if( !opengl32dll ) 
//	{
//		GLint params;
//		glGetIntegerv( GL_DEPTH_BITS, &params );
//		opengl32dll = true;
//	}
//
//	// Rendering context handle
//	if( m_Hglrc ) 
//	{
//		wglDeleteContext( m_Hglrc );
//		m_Hglrc = NULL;
//	}
//	// Draw context
//	if( m_Hwnd && m_Hdc ) 
//	{
//		ReleaseDC( m_Hwnd, m_Hdc );
//	}
//
//
//	m_Hdc			= NULL;
//	m_Hwnd			= NULL;
//	m_pixelFormatId	= 0;
//	m_Sharing		= false;
//}
//
//
//
////=================================================================================================
//bool SystemContext::logEq( bool a, bool b )
//{
//	return (((!a) && (!b)) || (a && b));
//}
//
//
//
////=================================================================================================
//bool SystemContext::chooseContext( SystemContext * p_pShareContext )
//{
//	bool B_Return = true;
//
//	// Workaround for MATROX driver: make a cheap call to OpenGL to force loading of DLL.
//	if( !opengl32dll ) 
//	{
//		GLint params;
//		glGetIntegerv(GL_DEPTH_BITS, &params);
//		opengl32dll = true;
//	}
//
//	// Initialize OpenGL drawing device
//	m_Hdc = ::GetDC( m_Hwnd );
//	if( m_Hdc == 0 ) 
//	{
//#ifndef NDEBUG
//		native_error_msg( "SystemContext::chooseContext()", "Paint device cannot be null. \n" );
//#endif
//		B_Return = false;
//	}
//
//#ifndef NDEBUG
//	NATIVE_ASSERT( (m_Hdc!=0) );
//#endif
//
//
//	// Initialize and choose best fitting Pixel Format
//	PIXELFORMATDESCRIPTOR pfd;
//	m_pixelFormatId = this->choosePixelFormat( &pfd );
//	if( m_pixelFormatId == 0 ) 
//	{
//		native_error_msg("SystemContext::chooseContext()", "SystemContext::choosePixelFormat() failed. \n");
//		B_Return = false;
//	}
//	// If found m_pixelFormat is set in function "choosePixelFormat()"
//	//m_pixelFormat = SystemPixelFormat::pfiToSystemPixelFormat( m_Hdc, m_pixelFormatId );
//
//#ifndef NDEBUG
//	NATIVE_ASSERT( (m_pixelFormatId!=0) );
//#endif
//
//
//	// Apply pixel format to DC
//	if( !::SetPixelFormat(m_Hdc, m_pixelFormatId, &pfd) ) 
//	{
//		native_error_msg( "SystemContext::chooseContext()", "SetPixelFormat() failed. \n" );
//		B_Return = false;
//	}
//
//
//	// Create context (GLRC) -> always create it event if master context passed in case of master context release.
//	m_Hglrc = ::wglCreateContext( m_Hdc );
//	if( m_Hglrc == 0 ) 
//	{
//		native_error_msg("SystemContext::chooseContext()", "wglCreateContext() failed. \n");
//		B_Return = false;
//	}
//
//#ifndef NDEBUG
//	NATIVE_ASSERT( (m_Hglrc!=0) );
//#endif
//
//
//	// Apply shared display list if needed (pretty much deprecated as I write (OpenGL 4.2 spec))
//	// Kept for compatibility and future use
//	if( p_pShareContext ) 
//	{
//		p_pShareContext->m_Sharing = m_Sharing = (::wglShareLists( p_pShareContext->m_Hglrc, m_Hglrc ) == TRUE);
//	}
//
//
//	// Make context current (has to be activated here to fix DC bound)
//	::wglMakeCurrent(m_Hdc, m_Hglrc);
//
//	// Stock DC auto updated format
//	this->updateFormatVersion();
//
//	return B_Return;
//}
//
//
//
////=================================================================================================
//int32_t SystemContext::choosePixelFormat( void* dummyPfd )
//{
//	// Workaround for MATROX driver: make a cheap call to OpenGL to force loading of DLL.
//	if (!opengl32dll) 
//	{
//		GLint params;
//		glGetIntegerv(GL_DEPTH_BITS, &params);
//		opengl32dll = true;
//	}
//
//
//	BYTE pmDepth = 0;
//
//
//	// Pixel format descriptor
//	PIXELFORMATDESCRIPTOR* p = (PIXELFORMATDESCRIPTOR*)dummyPfd;
//	p = SystemPixelFormat::systemPixelFormatToPfd( &m_pixelFormat );
//		
//
//	// Choose pixel format
//	int32_t chosenPfi = ::ChoosePixelFormat( m_Hdc, p );
//	if( !chosenPfi ) {
//		native_error_msg( "SystemContext::choosePixelFormat()", "ChoosePixelFormat() failed. \n");
//	}
//
//	// GDI function ChoosePixelFormat() does not handle overlay and direct-rendering requests
//	bool doSearch = (chosenPfi <= 0);
//	PIXELFORMATDESCRIPTOR pfd;
//	SystemPixelFormat fmt;
//	if( !doSearch ) 
//	{
//		::DescribePixelFormat( m_Hdc, chosenPfi, sizeof(PIXELFORMATDESCRIPTOR), &pfd );
//		fmt = SystemPixelFormat::pfdToSystemPixelFormat( &pfd );
//
//		if (m_pixelFormat.hasOverlay() && !fmt.hasOverlay())
//			doSearch = true;
//		else if ( !logEq(m_pixelFormat.directRendering(), fmt.directRendering()) )
//			doSearch = true;
//		else if ( (!(pfd.dwFlags & PFD_DRAW_TO_BITMAP) || pfd.cColorBits != pmDepth) )
//			doSearch = true;
//		else if ( !(pfd.dwFlags & PFD_DRAW_TO_WINDOW) )
//			doSearch = true;
//		else if ( !logEq(m_pixelFormat.rgba(), fmt.rgba()) )
//			doSearch = true;
//	}
//
//
//	if( doSearch ) 
//	{
//		int32_t pfiMax = ::DescribePixelFormat( m_Hdc, 0, 0, NULL );
//		int32_t bestScore = -1;
//		int32_t bestPfi = -1;
//
//		for (int32_t pfi = 1; pfi <= pfiMax; pfi++) 
//		{
//			::DescribePixelFormat( m_Hdc, pfi, sizeof(PIXELFORMATDESCRIPTOR), &pfd );
//			if ( !(pfd.dwFlags & PFD_SUPPORT_OPENGL))
//				continue;
//			if ( (!(pfd.dwFlags & PFD_DRAW_TO_BITMAP) || pfd.cColorBits != pmDepth))
//				continue;
//			if ( !(pfd.dwFlags & PFD_DRAW_TO_WINDOW))
//				continue;
//
//			fmt = SystemPixelFormat::pfdToSystemPixelFormat( &pfd );
//			if (m_pixelFormat.hasOverlay() && !fmt.hasOverlay())
//				continue;
//
//			int32_t score = pfd.cColorBits;
//			if (logEq(m_pixelFormat.depth(), fmt.depth()))
//				score += pfd.cDepthBits;
//			if (logEq(m_pixelFormat.alpha(), fmt.alpha()))
//				score += pfd.cAlphaBits;
//			if (logEq(m_pixelFormat.accum(), fmt.accum()))
//				score += pfd.cAccumBits;
//			if (logEq(m_pixelFormat.stencil(), fmt.stencil()))
//				score += pfd.cStencilBits;
//			if (logEq(m_pixelFormat.doubleBuffer(), fmt.doubleBuffer()))
//			    score += 1000;
//			if (logEq(m_pixelFormat.stereo(), fmt.stereo()))
//				score += 2000;
//			if (logEq(m_pixelFormat.directRendering(), fmt.directRendering()))
//				score += 4000;
//			if (logEq(m_pixelFormat.rgba(), fmt.rgba()))
//				score += 8000;
//			if (score > bestScore) 
//			{
//				bestScore = score;
//				bestPfi = pfi;
//			}
//		}
//
//		if( bestPfi > 0 ) 
//		{
//			// Stock chosen pfi ID
//			chosenPfi = bestPfi;
//			// Stock selected pixel format
//			m_pixelFormat = fmt;
//		}
//	}
//
//	return chosenPfi;
//}
//
//
//
////=================================================================================================
//void SystemContext::updateFormatVersion( void )
//{
//	const GLubyte *s = glGetString(GL_VERSION);
//
//	if (!(s && s[0] >= '0' && s[0] <= '9' && s[1] == '.' && s[2] >= '0' && s[2] <= '9')) 
//	{
//		if (!s)
//		{
//			native_error_msg("SystemContext::updateFormatVersion()", "OpenGL version string is null. \n");
//		}
//		else 
//		{
//			native_error_msg("SystemContext::updateFormatVersion()", "Unexpected OpenGL version string format. \n");
//		}
//		m_pixelFormat.setVersion(0, 0);
//		m_pixelFormat.setProfile(SystemPixelFormat::NoProfile);
//		m_pixelFormat.setOption(DeprecatedFunctions);
//		return;
//	}
//
//	int32_t major = s[0] - '0';
//	int32_t minor = s[2] - '0';
//	m_pixelFormat.setVersion(major, minor);
//
//	if( major < 3 ) 
//	{
//		m_pixelFormat.setProfile(SystemPixelFormat::NoProfile);
//		m_pixelFormat.setOption(DeprecatedFunctions);
//	} 
//	else 
//	{
//		GLint value = 0;
//		if (major > 3 || minor >= 2) {
//			glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &value);
//		}
//
//		switch (value) 
//		{
//		case WGL_CONTEXT_CORE_PROFILE_BIT_ARB:
//			m_pixelFormat.setProfile(SystemPixelFormat::CoreProfile);
//			break;
//		case WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB:
//			m_pixelFormat.setProfile(SystemPixelFormat::CompatibilityProfile);
//			break;
//		default:
//			m_pixelFormat.setProfile(SystemPixelFormat::NoProfile);
//			break;
//		}
//
//		glGetIntegerv(GL_CONTEXT_FLAGS, &value);
//		if (value & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT)
//			m_pixelFormat.setOption(NoDeprecatedFunctions);
//		else
//			m_pixelFormat.setOption(DeprecatedFunctions);
//	}
//}
//
//
//
////=================================================================================================
//SystemContext* SystemContext::m_current_context = NULL;
//
////=================================================================================================
//void SystemContext::set_current_context( SystemContext * p_context )
//{
//	m_current_context = p_context;
//}
//
////=================================================================================================
//const SystemContext* SystemContext::get_current_context( void )
//{
//	return m_current_context;
//}
//
//
//
////=================================================================================================
//bool SystemContext::makeCurrent( void )
//{
//	bool bret = true;
//
//	HGLRC hgl = (m_SystemContextMaster!=NULL) ? m_SystemContextMaster->m_Hglrc : m_Hglrc;
//
//	if( hgl == ::wglGetCurrentContext() )
//	{
//#ifndef NDEBUG
//		native_error_msg( "SystemContext::makeCurrent()", "context already current %i \n", (uintptr_t)hgl );
//#endif				
//		bret = false;
//	}
//
//	if( bret && (TRUE == ::wglMakeCurrent( m_Hdc, hgl)) ) 
//	{
//		set_current_context(this);	
//	}
//	else 
//	{
//		native_error_msg( "SystemContext::makeCurrent()", "wglMakeCurrent() context %i failed %s \n", (uintptr_t)hgl, native_system::getErrorMsg().c_str() );
//		bret = false;
//	}
//
//	return bret;
//}
//
////=================================================================================================
//bool SystemContext::doneCurrent( void )
//{
//	bool BReturn = true;
//
//	if( TRUE == ::wglMakeCurrent( NULL, NULL) )
//	{
//		set_current_context( NULL );
//	}
//	else 
//	{
//		native_error_msg( "SystemContext::doneCurrent()", "wglMakeCurrent(NULL,NULL) failed %s \n", native_system::getErrorMsg().c_str() );
//		BReturn = false;
//	}
//
//	return BReturn;
//}
//
//
//
////=================================================================================================
//void SystemContext::swapBuffers( void )
//{
//	// Multiple rendering buffers
//	if( m_pixelFormat.doubleBuffer() ) 
//	{
//		if( !m_pixelFormat.plane() ) 
//		{
//			if( !m_pixelFormat.hasOverlay() )
//			{
//				SwapBuffers( m_Hdc );
//			}
//			else // format has overlay
//			{
//				wglSwapLayerBuffers( m_Hdc, WGL_SWAP_MAIN_PLANE );
//			}
//		}
//		else // format has plane
//		{
//			wglSwapLayerBuffers( m_Hdc, WGL_SWAP_OVERLAY1 );
//		}
//	}
//
//	// Single rendering buffers
//	else
//	{
//		// Force OpenGL command termination
//		glFlush();
//		glFinish();
//
//#ifndef NDEBUG
//		if( !m_Hdc ) {
//			native_error_msg( "SystemContext::swapBuffers()", "HDC invalid \n" );
//		}
//#endif
//	}
//}
