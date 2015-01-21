
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
#include "eve/scene/Material.h"

#ifndef __EVE_SCENE_SCENE_H__
#include "eve/scene/Scene.h"
#endif

#ifndef __EVE_OPENGL_CORE_TEXTURE_H__
#include "eve/ogl/core/Texture.h"
#endif

#ifndef __EVE_IO_IMAGE_H__
#include "eve/io/Image.h"
#endif


//=================================================================================================
eve::scene::Material * eve::scene::Material::create_ptr(eve::scene::Scene *		p_pParentScene
													  , eve::scene::Object *	p_pParent
													  , const aiMaterial *		p_pMaterial
													  , const std::string &		p_fullPath)
{
	EVE_ASSERT(p_pParentScene);
	EVE_ASSERT(p_pParent);

	eve::scene::Material * ptr = new eve::scene::Material(p_pParentScene, p_pParent);
	ptr->initFromAssimpMaterial(p_pMaterial, p_fullPath);
	return ptr;
}



//=================================================================================================
eve::scene::Material::Material(eve::scene::Scene * p_pParentScene, eve::scene::Object * p_pParent)
	// Inheritance
	: eve::scene::Object(p_pParentScene, p_pParent, SceneObject_Material)
	, eve::scene::EventListenerSceneMaterial()

	// Members init
	, m_diffuse(1.0f)
	, m_specular(1.0f)
	, m_shininess(0.5f)
	, m_fresnelExponent(1.0f)

	, m_pTexDiffuse(nullptr)
	, m_pTexNormal(nullptr)
	, m_pTexEmissive(nullptr)
	, m_pTexOpacity(nullptr)
{}



//=================================================================================================
void eve::scene::Material::initFromAssimpMaterial(const aiMaterial * p_pMaterial, const std::string & p_fullPath)
{
	if (p_pMaterial)
	{
		m_pAiMaterial = p_pMaterial;

		aiString path;
		std::string folderPath = eve::files::remove_file_name(p_fullPath);
		std::string fullPath;

		// Diffuse.
		if (m_pAiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			fullPath = folderPath + path.data;
			eve::ogl::FormatTex fmtTexDif;
			if (eve::io::load_image(fullPath, &fmtTexDif))
			{
				m_pTexDiffuse = m_pScene->create(fmtTexDif);
			}
			else
			{
				EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(fullPath).c_str());
				EVE_ASSERT_FAILURE;
			}
		}

		// Normals.
		if (m_pAiMaterial->GetTexture(aiTextureType_NORMALS, 0, &path) == AI_SUCCESS)
		{
			fullPath = folderPath + path.data;
			eve::ogl::FormatTex fmtTexNor;
			if (eve::io::load_image(fullPath, &fmtTexNor))
			{
				m_pTexNormal = m_pScene->create(fmtTexNor);
			}
			else
			{
				EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(fullPath).c_str());
				EVE_ASSERT_FAILURE;
			}
		}

		// Emissive.
		if (m_pAiMaterial->GetTexture(aiTextureType_EMISSIVE, 0, &path) == AI_SUCCESS)
		{
			fullPath = folderPath + path.data;
			eve::ogl::FormatTex fmtTexEmi;
			if (eve::io::load_image(fullPath, &fmtTexEmi))
			{
				m_pTexEmissive = m_pScene->create(fmtTexEmi);
			}
			else
			{
				EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(fullPath).c_str());
				EVE_ASSERT_FAILURE;
			}
		}

		// Opacity
		if (m_pAiMaterial->GetTexture(aiTextureType_OPACITY, 0, &path) == AI_SUCCESS)
		{
			fullPath = folderPath + path.data;
			eve::ogl::FormatTex fmtTexOpa;
			if (eve::io::load_image(fullPath, &fmtTexOpa))
			{
				m_pTexOpacity = m_pScene->create(fmtTexOpa);
			}
			else
			{
				EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(fullPath).c_str());
				EVE_ASSERT_FAILURE;
			}
		}


		aiGetMaterialFloat(m_pAiMaterial, AI_MATKEY_SHININESS, &m_shininess); // AI_MATKEY_SHININESS_STRENGTH
		//aiGetMaterialFloat(m_pAiMaterial, AI_MATKEY_OPACITY, &m_o);
	}
	this->init();
}



