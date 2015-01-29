
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
#include "eve/ogl/core/Shader.h"


//=================================================================================================
eve::ogl::FormatShader::FormatShader(void)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, vert()
	, cont()
	, eval()
	, geom()
	, frag()
{}

//=================================================================================================
eve::ogl::FormatShader::~FormatShader(void)
{}

//=================================================================================================
eve::ogl::FormatShader::FormatShader(const eve::ogl::FormatShader & p_other)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, vert(p_other.vert)
	, cont(p_other.cont)
	, eval(p_other.eval)
	, geom(p_other.geom)
	, frag(p_other.frag)
{}

//=================================================================================================
const eve::ogl::FormatShader & eve::ogl::FormatShader::operator = (const eve::ogl::FormatShader & p_other)
{
	if (this != &p_other)
	{
		this->vert	= p_other.vert;
		this->cont	= p_other.cont;
		this->eval	= p_other.eval;
		this->geom	= p_other.geom;
		this->frag	= p_other.frag;
	}
	return *this;
}



//=================================================================================================
eve::ogl::Shader::Shader(void)
	// Inheritance
	: eve::ogl::Object()
	// Members init
	, m_id(0)
	, m_prgmId(nullptr)
	, m_vert()
	, m_cont()
	, m_eval()
	, m_geom()
	, m_frag()
{}



//=================================================================================================
void eve::ogl::Shader::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatShader * format = reinterpret_cast<eve::ogl::FormatShader*>(p_format);

	m_vert = format->vert;
	m_cont = format->cont;
	m_eval = format->eval;
	m_geom = format->geom;
	m_frag = format->frag;
}



//=================================================================================================
void eve::ogl::Shader::init(void)
{
	// Set name array content to 0 to avoid OpenGL deletion issues.
	m_prgmId = (GLuint *)calloc(eve::ogl::prgm_Max, sizeof(GLuint));
}

//=================================================================================================
void eve::ogl::Shader::release(void)
{
	EVE_RELEASE_PTR_C(m_prgmId);
}



//=================================================================================================
void eve::ogl::Shader::oglInit(void)
{
	glGenProgramPipelines(1, &m_id);
	EVE_OGL_CHECK_ERROR;


	char const * src = nullptr;

	if (m_vert.length() > 1)
	{
		src = m_vert.c_str();
		m_prgmId[prgm_Vertex] = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &src);
		EVE_OGL_CHECK_SHADER(m_prgmId[eve::ogl::prgm_Vertex]);

		glUseProgramStages(m_id, GL_VERTEX_SHADER_BIT, m_prgmId[eve::ogl::prgm_Vertex]);
		EVE_OGL_CHECK_ERROR;
	}

	if (m_cont.length() > 1)
	{
		src = m_cont.c_str();
		m_prgmId[prgm_Control] = glCreateShaderProgramv(GL_TESS_CONTROL_SHADER, 1, &src);
		EVE_OGL_CHECK_SHADER(m_prgmId[eve::ogl::prgm_Control]);

		glUseProgramStages(m_id, GL_TESS_CONTROL_SHADER_BIT, m_prgmId[eve::ogl::prgm_Control]);
		EVE_OGL_CHECK_ERROR;
	}

	if (m_eval.length() > 1)
	{
		src = m_eval.c_str();
		m_prgmId[prgm_Evaluation] = glCreateShaderProgramv(GL_TESS_EVALUATION_SHADER, 1, &src);
		EVE_OGL_CHECK_SHADER(m_prgmId[eve::ogl::prgm_Evaluation]);

		glUseProgramStages(m_id, GL_TESS_EVALUATION_SHADER_BIT, m_prgmId[eve::ogl::prgm_Evaluation]);
		EVE_OGL_CHECK_ERROR;
	}

	if (m_geom.length() > 1)
	{
		src = m_geom.c_str();
		m_prgmId[prgm_Geometry] = glCreateShaderProgramv(GL_GEOMETRY_SHADER, 1, &src);
		EVE_OGL_CHECK_SHADER(m_prgmId[eve::ogl::prgm_Geometry]);

		glUseProgramStages(m_id, GL_GEOMETRY_SHADER_BIT, m_prgmId[eve::ogl::prgm_Geometry]);
		EVE_OGL_CHECK_ERROR;
	}

	if (m_frag.length() > 1)
	{
		src = m_frag.c_str();
		m_prgmId[prgm_Fragment] = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &src);
		EVE_OGL_CHECK_SHADER(m_prgmId[eve::ogl::prgm_Fragment]);

		glUseProgramStages(m_id, GL_FRAGMENT_SHADER_BIT, m_prgmId[eve::ogl::prgm_Fragment]);
		EVE_OGL_CHECK_ERROR;
	}
}

