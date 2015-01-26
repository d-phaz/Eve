
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
#include "eve/io/Image.h"
#include "eve/sys/win32/Window.h"
#include "eve/time/Timer.h"

#ifndef __EVE_OPENGL_CORE_CONTEXT_H__
#include "eve/ogl/core/win32/Context.h"
#endif

#include "eve/ogl/core/ShaderManager.h"
#include "eve/ogl/Particule/ParticleManager.h"
#include "eve/ogl/Particule/Attractor.h"
#include "eve/ogl/Particule/RayCastAttractorUpdate.h"
#include "eve/ogl/Particule/IAttractorUpdate.h"

#define WORK_GROUP_SIZE 256


struct Vertex{
	eve::math::TVec4<float> pos;
};




class dataSwapper
{

	//////////////////////////////////////
	//				METHOD				//
	//////////////////////////////////////

	EVE_DISABLE_COPY(dataSwapper);
public:
	static dataSwapper * get_instance();
	static void release_instance();


	eve::ogl::Attractor<eve::math::TMatrix44<float>, eve::math::TVec4<float>, float> 	* m_attractor;
	eve::math::Cameraf *	m_pCamera;
	eve::math::TVec2<float> m_mouseInput;
	eve::time::Timer *  m_timer;

	double m_frameTimeDiff, m_time;

private:
	dataSwapper();
	~dataSwapper();

	static dataSwapper * m_singleton;
};

dataSwapper * dataSwapper::get_instance()
{
	if (!m_singleton)
	{
		m_singleton = new dataSwapper();
	}
	return m_singleton;
}

void dataSwapper::release_instance()
{
	if (m_singleton)
	{
		delete m_singleton;
		m_singleton = NULL;
	}

}

dataSwapper * dataSwapper::m_singleton = NULL;

dataSwapper::~dataSwapper()
{
	delete m_attractor;
	EVE_RELEASE_PTR(m_pCamera);
}

dataSwapper::dataSwapper()
	: m_mouseInput(0.0f, 0.0f)
	, m_attractor(nullptr)
	, m_pCamera(nullptr)
{

}


class RenderGL final
	: public eve::ogl::Renderer
{

	//////////////////////////////////////
	//				DATA				//
	//////////////////////////////////////


private:

	dataSwapper *									m_dataSwapper;
	eve::ogl::Uniform *								m_pUniform;
	eve::ogl::Texture *								m_pTexture;


	eve::ogl::ParticleManager	*					m_particleManager;
	eve::ogl::ShaderManager*						m_shaderManager;

	int												m_numParticles, m_iniRadius, m_frameCounter, m_fps;
	float											m_quadLength, m_velocityTranslate, m_velocityRotate;
	bool											m_useGravity, m_showFPS;
	double m_frameTimeDiffold;

	//////////////////////////////////////
	//				METHOD				//
	//////////////////////////////////////

	EVE_DISABLE_COPY(RenderGL);
	EVE_PUBLIC_DESTRUCTOR(RenderGL);

public:
	explicit RenderGL(void);


public:
	/** \brief Alloc and init class members. (pure virtual) */
	virtual void init(void) override;
	/** \brief Release and delete class members. (pure virtual) */
	virtual void release(void) override;


public:
	/** \brief Draw on screen callback. (pure virtual) */
	virtual void cb_display(void) override;

public:
	/** \brief Set render size. */
	virtual void setSize(uint32_t p_width, uint32_t p_height);

};


//=================================================================================================
RenderGL::RenderGL(void)
// Inheritance
: eve::ogl::Renderer()
// Members init
, m_pUniform(nullptr)
, m_dataSwapper(nullptr)
, m_numParticles(1000000)
, m_quadLength(0.01f)
, m_iniRadius(15)
, m_frameCounter(0)
, m_fps(0)
, m_velocityRotate(100.0f)
, m_useGravity(false)
, m_frameTimeDiffold(0.0)
, m_particleManager(new eve::ogl::ParticleManager())
{

}

