
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

#pragma once
#ifndef __EVE_UI_WIDGET_H__
#define __EVE_UI_WIDGET_H__

#ifndef __EVE_MEMORY_POINTER_H__
#include "eve/mem/Pointer.h"
#endif 

#ifndef __EVE_MATH_TYPES_H__
#include "eve/math/Types.h"
#endif


namespace eve
{
	namespace ui
	{
		/** 
		* \class eve::ui::Widget.
		*
		* \brief Abstract base ui object, all and each ui objects inherit from this class.
		* Widget also act as containers and propagate position, size, states to children.
		* Widget size and position may change depending on added or removed children.
		*
		* \note extends eve::mem::Pointer
		*/
		class Widget
			: public eve::mem::Pointer
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			static eve::ui::Widget *		m_p_widget_active;		//!< Specifies current active widget (shared pointer).

		protected:
			eve::ui::Widget *				m_pParent;				//!< Specifies parent widget (shared pointer).
			std::list<eve::ui::Widget*> *	m_pChildren;			//!< Specifies children list.

		protected:
			int32_t							m_x;					//!< Specifies widget position on X axis.
			int32_t							m_y;					//!< Specifies widget position on Y axis.
			int32_t							m_width;				//!< Specifies widget width.
			int32_t							m_height;				//!< Specifies widget height.

		protected:
			bool							m_bEnabled;				//!< Specifies enabled state (default to false).
			bool							m_bVisible;				//!< SPecifies visible state (default to false).
			bool							m_bSelected;			//!< Specifies selected state (default to false).


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Widget);
			EVE_PUBLIC_DESTRUCTOR(Widget);

		public:
			/** \brief Class default constructor. */
			explicit Widget(void);
			/** \brief Class constructor. */
			explicit Widget(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);
			/** \brief Class constructor. */
			explicit Widget(const eve::vec2i & p_position, const eve::vec2i & p_size);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members, propagates to children. (pure virtual) */
			virtual void release(void) override;


		public:
			/**
			* \brief Add child to widget.
			* Takes ownership of target widget \a p_pWidget.
			* Return false if widget already is registered.
			*/
			bool addChild(eve::ui::Widget * p_pWidget);
			/**
			* \brief Unregister a widget pointer.
			* Return false if widget is not registered.
			*/
			bool removeChild(eve::ui::Widget * p_pWidget);
			/**
			* \brief Unregister and release a widget pointer.
			* Return false if widget is not registered.
			*/
			bool releaseChild(eve::ui::Widget * p_pWidget);


		protected:
			/** \brief Update position based on children. */
			void childUpdatePosition(void);
			/** \brief Update size based on children. */
			void childUpdateSize(void);

			/** \brief Update widget based on children. */
			void childUpdate(void);


		public:
			/** \brief Enable widget and propagate to children. */
			virtual void enable(void);
			/** \brief Disable widget and propagate to children. */
			virtual void disnable(void);


		public:
			/** \brief Show widget and propagate to children. */
			virtual void show(void);
			/** \brief Hide widget and propagate to children. */
			virtual void hide(void);


		public:
			/** \brief Select widget and propagate to children. */
			virtual void select(void);
			/** \brief Unselect widget and propagate to children. */
			virtual void unselect(void);


		protected:
			/** \brief Test position is inside widget. */
			bool inside(int32_t p_x, int32_t p_y);
			/** \brief Test position is inside widget. */
			bool inside(const eve::vec2i & p_position);


		protected:
			/** \brief Translate object on both axis and propagate to children. */
			void translate(int32_t p_x, int32_t p_y);
			/** \brief Translate object on both axis and propagate to children. */
			void translate(const eve::vec2i & p_value);
			/** \brief Translate object on X axis and propagate to children. */
			void translateX(int32_t p_value);
			/** \brief Translate object on Y axis and propagate to children. */
			void translateY(int32_t p_value);


