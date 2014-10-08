
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
#include "eve/ogl/Renderer.h"
#include "eve/sys/win32/Window.h"


class Example final
	: public eve::sys::View
{
	friend class eve::mem::Pointer;

private:
	eve::ogl::Renderer *		m_pRendererOpenGL;
	eve::ogl::Fbo *				fbo;
	eve::ogl::Texture *			tex;
	eve::ogl::Shader *			shader;


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
	virtual void cb_evtWindowClose(void) override;

};

void Example::initThreadedData(void)
{
	// Call parent class.
	eve::sys::View::initThreadedData();

	m_pRendererOpenGL = EVE_CREATE_PTR(eve::ogl::Renderer);
	this->registerRenderer(m_pRendererOpenGL);

	eve::ogl::FormatFBO fmtFbo;
	fmtFbo.width	= 800;
	fmtFbo.height	= 600;
	fbo = m_pRendererOpenGL->createFBO(fmtFbo);

	eve::ogl::FormatTex fmtTex;
	fmtTex.width	= 800;
	fmtTex.height	= 600;
	tex = m_pRendererOpenGL->createTexture(fmtTex);

	eve::ogl::FormatShader fmtShader;
	shader = m_pRendererOpenGL->createShader(fmtShader);
}

void Example::releaseThreadedData(void)
{
	shader->requestRelease();
	tex->requestRelease();
	fbo->requestRelease();
	this->releaseRenderer(m_pRendererOpenGL);

	// Call parent class.
	eve::sys::View::releaseThreadedData();
}

void Example::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{
	EVE_LOG_INFO("Mouse down received.");

	m_pWindow->toggleFullScreen();
}

void Example::cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
{
	EVE_LOG_INFO("Key down received.");

	if (p_args.key == eve::sys::key_Return)
	{
		Example * pView = EveApp->addView<Example>();
	}
	else if (p_args.key == eve::sys::key_Escape)
	{
		eve::evt::notify_application_exit();
	}
}

void Example::cb_evtWindowClose(void)
{
	EVE_LOG_INFO("Window close received.");

	eve::evt::notify_application_exit();
}


// Launch application for view "Example".
EVE_APPLICATION(Example);
