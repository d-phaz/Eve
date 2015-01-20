
// Main header
#include "eve/scene/Scene.h"

#ifndef __EVE_SCENE_MESH_H__
#include "eve/scene/Mesh.h"
#endif


//=================================================================================================
eve::scene::Scene::Scene(void)
	// Inheritance.
	: eve::ogl::Renderer()
	, eve::scene::EventListenerScene()
	// Members init.
	, m_pVecMesh(nullptr)
{}



//=================================================================================================
void eve::scene::Scene::init(void)
{
	// Call parent class.
	eve::ogl::Renderer::init();

	m_pVecMesh = new std::vector<eve::scene::Mesh*>();
}

//=================================================================================================
void eve::scene::Scene::release(void)
{
	eve::scene::Mesh * mesh = nullptr;
	while (m_pVecMesh->size() > 0)
	{
		mesh = m_pVecMesh->back();
		m_pVecMesh->pop_back();
		EVE_RELEASE_PTR(mesh);
	}
	EVE_RELEASE_PTR_CPP(m_pVecMesh);

	// Call parent class.
	eve::ogl::Renderer::release();
}



//=================================================================================================
void eve::scene::Scene::cb_evtScene(eve::scene::EventArgsScene & p_args)
{
	switch (p_args.type)
	{
	case SceneEventType_add_fromPath:					this->loadFromFilePath(p_args.path); break;
			
	case SceneEventType_add_defaultLightArea:			
	case SceneEventType_add_defaultLightDirectional:	
	case SceneEventType_add_defaultLightPoint:			
	case SceneEventType_add_defaultLightSpot:			

	case SceneEventType_add_defaultCamera:				break;

	default: EVE_ASSERT_FAILURE; break;
	}
}



//=================================================================================================
bool eve::scene::Scene::loadFromFilePath(const std::wstring & p_filePath)
{
	bool ret = false;


	return ret;
}



//=================================================================================================
bool eve::scene::Scene::add(aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis, const std::string & p_fullPath)
{
	bool ret = false;

	eve::scene::Mesh * mesh = eve::scene::Mesh::create_ptr(this, nullptr, p_pMesh, p_pScene, p_upAxis, p_fullPath);
	if (mesh) 
	{
		m_pVecMesh->push_back(mesh);
		ret = true;
	}

	return ret;
}



//=================================================================================================
void eve::scene::Scene::cb_display(void)
{

}



