
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
#include "eve/ogl/core/ShaderManager.h"


eve::ogl::ShaderBaseModel::ShaderBaseModel()
	: m_shader(std::map<std::string, GLuint>())
	, m_shaderProgram(std::map<std::string, GLuint>())
{
}

eve::ogl::ShaderBaseModel::~ShaderBaseModel()
{
	m_shader.clear();
	m_shaderProgram.clear();
}

/*Returns ShaderID with the associated Key. Returns 0 if Key does not exist. */
GLuint eve::ogl::ShaderBaseModel::getShaderID(std::string ShaderKey)
{
	std::map<std::string, GLuint>::iterator it = m_shader.find(ShaderKey);

	if (it == m_shader.end()){
		return 0;
	}
	else {
		return it->second;
	}

}

/*Returns ShaderID with the associated Key. Returns 0 if Key does not exist. */
GLuint eve::ogl::ShaderBaseModel::getShaderProgramID(std::string ShaderProgramKey)
{
	std::map<std::string, GLuint>::iterator it = m_shaderProgram.find(ShaderProgramKey);

	if (it == m_shaderProgram.end())
		return 0;
	else
		return it->second;
}

/*Returns false, if element with the same key already exists, otherwise returns true */
bool eve::ogl::ShaderBaseModel::saveShader(std::string ShaderKey, GLuint ShaderID)
{
	return m_shader.insert(std::pair<std::string, GLuint>(ShaderKey, ShaderID)).second;
}

/*Returns false, if element with the same key already exists, otherwise returns true */
bool eve::ogl::ShaderBaseModel::saveShaderProgram(std::string ShaderProgramKey, GLuint ShaderProgramID)
{
	return m_shaderProgram.insert(std::pair<std::string, GLuint>(ShaderProgramKey, ShaderProgramID)).second;
}

void eve::ogl::ShaderBaseModel::deleteShader(std::string ShaderKey)
{
	m_shader.erase(ShaderKey);
}

void eve::ogl::ShaderBaseModel::deleteShaderProgram(std::string ShaderProgramKey)
{
	m_shaderProgram.erase(ShaderProgramKey);
}




eve::ogl::FormatShaderAdvanced::FormatShaderAdvanced(void)
// Inheritance
: eve::ogl::Format()
// Members init
, m_shaderMap()
, m_program()
, m_linkedMap()
{}

//=================================================================================================
eve::ogl::FormatShaderAdvanced::~FormatShaderAdvanced(void)
{}


void eve::ogl::FormatShaderAdvanced::loadShader(const std::string& shaderKey, const std::string& filename, GLenum type)
{
	m_shaderMap[shaderKey] = std::make_pair(filename, type);
}

void eve::ogl::FormatShaderAdvanced::createProgram(const std::string& shaderProgramKey)
{
	m_program.push_back(shaderProgramKey);
}

void eve::ogl::FormatShaderAdvanced::attachShader(const std::string& shaderKey, const std::string& shaderProgramKey)
{

	std::vector<std::string>::iterator it;

	it = find(m_program.begin(), m_program.end(), shaderProgramKey);

	if (it != m_program.end())
	{
		m_linkedMap[shaderKey] = shaderProgramKey;
	}

}


eve::ogl::ShaderManager::ShaderManager()
	: m_shaderMap(std::map<std::string, std::pair<std::string, GLenum >>())
	, m_program(std::vector<std::string>())
	, m_linkedMap(std::map<std::string, std::string>())
	, m_shaderData(ShaderBaseModel())
{
}

eve::ogl::ShaderManager::~ShaderManager()
{

}

void eve::ogl::ShaderManager::release(void)
{
	m_shaderMap.clear();
	m_program.clear();
	m_linkedMap.clear();

}

void eve::ogl::ShaderManager::oglUpdate(void)
{
	this->oglRelease();
	this->init();
	this->oglInit();
}


void eve::ogl::ShaderManager::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatShaderAdvanced * format = reinterpret_cast<eve::ogl::FormatShaderAdvanced*>(p_format);

	m_shaderMap = format->m_shaderMap;
	m_program = format->m_program;
	m_linkedMap = format->m_linkedMap;

}

void eve::ogl::ShaderManager::init(void)
{
	// Set name array content to 0 to avoid OpenGL deletion issues.

}

