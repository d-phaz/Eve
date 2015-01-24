
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
#ifndef __EVE_OPENGL_CORE_PIXEL_FORMAT_H__
#define __EVE_OPENGL_CORE_PIXEL_FORMAT_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_CORE_FLAGS_H__
#include "eve/core/Flags.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


namespace eve
{
	namespace ogl
	{
		/** 
		* \def eve::ogl::PixelFormatOption
		* \brief OpenGL Pixel format options.
		* Options are tested and used if available in the graphic driver(s).
		*/
		enum PixelFormatOption
		{
			pf_optDoubleBuffer			= 0x0001,
			pf_optDepthBuffer			= 0x0002,
			pf_optRgba					= 0x0004,
			pf_optAlphaChannel			= 0x0008,
			pf_optAccumBuffer			= 0x0010,
			pf_optStencilBuffer			= 0x0020,
			pf_optStereoBuffers			= 0x0040,
			pf_optDirectRendering		= 0x0080,
			pf_optHasOverlay			= 0x0100,
			pf_optSampleBuffers			= 0x0200,
			pf_optDeprecatedFunctions	= 0x0400,

			pf_optSingleBuffer			= pf_optDoubleBuffer		<< 16,
			pf_optNoDepthBuffer			= pf_optDepthBuffer			<< 16,
			pf_optColorIndex			= pf_optRgba				<< 16,
			pf_optNoAlphaChannel		= pf_optAlphaChannel		<< 16,
			pf_optNoAccumBuffer			= pf_optAccumBuffer			<< 16,
			pf_optNoStencilBuffer		= pf_optStencilBuffer		<< 16,
			pf_optNoStereoBuffers		= pf_optStereoBuffers		<< 16,
			pf_optIndirectRendering		= pf_optDirectRendering		<< 16,
			pf_optNoOverlay				= pf_optHasOverlay			<< 16,
			pf_optNoSampleBuffers		= pf_optSampleBuffers		<< 16,
			pf_optNoDeprecatedFunctions = pf_optDeprecatedFunctions << 16
		};

		/** 
		* \def eve::ogl::FormatOptions
		* \brief OpenGL pixel format options flag.
		*/
		typedef eve::core::CustomFlags<eve::ogl::PixelFormatOption> FormatOptions;
		EVE_DECLARE_OPERATORS_FOR_FLAGS(FormatOptions);


		/*!
		* \def eve::ogl::PixelFormatProfile
		*
		* \brief This enum describes the OpenGL context profiles that can be
		* specified for contexts implementing OpenGL version 3.2 or higher. 
		* These profiles are different from OpenGL ES profiles.
		*
		* \value pf_profNoProfile            OpenGL version is lower than 3.2.
		* \value pf_profCoreProfile          Functionality deprecated in OpenGL version 3.0 is not available.
		* \value pf_profCompatibilityProfile Functionality from earlier OpenGL versions is available.
		*/
		enum PixelFormatProfile
		{
			pf_profNoProfile,
			pf_profCoreProfile,
			pf_profCompatibilityProfile
		};


		/** 
		* \class eve::ogl::PixelFormat
		*
		* \brief Pixel format and options used to create OpenGL context.
		*/
		class PixelFormat
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			static PixelFormat				m_default_format;		//<! Default pixel format.

		public:
			FormatOptions					m_opts;					//!< Format options.
			int32_t							m_pln;					//!< Format plane.
			int32_t							m_depthSize;			//!< Depth buffer size.
			int32_t							m_accumSize;			//!< Accumulation buffer size. 
			int32_t							m_stencilSize;			//!< Stencil buffer size.
			int32_t							m_redSize;				//!< Red buffer size.
			int32_t							m_greenSize;			//!< Green buffer size.
			int32_t							m_blueSize;				//!< Blue buffer size.
			int32_t							m_alphaSize;			//!< Alpha buffer size.
			int32_t							m_numSamples;			//!< Per pixel sample number.
			int32_t							m_swapInterval;			//!< Swap intarval.
			int32_t							m_majorVersion;			//!< Requested OpenGL major version (first digit).
			int32_t							m_minorVersion;			//!< Requested OpenGL minor version (second digit).
			eve::ogl::PixelFormatProfile	m_profile;				//!< Requested OpenGL profile.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			/** \brief Class constructor. */
			PixelFormat(void);
			/** \brief Class copy constructor. */
			PixelFormat(const PixelFormat & p_parent);
			/** \brief Class destructor. */
			virtual ~PixelFormat(void);