//=================================================================================================
void eve::ogl::Shader::oglUpdate(void)
{
	this->oglRelease();
	this->oglInit();
}

//=================================================================================================
void eve::ogl::Shader::oglRelease(void)
{
	glDeleteProgram(m_prgmId[eve::ogl::prgm_Vertex]);
	glDeleteProgram(m_prgmId[eve::ogl::prgm_Control]);
	glDeleteProgram(m_prgmId[eve::ogl::prgm_Evaluation]);
	glDeleteProgram(m_prgmId[eve::ogl::prgm_Geometry]);
	glDeleteProgram(m_prgmId[eve::ogl::prgm_Fragment]);
	EVE_OGL_CHECK_ERROR;

	glDeleteProgramPipelines(1, &m_id);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Shader::bind(void)
{
	glBindProgramPipeline(m_id);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Shader::unbind(void)
{
	glBindProgramPipeline(0);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Shader::reloadShaderVertex(const std::string & p_vert)
{
	EVE_ASSERT(p_vert.length() > 1);

	m_vert = std::string(p_vert);
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Shader::reloadShaderControl(const std::string & p_cont)
{
	EVE_ASSERT(p_cont.length() > 1);

	m_cont = std::string(p_cont);
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Shader::reloadShaderEvaluation(const std::string & p_eval)
{
	EVE_ASSERT(p_eval.length() > 1);

	m_eval = std::string(p_eval);
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Shader::reloadShaderGeometry(const std::string & p_geom)
{
	EVE_ASSERT(p_geom.length() > 1);

	m_geom = std::string(p_geom);
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Shader::reloadShaderFragment(const std::string & p_frag)
{
	EVE_ASSERT(p_frag.length() > 1);

	m_frag = std::string(p_frag);
	this->requestOglUpdate();
}



//=================================================================================================
void eve::ogl::Shader::reloadShader(const std::string & p_vert, const std::string & p_frag)
{
	EVE_ASSERT(p_vert.length() > 1);
	EVE_ASSERT(p_frag.length() > 1);

	m_vert = std::string(p_vert);
	m_frag = std::string(p_frag);
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Shader::reloadShader(const std::string & p_vert, const std::string & p_geom, const std::string & p_frag)
{
	EVE_ASSERT(p_vert.length() > 1);
	EVE_ASSERT(p_geom.length() > 1);
	EVE_ASSERT(p_frag.length() > 1);

	m_vert = std::string(p_vert);
	m_geom = std::string(p_geom);
	m_frag = std::string(p_frag);
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Shader::reloadShader(const std::string & p_vert, const std::string & p_cont, const std::string & p_eval, const std::string & p_geom, const std::string & p_frag)
{
	EVE_ASSERT(p_vert.length() > 1);
	EVE_ASSERT(p_cont.length() > 1);
	EVE_ASSERT(p_eval.length() > 1);
	EVE_ASSERT(p_geom.length() > 1);
	EVE_ASSERT(p_frag.length() > 1);

	m_vert = std::string(p_vert);
	m_cont = std::string(p_cont);
	m_eval = std::string(p_eval);
	m_geom = std::string(p_geom);
	m_frag = std::string(p_frag);
	this->requestOglUpdate();
}
