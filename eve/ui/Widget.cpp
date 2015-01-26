
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
#include "eve/ui/Widget.h"


eve::ui::Widget * eve::ui::Widget::m_p_widget_active = nullptr;


//=================================================================================================
eve::ui::Widget::Widget(void)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_pParent(nullptr)
	, m_pChildren(nullptr)
	, m_position(eve::vec2i::zero())
	, m_size(eve::vec2i::zero())
	, m_bEnabled(false)
	, m_bVisible(false)
	, m_bSelected(false)
{}

//=================================================================================================
eve::ui::Widget::Widget(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_pParent(nullptr)
	, m_pChildren(nullptr)
	, m_position(p_x, p_y)
	, m_size(p_width, p_height)
	, m_bEnabled(false)
	, m_bVisible(false)
	, m_bSelected(false)
{}

//=================================================================================================
eve::ui::Widget::Widget(const eve::vec2i & p_position, const eve::vec2i & p_size)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_pParent(nullptr)
	, m_pChildren(nullptr)
	, m_position(p_position)
	, m_size(p_size)
	, m_bEnabled(false)
	, m_bVisible(false)
	, m_bSelected(false)
{}



//=================================================================================================
void eve::ui::Widget::init(void)
{
	m_pChildren = new std::list<eve::ui::Widget*>();
}

//=================================================================================================
void eve::ui::Widget::release(void)
{
	eve::ui::Widget * child = nullptr;
	while (!m_pChildren->empty())
	{
		child = m_pChildren->back();
		m_pChildren->pop_back();
		EVE_RELEASE_PTR(child);
	}
	EVE_RELEASE_PTR_CPP(m_pChildren);

	// Do not delete -> shared pointer.
	m_pParent = nullptr;
}



//=================================================================================================
bool eve::ui::Widget::addChild(eve::ui::Widget * p_pWidget)
{
	std::list<eve::ui::Widget*>::iterator itr = std::find(m_pChildren->begin(), m_pChildren->end(), p_pWidget);
	bool breturn = (itr == m_pChildren->end());
	if (breturn)
	{
		m_pChildren->push_back(p_pWidget);
		p_pWidget->setParent(this);

		this->childUpdate();
	}
	return breturn;
}

//=================================================================================================
bool eve::ui::Widget::removeChild(eve::ui::Widget * p_pWidget)
{
	std::list<eve::ui::Widget*>::iterator itr = std::find(m_pChildren->begin(), m_pChildren->end(), p_pWidget);
	bool breturn = (itr != m_pChildren->end());
	if (breturn)
	{
		m_pChildren->erase(itr);

		this->childUpdate();
	}
	return breturn;
}

//=================================================================================================
bool eve::ui::Widget::releaseChild(eve::ui::Widget * p_pWidget)
{
	std::list<eve::ui::Widget*>::iterator itr = std::find(m_pChildren->begin(), m_pChildren->end(), p_pWidget);
	bool breturn = (itr != m_pChildren->end());
	if (breturn)
	{
		eve::ui::Widget * child = (*itr);
		m_pChildren->erase(itr);
		EVE_RELEASE_PTR(child);

		this->childUpdate();
	}
	return breturn;
}



//=================================================================================================
void eve::ui::Widget::childUpdatePosition(void)
{
// 	int32_t temp_posX = 0;
// 	int32_t temp_posY = 0;
// 
// 	int32_t min_posX = INT_MAX;
// 	int32_t min_posY = INT_MAX;
// 
// 	// Iterate threw items.
// 	for (auto && itr : (*m_pChildren))
// 	{
// 		temp_posX = itr->getPositionX();
// 		temp_posY = itr->getPositionY();
// 
// 		if (temp_posX < min_posX) { min_posX = temp_posX; }
// 		if (temp_posY < min_posY) { min_posY = temp_posY; }
// 	}
// 
// 	m_position.x = min_posX;
// 	m_position.y = min_posY;	
}

//=================================================================================================
void eve::ui::Widget::childUpdateSize(void)
{
	int32_t temp_width   = 0;
	int32_t temp_height	 = 0;

	int32_t total_width  = m_size.x;
	int32_t total_height = m_size.y;

	// Iterate threw items to accumulate size.
	for (auto && itr : (*m_pChildren))
	{
		// Width
		temp_width = itr->getPositionX() - m_position.x + itr->getWidth();
		if (temp_width > total_width) {
			total_width = temp_width;
		}
		// Height
		temp_height = itr->getPositionY() - m_position.y + itr->getHeight();
		if (temp_height > total_height) {
			total_height = temp_height;
		}
	}

	m_size.x = total_width;
	m_size.y = total_height;
}

//=================================================================================================
void eve::ui::Widget::childUpdate(void)
{
	this->childUpdateSize();
}



//=================================================================================================
void eve::ui::Widget::enable(void)
{
	m_bEnabled = true;
	for (auto && itr : (*m_pChildren))
	{
		itr->enable();
	}
}

//=================================================================================================
void eve::ui::Widget::disnable(void)
{
	m_bEnabled = false;
	for (auto && itr : (*m_pChildren))
	{
		itr->disnable();
	}
}



//=================================================================================================
void eve::ui::Widget::show(void)
{
	m_bVisible = true;
	for (auto && itr : (*m_pChildren))
	{
		itr->show();
	}
}

//=================================================================================================
void eve::ui::Widget::hide(void)
{
	m_bVisible = false;
	for (auto && itr : (*m_pChildren))
	{
		itr->hide();
	}
}



//=================================================================================================
void eve::ui::Widget::select(void)
{
	m_bSelected = true;
	for (auto && itr : (*m_pChildren))
	{
		itr->select();
	}
}

//=================================================================================================
void eve::ui::Widget::unselect(void)
{
	m_bSelected = false;
	for (auto && itr : (*m_pChildren))
	{
		itr->unselect();
	}
}



//=================================================================================================
bool eve::ui::Widget::inside(int32_t p_x, int32_t p_y)
{
	bool bret = (p_x >= m_position.x) && (p_x <= m_position.x + m_size.x) &&
				(p_y >= m_position.y) && (p_y <= m_position.y + m_size.y);
	return bret;
}

//=================================================================================================
bool eve::ui::Widget::inside(const eve::vec2i & p_position)
{
	return this->inside(p_position.x, p_position.y);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::ui::Widget::setParent(eve::ui::Widget * p_pParent)
{
	// STock parent.
	m_pParent = p_pParent;

	// Propagate states.
	if (m_pParent->isEnabled())		{ this->enable();	}
	else							{ this->disnable(); }

	if (m_pParent->isVisible())		{ this->show();		}
	else							{ this->hide();		}

	if (m_pParent->isSelected())	{ this->select();	}
	else							{ this->unselect(); }
}



//=================================================================================================
void eve::ui::Widget::setPosition(int32_t p_x, int32_t p_y)
{
	eve::vec2i deport(p_x - m_position.x, p_y - m_position.y);
	m_position.x = p_x;
	m_position.y = p_y;
	for (auto && itr : (*m_pChildren))
	{
		itr->setPosition(itr->getPosition() + deport);
	}
}

//=================================================================================================
void eve::ui::Widget::setPosition(const eve::vec2i & p_value)
{
	eve::vec2i deport = p_value - m_position;
	m_position = p_value;
	for (auto && itr : (*m_pChildren))
	{
		itr->setPosition(itr->getPosition() + deport);
	}
}

//=================================================================================================
void eve::ui::Widget::setPositionX(int32_t p_value)
{
	int32_t deport = p_value - m_position.x;
	m_position.x = p_value;
	for (auto && itr : (*m_pChildren))
	{
		itr->setPositionX(itr->getPositionX() + deport);
	}
}

//=================================================================================================
void eve::ui::Widget::setPositionY(int32_t p_value)
{
	int32_t deport = p_value - m_position.y;
	m_position.y = p_value;
	for (auto && itr : (*m_pChildren))
	{
		itr->setPositionY(itr->getPositionY() + deport);
	}
}



//=================================================================================================
void eve::ui::Widget::setSize(int32_t p_width, int32_t p_height)
{
	eve::vec2i deport(p_width - m_size.x, p_height - m_size.y);
	m_size.x = p_width;
	m_size.y = p_height;
	for (auto && itr : (*m_pChildren))
	{
		itr->setSize(itr->getSize() + deport);
	}
}

//=================================================================================================
void eve::ui::Widget::setSize(const eve::vec2i & p_value)
{
	eve::vec2i deport = p_value - m_size;
	m_size = p_value;
	for (auto && itr : (*m_pChildren))
	{
		itr->setSize(itr->getSize() + deport);
	}
}

//=================================================================================================
void eve::ui::Widget::setWidth(int32_t p_value)
{
	int32_t deport = p_value - m_size.x;
	m_size.x = p_value;
	for (auto && itr : (*m_pChildren))
	{
		itr->setWidth(itr->getWidth() + deport);
	}
}

//=================================================================================================
void eve::ui::Widget::setHeight(int32_t p_value)
{
	int32_t deport = p_value - m_size.y;
	m_size.y = p_value;
	for (auto && itr : (*m_pChildren))
	{
		itr->setHeight(itr->getHeight() + deport);
	}
}
