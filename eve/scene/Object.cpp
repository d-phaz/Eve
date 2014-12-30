
// Main header
#include "scene/Item.h"

#ifndef __GL_BOX_3D_CORNERED_H__
#include "gl/primitive/Box3DCornered.h"
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////
//		scene::Item class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
scene::Item::Item( scene::Item * pParent )

	// Inheritance
	: EventListenner()

	// Members initialization
	, m_name				()

	, m_itemType			( Item_UNDEFINED )
	, m_itemSubType			( Item_SUBUNDEFINED )

	, m_pItemParent			( pParent )

	, m_bVisible			( true )
	, m_bLocked				( false )

	, m_pBox				( NULL )

#ifndef NDEBUG
	, m_bReleaseEnforcer	( false )
#endif
{}

//=================================================================================================
scene::Item::~Item( void )
{
#ifndef NDEBUG
	NATIVE_ASSERT( m_bReleaseEnforcer );
#endif
}



//=================================================================================================
void scene::Item::init( void )
{
#ifndef NDEBUG
	NATIVE_ASSERT( (m_itemSubType!=Item_SUBUNDEFINED) );
#endif

	m_objectType = ObjectID_t( m_itemSubType, this, m_pItemParent );
}

//=================================================================================================
void scene::Item::release( void )
{
	if( m_pBox != NULL )
	{
		m_pBox->requestRelease();
		m_pBox = NULL;
	}


	m_bVisible = true;
	m_bLocked  = false;

	// Do not delete -> shared pointer
	m_pItemParent = NULL;

	m_itemType		= Item_UNDEFINED;
	m_itemSubType	= Item_SUBUNDEFINED;


	// De initialization enforcer
#ifndef NDEBUG
	m_bReleaseEnforcer = true;
#endif
}



//=================================================================================================
bool scene::Item::hitTestBox( const Vec3f & p_origin, const Vec3f & p_direction )
{
	return this->hitTestBox( Rayf(p_origin, p_direction) );
}

//=================================================================================================
bool scene::Item::hitTestBox( const Rayf & p_ray )
{
#ifndef NDEBUG
	NATIVE_ASSERT( m_pBox!=NULL );
#endif

	return m_pBox->intersects( p_ray );
}
