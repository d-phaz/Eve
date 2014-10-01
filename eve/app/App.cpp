
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

// Main header
#include "eve/app/App.h"


eve::app::App *	eve::app::App::m_p_instance = nullptr;

//=================================================================================================
eve::app::App * eve::app::App::create_instance(void)
{
	EVE_ASSERT(!m_p_instance);

	m_p_instance = new eve::app::App();
	m_p_instance->init();
	return m_p_instance;
}

//=================================================================================================
void eve::app::App::release_instance(void)
{
	EVE_ASSERT(m_p_instance);
	EVE_RELEASE_PTR(m_p_instance);
}



//=================================================================================================
eve::app::App::App(void)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_bRunning(false)
	, m_pVecViews(nullptr)
	, m_pFence(nullptr)
{}



//=================================================================================================
void eve::app::App::init(void)
{
	// Messaging server (log).
	eve::mess::Server::create_instance();

	// Win32 COM
#if defined(EVE_OS_WIN)
	HRESULT rtn = ::CoInitializeEx(NULL, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE | COINIT_SPEED_OVER_MEMORY);
	if (!SUCCEEDED(rtn)) {
		EVE_LOG_ERROR("Can't initialize Win32 COM CoInitializeEx() failed.");
	}
#endif

	// View container.
	m_pVecViews = new std::vector<eve::sys::View*>();
	// Fence.
	m_pFence	= EVE_CREATE_PTR(eve::thr::SpinLock);

	// Register to application events.
	eve::evt::register_events_application(this);
}

//=================================================================================================
void eve::app::App::release(void)
{
	// Unregister from application events.
	eve::evt::unregister_events_application(this);

	// View container.
	eve::sys::View * view = nullptr;
	while (!m_pVecViews->empty())
	{
		view = m_pVecViews->back();
		m_pVecViews->pop_back();

		EVE_RELEASE_PTR(view);
	}
	EVE_RELEASE_PTR_CPP(m_pVecViews);

	// Fence.
	EVE_RELEASE_PTR(m_pFence);

	// Release Win32 COM.
#if defined(EVE_OS_WIN)
	::CoUninitialize();
#endif


	// Messaging server (log).
	eve::mess::Server::release_instance();
}



//=================================================================================================
void eve::app::App::runApp(void)
{
	m_bRunning = true;

	do 
	{
		::Sleep(30);
	} while (m_bRunning);
	
	EVE_LOG_INFO("Exiting application main loop.");
}



//=================================================================================================
bool eve::app::App::removeView(eve::sys::View * p_pView)
{
	m_pFence->lock();

	std::vector<eve::sys::View*>::iterator itr = std::find(m_pVecViews->begin(), m_pVecViews->end(), p_pView);
	bool breturn = (itr != m_pVecViews->end());
	if (breturn)
	{
		eve::sys::View * view = (*itr);
		m_pVecViews->erase(itr);
		EVE_RELEASE_PTR(view);
	}
	
	m_pFence->unlock();

	return breturn;
}



//=================================================================================================
void eve::app::App::cb_evtApplicationExit(void)
{
	m_bRunning = false;
}
