
// Main header
#include "eve/scene/Scene.h"

#ifndef __EVE_SCENE_MESH_H__
#include "eve/scene/Mesh.h"
#endif

#ifndef __EVE_SCENE_CAMERA_H__
#include "eve/scene/Camera.h"
#endif

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


std::map<eve::scene::SceneImportParam, std::string>	eve::scene::Scene::m_map_import_params;

//=================================================================================================
eve::scene::Scene::Scene(void)
	// Inheritance.
	: eve::ogl::Renderer()
	, eve::scene::EventListenerScene()
	// Members init.
	, m_pVecCamera(nullptr)
	, m_pCameraActive(nullptr)
	, m_pVecMesh(nullptr)
	, m_pShaderMesh(nullptr)
{}



//=================================================================================================
void eve::scene::Scene::init(void)
{
	// Call parent class.
	eve::ogl::Renderer::init();

	// Default import parameters.
	static bool bImportParamsInitialized = false;
	if (!bImportParamsInitialized)
	{
		m_map_import_params[SceneImportParam_Up_Axis]			= "Z";
		m_map_import_params[SceneImportParam_Flip_UV]			= "N";
		m_map_import_params[SceneImportParam_Generate_Normals]	= "Y";
		m_map_import_params[SceneImportParam_Normals_Max_Angle]	= "80.0";
		bImportParamsInitialized = true;
	}

	// Vectors.
	m_pVecCamera = new std::vector<eve::scene::Camera*>();
	m_pVecMesh	 = new std::vector<eve::scene::Mesh*>();

	// Mesh shader.
	eve::ogl::FormatShader fmtShader;
	fmtShader.vert = eve::io::load_program(eve::io::resource_path_glsl("SceneGBuffer.vert"));
	fmtShader.frag = eve::io::load_program(eve::io::resource_path_glsl("SceneGBuffer.frag"));
	m_pShaderMesh = this->create(fmtShader);
}

//=================================================================================================
void eve::scene::Scene::release(void)
{
	// Do not delete -> shared pointers.
	m_pCameraActive = nullptr;

	// Shader.
	m_pShaderMesh->requestRelease();
	m_pShaderMesh = nullptr;

	// Meshes.
	eve::scene::Mesh * mesh = nullptr;
	while (!m_pVecMesh->empty())
	{
		mesh = m_pVecMesh->back();
		m_pVecMesh->pop_back();
		EVE_RELEASE_PTR(mesh);
	}
	EVE_RELEASE_PTR_CPP(m_pVecMesh);

	// Cameras.
	eve::scene::Camera * cam = nullptr;
	while (!m_pVecCamera->empty())
	{
		cam = m_pVecCamera->back();
		m_pVecCamera->pop_back();
		EVE_RELEASE_PTR(cam);
	}
	EVE_RELEASE_PTR_CPP(m_pVecCamera);

	// Call parent class.
	eve::ogl::Renderer::release();
}



//=================================================================================================
void eve::scene::Scene::cb_evtScene(eve::scene::EventArgsScene & p_args)
{
	switch (p_args.type)
	{
	case SceneEventType_add_fromPath:					this->load(p_args.path); break;
			
	case SceneEventType_add_defaultLightArea:			
	case SceneEventType_add_defaultLightDirectional:	
	case SceneEventType_add_defaultLightPoint:			
	case SceneEventType_add_defaultLightSpot:			

	case SceneEventType_add_defaultCamera:				break;

	default: EVE_ASSERT_FAILURE; break;
	}
}