// 
// //=================================================================================================
// scene::Scene::Scene( void )
// 
// 	// Inheritance
// 	: scene::Item( NULL )
// 
// 	// Members init
// 	, m_pImporter					( NULL )
// 
// 	, m_pvecItemCamera				( NULL )
// 	, m_pvecItemMesh				( NULL )
// 	, m_pvecItemLight				( NULL )
// 	, m_pvecItemLightArea			( NULL )
// 	, m_pvecItemLightDirectional	( NULL )
// 	, m_pvecItemLightPoint			( NULL )
// 	, m_pvecItemLightSpot			( NULL )
// {}
// 
// //=================================================================================================
// scene::Scene::~Scene( void )
// {}
// 
// 
// 
// //=================================================================================================
// void scene::Scene::init( void )
// {
// 	m_itemType			= Item_Scene;
// 	m_itemSubType		= Item_Scene_Simple;
// 
// 	// Call parent class
// 	scene::Item::init();
// 
// 	m_pImporter					= scene::Importer::create_ptr();
// 
// 	m_pvecItemCamera			= new std::vector<ItemCameraController*>();
// 	m_pvecItemMesh				= new std::vector<ItemMesh*>();
// 
// 	m_pvecItemLight				= new std::vector<ItemLight*>();
// 	m_pvecItemLightArea			= new std::vector<ItemLightArea*>();
// 	m_pvecItemLightDirectional	= new std::vector<ItemLightDirectional*>();
// 	m_pvecItemLightPoint		= new std::vector<ItemLightPoint*>();
// 	m_pvecItemLightSpot			= new std::vector<ItemLightSpot*>();
// }
// 
// //=================================================================================================
// void scene::Scene::release( void )
// {
// 	if( m_pvecItemCamera!=NULL )
// 	{
// 		ItemCameraController * temp = NULL;
// 
// 		for( size_t i=0; i<m_pvecItemCamera->size(); i++ )
// 		{
// 			temp = (*m_pvecItemCamera)[ i ];
// 			(*m_pvecItemCamera)[ i ] = NULL;
// 			temp->requestRelease();
// 		}
// 		m_pvecItemCamera->clear();
// 		delete m_pvecItemCamera;
// 		m_pvecItemCamera = NULL;
// 	}
// 
// 
// 	if( m_pvecItemLight!=NULL )
// 	{
// 		ItemLight * temp = NULL;
// 
// 		for( size_t i=0; i<m_pvecItemLight->size(); i++ )
// 		{
// 			temp = (*m_pvecItemLight)[ i ];
// 			(*m_pvecItemLight)[ i ] = NULL;
// 			temp->requestRelease();
// 		}
// 		m_pvecItemLight->clear();
// 		delete m_pvecItemLight;
// 		m_pvecItemLight = NULL;
// 	}
// 	if( m_pvecItemLightArea != NULL )
// 	{
// 		m_pvecItemLightArea->clear();
// 		delete m_pvecItemLightArea;
// 		m_pvecItemLightArea = NULL;
// 	}
// 	if( m_pvecItemLightDirectional != NULL )
// 	{
// 		m_pvecItemLightDirectional->clear();
// 		delete m_pvecItemLightDirectional;
// 		m_pvecItemLightDirectional = NULL;
// 	}
// 	if( m_pvecItemLightPoint != NULL )
// 	{
// 		m_pvecItemLightPoint->clear();
// 		delete m_pvecItemLightPoint;
// 		m_pvecItemLightPoint = NULL;
// 	}
// 	if( m_pvecItemLightSpot != NULL )
// 	{
// 		m_pvecItemLightSpot->clear();
// 		delete m_pvecItemLightSpot;
// 		m_pvecItemLightSpot = NULL;
// 	}
// 
// 
// 	if( m_pvecItemMesh!=NULL )
// 	{
// 		ItemMesh * temp = NULL;
// 
// 		for( size_t i=0; i<m_pvecItemMesh->size(); i++ )
// 		{
// 			temp = (*m_pvecItemMesh)[ i ];
// 			(*m_pvecItemMesh)[ i ] = NULL;
// 			temp->requestRelease();
// 		}
// 		m_pvecItemMesh->clear();
// 		delete m_pvecItemMesh;
// 		m_pvecItemMesh = NULL;
// 	}
// 
// 
// 	if( m_pImporter!=NULL )
// 	{
// 		scene::Importer::release_ptr( m_pImporter );
// 		m_pImporter = NULL;
// 	}
// 
// 
// 	// Call parent class
// 	scene::Item::release();
// }
// 
// 
// 
// //=================================================================================================
// void scene::Scene::newControlEventMessage( evt::controlEventArgs & p_eventArgs )
// {
// 	// Nothing to do for now -> kept for future use
// }
// 
// 
// 
// //=================================================================================================
// bool scene::Scene::loadFromFilePath( const std::string & p_filePath )
// {
// 	bool bret = m_pImporter->import( p_filePath, this );
// 
// 	return bret;
// }
// 
// 
// 
// //=================================================================================================
// void scene::Scene::activate( void )
// {
// 	// Register main renderer to view
// 	std::vector<ItemCameraController*>::iterator it			 = m_pvecItemCamera->begin(); 
// 	std::vector<ItemCameraController*>::const_iterator itEnd = m_pvecItemCamera->end();
// 	for( ; it != itEnd; it++ )
// 	{
// 		(*it)->activate();
// 	}
// }
// 
// //=================================================================================================
// void scene::Scene::deactivate( void )
// {
// 	// Unregister main renderer from view
// 	std::vector<ItemCameraController*>::iterator it			 = m_pvecItemCamera->begin(); 
// 	std::vector<ItemCameraController*>::const_iterator itEnd = m_pvecItemCamera->end();
// 	for( ; it != itEnd; it++ )
// 	{
// 		(*it)->deactivate();
// 	}
// }
// 
// 
// 
// //=================================================================================================
// bool scene::Scene::addItem( aiCamera * pCam, const aiScene * p_pScene, const Vec3f & p_upAxis )
// {
// 	bool breturn = false;
// 
// 	scene::ItemCameraController * cam = scene::ItemCameraController::create_ptr( this, pCam, p_pScene, p_upAxis );
// 	if( cam != NULL ) 
// 	{
// 		m_pvecItemCamera->push_back( cam );
// 		breturn = true;
// 	}
// 
// 	return breturn;
// }
// 
// //=================================================================================================
// bool scene::Scene::addItem( aiLight * pLight, const aiScene * p_pScene, const Vec3f & p_upAxis )
// {
// 	bool breturn = false;
// 
// 	scene::ItemLight * light = NULL;
// 
// 	switch( pLight->mType )
// 	{
// 	case aiLightSource_DIRECTIONAL:
// 		{
// 			light = scene::ItemLightDirectional::create_ptr( this, pLight, p_pScene, p_upAxis );
// 			if( light != NULL ) {
// 				m_pvecItemLightDirectional->push_back( (scene::ItemLightDirectional*)light );
// 			}
// 		}
// 		break;
// 
// 	case aiLightSource_POINT:
// 		{
// 			light = scene::ItemLightPoint::create_ptr( this, pLight, p_pScene, p_upAxis );
// 			if( light != NULL ) {
// 				m_pvecItemLightPoint->push_back( (scene::ItemLightPoint*)light );
// 			}
// 		}
// 		break;
// 
// 	case aiLightSource_SPOT:
// 		{
// 			light = scene::ItemLightSpot::create_ptr( this, pLight, p_pScene, p_upAxis );
// 			if( light != NULL ) {
// 				m_pvecItemLightSpot->push_back( (scene::ItemLightSpot*)light );
// 			}
// 		}
// 		break;
// 	}
// 
// 	if( light != NULL ) 
// 	{
// 		m_pvecItemLight->push_back( light );
// 		breturn = true;
// 	}
// 
// 	return breturn;
// }
// 
// //=================================================================================================
// bool scene::Scene::addItem( aiMesh * pMesh, const aiScene * p_pScene, const Vec3f & p_upAxis, const std::string & p_fullPath )
// {
// 	bool breturn = false;
// 
// 	scene::ItemMesh * mesh = scene::ItemMesh::create_ptr( this, pMesh, p_pScene, p_upAxis, p_fullPath );
// 	if( mesh != NULL ) 
// 	{
// 		m_pvecItemMesh->push_back( mesh );
// 		breturn = true;
// 	}
// 
// 	return breturn;
// }
// 
// 
// 
// //=================================================================================================
// void scene::Scene::addCamera( void )
// {
// 	scene::ItemCameraController * cam = scene::ItemCameraController::create_ptr( this );
// 	m_pvecItemCamera->push_back( cam );
// }
// 
// 
// 
// //=================================================================================================
// void scene::Scene::addLightArea( void )
// {
// 	scene::ItemLightArea * light = scene::ItemLightArea::create_ptr( this );
// 	m_pvecItemLight->push_back( light );
// 	m_pvecItemLightArea->push_back( light );
// }
// 
// //=================================================================================================
// void scene::Scene::addLightDirectional(void)
// {
// 	scene::ItemLightDirectional * light = scene::ItemLightDirectional::create_ptr( this );
// 	m_pvecItemLight->push_back( light );
// 	m_pvecItemLightDirectional->push_back( light );
// }
// 
// //=================================================================================================
// void scene::Scene::addLightPoint( void )
// {
// 	scene::ItemLightPoint * light = scene::ItemLightPoint::create_ptr( this );
// 	m_pvecItemLight->push_back( light );
// 	m_pvecItemLightPoint->push_back( light );
// }
// 
// //=================================================================================================
// void scene::Scene::addLightSpot( void )
// {
// 	scene::ItemLightSpot * light = scene::ItemLightSpot::create_ptr( this );
// 	m_pvecItemLight->push_back( light );
// 	m_pvecItemLightSpot->push_back( light );
// }

