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
//#pragma once
//#ifndef __EVE_OPENGL_CONTEXT_H__
//#define __EVE_OPENGL_CONTEXT_H__
//
//#ifndef __EVE_CORE_INCLUDES_H__
//#include "eve/core/Includes.h"
//#endif
//
//#ifndef __EVE_MEMORY_INCLUDES_H__
//#include "eve/mem/Includes.h"
//#endif
//
//#ifndef __EVE_MESSAGING_INCLUDES_H__
//#include "eve/mess/Includes.h"
//#endif
//
//
//namespace eve
//{
//	namespace gl
//	{
//		/** 
//		* \class eve::gl::Context
//		*
//		* \brief OpenGL master context.
//		* Create and manage rendering context (GLRC) based on available pixel format.
//		*
//		* \note extends mem::Pointer
//		*/
//		class Context final
//			: public eve::mem::Pointer
//		{
//
//			friend class eve::mem::Pointer;
//
//			//////////////////////////////////////
//			//				DATA				//
//			//////////////////////////////////////
//
//		private:
//			static eve::gl::Context *		m_p_instance;			//<! Class unique instance.
//			
//			HGLRC							m_hGLRC;				//!< OpenGL rendering context handle.
//			HDC								m_hDC;					//!< Draw context (linked to window) handle.
//
//			int32_t							m_pixelFormatId;		//!< Pixel format ID.
//
//
//			//////////////////////////////////////
//			//				METHOD				//
//			//////////////////////////////////////
//
//			EVE_DISABLE_COPY(Context);
//			EVE_PROTECT_DESTRUCTOR(Context);
//
//
//		public:
//			/** \brief Create unique instance. */
//			static eve::gl::Context * create_instance(void);
//			/** \brief Get unique instance. */
//			static eve::gl::Context * get_instance(void);
//			/** \brief Release unique instance */
//			static void release_instance(void);
//
//
//		private:
//			/** \brief Class constructor. */
//			Context(void);
//
//
//		private:
//			/** \brief Alloc and init class members. (pure virtual) */
//			virtual void init(void) override;
//			/**
//			* \brief Release and delete class members. (pure virtual)
//			* Stop this object's thread execution (if any) immediately.
//			*/
//			virtual void release(void) override;
//
//
//		private:
//			/** \brief Choose available and compliant context properties. */
//			bool chooseContext(void);
//			/** 
//			* \brief Choose available pixel format, as close to desired options as possible depending on hardware
//			* \param p_pPfd pixel format descriptor as void pointer.
//			* \return Chosen pixel format ID as int32_t.
//			*/
//			int32_t choosePixelFormat(void * p_pPfd);
//
//			/** \brief DC attached pixel format may change selected options, grab and stock updated values. */
//			void updateFormatVersion(void);
//
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			//		GET / SET
//			///////////////////////////////////////////////////////////////////////////////////////
//
//		public:
//			/** \brief Get OpenGL rendering context handle. */
//			const HGLRC getHandle(void);
//
//		}; // class Context
//
//	} // namespace gl
//
//} // namespace eve
//
//
///** \def EveContextGL: Convenience macro to access OpenGL context instance. */
//#define EveContextGL	eve::gl::Context::get_instance()
//
//
////=================================================================================================
//inline const HGLRC eve::gl::Context::getHandle(void)	{ return m_hGLRC; }
//
//
//
//namespace eve
//{
//	namespace gl
//	{
//		/**
//		* \class eve::gl::SubContext
//		*
//		* \brief OpenGL window binded context linked to master context (aka eve::gl::Context).
//		*
//		* \note extends mem::Pointer
//		*/
//		class SubContext final
//			: public eve::mem::Pointer
//		{
//
//			friend class eve::mem::Pointer;
//
//			//////////////////////////////////////
//			//				DATA				//
//			//////////////////////////////////////
//
//		private:
//			static eve::gl::SubContext *		m_p_context_current;		//<! Current OpenGL context.
//
//		private:
//			HDC									m_hDC;						//!< Draw context (linked to window) handle.
//			HWND								m_hWnd;						//!< Window handle.
//
//
//			//////////////////////////////////////
//			//				METHOD				//
//			//////////////////////////////////////
//
//			EVE_DISABLE_COPY(SubContext);
//			EVE_PROTECT_DESTRUCTOR(SubContext);
//
//
//		private:
//			/** \brief Class constructor. */
//			SubContext(void);
//
//
//		private:
//			/** \brief Alloc and init class members. (pure virtual) */
//			virtual void init(void) override;
//			/**
//			* \brief Release and delete class members. (pure virtual)
//			* Stop this object's thread execution (if any) immediately.
//			*/
//			virtual void release(void) override;
//
//
//		public:
//			/** 
//			* \brief Make context current (aka active). 
//			* \note Only 1 context can be current at a time.
//			*/
//			bool makeCurrent(void);
//			/** \brief Release context activation. */
//			bool doneCurrent(void);
//			/** \brief Terminate OpenGL operations and swap buffers if multiple buffers are in use.	*/
//			void swapBuffers(void);
//
//
//		private:
//			/** \brief Stock current context. */
//			static void set_current_context(eve::gl::SubContext * p_pContext);
//			/** \brief Get current context. */
//			static const eve::gl::SubContext * get_current_context(void);
//
//		}; // class SubContext
//
//	} // namespace gl
//
//} // namespace eve
//
//
//
//#endif // __EVE_OPENGL_CONTEXT_H__
//
//
//#ifndef __NATIVE_TYPES_H__
//#include "Native_types.h"
//#endif
//
//#ifndef __NATIVE_GLOBALMACRO_H__
//#include "Native_GlobalMacro.h"
//#endif
//
//#ifndef __SYSTEM_PIXEL_FORMAT_H__
//#include "SystemPixelFormat.h"
//#endif
//
//
//class SystemNode;
//class SystemWindow;
//
//
///**
//* @class SystemContext 
//* 
//* @brief describes Pixel Format and manages OpenGL context
//*/
//class SystemContext
//{
//	//////////////////////////////////////
//	//			FRIEND CLASSES			//
//	//////////////////////////////////////
//
//	friend class SystemNode;
//	friend class SystemNodeControl;
//
//
//	//////////////////////////////////////
//	//				DATAS				//
//	//////////////////////////////////////
//
//protected:
//	static SystemContext*	m_current_context;
//
//	SystemNode *			m_pNode;
//	SystemContext *			m_SystemContextMaster;
//
//	HGLRC					m_Hglrc;
//	HDC						m_Hdc;
//    HWND					m_Hwnd;
//
//    int32_t					m_pixelFormatId;
//
//	SystemPixelFormat		m_pixelFormat;
//
//
//public:
//	uint32_t				m_NodalId;
//	bool					m_Sharing;
//	bool					m_bValid;
//
//
//	//////////////////////////////////////
//	//				METHOD				//
//	//////////////////////////////////////
//
//	NATIVE_DISABLE_COPY(SystemContext)
//
//private:
//	/**
//	* @brief convenience comparison function
//	*/
//	static bool logEq( bool a, bool b );
//
//
//protected:
//	/**
//	* @brief choose available and compliant context properties
//	* @param p_pShareContext parent context as SystemContext pointer (default to NULL)
//	*/
//	bool chooseContext( SystemContext * p_pShareContext=NULL );
//	/**
//	* @brief choose available pixel format, as close to desired options as possible depending on hardware
//	* @param p_pPfd pixel format descriptor as void pointer
//	* @return chosen pixel format ID as int32_t
//	*/
//	int32_t choosePixelFormat( void * p_pPfd );
//
//
//	/**
//	* @brief DC attached pixel format may change selected options, 
//	* grab and stock updated values
//	*/
//	void updateFormatVersion( void );
//
//
//
//public:
//	/**
//	* @brief SystemContext class constructor
//	*/
//    SystemContext( void );
//	/**
//	* @brief SystemContext class destructor
//	*/
//    virtual ~SystemContext( void );
//
//
//	/**
//	* @brief initialisation function
//	* 
//	* @param p_nodalId parent node ID as int32_t
//	* @param p_pNode parent node as SystemNode pointer
//	* @param p_pContextMaster master/parent context as SystemContext pointer (default to NULL)
//	*
//	* @return true on creation success (HDC + HGLRC), false otherwise
//	* 
//	* @note after calling that function context is current
//	*/
//	bool init( int32_t p_nodalId, SystemNode * p_pNode, SystemContext * p_pContextMaster=NULL );
//
//
//	/**
//	* @brief release HGLRC and HDC, nullify members
//	*/
//	void release( void );
//
//
//	/**
//	* @brief make context current/active
//	* @note this should be atomic
//	*/
//    bool makeCurrent( void );
//	/**
//	* @brief release context activation
//	* @note this should be atomic
//	*/
//    bool doneCurrent( void );
//	/**
//	* @brief terminate OpenGL operations and swap buffers if needed
//	*/
//	virtual void swapBuffers( void );
//
//
//	/**
//	* @brief stock current context as \a p_pContext
//	*/
//	static void set_current_context( SystemContext * p_pContext );
//	/**
//	* @brief return current context as SystemContext pointer
//	*/
//	static const SystemContext * get_current_context( void );
//};
//
//#endif // __SYSTEM_CONTEXT_H__