//=================================================================================================
bool eve::scene::Scene::load(const std::wstring & p_filePath)
{
	bool ret = false;

	// String path.
	std::string path = eve::str::to_string(p_filePath);

	// Assimp base importer
	Assimp::Importer * pImporter = new Assimp::Importer();
	// Set verbose mode
#ifndef NDEBUG
	pImporter->SetExtraVerbose(true);
#endif

	// Set common importer params.
	pImporter->SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);

	// Import flags.
	uint32_t flags = aiProcess_Triangulate;
				// | aiProcess_JoinIdenticalVertices
				// | aiProcess_RemoveRedundantMaterials
				// | aiProcess_SortByPType;

	if (m_map_import_params[SceneImportParam_Flip_UV] == "Y")
	{
		flags |= aiProcess_FlipUVs;
	}

	if (m_map_import_params[SceneImportParam_Generate_Normals] == "Y")
	{
		flags |= aiProcess_GenSmoothNormals;

		float angle = static_cast<float>(::atof(m_map_import_params[SceneImportParam_Normals_Max_Angle].c_str()));
		pImporter->SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, angle);
	}

	// Do not use these flags for now, it seems it could damage the scene -> will have to hardly test it !!!
	//if( p_bOptimize ) 
	//	flags |= aiProcess_ImproveCacheLocality 
	//		  | aiProcess_OptimizeGraph
	//		  | aiProcess_OptimizeMeshes 
	//		  | aiProcess_FindDegenerates;



	// Import scene.
	const aiScene * pAiScene = pImporter->ReadFile(path.c_str(), flags);
	if (pAiScene)
	{
		// Grab scene Up axis.
		eve::Axis upAxis;
		std::string axis = m_map_import_params[SceneImportParam_Up_Axis];
			 if (axis == "X") { upAxis = eve::Axis_X; }
		else if (axis == "Y") { upAxis = eve::Axis_Y; }
		else if (axis == "Z") { upAxis = eve::Axis_Z; }

		// Run threw scene meshes.
		if (pAiScene->HasMeshes())
		{
			for (size_t i = 0; i < pAiScene->mNumMeshes; i++)
			{
				this->add(pAiScene->mMeshes[i], pAiScene, upAxis, path);
			}
		}

// 		// Run threw scene lights.
// 		if (pAiScene->HasLights())
// 		{
// 			aiLight * light = NULL;
// 			for (size_t i = 0; i < pAiScene->mNumLights; i++)
// 			{
// 				light = pAiScene->mLights[i];
// 				this->add(light, pAiScene, upAxis);
// 			}
// 		} 
// 
		// Run threw scene cameras.
		if (pAiScene->HasCameras())
		{
			for (size_t i = 0; i < pAiScene->mNumCameras; i++)
			{
				this->add(pAiScene->mCameras[i], pAiScene, upAxis);
			}
		} 
 
// // 		// Run threw scene animations
// // 		if (pAiScene->HasAnimations())
// // 		{
// // 			for (size_t i = 0; i < pAiScene->mNumAnimations; i++)
// // 			{
// // 				aiNodeAnim * pAnim = pAiScene->mAnimations[i]->mChannels[i]; // Do not use mMeshChannels !!!
// // 
// // 				pAnim->mNodeName;
// // 			}
// // 		}

		ret = true;
	}
	// Loading failed.
	else
	{
		EVE_LOG_ERROR("File import failed, report: %s", eve::str::to_wstring(pImporter->GetErrorString()));
		// TODO: create error window.
	}

	// Free ASSIMP importer.
	delete pImporter;

	return ret;
}



//=================================================================================================
bool eve::scene::Scene::add(const aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis, const std::string & p_fullPath)
{
	bool ret = false;
	m_pFence->lock();

	eve::scene::Mesh * mesh = eve::scene::Mesh::create_ptr(this, nullptr, p_pMesh, p_pScene, p_upAxis, p_fullPath);
	if (mesh) 
	{
		m_pVecMesh->push_back(mesh);
		ret = true;
	}

	m_pFence->unlock();
	return ret;
}

//=================================================================================================
bool eve::scene::Scene::add(const aiCamera * p_pCamera, const aiScene * p_pScene, eve::Axis p_upAxis)
{
	bool ret = false;
	m_pFence->lock();

	eve::scene::Camera * cam = eve::scene::Camera::create_ptr(this, nullptr, p_pCamera, p_pScene, p_upAxis);
	if (cam)
	{
		m_pVecCamera->push_back(cam);
		if (!m_pCameraActive) { m_pCameraActive = cam; }
		ret = true;
	}

	m_pFence->unlock();
	return ret;
}



//=================================================================================================
void eve::scene::Scene::cb_display(void)
{
	if (m_pCameraActive)
	{
		glViewport(0
				 , 0
				 , static_cast<GLsizei>(m_pCameraActive->getDisplayWidth())
				 , static_cast<GLsizei>(m_pCameraActive->getDisplayHeight()));

		// Enable depth read/write.
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		// Cull triangles which normal is not towards the camera.
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_pShaderMesh->bind();
		m_pCameraActive->oglBind();

		for (auto && itr : (*m_pVecMesh))
		{
			itr->oglDraw();
		}

		m_pCameraActive->oglUnbind();
		m_pShaderMesh->unbind();

		// Disable culling
		glDisable(GL_CULL_FACE);
		// Disable depth read/write
		glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::scene::Scene::set_import_param(eve::scene::SceneImportParam p_param, const std::string & p_value)
{
	auto & itr = m_map_import_params.find(p_param);
	EVE_ASSERT(itr != m_map_import_params.end());
	itr->second = p_value;
}
