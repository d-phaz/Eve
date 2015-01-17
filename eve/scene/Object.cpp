
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
#include "eve/scene/Object.h"


//=================================================================================================
eve::scene::Object::Object(eve::scene::Scene * p_pScene, eve::scene::Object * p_pParent)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_name()
	, m_objectType(eve::scene::SceneObject_UNDEFINED)
	, m_pScene(p_pScene)
	, m_pParent(p_pParent)
	, m_bVisible(true)
	, m_bLocked(false)
{}



//=================================================================================================
void eve::scene::Object::init(void)
{
	EVE_ASSERT(m_objectType != eve::scene::SceneObject_UNDEFINED);
}

//=================================================================================================
void eve::scene::Object::release(void)
{
	m_bVisible	 = true;
	m_bLocked	 = false;
	m_objectType = eve::scene::SceneObject_UNDEFINED;

	// Do not delete -> shared pointers.
	m_pScene  = nullptr;
	m_pParent = nullptr;
}
