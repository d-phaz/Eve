
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
	, m_x(0)
	, m_y(0)
	, m_width(0)
	, m_height(0)
	, m_bEnabled(false)
	, m_bSelected(false)
	, m_bVisible(false)
	, m_bPaint(false)
{}

//=================================================================================================
eve::ui::Widget::Widget(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_pParent(nullptr)
	, m_pChildren(nullptr)
	, m_x(p_x)
	, m_y(p_y)
	, m_width(p_width)
	, m_height(p_height)
	, m_bEnabled(false)
	, m_bSelected(false)
	, m_bVisible(false)
	, m_bPaint(false)
{}

//=================================================================================================
eve::ui::Widget::Widget(const eve::vec2i & p_position, const eve::vec2i & p_size)
	// Inheritance
	: eve::mem::Pointer()
	// Members init
	, m_pParent(nullptr)
	, m_pChildren(nullptr)
	, m_x(p_position.x)
	, m_y(p_position.y)
	, m_width(p_size.x)
	, m_height(p_size.y)
	, m_bEnabled(false)
	, m_bSelected(false)
	, m_bVisible(false)
	, m_bPaint(false)
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
		p_pWidget->setParentWidget(this);

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

	int32_t total_width  = m_width;
	int32_t total_height = m_height;

	// Iterate threw items to accumulate size.
	for (auto && itr : (*m_pChildren))
	{
		// Width
		temp_width = itr->getPositionX() - m_x + itr->getWidth();
		if (temp_width > total_width) {
			total_width = temp_width;
		}
		// Height
		temp_height = itr->getPositionY() - m_y + itr->getHeight();
		if (temp_height > total_height) {
			total_height = temp_height;
		}
	}

	m_width  = total_width;
	m_height = total_height;
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
void eve::ui::Widget::show(void)
{
	m_bVisible = true;
	for (auto && itr : (*m_pChildren))
	{
		itr->show();
	}
	this->requestPaint();
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
void eve::ui::Widget::requestPaint(void)
{
	m_bPaint = true;
	for (auto && itr : (*m_pChildren))
	{
		itr->requestPaint();
	}
}

//=================================================================================================
bool eve::ui::Widget::needPaint(void)
{
	return (m_bPaint && m_bVisible);
}



//=================================================================================================
void eve::ui::Widget::oglDrawColored(void)
{
	m_bPaint = false;
	for (auto && itr : (*m_pChildren))
	{
		if (itr->needPaint())
		{
			itr->oglDrawColored();
		}
	}
}

//=================================================================================================
void eve::ui::Widget::oglDrawTextured(void)
{
	m_bPaint = false;
	for (auto && itr : (*m_pChildren))
	{
		if (itr->needPaint())
		{
			itr->oglDrawTextured();
		}
	}
}



//=================================================================================================
bool eve::ui::Widget::inside(int32_t p_x, int32_t p_y)
{
	bool bret = (p_x >= m_x) && (p_x <= m_x + m_width) &&
				(p_y >= m_y) && (p_y <= m_y + m_height);
	return bret;
}

//=================================================================================================
bool eve::ui::Widget::inside(const eve::vec2i & p_position)
{
	return this->inside(p_position.x, p_position.y);
}



//=================================================================================================
void eve::ui::Widget::translate(int32_t p_x, int32_t p_y)
{
	m_x += p_x;
	m_y += p_y;
	for (auto && itr : (*m_pChildren))
	{
		itr->translate(p_x, p_y);
	}
}

//=================================================================================================
void eve::ui::Widget::translate(const eve::vec2i & p_value)
{
	this->translate(p_value.x, p_value.y);
}

//=================================================================================================
void eve::ui::Widget::translateX(int32_t p_value)
{
	m_x += p_value;
	for (auto && itr : (*m_pChildren))
	{
		itr->translateX(p_value);
	}
}

//=================================================================================================
void eve::ui::Widget::translateY(int32_t p_value)
{
	m_y += p_value;
	for (auto && itr : (*m_pChildren))
	{
		itr->translateX(p_value);
	}
}



//=================================================================================================
void eve::ui::Widget::inflate(int32_t p_width, int32_t p_height)
{
	float ratioX = 0.0f;
	float ratioY = 0.0f;

	for (auto && itr : (*m_pChildren))
	{
		ratioX = static_cast<float>(itr->getWidth())  / static_cast<float>(m_width);
		ratioY = static_cast<float>(itr->getHeight()) / static_cast<float>(m_height);

		itr->inflate(static_cast<int32_t>(static_cast<float>(p_width) * ratioX)
			       , static_cast<int32_t>(static_cast<float>(p_height) * ratioY));
	}

	m_width  += p_width;
	m_height += p_height;
}

//=================================================================================================
void eve::ui::Widget::inflate(const eve::vec2i & p_value)
{
	this->inflate(p_value.x, p_value.y);
}

//=================================================================================================
void eve::ui::Widget::inflateX(int32_t p_value)
{
	float ratio = 0.0f;

	for (auto && itr : (*m_pChildren))
	{
		ratio = static_cast<float>(itr->getWidth()) / static_cast<float>(m_width);
		itr->inflateX(static_cast<int32_t>(static_cast<float>(p_value) * ratio));
	}

	m_width += p_value;
}

//=================================================================================================
void eve::ui::Widget::inflateY(int32_t p_value)
{
	float ratio = 0.0f;

	for (auto && itr : (*m_pChildren))
	{
		ratio = static_cast<float>(itr->getHeight()) / static_cast<float>(m_height);
		itr->inflateY(static_cast<int32_t>(static_cast<float>(p_value) * ratio));
	}

	m_height += p_value;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::ui::Widget::setParentWidget(eve::ui::Widget * p_pParent)
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
	int32_t deportX(p_x - m_x);
	int32_t deportY(p_y - m_y);
	this->translate(deportX, deportY);
}

//=================================================================================================
void eve::ui::Widget::setPosition(const eve::vec2i & p_value)
{
	this->setPosition(p_value.x, p_value.y);
}

//=================================================================================================
void eve::ui::Widget::setPositionX(int32_t p_value)
{
	int32_t deport = p_value - m_x;
	this->translateX(deport);
}

//=================================================================================================
void eve::ui::Widget::setPositionY(int32_t p_value)
{
	int32_t deport = p_value - m_y;
	this->translateY(deport);
}



//=================================================================================================
void eve::ui::Widget::setSize(int32_t p_width, int32_t p_height)
{
	int32_t deportX(p_width - m_width);
	int32_t deportY(p_height - m_height);
	this->inflate(deportX, deportY);
}

//=================================================================================================
void eve::ui::Widget::setSize(const eve::vec2i & p_value)
{
	this->setSize(p_value.x, p_value.y);
}

//=================================================================================================
void eve::ui::Widget::setWidth(int32_t p_value)
{
	int32_t deport = p_value - m_width;
	this->inflateX(deport);
}

//=================================================================================================
void eve::ui::Widget::setHeight(int32_t p_value)
{
	int32_t deport = p_value - m_height;
	this->inflateY(deport);
}