void eve::ogl::ShaderManager::oglInit(void)
{

	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);

	//Initiliaze shader and shader program

	std::map<std::string, std::pair<std::string, GLenum >>::iterator shaderMapIt;



	for (shaderMapIt = m_shaderMap.begin(); shaderMapIt != m_shaderMap.end(); shaderMapIt++)
	{
		loadShader(shaderMapIt->first, shaderMapIt->second.first, shaderMapIt->second.second);
	}

	std::vector<std::string>::iterator programIt;

	for (programIt = m_program.begin(); programIt != m_program.end(); programIt++)
	{
		createProgram(*programIt);
	}

	std::map<std::string, std::string>::iterator linkedMapIt;

	for (linkedMapIt = m_linkedMap.begin(); linkedMapIt != m_linkedMap.end(); linkedMapIt++)
	{
		attachShader(linkedMapIt->first, linkedMapIt->second);
	}

	for (programIt = m_program.begin(); programIt != m_program.end(); programIt++)
	{
		linkProgram(*programIt);
	}

	//Since the programs are linked the shaders are not needed anymore

	for (shaderMapIt = m_shaderMap.begin(); shaderMapIt != m_shaderMap.end(); shaderMapIt++)
	{
		deleteShader(shaderMapIt->first);
	}
}

//=================================================================================================
void eve::ogl::ShaderManager::oglRelease(void)
{

	glDeleteVertexArrays(1, &m_VertexArrayID);

	std::map<std::string, GLuint>::iterator it = m_shaderData.m_shaderProgram.begin();

	while (it != m_shaderData.m_shaderProgram.end())
	{
		glDeleteProgram(it->second);
		it++;
	}
	
	EVE_OGL_CHECK_ERROR;
}

void eve::ogl::ShaderManager::loadShader(const std::string& shaderKey, const std::string& program, GLenum type){


	glGetError();

	GLuint shaderID = glCreateShader(type);
	const char* source = program.c_str();

	if (shaderID != 0){
		m_shaderData.saveShader(shaderKey, shaderID);
		glShaderSource(shaderID, 1, &source, NULL);
		glCompileShader(shaderID);
	}

	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

	if (glGetError() != GL_NO_ERROR || compileStatus == GL_FALSE){

		if (shaderID != 0){
			m_shaderData.deleteShader(shaderKey);
		}

		GLsizei length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length); //Get the length of the compilation log
		char* compilationLog = new char[length];			 //Create the needed char array
		glGetShaderInfoLog(shaderID, length, NULL, compilationLog); //Get the compilation log
		std::string compilationLogString(compilationLog); //Create string for the compilation log
		delete[] compilationLog; //Delete the compilation log array

		throw std::runtime_error(("ERROR: \nCompilation log of shader " + shaderKey + ":\n" + compilationLogString).c_str());

	}


}

void eve::ogl::ShaderManager::attachShader(const std::string& shaderKey, const std::string& shaderProgramKey){
	glGetError();

	GLuint shaderID = m_shaderData.getShaderID(shaderKey);
	GLuint shaderProgramID = m_shaderData.getShaderProgramID(shaderProgramKey);

	if (shaderProgramID != 0 && shaderID != 0){
		glAttachShader(shaderProgramID, shaderID);
	}
	else {
		throw std::runtime_error("ERROR: No shader with associated key does exist!");
	}

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error((std::string("ERROR: Could not attach shader ") + std::string(shaderKey) + std::string(" to ") + std::string(shaderProgramKey)).c_str());
	}
}

void eve::ogl::ShaderManager::detachShader(const std::string& shaderKey, const std::string& shaderProgramKey){
	glGetError();

	GLuint shaderID = m_shaderData.getShaderID(shaderKey);
	GLuint shaderProgramID = m_shaderData.getShaderProgramID(shaderProgramKey);

	if (shaderProgramID != 0 && shaderID != 0){
		glDetachShader(shaderProgramID, shaderID);
	}
	else {
		throw std::runtime_error("ERROR: No shader or shader-program with associated key does exist!");
	}

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not detach shader " + std::string(shaderKey) + " from " + std::string(shaderProgramKey)).c_str());
	}
}

void eve::ogl::ShaderManager::resetProgram(){
	glUseProgram(0);
}

void eve::ogl::ShaderManager::createProgram(const std::string& shaderProgramKey){

	glGetError();

	GLuint shaderProgramID = glCreateProgram();

	if (shaderProgramID != 0){
		m_shaderData.saveShaderProgram(shaderProgramKey, shaderProgramID);
	}

	if (glGetError() != GL_NO_ERROR){

		if (shaderProgramID != 0){
			m_shaderData.deleteShaderProgram(shaderProgramKey);
		}

		throw std::runtime_error(("ERROR: Could not create shader-program " + shaderProgramKey).c_str());
	}
}

