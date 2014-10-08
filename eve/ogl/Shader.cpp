
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
#include "eve/ogl/Shader.h"


//=================================================================================================
eve::ogl::FormatShader::FormatShader(void)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, vertex()
	, control()
	, eval()
	, geom()
	, fragment()
{}

//=================================================================================================
eve::ogl::FormatShader::~FormatShader(void)
{}

//=================================================================================================
eve::ogl::FormatShader::FormatShader(const eve::ogl::FormatShader & p_other)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, vertex(p_other.vertex)
	, control(p_other.control)
	, eval(p_other.eval)
	, geom(p_other.geom)
	, fragment(p_other.fragment)
{}

//=================================================================================================
const eve::ogl::FormatShader & eve::ogl::FormatShader::operator = (const eve::ogl::FormatShader & p_other)
{
	if (this != &p_other)
	{
		this->vertex	= p_other.vertex;
		this->control	= p_other.control;
		this->eval		= p_other.eval;
		this->geom		= p_other.geom;
		this->fragment	= p_other.fragment;
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
	, m_vertex()
	, m_control()
	, m_eval()
	, m_geom()
	, m_fragment()
{}



//=================================================================================================
void eve::ogl::Shader::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatShader * format = reinterpret_cast<eve::ogl::FormatShader*>(p_format);

	m_vertex	= format->vertex;
	m_control	= format->control;
	m_eval		= format->eval;
	m_geom		= format->geom;
	m_fragment	= format->fragment;
}



//=================================================================================================
void eve::ogl::Shader::init(void)
{
	// Set name array content to 0 to avoid OpenGL deletion issues.
	m_prgmId = (GLuint *)calloc(eve::ogl::Shader::prgm_Max, sizeof(GLuint));
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

	if (m_vertex.size() > 0)
	{
		src = m_vertex.c_str();
		m_prgmId[prgm_Vertex] = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &src);
		EVE_OGL_CHECK_SHADER(m_prgmId[eve::ogl::Shader::prgm_Vertex]);

		glUseProgramStages(m_id, GL_VERTEX_SHADER_BIT, m_prgmId[eve::ogl::Shader::prgm_Vertex]);
		EVE_OGL_CHECK_ERROR;
	}

	if (m_control.size() > 0)
	{
		src = m_control.c_str();
		m_prgmId[prgm_Control] = glCreateShaderProgramv(GL_TESS_CONTROL_SHADER, 1, &src);
		EVE_OGL_CHECK_SHADER(m_prgmId[eve::ogl::Shader::prgm_Control]);

		glUseProgramStages(m_id, GL_TESS_CONTROL_SHADER_BIT, m_prgmId[eve::ogl::Shader::prgm_Control]);
		EVE_OGL_CHECK_ERROR;
	}

	if (m_eval.size() > 0)
	{
		src = m_eval.c_str();
		m_prgmId[prgm_Evaluation] = glCreateShaderProgramv(GL_TESS_EVALUATION_SHADER, 1, &src);
		EVE_OGL_CHECK_SHADER(m_prgmId[eve::ogl::Shader::prgm_Evaluation]);

		glUseProgramStages(m_id, GL_TESS_EVALUATION_SHADER_BIT, m_prgmId[eve::ogl::Shader::prgm_Evaluation]);
		EVE_OGL_CHECK_ERROR;
	}

	if (m_geom.size() > 0)
	{
		src = m_geom.c_str();
		m_prgmId[prgm_Geometry] = glCreateShaderProgramv(GL_GEOMETRY_SHADER, 1, &src);
		EVE_OGL_CHECK_SHADER(m_prgmId[eve::ogl::Shader::prgm_Geometry]);

		glUseProgramStages(m_id, GL_GEOMETRY_SHADER_BIT, m_prgmId[eve::ogl::Shader::prgm_Geometry]);
		EVE_OGL_CHECK_ERROR;
	}

	if (m_fragment.size() > 0)
	{
		src = m_fragment.c_str();
		m_prgmId[prgm_Fragment] = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &src);
		EVE_OGL_CHECK_SHADER(m_prgmId[eve::ogl::Shader::prgm_Fragment]);

		glUseProgramStages(m_id, GL_FRAGMENT_SHADER_BIT, m_prgmId[eve::ogl::Shader::prgm_Fragment]);
		EVE_OGL_CHECK_ERROR;
	}
}

//=================================================================================================
void eve::ogl::Shader::oglUpdate(void)
{
	// Shader pipeline cannot be updated for now.
	EVE_ASSERT_FAILURE;
}

//=================================================================================================
void eve::ogl::Shader::oglRelease(void)
{
	glDeleteProgram(m_prgmId[eve::ogl::Shader::prgm_Vertex]);
	glDeleteProgram(m_prgmId[eve::ogl::Shader::prgm_Control]);
	glDeleteProgram(m_prgmId[eve::ogl::Shader::prgm_Evaluation]);
	glDeleteProgram(m_prgmId[eve::ogl::Shader::prgm_Geometry]);
	glDeleteProgram(m_prgmId[eve::ogl::Shader::prgm_Fragment]);
	EVE_OGL_CHECK_ERROR;

	glDeleteProgramPipelines(1, &m_id);
	EVE_OGL_CHECK_ERROR;

	this->release();
}



//=================================================================================================
void eve::ogl::Shader::bind(GLenum p_index)
{
	glBindProgramPipeline(m_id);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Shader::unbind(GLenum p_index)
{
	glBindProgramPipeline(0);
	EVE_OGL_CHECK_ERROR;
}