//=================================================================================================
void RenderGL::init(void)
{
	// Call parent class.
	eve::ogl::Renderer::init();

	m_dataSwapper = dataSwapper::get_instance();
	m_dataSwapper->m_pCamera = eve::math::Cameraf::create_ptr(1920.0f, 1080.0f);
	m_dataSwapper->m_pCamera->setPerspective(60.0f, (float)1920.0f / (float)1080.0f, 5.f, 3000.0f);

	m_dataSwapper->m_pCamera->setFov(1000.0f);

	eve::ogl::RayCastAttractorUpdate * attUpdate = new eve::ogl::RayCastAttractorUpdate();
	attUpdate->initAttractor(1920.0f, 1080.0f, 45.0f, 1.f);
	m_dataSwapper->m_attractor = new eve::ogl::Attractor<eve::math::TMatrix44<float>, eve::math::TVec4<float>, float>(attUpdate);
	m_dataSwapper->m_attractor->setStrategy(attUpdate);

	m_particleManager->loadParticleBuffer(m_numParticles, m_iniRadius, this);

	eve::ogl::FormatShaderAdvanced fmtShaderAdv;

	fmtShaderAdv.loadShader("vertexShader", eve::io::load_program(eve::io::resource_path_glsl("Particule.vert")), GL_VERTEX_SHADER);
	fmtShaderAdv.loadShader("geometryShader", eve::io::load_program(eve::io::resource_path_glsl("Particule.geom")), GL_GEOMETRY_SHADER);
	fmtShaderAdv.loadShader("fragmentShader", eve::io::load_program(eve::io::resource_path_glsl("Particule.frag")), GL_FRAGMENT_SHADER);
	fmtShaderAdv.loadShader("computeShader", eve::io::load_program(eve::io::resource_path_glsl("Particule.comp")), GL_COMPUTE_SHADER);

	fmtShaderAdv.createProgram("shaderProg");
	fmtShaderAdv.createProgram("computeProg");

	fmtShaderAdv.attachShader("vertexShader", "shaderProg");
	fmtShaderAdv.attachShader("geometryShader", "shaderProg");
	fmtShaderAdv.attachShader("fragmentShader", "shaderProg");
	fmtShaderAdv.attachShader("computeShader", "computeProg");

	m_shaderManager = this->create(fmtShaderAdv);

	eve::ogl::FormatUniform fmtUniform;
	fmtUniform.blockSize = EVE_OGL_SIZEOF_MAT4;
	fmtUniform.dynamic = true;
	fmtUniform.data = m_dataSwapper->m_pCamera->getMatrixModelViewProjection().m;
	m_pUniform = this->create(fmtUniform);

	eve::ogl::FormatTex fmtTex;
	if (!eve::io::load_image(eve::io::resource_path_image("Particle.tga"), &fmtTex))
	{
		EVE_LOG_ERROR("Unable to load file %s", eve::io::resource_path_image("Particle.tga").c_str());
		EVE_ASSERT_FAILURE;
	}
	m_pTexture = this->create(fmtTex);

	m_dataSwapper->m_frameTimeDiff = 60;
	m_dataSwapper->m_time = 60;


}

//=================================================================================================
void RenderGL::release(void)
{

	m_pTexture->requestRelease();
	m_pUniform->requestRelease();
	delete m_particleManager;

	// Call parent class.
	eve::ogl::Renderer::release();
}

void RenderGL::setSize(uint32_t p_width, uint32_t p_height)
{
	// Call parent class.
	eve::ogl::Renderer::setSize(p_width, p_height);

	m_dataSwapper->m_pCamera->setDisplaySize(p_width, p_height);
}

