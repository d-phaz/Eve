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
//// Main header
//#include "SystemPixelFormat.h"
//
//// OpenGL header
//#ifndef __OGL_EXTERNAL_H__
//#include "gl/OGLExternal.h"
//#endif
//
//#ifndef __GL_UTILITIES_H__
//#include "gl/Utilities.h"
//#endif
//
//// System header
//#ifndef __SYSTEM_CONTEXT_H__
//#include "SystemContext.h"
//#endif
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
////		Static
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//static bool opengl32dll = false;	//<! convenience driver awakening boolean
//
//SystemPixelFormat SystemPixelFormat::m_default_format = SystemPixelFormat(); //<! Default pixel format
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
////		SystemPixelFormat class
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
////=================================================================================================
//SystemPixelFormat::SystemPixelFormat( void )
//
//	// Members initialization
//	: m_opts				( (DirectRendering | Rgba | DepthBuffer | StencilBuffer | NoDeprecatedFunctions) )
//    , m_pln					(  0 )
//    , m_depthSize			( 24 )
//	, m_accumSize			( -1 )
//	, m_stencilSize			( -1 )
//	, m_redSize				(  8 ) 
//	, m_greenSize			(  8 )
//	, m_blueSize			(  8 ) 
//	, m_alphaSize			(  8 )
//    , m_numSamples			( -1 )
//    , m_swapInterval		( -1 )
//    , m_majorVersion		( REQUIRED_OPENGL_MAJOR_VERSION )
//    , m_minorVersion		( REQUIRED_OPENGL_MINOR_VERSION )
//    , m_profile				( CoreProfile )
//{}
//
////=================================================================================================
//SystemPixelFormat::SystemPixelFormat( const SystemPixelFormat & p_parent )
//
//	// Members init
//	: m_opts			( p_parent.m_opts )
//    , m_pln				( p_parent.m_pln )
//    , m_depthSize		( p_parent.m_depthSize )
//	, m_accumSize		( p_parent.m_accumSize )
//	, m_stencilSize		( p_parent.m_stencilSize )
//	, m_redSize			( p_parent.m_redSize )
//	, m_greenSize		( p_parent.m_greenSize )
//	, m_blueSize		( p_parent.m_blueSize )
//	, m_alphaSize		( p_parent.m_alphaSize )
//    , m_numSamples		( p_parent.m_numSamples )
//    , m_swapInterval	( p_parent.m_swapInterval )
//    , m_majorVersion	( p_parent.m_majorVersion )
//    , m_minorVersion	( p_parent.m_minorVersion )
//    , m_profile			( p_parent.m_profile )
//{}
//
////=================================================================================================
//SystemPixelFormat::~SystemPixelFormat( void )
//{}
//
//
//
////=================================================================================================
//SystemPixelFormat & SystemPixelFormat::operator=( const SystemPixelFormat & p_parent )
//{
//	m_opts			= p_parent.m_opts;
//    m_pln			= p_parent.m_pln;
//    m_depthSize		= p_parent.m_depthSize;
//	m_accumSize		= p_parent.m_accumSize;
//	m_stencilSize	= p_parent.m_stencilSize;
//	m_redSize		= p_parent.m_redSize;
//	m_greenSize		= p_parent.m_greenSize;
//	m_blueSize		= p_parent.m_blueSize;
//	m_alphaSize		= p_parent.m_alphaSize;
//    m_numSamples	= p_parent.m_numSamples;
//    m_swapInterval	= p_parent.m_swapInterval;
//    m_majorVersion	= p_parent.m_majorVersion;
//    m_minorVersion	= p_parent.m_minorVersion;
//    m_profile		= p_parent.m_profile;
//
//	return *this;
//}
//
//
//
//
////=================================================================================================
//void SystemPixelFormat::init( FormatOptions p_options, int32_t p_plane )
//{
//	FormatOptions newOpts = p_options;
//	m_opts = SystemPixelFormat::default_format().m_opts;
//    m_opts |= (newOpts & 0xffff);
//    m_opts &= ~(newOpts >> 16);
//    m_pln = p_plane;
//}
//
//
//
////=================================================================================================
//SystemPixelFormat SystemPixelFormat::pfdToSystemPixelFormat( const PIXELFORMATDESCRIPTOR* _pfd )
//{
//    SystemPixelFormat fmt;
//
//	// Double buffering
//    fmt.setDoubleBuffer( _pfd->dwFlags & PFD_DOUBLEBUFFER);
//    
//	// Depth 
//	fmt.setDepth( (_pfd->cDepthBits>0) );
//    if( fmt.depth() ) {
//        fmt.setDepthBufferSize( _pfd->cDepthBits );
//	}
//
//	// RGBA 
//    fmt.setRgba( _pfd->iPixelType == PFD_TYPE_RGBA );
//    fmt.setRedBufferSize( _pfd->cRedBits );
//    fmt.setGreenBufferSize( _pfd->cGreenBits );
//    fmt.setBlueBufferSize( _pfd->cBlueBits );
//    fmt.setAlpha( (_pfd->cAlphaBits>0) );
//
//    if( fmt.alpha() ) {
//        fmt.setAlphaBufferSize(_pfd->cAlphaBits);
//	}
//
//
//    fmt.setAccum( (_pfd->cAccumBits>0) );
//    if( fmt.accum() ) {
//        fmt.setAccumBufferSize( _pfd->cAccumRedBits );
//	}
//
//    fmt.setStencil( (_pfd->cStencilBits>0) );
//    if( fmt.stencil() ) {
//        fmt.setStencilBufferSize( _pfd->cStencilBits );
//	}
//
//    fmt.setStereo( _pfd->dwFlags & PFD_STEREO );
//
//    fmt.setDirectRendering( (_pfd->dwFlags & PFD_GENERIC_ACCELERATED) || !(_pfd->dwFlags & PFD_GENERIC_FORMAT) );
//
//    fmt.setOverlay( (_pfd->bReserved & 0x0f) != 0 );
//
//    return fmt;
//}
//
////=================================================================================================
//PIXELFORMATDESCRIPTOR * SystemPixelFormat::systemPixelFormatToPfd( const SystemPixelFormat * p_sysPixelFormat )
//{
//	// Pixel format descriptor
//	PIXELFORMATDESCRIPTOR * Ptr_Return = (PIXELFORMATDESCRIPTOR*)malloc( sizeof(PIXELFORMATDESCRIPTOR) );
//	memset(Ptr_Return, 0, sizeof(PIXELFORMATDESCRIPTOR));
//
//	Ptr_Return->nSize = sizeof(PIXELFORMATDESCRIPTOR);
//	Ptr_Return->nVersion = 1;
//
//	// Draw flags
//	Ptr_Return->dwFlags  = PFD_SUPPORT_OPENGL;
//	//p->dwFlags |= PFD_DRAW_TO_BITMAP;
//	Ptr_Return->dwFlags |= PFD_DRAW_TO_WINDOW;
//
//	// Direct Rendering
//	if ( !p_sysPixelFormat->directRendering() ) {
//		Ptr_Return->dwFlags |= PFD_GENERIC_FORMAT;
//	}
//
//	// Double Buffering
//	if ( p_sysPixelFormat->doubleBuffer() ) {
//		Ptr_Return->dwFlags |= PFD_DOUBLEBUFFER;
//	}
//
//	// Stereo
//	if( p_sysPixelFormat->stereo() ) {
//		Ptr_Return->dwFlags |= PFD_STEREO;
//	}
//
//	// Depth
//	if( p_sysPixelFormat->depth() ) {
//		Ptr_Return->cDepthBits = (p_sysPixelFormat->depthBufferSize() == -1 ? 32 : p_sysPixelFormat->depthBufferSize());
//	}
//	else {
//		Ptr_Return->dwFlags |= PFD_DEPTH_DONTCARE;
//	}
//
//
//	// RGBA
//	if( p_sysPixelFormat->rgba() ) 
//	{
//		Ptr_Return->iPixelType = PFD_TYPE_RGBA;
//
//		if (p_sysPixelFormat->redBufferSize() != -1)
//			Ptr_Return->cRedBits = p_sysPixelFormat->redBufferSize();
//		if (p_sysPixelFormat->greenBufferSize() != -1)
//			Ptr_Return->cGreenBits = p_sysPixelFormat->greenBufferSize();
//		if (p_sysPixelFormat->blueBufferSize() != -1)
//			Ptr_Return->cBlueBits = p_sysPixelFormat->blueBufferSize();
//
//		Ptr_Return->cColorBits = 32;
//	} 
//	else 
//	{
//		Ptr_Return->iPixelType = PFD_TYPE_COLORINDEX;
//		Ptr_Return->cColorBits = 8;
//	}
//
//	// Alpha
//	if( p_sysPixelFormat->alpha() ) {
//		Ptr_Return->cAlphaBits = p_sysPixelFormat->alphaBufferSize() == -1 ? 8 : p_sysPixelFormat->alphaBufferSize();
//	}
//
//	// Accum buffer
//	if (p_sysPixelFormat->accum()) 
//	{
//		BYTE value = (p_sysPixelFormat->accumBufferSize() == -1 ? 16 : p_sysPixelFormat->accumBufferSize());
//		Ptr_Return->cAccumRedBits = Ptr_Return->cAccumGreenBits = Ptr_Return->cAccumBlueBits = Ptr_Return->cAccumAlphaBits = value;
//	}
//
//	// Stencil
//	if( p_sysPixelFormat->stencil() ) {
//		Ptr_Return->cStencilBits = (p_sysPixelFormat->stencilBufferSize() == -1 ? 8 : p_sysPixelFormat->stencilBufferSize());
//	}
//
//	// iLayerType is ignored, backward compatibility only
//	Ptr_Return->iLayerType = PFD_MAIN_PLANE;
//
//	return Ptr_Return;
//}
//
//
//
////=================================================================================================
//SystemPixelFormat SystemPixelFormat::pfiToSystemPixelFormat( HDC hdc, int32_t pfi )
//{
//	// Return value
//    SystemPixelFormat fmt;
//
//	// Attributes
//    int32_t * iAttributes = (int32_t*)malloc( sizeof(int32_t)*14 );
//	memset( iAttributes, 0, sizeof(int32_t)*14 );
//
//    int32_t * iValues = (int32_t*)malloc( sizeof(int32_t) * 14 );
//	memset( iValues, 0, sizeof(int32_t)*14 );
//
//	// Inc
//    int32_t i = 0;
//
//    bool has_sample_buffers = false; //GLExtensions::glExtensions() & GLExtensions::SampleBuffers;
//
//    iAttributes[ i++ ] = WGL_DOUBLE_BUFFER_ARB;		// 0
//    iAttributes[ i++ ] = WGL_DEPTH_BITS_ARB;		// 1
//    iAttributes[ i++ ] = WGL_PIXEL_TYPE_ARB;		// 2
//    iAttributes[ i++ ] = WGL_RED_BITS_ARB;			// 3
//    iAttributes[ i++ ] = WGL_GREEN_BITS_ARB;		// 4
//    iAttributes[ i++ ] = WGL_BLUE_BITS_ARB;			// 5
//    iAttributes[ i++ ] = WGL_ALPHA_BITS_ARB;		// 6
//    iAttributes[ i++ ] = WGL_ACCUM_BITS_ARB;		// 7
//    iAttributes[ i++ ] = WGL_STENCIL_BITS_ARB;		// 8
//    iAttributes[ i++ ] = WGL_STEREO_ARB;			// 9
//    iAttributes[ i++ ] = WGL_ACCELERATION_ARB;		// 10
//    iAttributes[ i++ ] = WGL_NUMBER_OVERLAYS_ARB;	// 11
//
//    if( has_sample_buffers ) 
//	{
//        iAttributes[i++] = WGL_SAMPLE_BUFFERS_ARB;	// 12
//        iAttributes[i++] = WGL_SAMPLES_ARB;			// 13
//    }
//
//	//  Prototype for wglGetPixelFormatAttribivARB()
//	//typedef BOOL (WINAPI* PFNWGLGETPIXELFORMATATTRIBIVARBPROC)(HDC hdc,int iPixelFormat,int iLayerPlane,UINT nAttributes,const int *piAttributes,int *piValues);
//	//PFNWGLGETPIXELFORMATATTRIBIVARBPROC cb_wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)wglGetProcAddress("wglGetPixelFormatAttribivARB");
//
//	// It seems we have a hard time to retrieve "wglGetPixelFormatAttribivARB" callback !!!
//
//    if( wglGetPixelFormatAttribivARB && wglGetPixelFormatAttribivARB( hdc, pfi, 0, i, iAttributes, iValues) )
//    {
//        fmt.setDoubleBuffer( iValues[0] );
//        fmt.setDepth( iValues[1] );
//
//        if( fmt.depth() ) {
//            fmt.setDepthBufferSize(iValues[1]);
//		}
//
//        fmt.setRgba(iValues[2] == WGL_TYPE_RGBA_ARB);
//        fmt.setRedBufferSize(iValues[3]);
//        fmt.setGreenBufferSize(iValues[4]);
//        fmt.setBlueBufferSize(iValues[5]);
//        fmt.setAlpha(iValues[6]);
//        if (fmt.alpha())
//            fmt.setAlphaBufferSize(iValues[6]);
//
//        fmt.setAccum(iValues[7]);
//        if (fmt.accum())
//            fmt.setAccumBufferSize(iValues[7]);
//
//        fmt.setStencil(iValues[8]);
//        if (fmt.stencil())
//            fmt.setStencilBufferSize(iValues[8]);
//
//        fmt.setStereo(iValues[9]);
//
//        if (iValues[10] == WGL_FULL_ACCELERATION_ARB)
//            fmt.setDirectRendering(true);
//        else
//            fmt.setDirectRendering(false);
//
//        fmt.setOverlay(iValues[11]);
//
//        if( has_sample_buffers ) 
//		{
//            fmt.setSampleBuffers(iValues[12]);
//            if (fmt.sampleBuffers())
//                fmt.setSamples(iValues[13]);
//        }
//    }
//
//	// Free memory
//	free( iAttributes );
//	free( iValues );
//
//    return fmt;
//}
//
//
//
////=================================================================================================
//bool SystemPixelFormat::hasOpenGLOverlays( void )
//{
//    // workaround for matrox driver:
//    // make a cheap call to opengl to force loading of DLL
//    if( !opengl32dll ) 
//	{
//        GLint params;
//        glGetIntegerv(GL_DEPTH_BITS, &params);
//        opengl32dll = true;
//    }
//
//    static bool hasOl = false;
//
//
//	// Check once by Pixel Format
//	static bool checkDone = false;
//    if( !checkDone ) 
//	{
//        checkDone = true;
//
//        HDC display_dc = ::GetDC(0);
//        
//		int32_t pfiMax = ::DescribePixelFormat(display_dc, 0, 0, NULL);
//        
//		PIXELFORMATDESCRIPTOR pfd;
//        for (int32_t pfi = 1; pfi <= pfiMax; pfi++) 
//		{
//            ::DescribePixelFormat( display_dc, pfi, sizeof(PIXELFORMATDESCRIPTOR), &pfd );
//
//            if( (pfd.bReserved & 0x0f) && (pfd.dwFlags & PFD_SUPPORT_OPENGL) ) 
//			{
//                // format has overlays/underlays
//                LAYERPLANEDESCRIPTOR lpd;
//                ::wglDescribeLayerPlane( display_dc, pfi, 1, sizeof(LAYERPLANEDESCRIPTOR), &lpd );
//
//                if( lpd.dwFlags & LPD_SUPPORT_OPENGL ) 
//				{
//                    hasOl = true;
//                    break;
//                }
//            }
//        }
//        ::ReleaseDC( NULL, display_dc );
//    }
//
//    return hasOl;
//}
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
////		GET / SET
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
////=================================================================================================
//SystemPixelFormat SystemPixelFormat::default_format( void )
//{
//	return m_default_format;
//}
//
////=================================================================================================
//void SystemPixelFormat::set_default_format( const SystemPixelFormat & p_format )
//{
//	m_default_format = p_format;
//}
//
//
//
////=================================================================================================
//void SystemPixelFormat::setDepthBufferSize( int32_t p_size )
//{
//    if( p_size > 0 ) 
//	{
//		m_depthSize = p_size;
//		this->setDepth( (p_size>0) );
//    }
//}
//
////=================================================================================================
//void SystemPixelFormat::setRedBufferSize( int32_t p_size )
//{
//    if( p_size > 0 ) {
//		m_redSize = p_size;
//    }
//}
//
////=================================================================================================
//void SystemPixelFormat::setGreenBufferSize( int32_t p_size )
//{
//    if( p_size > 0 ) {
//		m_greenSize = p_size;
//    }
//}
//
////=================================================================================================
//void SystemPixelFormat::setBlueBufferSize( int32_t p_size )
//{
//	if( p_size > 0 ) {
//        m_blueSize = p_size;
//    }
//}
//
////=================================================================================================
//void SystemPixelFormat::setAlphaBufferSize( int32_t p_size )
//{
//    if( p_size > 0 ) 
//	{
//		m_alphaSize = p_size;
//		setAlpha( (p_size>0) );
//    }
//    
//}
//
////=================================================================================================
//void SystemPixelFormat::setAccumBufferSize( int32_t p_size )
//{
//    if( p_size > 0 )
//	{
//		m_accumSize = p_size;
//		this->setAccum( (p_size>0) );
//    }
//    
//}
//
////=================================================================================================
//void SystemPixelFormat::setStencilBufferSize( int32_t p_size)
//{
//    if( p_size > 0 )
//	{
//		m_stencilSize = p_size;
//		this->setStencil( p_size > 0 );
//    }
//    
//}
//
//
//
////=================================================================================================
//void SystemPixelFormat::setDoubleBuffer( bool p_enable )
//{
//	if( p_enable != this->doubleBuffer() ) {
//		this->setOption( p_enable ? DoubleBuffer : SingleBuffer );
//	}
//}
//
////=================================================================================================
//void SystemPixelFormat::setDepth( bool p_enable )
//{
//	if( p_enable != this->depth() ) {
//		this->setOption( p_enable ? DepthBuffer : NoDepthBuffer );
//	}
//}
//
////=================================================================================================
//void SystemPixelFormat::setRgba(bool p_enable)
//{
//	if( p_enable != this->rgba() ) {
//		this->setOption( p_enable ? Rgba : ColorIndex );
//	}
//}
//
////=================================================================================================
//void SystemPixelFormat::setAlpha( bool p_enable )
//{
//	if( p_enable != this->alpha() ) {
//		this->setOption( p_enable ? AlphaChannel : NoAlphaChannel );
//	}
//}
//
////=================================================================================================
//void SystemPixelFormat::setAccum(bool p_enable)
//{
//	if( p_enable != this->accum() ) {
//		this->setOption(p_enable ? AccumBuffer : NoAccumBuffer);
//	}
//}
//
////=================================================================================================
//void SystemPixelFormat::setStencil(bool p_enable)
//{
//	if( p_enable != this->stencil() ) {
//		this->setOption(p_enable ? StencilBuffer: NoStencilBuffer);
//	}
//}
//
////=================================================================================================
//void SystemPixelFormat::setStereo(bool p_enable)
//{
//	if( p_enable != this->stereo() ) {
//		this->setOption(p_enable ? StereoBuffers : NoStereoBuffers);
//	}
//}
//
////=================================================================================================
//void SystemPixelFormat::setDirectRendering(bool p_enable)
//{
//	if( p_enable != this->directRendering() ) {
//		this->setOption(p_enable ? DirectRendering : IndirectRendering);
//	}
//}
//
////=================================================================================================
//void SystemPixelFormat::setSampleBuffers(bool p_enable)
//{
//	if( p_enable != this->sampleBuffers() ) {
//		this->setOption(p_enable ? SampleBuffers : NoSampleBuffers);
//	}
//}
//
////=================================================================================================
//void SystemPixelFormat::setSamples( int32_t p_numSamples )
//{
//    if( p_numSamples > 0 && p_numSamples != m_numSamples ) 
//	{
//        m_numSamples = p_numSamples;
//		this->setSampleBuffers( (p_numSamples > 0) );
//    }
//    
//}
//
////=================================================================================================
//void SystemPixelFormat::setSwapInterval( int32_t p_interval )
//{
//    m_swapInterval = p_interval;
//}
//
////=================================================================================================
//void SystemPixelFormat::setOverlay( bool p_enable )
//{
//	if( p_enable != this->hasOpenGLOverlays() ) {
//		this->setOption( p_enable ? HasOverlay : NoOverlay );
//	}
//}
//
////=================================================================================================
//void SystemPixelFormat::setPlane( int32_t p_plane )
//{
//    m_pln = p_plane;
//}
//
//
//
////=================================================================================================
//void SystemPixelFormat::setOption( FormatOptions p_opt )
//{
//	FormatOptions options_on = p_opt & 0xffff;
//    if( options_on ) {
//        m_opts |= options_on;
//	}
//    else {
//       m_opts &= (~(p_opt >> 16)) & 0xffff;
//	}
//}
//
////=================================================================================================
//bool SystemPixelFormat::testOption(FormatOptions p_opt) const
//{
//	bool B_Return;
//	FormatOptions options_on = p_opt & 0xffff;
//    if( options_on ) {
//       B_Return = (m_opts & options_on) != 0;
//	}
//    else {
//       B_Return = (m_opts & ((p_opt >> 16) & 0xffff) ) == 0;
//	}
//
//	return B_Return;
//}
//
////=================================================================================================
//void SystemPixelFormat::setVersion( int32_t p_major, int32_t p_minor )
//{
//    if( p_major > 1 && p_minor > 0 )
//	{
//		m_majorVersion = p_major;
//		m_minorVersion = p_minor;
//    }
//}
//
////=================================================================================================
//void SystemPixelFormat::setProfile( OpenGLContextProfile p_profile )
//{
//    //detach();
//    m_profile = p_profile;
//}
//
////=================================================================================================
//SystemPixelFormat::OpenGLContextProfile SystemPixelFormat::profile( void ) const
//{
//    return m_profile;
//}