			/** \brief Assignment operator (copy values from p_parent). */
			PixelFormat &operator=(const PixelFormat & p_parent);


		public:
			/** \brief Comparison operator '==' (are format the same?). */
			friend bool operator==(const PixelFormat& p_formatFirst, const PixelFormat& p_formatSecond);
			/** \brief Comparison operator '!=' (are format different?). */
			friend bool operator!=(const PixelFormat& p_formatFirst, const PixelFormat& p_formatSecond);


		public:
			/**
			* \brief Creates a PixelFormat object that is a copy of the current defaultFormat.
			*
			* If \a p_options is not 0, the default format is modified by the specified format options. 
			* The \a p_options parameter should be eve::ogl::FormatOption values OR'ed together.
			*
			* The \a p_plane parameter defaults to 0 and is the plane which this format should be associated with. 
			* Not all OpenGL implementations supports overlay/underlay rendering planes.
			*/
			void init(FormatOptions p_options, int32_t p_plane = 0);


		public:
			/**
			* \brief Convert system PIXELFORMATDESCRIPTOR to eve::ogl::PixelFormat.
			* \param p_pfd Win32 pixel format descriptor as PIXELFORMATDESCRIPTOR pointer.
			* \return usable pixel format as eve::ogl::PixelFormat.
			*/
			static PixelFormat pfdToPixelFormat(const PIXELFORMATDESCRIPTOR * p_pfd);
			/**
			* \brief convert system PixelFormat to PIXELFORMATDESCRIPTOR.
			* \param p_pPixelFormat pixel format as eve::ogl::PixelFormat pointer.
			* \return usable Win32 pixel format descriptor as PIXELFORMATDESCRIPTOR pointer.
			*/
			static PIXELFORMATDESCRIPTOR pixelFormatToPfd(const PixelFormat * p_pPixelFormat);
			/**
			* \brief Convert pixel format to eve::ogl::PixelFormat (identified by id)
			* \param p_hdc draw context as HDC.
			* \param p_pfi pixel format ID as int32_t.
			* \return usable pixel format as eve::ogl::PixelFormat.
			*/
			static PixelFormat pfiToSystemPixelFormat(HDC p_hdc, int32_t p_pfi);

			
		public:
			/**
			* \brief Choose available pixel format, as close to desired options as possible depending on hardware
			* \param p_hdc draw context as HDC.
			* \param p_pPfd pixel format descriptor as PIXELFORMATDESCRIPTOR pointer.
			* \param p_in_out_PixelFormat desired pixel format as eve::ogl::PixelFormat, updated if not all options are available.
			* \return Chosen pixel format ID as int32_t.
			*/
			static int32_t choose_pixel_format(HDC p_hdc, PIXELFORMATDESCRIPTOR p_pPfd, eve::ogl::PixelFormat * p_in_out_PixelFormat);


		public:
			/** \brief Test if current OpenGL implementations supports overlay/underlay rendering planes. */
			static bool hasOverlays(void);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get default pixel format as eve::ogl::PixelFormat. */
			static const eve::ogl::PixelFormat & default_format(void);
			/** \brief Set default pixel format to \a p_format. */
			static void set_default_format(const PixelFormat & p_format);


		public:
			/** \brief Set minimum depth buffer size to \a p_size. */
			void setDepthBufferSize(int32_t p_size);
			/** \brief Get depth buffer size. */
			const int32_t  depthBufferSize(void) const;


		public:
			/** \brief Set red buffer size to \a p_size. */
			void setRedBufferSize(int32_t p_size);
			/** \brief Get red buffer size. */
			const int32_t  redBufferSize(void) const;


		public:
			/** \brief Set green buffer size to \a p_size. */
			void setGreenBufferSize(int32_t p_size);
			/** \brief Get green buffer size. */
			const int32_t  greenBufferSize(void) const;


