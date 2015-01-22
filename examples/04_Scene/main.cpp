
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

#include "eve/app/App.h"
#include "eve/math/Includes.h"
#include "eve/io/Image.h"
#include "eve/ogl/core/Renderer.h"
#include "eve/sys/win32/Window.h"

#include "eve/scene/Scene.h"


class Example final
	: public eve::sys::View
{
	friend class eve::mem::Pointer;

private:
	eve::scene::Scene * m_pScene;


	EVE_DISABLE_COPY(Example);
	EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(Example);

private:
	/** \brief Alloc and init threaded data. (pure virtual) */
	virtual void initThreadedData(void) override;
	/** \brief Release and delete threaded data. (pure virtual) */
	virtual void releaseThreadedData(void) override;

public:
	virtual void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args) override;
	virtual void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args) override;
	virtual void cb_evtTextInput(eve::evt::TextEventArgs & p_args) override;
	virtual void cb_evtWindowClose(eve::evt::EventArgs & p_arg) override;

};

void Example::initThreadedData(void)
{
	// Call parent class.
	eve::sys::View::initThreadedData();

	// Register new RenderGL.
	m_pScene = EVE_CREATE_PTR(eve::scene::Scene);
	std::wstring path(EVE_TXT("C:\\Users\\aleister_doe\\Desktop\\import\\untitled_spot.dae"));
	m_pScene->loadFromFilePath(path);
	this->registerRenderer(m_pScene);
}

void Example::releaseThreadedData(void)
{
	// Call parent class.
	eve::sys::View::releaseThreadedData();
}

void Example::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{
	//m_pWindow->toggleFullScreen();
	//m_pRender->setSize(m_pWindow->getWidth(), m_pWindow->getHeight());
}

void Example::cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
{
	EVE_LOG_INFO("Pressed key: %d ctrl: %d   alt: %d   shift: %d"
				, p_args.key
				, eve::sys::modifier_crtl(p_args.modifier)
				, eve::sys::modifier_alt(p_args.modifier)
				, eve::sys::modifier_shift(p_args.modifier));

	if (p_args.key == eve::sys::key_Escape
	 || p_args.key == eve::sys::key_Q && eve::sys::modifier_crtl(p_args.modifier))
	{
		eve::evt::notify_application_exit();
	}
}

void Example::cb_evtTextInput(eve::evt::TextEventArgs & p_args)
{
	wchar_t txt[2];
	txt[0] = p_args.text;
	txt[1] = EVE_TXT('\0');
	EVE_LOG_INFO("Pressed key: %s", txt);
}

void Example::cb_evtWindowClose(eve::evt::EventArgs & p_arg)
{
	eve::evt::notify_application_exit();
}


// Launch application for view "Example".
EVE_APPLICATION(Example);
