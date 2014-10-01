
#pragma once
#ifndef __SYSTEM_CONTEXT_H__
#define __SYSTEM_CONTEXT_H__

#ifndef __NATIVE_TYPES_H__
#include "Native_types.h"
#endif

#ifndef __NATIVE_GLOBALMACRO_H__
#include "Native_GlobalMacro.h"
#endif

#ifndef __SYSTEM_PIXEL_FORMAT_H__
#include "SystemPixelFormat.h"
#endif


class SystemNode;
class SystemWindow;


/**
* @class SystemContext 
* 
* @brief describes Pixel Format and manages OpenGL context
*/
class SystemContext
{
	//////////////////////////////////////
	//			FRIEND CLASSES			//
	//////////////////////////////////////

	friend class SystemNode;
	friend class SystemNodeControl;


	//////////////////////////////////////
	//				DATAS				//
	//////////////////////////////////////

protected:
	static SystemContext*	m_current_context;

	SystemNode *			m_pNode;
	SystemContext *			m_SystemContextMaster;

	HGLRC					m_Hglrc;
	HDC						m_Hdc;
    HWND					m_Hwnd;

    int32_t					m_pixelFormatId;

	SystemPixelFormat		m_pixelFormat;


public:
	uint32_t				m_NodalId;
	bool					m_Sharing;
	bool					m_bValid;


	//////////////////////////////////////
	//				METHOD				//
	//////////////////////////////////////

	NATIVE_DISABLE_COPY(SystemContext)

private:
	/**
	* @brief convenience comparison function
	*/
	static bool logEq( bool a, bool b );


protected:
	/**
	* @brief choose available and compliant context properties
	* @param p_pShareContext parent context as SystemContext pointer (default to NULL)
	*/
	bool chooseContext( SystemContext * p_pShareContext=NULL );
	/**
	* @brief choose available pixel format, as close to desired options as possible depending on hardware
	* @param p_pPfd pixel format descriptor as void pointer
	* @return chosen pixel format ID as int32_t
	*/
	int32_t choosePixelFormat( void * p_pPfd );


	/**
	* @brief DC attached pixel format may change selected options, 
	* grab and stock updated values
	*/
	void updateFormatVersion( void );



public:
	/**
	* @brief SystemContext class constructor
	*/
    SystemContext( void );
	/**
	* @brief SystemContext class destructor
	*/
    virtual ~SystemContext( void );


	/**
	* @brief initialisation function
	* 
	* @param p_nodalId parent node ID as int32_t
	* @param p_pNode parent node as SystemNode pointer
	* @param p_pContextMaster master/parent context as SystemContext pointer (default to NULL)
	*
	* @return true on creation success (HDC + HGLRC), false otherwise
	* 
	* @note after calling that function context is current
	*/
	bool init( int32_t p_nodalId, SystemNode * p_pNode, SystemContext * p_pContextMaster=NULL );


	/**
	* @brief release HGLRC and HDC, nullify members
	*/
	void release( void );


	/**
	* @brief make context current/active
	* @note this should be atomic
	*/
    bool makeCurrent( void );
	/**
	* @brief release context activation
	* @note this should be atomic
	*/
    bool doneCurrent( void );
	/**
	* @brief terminate OpenGL operations and swap buffers if needed
	*/
	virtual void swapBuffers( void );


	/**
	* @brief stock current context as \a p_pContext
	*/
	static void set_current_context( SystemContext * p_pContext );
	/**
	* @brief return current context as SystemContext pointer
	*/
	static const SystemContext * get_current_context( void );
};

#endif // __SYSTEM_CONTEXT_H__