		public:
			/** \brief Set blue buffer size to \a p_size. */
			void setBlueBufferSize(int32_t p_size);
			/** \brief Get blue buffer size. */
			const int32_t  blueBufferSize(void) const;


		public:
			/**
			* \brief Set alpha buffer size to \a p_size.
			* This function implicitly enables the alpha channel.
			*/
			void setAlphaBufferSize(int32_t p_size);
			/** \brief Get alpha buffer size. */
			const int32_t  alphaBufferSize(void) const;


		public:
			/** \brief Set accumulation buffer size, where \a p_size is the bit depth for each RGBA component. */
			void setAccumBufferSize(int32_t p_size);
			/** \brief Get accumulation buffer size. */
			const int32_t  accumBufferSize(void) const;


		public:
			/** \brief Set stencil buffer size to \a p_size. */
			void setStencilBufferSize(int32_t p_size);
			/** \brief Get stencil buffer size.	*/
			const int32_t  stencilBufferSize(void) const;


		public:
			/**
			* \brief Returns true if double buffering is enabled; otherwise returns false.
			* Double buffering is enabled by default.
			*/
			const bool doubleBuffer(void) const;
			/**
			* \brief If \a p_enable is true sets double buffering; otherwise sets single buffering.
			*
			* Double buffering is enabled by default.
			*
			* Double buffering is a technique where graphics are rendered on an off-screen buffer and not directly to the screen. 
			* When the drawing has been completed, the program calls a swapBuffers() function to exchange the screen contents with the buffer. 
			* The result is flicker-free drawing and often better performance.
			*
			* Note that single buffered contexts are currently not supported with EGL.
			*/
			void setDoubleBuffer(bool p_enable);


		public:
			/**
			* \brief Returns true if the depth buffer is enabled; otherwise returns false.
			* The depth buffer is enabled by default.
			*/
			const bool depth(void) const;
			/**
			* \brief If \a p_enable is true enables the depth buffer; otherwise disables the depth buffer.
			*
			* The depth buffer is enabled by default.
			*
			* The purpose of a depth buffer (or Z-buffering) is to remove hidden surfaces. 
			* Pixels are assigned Z values based on the distance to the viewer. 
			* A pixel with a high Z value is closer to the viewer than a pixel with a low Z value. 
			* This information is used to decide whether to draw a pixel or not.
			*/
			void setDepth(bool p_enable);


		public:
			/**
			* \brief Returns true if RGBA color mode is set. Returns false if color index mode is set.
			* The default color mode is RGBA.
			*/
			const bool rgba(void) const;
			/**
			* \brief If \a p_enable is true sets RGBA mode. If \a p_enable is false sets color index mode.
			*
			* The default color mode is RGBA.
			*
			* RGBA is the preferred mode for most OpenGL applications. 
			* In RGBA color mode you specify colors as red + green + blue + alpha quadruplets.
			*
			* In color index mode you specify an index into a color lookup table.
			*/
			void setRgba(bool p_enable);


		public:
			/**
			* \brief Returns true if alpha buffer is set, false otherwise.
			* Alpha is set by default.
			*/
			const bool alpha(void) const;
			/**
			* \brief If \a p_enable is true enables the alpha buffer; otherwise disables the alpha buffer.
			*
			* The alpha buffer is disabled by default.
			*
			* The alpha buffer is typically used for implementing transparency or translucency. 
			* The A in RGBA specifies the transparency of a pixel.
			*/
			void setAlpha(bool p_enable);


		public:
			/**
			* \brief Returns true if the accumulation buffer is enabled; otherwise returns false.
			* The accumulation buffer is disabled by default.
			*/
			const bool accum(void) const;
			/*
			* \brief If \a p_enable is true enables the accumulation buffer; otherwise disables the accumulation buffer.
			*
			* The accumulation buffer is disabled by default.
			*
			* The accumulation buffer is used to create blur effects and multiple exposures.
			*/
			void setAccum(bool p_enable);


		public:
			/**
			* \brief Returns true if the stencil buffer is enabled; otherwise returns false.
			* The stencil buffer is enabled by default.
			*/
			const bool stencil(void) const;
			/**
			* \brief If \a p_enable is true enables the stencil buffer; otherwise disables the stencil buffer.
			*
			* The stencil buffer is enabled by default.
			*
			* The stencil buffer masks certain parts of the drawing area so that masked parts are not drawn on.
			*/
			void setStencil(bool p_enable);