//=================================================================================================
void RenderGL::cb_display(void)
{
	m_dataSwapper->m_frameTimeDiff = m_dataSwapper->m_timer->getDiffTimeDelta()/10.0f;
	m_dataSwapper->m_time = m_dataSwapper->m_timer->getDiffTime();


	glViewport(0, 0, 1920.0f, 1080.0f);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_pUniform->bind(1);

	m_pTexture->bind(0);


	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_particleManager->getId());
	m_shaderManager->useProgram("computeProg");

	m_particleManager->loadFloatUniform(
		m_shaderManager->getShaderProgramID("computeProg"),
		"frameTimeDiff",
		static_cast<float>(1 / m_dataSwapper->m_frameTimeDiff));

	m_particleManager->loadVec4Uniform(
		m_shaderManager->getShaderProgramID("computeProg"),
		"attPos",
		m_dataSwapper->m_attractor->getAttractorPos().x ,
		m_dataSwapper->m_attractor->getAttractorPos().y ,
		m_dataSwapper->m_attractor->getAttractorPos().z ,
		m_useGravity ? -1.0f : 1.0f); //Uses the last vector-entry to determine whether the attractor or the gravity is used ?

	m_particleManager->loadUintUniform(
		m_shaderManager->getShaderProgramID("computeProg"),
		"maxParticles",
		(GLuint)m_numParticles
		);

	glDispatchCompute((m_numParticles / WORK_GROUP_SIZE) + 1, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

	m_shaderManager->useProgram("shaderProg");

	m_particleManager->loadMatrix4Uniform(
		m_shaderManager->getShaderProgramID("shaderProg"),
		"viewMatrix",
		m_dataSwapper->m_pCamera->getMatrixModelView().m);

	m_particleManager->loadVec4Uniform(
		m_shaderManager->getShaderProgramID("shaderProg"),
		"camPos",
		m_dataSwapper->m_pCamera->getEyePointX(),
		m_dataSwapper->m_pCamera->getEyePointY(),
		m_dataSwapper->m_pCamera->getEyePointZ(),
		1.0f);

	m_particleManager->loadMatrix4Uniform(
		m_shaderManager->getShaderProgramID("shaderProg"),
		"projMatrix",
		m_dataSwapper->m_pCamera->getMatrixProjection().m);

	m_particleManager->loadFloatUniform(
		m_shaderManager->getShaderProgramID("shaderProg"),
		"quadLength",
		m_quadLength);

	m_particleManager->loadFloatUniform(
		m_shaderManager->getShaderProgramID("shaderProg"),
		"time",
		static_cast<float>(m_dataSwapper->m_time));


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleManager->getId());
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(eve::ogl::Particle), (GLvoid*)0);
	glDrawArrays(GL_POINTS, 0, m_numParticles);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	EVE_OGL_CHECK_ERROR;


	m_pTexture->unbind(0);

	m_pUniform->unbind(1);

	m_dataSwapper->m_attractor->updateAttractor(m_dataSwapper->m_pCamera, m_dataSwapper->m_mouseInput);


	if (m_dataSwapper->m_timer->getDiffTime() > 1000.0f)
	{
		m_dataSwapper->m_timer->restart();
	}

}



class Example final
	: public eve::ui::View
{

private:
	RenderGL * m_pRender;
	dataSwapper * m_dataSwapper;

	EVE_DISABLE_COPY(Example);
	EVE_PUBLIC_DESTRUCTOR(Example);

public:
	/** \brief class constructor. */
	explicit Example(void){};

public:
	/** \brief Setup format properties. (pure virtual) */
	virtual void setup(void);

private:
	/** \brief Alloc and init threaded data. (pure virtual) */
	virtual void initThreadedData(void) override;
	/** \brief Release and delete threaded data. (pure virtual) */
	virtual void releaseThreadedData(void) override;

	float											m_quadLength, m_velocityTranslate, m_velocityRotate;

public:
	virtual void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args) override;
	virtual void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args) override;
	virtual void cb_evtWindowClose(eve::evt::EventArgs & p_arg) override;

};

void Example::setup(void)
{
	// Call parent class.
	eve::ui::View::setup();

	m_format.x			= 50;
	m_format.y			= 50;
	m_format.width		= 800;
	m_format.height		= 600;
}

void Example::initThreadedData(void)
{
	// Call parent class.
	eve::ui::View::initThreadedData();

	m_velocityTranslate = 100.0f;
	m_dataSwapper = dataSwapper::get_instance();


	// Register new RenderGL.

	m_pRender = EVE_CREATE_PTR(RenderGL);
	this->registerRenderer(m_pRender);

	//m_pWindow->toggleFullScreen();
	m_pRender->setSize(m_pWindow->getWidth(), m_pWindow->getHeight());

}

void Example::releaseThreadedData(void)
{
	// Call parent class.
	eve::ui::View::releaseThreadedData();
}

