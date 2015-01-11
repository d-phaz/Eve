#ifndef _SHADERMANAGER_
#define _SHADERMANAGER_

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve\core\Includes.h"
#endif

#ifndef __EVE_OPENGL_CORE_EXTERNAL_H__
#include "eve/ogl/core/External.h"
#endif

#ifndef __EVE_OPENGL_CORE_OBJECT_H__
#include "eve/ogl/core/Object.h"
#endif

namespace eve
{
	namespace ogl
	{

		class ShaderBaseModel{

			friend class ShaderManager;

		private:
			std::map<std::string, GLuint> 	m_shader;
			std::map<std::string, GLuint> 	m_shaderProgram;

			//May only be instantiated in ShaderManager
			ShaderBaseModel();

			~ShaderBaseModel();

		public:

			/*Returns ShaderID with the associated Key. Returns 0 if Key does not exist. */
			GLuint getShaderID(std::string ShaderKey);

			/*Returns ShaderID with the associated Key. Returns 0 if Key does not exist. */
			GLuint getShaderProgramID(std::string ShaderProgramKey);

			/*Returns false, if element with the same key already exists, otherwise returns true */
			bool saveShader(std::string ShaderKey, GLuint ShaderID);

			/*Returns false, if element with the same key already exists, otherwise returns true */
			bool saveShaderProgram(std::string ShaderProgramKey, GLuint ShaderProgramID);

			void deleteShader(std::string ShaderKey);

			void deleteShaderProgram(std::string ShaderProgramKey);

		};

		class FormatShaderAdvanced final
			: public eve::ogl::Format
		{

		public:
			std::map<std::string, std::pair<std::string, GLenum >> m_shaderMap;
			std::vector<std::string> m_program;
			std::map<std::string, std::string> m_linkedMap;

			void loadShader(const std::string& p_shaderKey, const std::string& p_filename, GLenum p_type);

			void createProgram(const std::string& p_shaderProgramKey);

			void attachShader(const std::string& p_shaderKey, const std::string& p_shaderProgramKey);

			/** \brief Class constructor. */
			FormatShaderAdvanced(void);
			/** \brief Class destructor. */
			virtual ~FormatShaderAdvanced(void);

			/** \brief Copy constructor. */
			FormatShaderAdvanced(const eve::ogl::FormatShaderAdvanced & p_other);
			/** \brief Assignment operator. */
			const eve::ogl::FormatShaderAdvanced & operator = (const eve::ogl::FormatShaderAdvanced & p_other);

		};

		class ShaderManager
			: public eve::ogl::Object
		{

			friend class eve::mem::Pointer;
			friend class eve::ogl::Renderer;
			friend class eve::ogl::Object;

		private:
			ShaderBaseModel	m_shaderData;

			GLuint 	m_VertexArrayID;

			ShaderManager();

			~ShaderManager();

			std::map<std::string, std::pair<std::string, GLenum >> m_shaderMap;
			std::vector<std::string> m_program;
			std::map<std::string, std::string> m_linkedMap;



		protected:
			/** \brief Init OpenGL components. */
			virtual void oglInit(void);
			/** \brief Update OpenGL components. */
			virtual void oglUpdate(void);
			/** \brief Deallocate and release OpenGL components. */
			virtual void oglRelease(void);

			void release(void);

			void setAttributes(eve::ogl::Format* p_format);
		public:

			void init(void);

			void 			loadShader(const std::string& p_shaderKey, const std::string& p_program, GLenum p_type);
			void 			attachShader(const std::string& p_shaderKey, const std::string& p_shaderProgramKey);
			void 			detachShader(const std::string& p_shaderKey, const std::string& p_shaderProgramKey);

			void 			createProgram(const std::string& p_shaderProgramKey);
			void 			useProgram(const std::string& p_shaderProgramKey);
			void 			linkProgram(const std::string& p_shaderProgramKey);

			GLuint 			getShaderID(const std::string& p_shaderKey);
			GLuint 			getShaderProgramID(const std::string& p_shaderProgramKey);

			void 			deleteProgram(const std::string& p_shaderProgramKey);
			void 			deleteShader(const std::string& p_shaderKey);

			void 			resetProgram();

			void 			loadUintUniform(const std::string& p_shaderProgram, const std::string& p_name, GLuint p_value);
			void 			loadFloatUniform(const std::string& p_shaderProgram, const std::string& p_name, GLfloat p_value);
			void 			loadVec4Uniform(const std::string& p_shaderProgram, const std::string& p_name, GLfloat x, GLfloat p_y, GLfloat p_z, GLfloat p_w);
			void 			loadMatrix4Uniform(const std::string& p_shaderProgram, const std::string& p_name, const GLfloat* p_value);

			void 			getBufferVariableIndices(const std::string& p_shaderProgram, int p_length, const GLchar** p_names, GLint* p_indices);

			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get OpenGL shader unique id. (pure virtual) */
			virtual const GLuint getId(void) const override;

		};

	} // namespace ogl

} // namespace eve

EVE_FORCE_INLINE const GLuint eve::ogl::ShaderManager::getId(void) const	{ return 0; }


#endif