		public:
			/**
			* \brief Returns true if stereo buffering is enabled; otherwise returns false.
			* Stereo buffering is disabled by default.
			*/
			const bool stereo(void) const;
			/*
			* \brief If \a p_enable is true enables stereo buffering; otherwise disables stereo buffering.
			*
			* Stereo buffering is disabled by default.
			*
			* Stereo buffering provides extra color buffers to generate left-eye and right-eye images.
			*/
			void setStereo(bool p_enable);


		public:
			/**
			* \brief Returns true if direct rendering is enabled; otherwise returns false.
			* Direct rendering is enabled by default.
			*/
			const bool directRendering(void) const;
			/*
			* \brief If \a p_enable is true enables direct rendering; otherwise disables direct rendering.
			*
			* Direct rendering is enabled by default.
			*
			* Enabling this option will make OpenGL bypass the underlying window system and render directly from hardware to the screen, 
			* if this is supported by the system.
			*/
			void setDirectRendering(bool p_enable);


		public:
			/**
			* \brief If \a p_enable is true, a GL context with multisample buffer support is picked; otherwise ignored.
			*/
			const bool sampleBuffers(void) const;
			/**
			* \brief Returns true if multisample buffer support is enabled; otherwise returns false.
			* The multi-sample buffer is disabled by default.
			*/
			void setSampleBuffers(bool p_enable);


		public:
			/**
			* \brief  Returns true if overlay plane is enabled; otherwise returns false.
			* Overlay is disabled by default.
			*/
			const bool hasOverlay(void) const;
			/**
			* \brief If \a p_enable is true enables an overlay plane; otherwise disables the overlay plane.
			*
			* Enabling the overlay plane will cause QGLWidget to create an additional context in an overlay plane.
			*/
			void setOverlay(bool p_enable);


		public:
			/**
			* \brief Returns the number of samples per pixel when multi-sampling is enabled. 
			* By default, the highest number of samples that is available is used.
			*/
			const int32_t samples(void) const;
			/**
			* \brief Set the preferred number of samples per pixel when multi-sampling is enabled to \a p_numSamples. 
			* By default, the highest number of samples available is used.
			*/
			void setSamples(int32_t p_numSamples);


		public:
			/**
			* \brief Returns the currently set swap interval. -1 is returned if setting
			* the swap interval isn't supported in the system GL implementation.
			*/
			const int32_t  swapInterval(void) const;
			/**
			* \brief Set the preferred swap interval. This can be used to sync the GL
			* drawing into a system window to the vertical refresh of the screen.
			* Setting an \a p_interval value of 0 will turn the vertical refresh syncing
			* off, any value higher than 0 will turn the vertical syncing on.
			*
			* Under Windows and under X11, where the \c{WGL_EXT_swap_control}
			* and \c{GLX_SGI_video_sync} extensions are used, the \a p_interval
			* parameter can be used to set the minimum number of video frames
			* that are displayed before a buffer swap will occur. In effect,
			* setting the \a p_interval to 10, means there will be 10 vertical
			* retraces between every buffer swap.
			*
			* Under Windows the \c{WGL_EXT_swap_control} extension has to be present,
			* and under X11 the \c{GLX_SGI_video_sync} extension has to be present.
			*/
			void setSwapInterval(int32_t p_interval);


		public:
			/**
			* \brief Returns the plane of this format. The default for normal formats is 0, which means the normal plane. 
			* The default for overlay formats is 1, which is the first overlay plane.
			*/
			const int32_t plane(void) const;
			/**
			* \brief Sets the requested plane to \a p_plane. 
			* 0 is the normal plane, 
			* 1 is the first overlay plane, 
			* 2 is the second overlay plane, etc.; 
			* -1, -2, etc. are underlay planes.
			*/
			void setPlane(int32_t p_plane);


		public:
			/** \brief Sets the format option to \a p_opt. (convenience method) */
			void setOption(eve::ogl::FormatOptions p_opt);
			/** \brief Returns true if format option \a p_opt is set, false otherwise. */
			bool testOption(eve::ogl::FormatOptions p_opt) const;
			