			/** \brief Inflate object on both axis (rise its size) and propagate to children. */
			void inflate(int32_t p_width, int32_t p_height);
			/** \brief Inflate object on both axis (rise its size) and propagate to children. */
			void inflate(const eve::vec2i & p_value);
			/** \brief Inflate object on X axis (rise its width) and propagate to children. */
			void inflateX(int32_t p_value);
			/** \brief Inflate object on Y axis (rise its height) and propagate to children. */
			void inflateY(int32_t p_value);


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get active widget. */
			static eve::ui::Widget * get_widget_active(void);


		public:
			/** \brief Get parent widget. */
			eve::ui::Widget * getParent(void) const;
			/** \brief Set parent. */
			void setParent(eve::ui::Widget * p_pParent);


		public:
			/** \brief Get children list. */
			std::list<eve::ui::Widget*> * getChildren(void) const;


		public:
			/** \brief Get position. */
			const eve::vec2i getPosition(void) const;
			/** \brief Get position on X axis. */
			int32_t getPositionX(void) const;
			/** \brief Get position on Y axis. */
			int32_t getPositionY(void) const;

			/** \brief Set position. */
			void setPosition(int32_t p_x, int32_t p_y);
			/** \brief Set position. */
			void setPosition(const eve::vec2i & p_value);
			/** \brief Set position on X axis. */
			void setPositionX(int32_t p_value);
			/** \brief Set position on Y axis. */
			void setPositionY(int32_t p_value);


		public:
			/** \brief Get size. */
			const eve::vec2i getSize(void) const;
			/** \brief Get width. */
			int32_t getWidth(void);
			/** \brief Get height. */
			int32_t getHeight(void);

			/** \brief Set size. */
			void setSize(int32_t p_width, int32_t p_height);
			/** \brief Set size. */
			void setSize(const eve::vec2i & p_value);
			/** \brief Set width */
			void setWidth(int32_t p_value);
			/** \brief Set height */
			void setHeight(int32_t p_value);


		public:
			/** \brief Get enabled state. */
			bool isEnabled(void);
			/** \brief Get visible state. */
			bool isVisible(void);
			/** \brief Get selected state. */
			bool isSelected(void);

		}; // class Widget

	} // namespace ui

} // namespace eve

///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
EVE_FORCE_INLINE eve::ui::Widget * eve::ui::Widget::get_widget_active(void) { return m_p_widget_active; }


//=================================================================================================
EVE_FORCE_INLINE eve::ui::Widget *				eve::ui::Widget::getParent(void) const		{ return m_pParent; }
EVE_FORCE_INLINE std::list<eve::ui::Widget*> *	eve::ui::Widget::getChildren(void) const	{ return m_pChildren; }


//=================================================================================================
EVE_FORCE_INLINE const eve::vec2i	eve::ui::Widget::getPosition(void) const	{ return eve::vec2i(m_x, m_y);	}
EVE_FORCE_INLINE int32_t			eve::ui::Widget::getPositionX(void) const	{ return m_x; }
EVE_FORCE_INLINE int32_t			eve::ui::Widget::getPositionY(void) const	{ return m_y; }


//=================================================================================================
EVE_FORCE_INLINE const eve::vec2i   eve::ui::Widget::getSize(void) const		{ return eve::vec2i(m_width, m_height);	}
EVE_FORCE_INLINE int32_t			eve::ui::Widget::getWidth(void)				{ return m_width; }
EVE_FORCE_INLINE int32_t			eve::ui::Widget::getHeight(void)			{ return m_height; }


//=================================================================================================
EVE_FORCE_INLINE bool				eve::ui::Widget::isEnabled(void)			{ return m_bEnabled;	}
EVE_FORCE_INLINE bool				eve::ui::Widget::isVisible(void)			{ return m_bVisible;	}
EVE_FORCE_INLINE bool				eve::ui::Widget::isSelected(void)			{ return m_bSelected;	}

#endif // __EVE_UI_WIDGET_H__