void eve::ogl::ShaderManager::useProgram(const std::string& shaderProgramKey){
	glGetError();

	GLuint shaderProgramID = m_shaderData.getShaderProgramID(shaderProgramKey);

	if (shaderProgramID != 0){
		glUseProgram(shaderProgramID);
	}
	else {
		throw std::runtime_error("ERROR: No shader-program with associated key does exist!");
	}

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not use shaderProgram " + shaderProgramKey + "!\n").c_str());
	}
}

void eve::ogl::ShaderManager::linkProgram(const std::string& shaderProgramKey){
	glGetError();

	GLuint shaderProgramID = m_shaderData.getShaderProgramID(shaderProgramKey);

	if (shaderProgramID != 0){
		glLinkProgram(shaderProgramID);
	}
	else {
		throw std::runtime_error("ERROR: No shader-program with associated key does exist!");
	}

	GLint linkStatus;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linkStatus);

	if (glGetError() != GL_NO_ERROR || linkStatus == GL_FALSE){

		GLsizei length;
		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &length); //Get the length of the compilation log
		char* linkingLog = new char[length];			 //Create the needed char array
		glGetProgramInfoLog(shaderProgramID, length, NULL, linkingLog); //Get the compilation log
		std::string linkingLogString(linkingLog);	//Save the linking log in a string
		delete[] linkingLog;	//Free the allocated memory

		throw std::runtime_error(("ERROR: \nLinker log of shader-programm " + shaderProgramKey + ":\n" + linkingLogString).c_str());

	}
}

GLuint eve::ogl::ShaderManager::getShaderID(const std::string& shaderKey){
	return m_shaderData.getShaderID(shaderKey);
}

GLuint eve::ogl::ShaderManager::getShaderProgramID(const std::string& shaderProgramKey){
	return m_shaderData.getShaderProgramID(shaderProgramKey);
}

void eve::ogl::ShaderManager::deleteProgram(const std::string& shaderProgramKey){
	glGetError();

	GLuint shaderProgramID = m_shaderData.getShaderProgramID(shaderProgramKey);

	if (shaderProgramID != 0){
		glDeleteProgram(shaderProgramID);
	}
	else {
		throw std::runtime_error("ERROR: No shader-program with associated key does exist!");
	}

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not delete shader-program " + shaderProgramKey).c_str());
	}
}

void eve::ogl::ShaderManager::deleteShader(const std::string& shaderKey){
	glGetError();

	GLuint shaderID = m_shaderData.getShaderID(shaderKey);

	if (shaderID != 0){
		glDeleteShader(shaderID);
	}
	else {
		throw std::runtime_error("ERROR: No shader-program with associated key does exist!");
	}

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not delete shader " + shaderKey).c_str());
	}
}


void eve::ogl::ShaderManager::loadUintUniform(const std::string& shaderProgram, const std::string& name, GLuint value){
	glGetError();

	int _uniID = glGetUniformLocation(getShaderProgramID(shaderProgram), name.c_str());

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not get " + name + "-uniform-location!").c_str());
	}

	glUniform1ui(_uniID, value);

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not update " + name + "-uniform-location!").c_str());
	}
}

void eve::ogl::ShaderManager::loadFloatUniform(const std::string& shaderProgram, const std::string& name, GLfloat value){
	glGetError();

	int _uniID = glGetUniformLocation(getShaderProgramID(shaderProgram), name.c_str());

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not get " + name + "-uniform-location!").c_str());
	}

	glUniform1f(_uniID, value);

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not update " + name + "-uniform-location!").c_str());
	}
}

void eve::ogl::ShaderManager::loadVec4Uniform(const std::string& shaderProgram, const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
	glGetError();
	int _uniID = glGetUniformLocation(getShaderProgramID(shaderProgram), name.c_str());

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not get " + name + "-uniform-location!").c_str());
	}

	glUniform4f(_uniID, x, y, z, w);

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not update " + name + "-uniform-location!").c_str());
	}
}

void eve::ogl::ShaderManager::loadMatrix4Uniform(const std::string& shaderProgram, const std::string& name, const GLfloat* value){
	glGetError();
	int _uniID = glGetUniformLocation(getShaderProgramID(shaderProgram), name.c_str());

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not get " + name + "-uniform-location!").c_str());
	}

	glUniformMatrix4fv(_uniID, 1, GL_FALSE, value);

	if (glGetError() != GL_NO_ERROR){
		throw std::runtime_error(("ERROR: Could not update " + name + "-uniform-location!").c_str());
	}
}

void eve::ogl::ShaderManager::getBufferVariableIndices(const std::string& shaderProgram, int length, const GLchar** names, GLint* indices){
	for (int i = 0; i < length; ++i){
		indices[i] = glGetProgramResourceIndex(getShaderProgramID(shaderProgram), GL_BUFFER_VARIABLE, names[i]);
	}
}