		public:
			/**
			* \brief Set the OpenGL version to the \a p_major and \a p_minor numbers. 
			* If a context compatible with the requested OpenGL version cannot be created, 
			* a context compatible with version 1.x is created instead.
			*/
			void setVersion(int32_t p_major, int32_t p_minor);


		public:
			/** \brief Set the OpenGL context profile to \a p_profile. */
			void setProfile(eve::ogl::PixelFormatProfile p_profile);
			/** \brief Get the OpenGL context profile as eve::ogl::PixelFormatProfile. */
			eve::ogl::PixelFormatProfile profile(void) const;

		}; // PixelFormat

	} // namespace ogl

} // namespace eve

//=================================================================================================
EVE_FORCE_INLINE const eve::ogl::PixelFormat & eve::ogl::PixelFormat::default_format(void) { return m_default_format; }



//=================================================================================================
EVE_FORCE_INLINE const int32_t eve::ogl::PixelFormat::depthBufferSize(void) const		{ return m_depthSize;		}
EVE_FORCE_INLINE const int32_t eve::ogl::PixelFormat::redBufferSize(void) const			{ return m_redSize;			}
EVE_FORCE_INLINE const int32_t eve::ogl::PixelFormat::greenBufferSize(void) const		{ return m_greenSize;		}
EVE_FORCE_INLINE const int32_t eve::ogl::PixelFormat::blueBufferSize(void) const		{ return m_blueSize;		}
EVE_FORCE_INLINE const int32_t eve::ogl::PixelFormat::alphaBufferSize(void) const		{ return m_alphaSize;		}
EVE_FORCE_INLINE const int32_t eve::ogl::PixelFormat::accumBufferSize(void) const		{ return m_accumSize;		}
EVE_FORCE_INLINE const int32_t eve::ogl::PixelFormat::stencilBufferSize(void) const		{ return m_stencilSize;		}



//=================================================================================================
EVE_FORCE_INLINE const bool eve::ogl::PixelFormat::doubleBuffer(void) const			{ return this->testOption(pf_optDoubleBuffer);		}
EVE_FORCE_INLINE const bool eve::ogl::PixelFormat::depth(void) const				{ return this->testOption(pf_optDepthBuffer);		}
EVE_FORCE_INLINE const bool eve::ogl::PixelFormat::rgba(void) const					{ return this->testOption(pf_optRgba);				}
EVE_FORCE_INLINE const bool eve::ogl::PixelFormat::alpha(void) const				{ return this->testOption(pf_optAlphaChannel);		}
EVE_FORCE_INLINE const bool eve::ogl::PixelFormat::accum(void) const				{ return this->testOption(pf_optAccumBuffer);		}
EVE_FORCE_INLINE const bool eve::ogl::PixelFormat::stencil(void) const				{ return this->testOption(pf_optStencilBuffer);		}
EVE_FORCE_INLINE const bool eve::ogl::PixelFormat::stereo(void) const				{ return this->testOption(pf_optStereoBuffers);		}
EVE_FORCE_INLINE const bool eve::ogl::PixelFormat::directRendering(void) const		{ return this->testOption(pf_optDirectRendering);	}
EVE_FORCE_INLINE const bool eve::ogl::PixelFormat::sampleBuffers(void) const		{ return this->testOption(pf_optSampleBuffers);		}
EVE_FORCE_INLINE const bool eve::ogl::PixelFormat::hasOverlay(void) const			{ return this->testOption(pf_optHasOverlay);			}



//=================================================================================================
EVE_FORCE_INLINE const int32_t eve::ogl::PixelFormat::samples(void) const			{ return m_numSamples;		}
EVE_FORCE_INLINE const int32_t eve::ogl::PixelFormat::swapInterval(void) const		{ return m_swapInterval;	}
EVE_FORCE_INLINE const int32_t eve::ogl::PixelFormat::plane(void) const				{ return m_pln;				}



//=================================================================================================
EVE_FORCE_INLINE eve::ogl::PixelFormatProfile eve::ogl::PixelFormat::profile(void) const { return m_profile; }

#endif // __EVE_OPENGL_CORE_PIXEL_FORMAT_H__
