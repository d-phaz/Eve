
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
#ifndef __EVE_MEMORY_SCOPED_H__
#define __EVE_MEMORY_SCOPED_H__


#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif


namespace eve
{
	namespace mem
	{

		/** 
		 * \class eve::mem::Scoped
		 * \brief Scoped pointer template
		 */
		template<class T>
		class Scoped final
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			T *			m_pData;		///< Contained pointer.

			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Scoped)

		public:
			/** \brief Class constructor. */
			explicit Scoped(void);
			/** \brief Class destructor. */
			virtual ~Scoped(void);


			/** \brief Get contained pointer content using '*' operator. */
			T &operator*(void) const;
			/** \brief Retrieve contained pointer using '->' operator. */
			T * operator->(void) const;


			/** \brief Null comparison operator. */
			bool operator!(void) const;
			/** \brief Equal comparison operator. */
			inline bool operator==(const Scoped<T> & p_other) const;
			/** \brief Different comparison operator. */
			inline bool operator!=(const Scoped<T> & p_other) const;


			/** \brief Retrieve contained pointer. */
			T * data(void) const;

			
			/** \brief Release contained pointer and take ownership of new one. */
			void take( T * p_pPtr );
			/** \brief Give ownership of contained pointer. */
			T * give(void);


			/** \brief Give ownership of contained pointer and take ownership of new one. */
			T * reset(T * p_pPtr);

		}; // class Pointer

	} // namespace mem

} // namespace eve


//=================================================================================================
template<class T>
eve::mem::Scoped<T>::Scoped(void)
{
	m_pData = EVE_CREATE_PTR(T);
}

//=================================================================================================
template<class T>
eve::mem::Scoped<T>::~Scoped(void)
{
	EVE_RELEASE_PTR(m_pData);
}



//=================================================================================================
template<class T>
inline T & eve::mem::Scoped<T>::operator*(void) const
{
	EVE_ASSERT(m_pData);
	return *m_pData;
}

//=================================================================================================
template<class T>
inline T * eve::mem::Scoped<T>::operator->(void) const
{
	EVE_ASSERT(m_pData);
	return m_pData;
}



//=================================================================================================
template<class T>
inline bool eve::mem::Scoped<T>::operator!(void) const
{
	return !m_pData;
}

//=================================================================================================
template<class T>
inline bool eve::mem::Scoped<T>::operator==(const Scoped<T> & p_other) const
{
	return this->m_pData == p_other.m_pData;
}

//=================================================================================================
template<class T>
inline bool eve::mem::Scoped<T>::operator!=(const Scoped<T> & p_other) const
{
	return this->m_pData != p_other.m_pData;
}



//=================================================================================================
template<class T>
inline T * eve::mem::Scoped<T>::data(void) const
{
	return this->m_pData;
}



//=================================================================================================
template<class T>
inline void eve::mem::Scoped<T>::take(T * p_pPtr)
{
	EVE_ASSERT(p_pPtr && m_pData != p_pPtr);

	T * oldPtr	= m_pData;
	m_pData		= p_pPtr;

	EVE_RELEASE_PTR(oldPtr);
}

//=================================================================================================
template<class T>
inline T * eve::mem::Scoped<T>::give(void)
{
	T *oldD = m_pData;
	m_pData = nullptr;

	return oldD;
}

//=================================================================================================
template<class T>
T * eve::mem::Scoped<T>::reset(T * p_pPtr)
{
	EVE_ASSERT(p_pPtr && m_pData != p_pPtr);

	T * oldPtr	= m_pData;
	m_pData		= p_pPtr;

	return oldPtr
}

#endif //__EVE_MEMORY_SCOPED_H__