//=================================================================================================
void eve::scene::Material::init(void)
{
	// Call parent class
	eve::scene::Object::init();


	std::string path;

	// Diffuse.
	if (!m_pTexDiffuse)
	{
		path = eve::io::resource_path_material("diffuse.png");
		eve::ogl::FormatTex fmtTexDif;
		if (eve::io::load_image(path, &fmtTexDif))
		{
			m_pTexDiffuse = m_pScene->create(fmtTexDif);
		}
		else
		{
			EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(path).c_str());
			EVE_ASSERT_FAILURE;
		}
	}

	// Normals.
	if (!m_pTexNormal)
	{
		path = eve::io::resource_path_material("normal.png");
		eve::ogl::FormatTex fmtTexNor;
		if (eve::io::load_image(path, &fmtTexNor))
		{
			m_pTexNormal = m_pScene->create(fmtTexNor);
		}
		else
		{
			EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(path).c_str());
			EVE_ASSERT_FAILURE;
		}
	}

	// Emissive.
	if (!m_pTexEmissive)
	{
		path = eve::io::resource_path_material("emissive.png");
		eve::ogl::FormatTex fmtTexEmi;
		if (eve::io::load_image(path, &fmtTexEmi))
		{
			m_pTexEmissive = m_pScene->create(fmtTexEmi);
		}
		else
		{
			EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(path).c_str());
			EVE_ASSERT_FAILURE;
		}
	}

	// Opacity.
	if (!m_pTexOpacity)
	{
		path = eve::io::resource_path_material("opacity.png");
		eve::ogl::FormatTex fmtTexOpa;
		if (eve::io::load_image(path, &fmtTexOpa))
		{
			m_pTexOpacity = m_pScene->create(fmtTexOpa);
		}
		else
		{
			EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(path).c_str());
			EVE_ASSERT_FAILURE;
		}
	}
}

//=================================================================================================
void eve::scene::Material::release(void)
{
	m_pTexDiffuse->requestRelease();
	m_pTexDiffuse = nullptr;
	m_pTexNormal->requestRelease();
	m_pTexNormal = nullptr;
	m_pTexEmissive->requestRelease();
	m_pTexEmissive = nullptr;
	m_pTexOpacity->requestRelease();
	m_pTexOpacity = nullptr;

	// Do not delete -> shared pointer.
	m_pAiMaterial = nullptr;

	// Call parent class
	eve::scene::Object::release();
}



//=================================================================================================
void eve::scene::Material::cb_evtSceneMaterial(eve::scene::EventArgsSceneMaterial & p_args)
{
	switch (p_args.type)
	{
	case SceneMaterialEventType_ValueDiffuse:		this->setDiffuse(p_args.value);				break;
	case SceneMaterialEventType_ValueSpecular:		this->setSpecular(p_args.value);			break;
	case SceneMaterialEventType_ValueShininess:		this->setShininess(p_args.value);			break;
	case SceneMaterialEventType_ValueFresnel:		this->setFresnelExponent(p_args.value);		break;


	default: EVE_ASSERT_FAILURE; break;
	}
}



//=================================================================================================
void eve::scene::Material::bind(void)
{
	m_pTexDiffuse->bind(1);
	m_pTexNormal->bind(2);
	m_pTexEmissive->bind(3);
	m_pTexOpacity->bind(4);
}

//=================================================================================================
void eve::scene::Material::unbind(void)
{
	eve::ogl::Texture::unbind(4);
	eve::ogl::Texture::unbind(3);
	eve::ogl::Texture::unbind(2);
	eve::ogl::Texture::unbind(1);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
bool eve::scene::Material::setTexDiffuse(const std::string & p_path)
{
	eve::ogl::FormatTex fmtTex;
	bool ret = eve::io::load_image(p_path, &fmtTex);
	if (ret)
	{
		m_pTexDiffuse->updateAttributes(&fmtTex);
	}
	else
	{
		EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(p_path).c_str());
		EVE_ASSERT_FAILURE;
	}
	return ret;
}

//=================================================================================================
bool eve::scene::Material::setTexNormal(const std::string & p_path)
{
	eve::ogl::FormatTex fmtTex;
	bool ret = eve::io::load_image(p_path, &fmtTex);
	if (ret)
	{
		m_pTexNormal->updateAttributes(&fmtTex);
	}
	else
	{
		EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(p_path).c_str());
		EVE_ASSERT_FAILURE;
	}
	return ret;
}

//=================================================================================================
bool eve::scene::Material::setTexEmissive(const std::string & p_path)
{
	eve::ogl::FormatTex fmtTex;
	bool ret = eve::io::load_image(p_path, &fmtTex);
	if (ret)
	{
		m_pTexEmissive->updateAttributes(&fmtTex);
	}
	else
	{
		EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(p_path).c_str());
		EVE_ASSERT_FAILURE;
	}
	return ret;
}

//=================================================================================================
bool eve::scene::Material::setTexOpacity(const std::string & p_path)
{
	eve::ogl::FormatTex fmtTex;
	bool ret = eve::io::load_image(p_path, &fmtTex);
	if (ret)
	{
		m_pTexOpacity->updateAttributes(&fmtTex);
	}
	else
	{
		EVE_LOG_ERROR("Unable to load file %s", eve::str::to_wstring(p_path).c_str());
		EVE_ASSERT_FAILURE;
	}
	return ret;
}
