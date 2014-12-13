
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
#include "eve/ogl/core/Renderer.h"
#include "eve/sys/win32/Window.h"
#include "eve/time/Absolute.h"
#include "eve/time/Clock.h"

class Example final
	: public eve::sys::View
{
	friend class eve::mem::Pointer;

private:
	eve::ogl::Renderer *		renderer;

	eve::ogl::Fbo *				fbo;
	eve::ogl::Pbo *				pbo;
	eve::ogl::Texture *			tex;
	eve::ogl::Shader *			shader;
	eve::ogl::Vao *				vao;

	eve::time::Timer *			m_pTimer;
	eve::time::Clock *			m_pClock;

	float *						m_vec4;


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
	virtual void cb_evtWindowClose(eve::evt::EventArgs & p_arg) override;

public:
	void cb_evtClock(void);

};

void Example::initThreadedData(void)
{
	// Call parent class.
	eve::sys::View::initThreadedData();

	renderer = EVE_CREATE_PTR(eve::ogl::Renderer);
	this->registerRenderer(renderer);

	eve::ogl::FormatFbo fmtFbo;
	fmtFbo.width	= 800;
	fmtFbo.height	= 600;
	fbo = renderer->create(fmtFbo);

	eve::ogl::FormatPbo fmtPbo;
	fmtPbo.width		= 800;
	fmtPbo.height		= 600;
	fmtPbo.numChannels	= 4;
	pbo = renderer->create(fmtPbo);

	eve::ogl::FormatTex fmtTex;
	fmtTex.width	= 800;
	fmtTex.height	= 600;
	tex = renderer->create(fmtTex);

	eve::ogl::FormatShader fmtShader;
	shader = renderer->create(fmtShader);

	eve::ogl::FormatVao fmtVao = eve::geom::create_cube_colored(eve::vec3f::zero(), eve::vec3f::one(), eve::color4f::red());
	vao = renderer->create(fmtVao);


	//m_pTimer = EVE_CREATE_PTR(eve::time::Timer);
	m_pTimer = eve::time::Timer::create_ptr(true);

	m_pClock = EVE_CREATE_PTR(eve::time::Clock);
	m_pClock->registerListener(this);
	m_pClock->setRunWait(5);
	m_pClock->setPeriodicInterval(10);
	//m_pClock->start();

	m_vec4 = (float*)eve::mem::align_malloc(sizeof(float)* 4, 16);
	EVE_ASSERT(m_vec4);

	eve::vec4i_t vec { 1, 3, 9, 27 };
	EVE_LOG_INFO("eve::vec4i_t[3] : %d", vec[3]);

	eve::vec4f v(0.0F, 1.0F, 2.0f, 3.0f);
	EVE_LOG_INFO("Vec4f.z : %f", v.z);

	eve::mat22f mat22(0.0f);
	eve::mat33f mat33(0.0f);
	eve::mat44f mat44(0.0f);

	eve::math::Cameraf * cam = eve::math::Cameraf::create_ptr();
	EVE_RELEASE_PTR(cam);
}

void Example::releaseThreadedData(void)
{
	eve::mem::align_free(m_vec4);

	EVE_RELEASE_PTR(m_pClock);
	EVE_RELEASE_PTR(m_pTimer);

	shader->requestRelease(); 
	tex->requestRelease();
	pbo->requestRelease();
	fbo->requestRelease();
	vao->requestRelease();
	this->releaseRenderer(renderer);

	// Call parent class.
	eve::sys::View::releaseThreadedData();
}

void Example::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{
	EVE_LOG_INFO("Mouse down received, x:%d y:%d.", p_args.x, p_args.y);
	EVE_LOG_TIME;

	if (m_pTimer->isRunning())
	{
		//m_pTimer->stop();
		EVE_LOG_INFO("Timer elapsed time: %d", m_pTimer->getElapsedTime());
		EVE_LOG_INFO("%d ms since application startup.", p_args.time);
	}
	else {
		m_pTimer->start();
	}

	//m_pWindow->toggleFullScreen();

}

void Example::cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
{
	EVE_LOG_INFO("Key down received, %d ms application run.", p_args.time);

	if (p_args.key == eve::sys::key_Return)
	{
		Example * pView = EveApp->addView<Example>();
	}
	else if (p_args.key == eve::sys::key_Escape)
	{
		eve::evt::notify_application_exit();
	}
}

void Example::cb_evtWindowClose(eve::evt::EventArgs & p_arg)
{
	EVE_LOG_INFO("Window close received.");

	eve::evt::notify_application_exit();
}

void Example::cb_evtClock(void)
{
	EVE_LOG_INFO("Clock event triggered, interval is %d.", m_pTimer->getElapsedTime());
	m_pTimer->restart();
}


// Launch application for view "Example".
EVE_APPLICATION(Example);
