
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
#include "eve/thr/ThreadPool.h"

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 

#ifndef __EVE_THREADING_THREADED_WORK_IO_H__
#include "eve/thr/ThreadedWorkIO.h"
#endif

#ifndef __EVE_THREADING_WORKER_H__
#include "eve/thr/Worker.h"
#endif


//=================================================================================================
eve::thr::ThreadPool * eve::thr::ThreadPool::create_ptr(size_t p_numThread)
{
	eve::thr::ThreadPool * ptr = new eve::thr::ThreadPool(p_numThread);
	ptr->init();
	return ptr;
}



//=================================================================================================
eve::thr::ThreadPool::ThreadPool(size_t p_numThread)

	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_numThread(p_numThread)
	, m_pThreadsActive(nullptr)
	, m_pThreadsSleeping(nullptr)
	, m_pFence(nullptr)
{}



//=================================================================================================
void eve::thr::ThreadPool::init(void)
{
	m_pThreadsActive	= new std::vector<eve::thr::ThreadedWorkIO *>(m_numThread);
	m_pThreadsSleeping	= new std::vector<eve::thr::ThreadedWorkIO *>(m_numThread);

	m_pFence			= EVE_CREATE_PTR(eve::thr::SpinLock);

	
	eve::thr::ThreadedWorkIO * thrd = nullptr;
	for (size_t i = 0; i < m_numThread; i++)
	{
		thrd = EVE_CREATE_PTR(eve::thr::ThreadedWorkIO);
		thrd->setCallbackStart(eve::evt::create_callback_auto(this, &eve::thr::ThreadPool::threadSetActive, thrd));
		thrd->setCallbackExit(eve::evt::create_callback_auto(this, &eve::thr::ThreadPool::threadSetSleeping, thrd));

		m_pThreadsSleeping->push_back(thrd);
	}
}

//=================================================================================================
void eve::thr::ThreadPool::release(void)
{
	m_pFence->lock();

	eve::thr::ThreadedWorkIO * thrd = nullptr;
	while (!m_pThreadsActive->empty())
	{
		thrd = m_pThreadsActive->back();
		m_pThreadsActive->pop_back();

		thrd->stop();
		EVE_RELEASE_PTR(thrd);
	}
	EVE_RELEASE_PTR_CPP(m_pThreadsActive);

	while (!m_pThreadsSleeping->empty())
	{
		thrd = m_pThreadsSleeping->back();
		m_pThreadsSleeping->pop_back();

		thrd->stop();
		EVE_RELEASE_PTR(thrd);
	}
	EVE_RELEASE_PTR_CPP(m_pThreadsSleeping);

	m_pFence->unlock();

	EVE_RELEASE_PTR(m_pFence);
}



//=================================================================================================
void eve::thr::ThreadPool::threadSetActive(eve::thr::ThreadedWorkIO * p_pThread)
{
	m_pFence->lock();
	
	std::vector<eve::thr::ThreadedWorkIO *>::iterator itrE = m_pThreadsSleeping->end();
	std::vector<eve::thr::ThreadedWorkIO *>::iterator itr = std::find(m_pThreadsSleeping->begin(), itrE, p_pThread);
	if (itr != itrE)
	{
		m_pThreadsSleeping->erase(itr);
	}

	m_pThreadsActive->push_back(p_pThread);

	m_pFence->unlock();
}

//=================================================================================================
void eve::thr::ThreadPool::threadSetSleeping(eve::thr::ThreadedWorkIO * p_pThread)
{
	m_pFence->lock();

	std::vector<eve::thr::ThreadedWorkIO *>::iterator itrE = m_pThreadsActive->end();
	std::vector<eve::thr::ThreadedWorkIO *>::iterator itr = std::find(m_pThreadsActive->begin(), itrE, p_pThread);
	if (itr != itrE)
	{
		m_pThreadsActive->erase(itr);
	}

	m_pThreadsSleeping->push_back(p_pThread);

	m_pFence->unlock();
}



//=================================================================================================
void eve::thr::ThreadPool::addWorker(eve::thr::Worker * p_pWorker)
{
	m_pFence->lock();

	if (m_pThreadsSleeping->size() > 0)
	{
		eve::thr::ThreadedWorkIO * thrd = m_pThreadsSleeping->back();
		m_pThreadsSleeping->pop_back();

		thrd->addWorker(p_pWorker);
		m_pThreadsActive->push_back(thrd);
	}
	else
	{
		m_pThreadsActive->front()->addWorker(p_pWorker);
	}

	m_pFence->unlock();
}

//=================================================================================================
void eve::thr::ThreadPool::addPriorityWorker(eve::thr::Worker * p_pWorker)
{
	m_pFence->lock();

	if (m_pThreadsSleeping->size() > 0)
	{
		eve::thr::ThreadedWorkIO * thrd = m_pThreadsSleeping->back();
		m_pThreadsSleeping->pop_back();

		thrd->addPriorityWorker(p_pWorker);
		m_pThreadsActive->push_back(thrd);
	}
	else
	{
		m_pThreadsActive->front()->addPriorityWorker(p_pWorker);
	}

	m_pFence->unlock();
}
