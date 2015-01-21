
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
#include "eve/ogl/particule/ParticleManager.h"


eve::ogl::ParticleManager::ParticleManager()
	: eve::ogl::Object()
	, m_bufferData(std::map<std::string, GLuint>())
	, m_numParticles(0)
	, m_iniRadius(0)
{
}

eve::ogl::ParticleManager::~ParticleManager()
{
	
}

void eve::ogl::ParticleManager::release(void)
{
	if (m_particles)
	{
		delete m_particles;
		m_particles = NULL;
	}

	m_bufferData.clear();
}

eve::ogl::ParticleManager::ParticleManager(const ParticleManager & p_other)
// Inheritance
: eve::ogl::Object()
// Members init
, m_numParticles(p_other.m_numParticles)
, m_bufferData(p_other.m_bufferData)
, m_iniRadius(p_other.m_iniRadius)
{}

//=================================================================================================
const eve::ogl::ParticleManager & eve::ogl::ParticleManager::operator = (const eve::ogl::ParticleManager & p_other)
{
	if (this != &p_other)
	{
		this->m_bufferData = p_other.m_bufferData;
		this->m_numParticles = p_other.m_numParticles;
		this->m_iniRadius = p_other.m_iniRadius;
	}
	return *this;
}


eve::ogl::ParticleManager::ParticleManager(eve::ogl::ParticleManager&& other)
// Inheritance
: eve::ogl::Object()
, m_bufferData(std::map<std::string, GLuint>())
, m_numParticles(0)
, m_iniRadius(0)
{
	std::cout << "In MemoryBlock(MemoryBlock&&). length = "
		<< other.m_numParticles << ". Moving resource." << std::endl;

	// Copy the data pointer and its length from the 
	// source object.
	m_numParticles = other.m_numParticles;
	m_iniRadius = other.m_iniRadius;
	m_bufferData = other.m_bufferData;

	// Release the data pointer from the source object so that
	// the destructor does not free the memory multiple times.
	other.m_bufferData.clear();
	other.m_numParticles	= 0;
	other.m_iniRadius = 0;
}


// Move assignment operator.
eve::ogl::ParticleManager& eve::ogl::ParticleManager::operator=(eve::ogl::ParticleManager&& other)
{
	std::cout << "In operator=(MemoryBlock&&). length = "
		<< other.m_numParticles << "." << std::endl;

	if (this != &other)
	{
		// Free the existing resource.
		m_bufferData.clear();

		// Copy the data pointer and its length from the 
		// source object.
		m_numParticles = other.m_numParticles;
		m_iniRadius = other.m_iniRadius;
		m_bufferData = other.m_bufferData;

		// Release the data pointer from the source object so that
		// the destructor does not free the memory multiple times.
		other.m_bufferData.clear();
		other.m_numParticles = 0;
		other.m_iniRadius = 0;
	}
	return *this;
}

void eve::ogl::ParticleManager::loadParticleBuffer(int numParticles, int iniRadius, eve::ogl::Renderer * p_pRenderer)
{
	glGetError();
	
	m_numParticles = numParticles;
	m_iniRadius = iniRadius;

	m_bufferData = std::map<std::string, GLuint>();

	this->linkToRenderer(p_pRenderer);
	this->init();
	this->requestOglInit();
}


void eve::ogl::ParticleManager::setAttributes(eve::ogl::Format * p_format)
{

}


void eve::ogl::ParticleManager::oglInit(void)
{
	GLuint bufferID;

	Particle* m_particles = new Particle[m_numParticles];
	setParticles(m_particles, m_numParticles, m_iniRadius);

	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_numParticles*sizeof(Particle), m_particles, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, bufferID);

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error("ERROR: Could not generate or bind shader storage buffer for particles!");
	}

	m_bufferData.insert(std::make_pair("particleBuffer", bufferID));

}

void eve::ogl::ParticleManager::oglRelease(void)
{
	GLuint ID = getId();
	glDeleteBuffers(1, &ID);
}

void eve::ogl::ParticleManager::setParticles(struct Particle* particles, int numParticles, int iniRadius)
{
	float rndX, rndY, rndZ;
	std::mt19937 eng;
	std::uniform_real_distribution<float> dist(static_cast<float>(iniRadius)*(-1.0f), static_cast<float>(iniRadius));

	for(int i = 0; i < numParticles; ++i){
		rndX = dist(eng);
		rndY = dist(eng);
		rndZ = dist(eng);
		particles[i].m_currPosition = eve::math::TVec4<float>(rndX, rndY, rndZ, 1.0f);
		particles[i].m_prevPosition = eve::math::TVec4<float>(rndX, rndY, rndZ, 1.0f);
	}
}


const GLuint eve::ogl::ParticleManager::getId(void) const
{ 

	std::map<std::string, GLuint>::const_iterator it = m_bufferData.find("particleBuffer");

	if (it == m_bufferData.end())
	{
		return 0;
	}
	else
	{
		const GLuint idReturn = it->second;
		return idReturn;
	}
}

void eve::ogl::ParticleManager::loadUintUniform(GLuint shaderProgramID, std::string name, GLuint value)
{
	glGetError();

	int _uniID = glGetUniformLocation(shaderProgramID, name.c_str());

	if(glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not get "+name+"-uniform-location!").c_str());
	}

	glUniform1ui(_uniID, value);

	if(glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not update "+name+"-uniform-location!").c_str());
	}
}

void eve::ogl::ParticleManager::loadFloatUniform(GLuint shaderProgramID, std::string name, GLfloat value)
{
	glGetError();

	int _uniID = glGetUniformLocation(shaderProgramID, name.c_str());

	if(glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not get "+name+"-uniform-location!").c_str());
	}

	glUniform1f(_uniID, value);

	if(glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not update "+name+"-uniform-location!").c_str());
	}
}

void eve::ogl::ParticleManager::loadVec4Uniform(GLuint shaderProgramID, std::string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glGetError();
	int _uniID = glGetUniformLocation(shaderProgramID, name.c_str());

	if(glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not get "+name+"-uniform-location!").c_str());
	}

	glUniform4f(_uniID, x, y, z, w);

	if(glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not update "+name+"-uniform-location!").c_str());
	}
}

void eve::ogl::ParticleManager::loadMatrix4Uniform(GLuint shaderProgramID, std::string name, const GLfloat* value)
{
	glGetError();
	int _uniID = glGetUniformLocation(shaderProgramID, name.c_str());

	if(glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not get "+name+"-uniform-location!").c_str());
	}

	glUniformMatrix4fv(_uniID, 1, GL_FALSE, value);

	if(glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not update "+name+"-uniform-location!").c_str());
	}
}