void Example::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{

	switch (p_args.button)
	{
	case eve::sys::btn_WheelUp:
	{
		float resultFOV = m_dataSwapper->m_pCamera->getFov() - 1000.0f;
		if (resultFOV < 1000.0f)
		{
			resultFOV = m_dataSwapper->m_pCamera->getFov() - 100.0f;
			if (resultFOV < 100.0f)
			{
				resultFOV = m_dataSwapper->m_pCamera->getFov() - 10.0f;
				if (resultFOV < 10.0f)
				{
					resultFOV = m_dataSwapper->m_pCamera->getFov() - 1.0f;

					if (resultFOV < 1.0f)
					{
						resultFOV = m_dataSwapper->m_pCamera->getFov() - .1f;

						if (resultFOV < 0.10f)
						{
							resultFOV = m_dataSwapper->m_pCamera->getFov() - .01f;

							if (resultFOV < 0.01f)
								resultFOV = 0.01f;
						}
					}
				}
			}
		}

		m_dataSwapper->m_pCamera->setFov(resultFOV);
		break;
	}

	case eve::sys::btn_WheelDown:
	{
		float resultFOV = m_dataSwapper->m_pCamera->getFov() + 1000.0f;
		if (m_dataSwapper->m_pCamera->getFov() < 100000.0f)
		{
			resultFOV = m_dataSwapper->m_pCamera->getFov() + 1000.0f;

			if (m_dataSwapper->m_pCamera->getFov() < 1000.0f)
			{
				resultFOV = m_dataSwapper->m_pCamera->getFov() + 100.0f;

				if (m_dataSwapper->m_pCamera->getFov() < 10.0f)
				{
					resultFOV = m_dataSwapper->m_pCamera->getFov() + 1.0f;

					if (m_dataSwapper->m_pCamera->getFov() < 1.0f)
					{
						resultFOV = m_dataSwapper->m_pCamera->getFov() + 0.1f;
					}
				}
			}
		}


		m_dataSwapper->m_pCamera->setFov(resultFOV);
		break;
	}

	case eve::sys::btn_Left:
	{
		m_dataSwapper->m_mouseInput = eve::math::TVec2<float>(p_args.x, p_args.y);
		break;
	}
	case eve::sys::btn_Middle:
	{
		m_dataSwapper->m_pCamera->rotateX(1.0f * p_args.x * m_velocityTranslate);
		m_dataSwapper->m_pCamera->rotateY(1.0f * p_args.y * m_velocityTranslate);
		break;
	}
	}
}

void Example::cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
{
	if (p_args.key == eve::sys::key_Escape)
	{
		eve::evt::notify_application_exit();
	}
	if (p_args.key == eve::sys::key_Up)
	{
		m_dataSwapper->m_attractor->incrementDepth(1.0f);
	}
	if (p_args.key == eve::sys::key_Down)
	{
		m_dataSwapper->m_attractor->incrementDepth(-1.0f);
	}
	if (p_args.key == eve::sys::key_S)
	{
		m_dataSwapper->m_pCamera->translateZ(1.0f * m_velocityTranslate * m_dataSwapper->m_frameTimeDiff);
	}
	if (p_args.key == eve::sys::key_W)
	{
		m_dataSwapper->m_pCamera->translateZ(-1.0f * m_velocityTranslate * m_dataSwapper->m_frameTimeDiff);
	}
}

void Example::cb_evtWindowClose(eve::evt::EventArgs & p_arg)
{
	eve::evt::notify_application_exit();
}

class Application final
	: public eve::app::App
{
public:
	dataSwapper * m_dataSwapper;
	/** \brief Launch application main loop. */
	virtual void runApp(void);

};

//=================================================================================================
void Application::runApp(void)
{
	m_bRunning = true;;
	m_dataSwapper = dataSwapper::get_instance();
	m_dataSwapper->m_timer = m_p_timer;

	m_p_semaphore->lock();

	EVE_LOG_INFO("Exiting application main loop.");
	this->release();

	dataSwapper::release_instance();
}


// Launch application for view "Example".
EVE_APPLICATION_CUSTOM(Example, Application);
