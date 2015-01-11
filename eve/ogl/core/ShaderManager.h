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
			std::map<std::string, std::pair<std::string, GLenum >> shaderMap;
			std::vector<std::string> program;
			std::map<std::string, std::string> linkedMap;

			void loadShader(const std::string& shaderKey, const std::string& filename, GLenum type);

			void createProgram(const std::string& shaderProgramKey);

			void attachShader(const std::string& shaderKey, const std::string& shaderProgramKey);

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
			ShaderBaseModel	_shaderData;

			GLuint 	_VertexArrayID;

			ShaderManager();

			~ShaderManager();

			std::map<std::string, std::pair<std::string, GLenum >> shaderMap;
			std::vector<std::string> program;
			std::map<std::string, std::string> linkedMap;



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

			void 			loadShader(const std::string& shaderKey, const std::string& program, GLenum type);
			void 			attachShader(const std::string& shaderKey, const std::string& shaderProgramKey);
			void 			detachShader(const std::string& shaderKey, const std::string& shaderProgramKey);

			void 			createProgram(const std::string& shaderProgramKey);
			void 			useProgram(const std::string& shaderProgramKey);
			void 			linkProgram(const std::string& shaderProgramKey);

			GLuint 			getShaderID(const std::string& shaderKey);
			GLuint 			getShaderProgramID(const std::string& shaderProgramKey);

			void 			deleteProgram(const std::string& shaderProgramKey);
			void 			deleteShader(const std::string& shaderKey);

			void 			resetProgram();

			void 			loadUintUniform(const std::string& shaderProgram, const std::string& name, GLuint value);
			void 			loadFloatUniform(const std::string& shaderProgram, const std::string& name, GLfloat value);
			void 			loadVec4Uniform(const std::string& shaderProgram, const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
			void 			loadMatrix4Uniform(const std::string& shaderProgram, const std::string& name, const GLfloat* value);

			void 			getBufferVariableIndices(const std::string& shaderProgram, int length, const GLchar** names, GLint* indices);

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