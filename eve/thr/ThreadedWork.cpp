
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
#include "eve/thr/ThreadedWork.h"

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 

#ifndef __EVE_THREADING_WORKER_H__
#include "eve/thr/Worker.h"
#endif


//=================================================================================================
eve::thr::ThreadedWork::ThreadedWork(void)

	// Inheritance
	: eve::thr::Thread()

	// Members init
	, m_pWorkers(nullptr)
{}



//=================================================================================================
void eve::thr::ThreadedWork::init(void)
{
	// Call parent class.
	eve::thr::Thread::init();

	m_pWorkers = new std::deque<eve::thr::Worker *>();
}

//=================================================================================================
void eve::thr::ThreadedWork::release(void)
{
	eve::thr::Worker * wk = nullptr;
	for (auto & it : (*m_pWorkers))
	{
		wk = it;
		it = nullptr;
		EVE_RELEASE_PTR(wk);
	}
	m_pWorkers->clear();
	EVE_RELEASE_PTR_CPP(m_pWorkers);

	// Call parent class.
	eve::thr::Thread::release();
}



//=================================================================================================
void eve::thr::ThreadedWork::initThreadedData(void)
{
	// Nothing to do for now.
}

//=================================================================================================
void eve::thr::ThreadedWork::releaseThreadedData(void)
{
	// Nothing to do for now.
}



//=================================================================================================
void eve::thr::ThreadedWork::addWorker(eve::thr::Worker * p_pWorker)
{
	EVE_ASSERT(p_pWorker);

	m_pFence->lock();

	bool needStart = m_pWorkers->empty();
	m_pWorkers->push_back(p_pWorker);

	if (needStart)
	{
		this->start();
	}

	m_pFence->unlock();
}

//=================================================================================================
void eve::thr::ThreadedWork::addPriorityWorker(eve::thr::Worker * p_pWorker)
{
	EVE_ASSERT(p_pWorker);

	m_pFence->lock();

	bool needStart = m_pWorkers->empty();
	m_pWorkers->push_front(p_pWorker);

	if (needStart)
	{
		this->start();
	}
	
	m_pFence->unlock();
}



//=================================================================================================
void eve::thr::ThreadedWork::run(void)
{
	while (!m_pWorkers->empty())
	{
		// Grab next worker.
		m_pFence->lock();		
		eve::thr::Worker * worker = m_pWorkers->front();
		m_pWorkers->pop_front();
		m_pFence->unlock();

		// Do work.
		worker->beforeWork();
		while (worker->work());
		worker->afterWork();

		EVE_RELEASE_PTR(worker);
	}
}
