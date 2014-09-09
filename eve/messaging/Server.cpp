
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
#include "eve/messaging/Server.h"

#include <sys/timeb.h>

#ifndef __EVE_THREADING_INCLUDES_H__
#include "eve/threading/Includes.h"
#endif



//=================================================================================================
#if defined(EVE_OS_DARWIN)
int localtime_s(tm * _tm, const time_t * time)
{
	tm * posix_local_time_struct = localtime(time);
	if (posix_local_time_struct == NULL) return 1;
	*_tm = *posix_local_time_struct;
	return 0;
}
#endif 



//=================================================================================================
static char * get_current_time(void)
{
#if defined(EVE_OS_WIN)
	static char strCurrTime[35];
	char timeline[26];
	struct _timeb timebuffer;

	_ftime64_s(&timebuffer);
	ctime_s(timeline, 26, &(timebuffer.time));
	
	memset(strCurrTime, 0, sizeof(strCurrTime));	
	sprintf(strCurrTime, "%.8s.%02hu", &timeline[11], timebuffer.millitm);
	
#elif defined(EVE_OS_DARWIN) 
	static time_t curTime;
	struct tm timestamp;
	time(&curTime);
	static char strCurrTime[32];
	localtime_s(&timestamp, &curTime);
	strftime(strCurrTime, sizeof(strCurrTime), "%Y-%m-%d %H:%M:%S", &timestamp);

#endif

	return strCurrTime;
}

//=================================================================================================
static char * get_current_date(void)
{
	static char strCurrDate[17];
	static time_t curTime;
	time(&curTime);

	struct tm timestamp;
	localtime_s(&timestamp, &curTime);

	memset(strCurrDate, 0, sizeof(strCurrDate));
	sprintf(strCurrDate, "%04d-%02d-%02d at %02d:%02d", timestamp.tm_year + 1900, timestamp.tm_mon + 1, timestamp.tm_mday, timestamp.tm_hour, timestamp.tm_min);

	return strCurrDate;
}


eve::messaging::Server * eve::messaging::Server::m_p_server = nullptr;
eve::threading::Mutex *	eve::messaging::Server::m_p_mutex = nullptr;


//=================================================================================================
eve::messaging::Server * eve::messaging::Server::create_instance(const std::string & p_logFilePath)
{
	EVE_ASSERT(!m_p_server);
	EVE_ASSERT(!m_p_mutex);

	m_p_server	= EVE_CREATE_PTR(eve::messaging::Server);
	m_p_mutex	= EVE_CREATE_PTR(eve::threading::Mutex);

	if (p_logFilePath.size() > 0)
	{
		set_log_in_file(set_msg_stream_path(p_logFilePath));
	}

	return m_p_server;
}

//=================================================================================================
void eve::messaging::Server::release_instance(void)
{
	EVE_ASSERT(m_p_server);
	EVE_RELEASE_PTR(m_p_server);

	EVE_ASSERT(m_p_mutex);
	EVE_RELEASE_PTR(eve::messaging::Server::m_p_mutex);
}



//=================================================================================================
eve::messaging::Server::Server(void)
	
	// Inheritance
	: eve::memory::Pointer()

	// Members init
	, m_pHandlerError(nullptr)
	, m_pHandlerWarning(nullptr)
	, m_pHandlerInfo(nullptr)
	, m_pHandlerProgress(nullptr)
	, m_pHandlerDebug(nullptr)

	, m_pStreamError(nullptr)
	, m_pStreamWarning(nullptr)
	, m_pStreamInfo(nullptr)
	, m_pStreamProgress(nullptr)
	, m_pStreamDebug(nullptr)
{}



//=================================================================================================
void eve::messaging::Server::init(void)
{
	// Default mode -> log in console if not in Release mode, else do nothing.
	m_pHandlerError		= &eve::messaging::Server::default_log_error;
	m_pHandlerWarning	= &eve::messaging::Server::default_log_warning;
	m_pHandlerInfo		= &eve::messaging::Server::default_log_info;
	m_pHandlerProgress	= &eve::messaging::Server::default_log_progress;
	m_pHandlerDebug		= &eve::messaging::Server::default_log_debug;
}

//=================================================================================================
void eve::messaging::Server::release(void)
{
	
}



//=================================================================================================
void eve::messaging::Server::default_log_error(const char *funcName, const char *format, ...)
{
#if !defined(NDEBUG)
	
	m_p_mutex->lock();

	va_list arg;

	std::string mess = " [ ERROR ] ";
	mess += get_current_date();
	mess += " ";
	mess += funcName;
	mess += " ";
	mess += format;
	mess += "\n";

	va_start(arg, format);
	vfprintf(stderr, mess.c_str(), arg);
	fflush(stderr);
	va_end(arg);

	m_p_mutex->unlock();
#endif
}

//=================================================================================================
void eve::messaging::Server::default_log_info(const char *funcName, const char *format, ...)
{
#if !defined(NDEBUG)
	
	m_p_mutex->lock();
	
	va_list arg;

	std::string mess = " [ INFO ] ";
	mess += get_current_date();
	mess += " ";
	mess += funcName;
	mess += " ";
	mess += format;

	va_start(arg, format);
	vfprintf(stderr, mess.c_str(), arg);
	fflush(stderr);
	va_end(arg);

	m_p_mutex->unlock();

#endif
}

//=================================================================================================
void eve::messaging::Server::default_log_warning(const char *funcName, const char *format, ...)
{
#if !defined(NDEBUG)
	
	m_p_mutex->lock();

	va_list arg;

	std::string mess = " [ WARNING ] ";
	mess += get_current_date();
	mess += " ";
	mess += funcName;
	mess += " ";
	mess += format;

	va_start(arg, format);
	vfprintf(stderr, mess.c_str(), arg);
	fflush(stderr);
	va_end(arg);

	m_p_mutex->unlock();

#endif
}

//=================================================================================================
void eve::messaging::Server::default_log_progress(const char *funcName, const char *format, ...)
{
#if !defined(NDEBUG)
	
	m_p_mutex->lock();

	va_list arg;

	std::string mess = " [ PROGRESS ] ";
	mess += get_current_date();
	mess += " ";
	mess += funcName;
	mess += " ";
	mess += format;

	va_start(arg, format);
	vfprintf(stderr, mess.c_str(), arg);
	fflush(stderr);
	va_end(arg);

	m_p_mutex->unlock();

#endif
}

//=================================================================================================
void eve::messaging::Server::default_log_debug(const char *funcName, const char *format, ...)
{
#if !defined(NDEBUG)

	m_p_mutex->lock();
	
	va_list arg;

	std::string mess = " [ DEBUG ] ";
	mess += get_current_date();
	mess += " ";
	mess += funcName;
	mess += " ";
	mess += format;

	va_start(arg, format);
	vfprintf(stderr, mess.c_str(), arg);
	fflush(stderr);
	va_end(arg);

	m_p_mutex->unlock();

#endif
}



//=================================================================================================
void eve::messaging::Server::default_log_in_file_error(const char *funcName, const char *format, ...)
{
	m_p_mutex->lock();

	va_list arg;

	std::string mess = " [ ERROR ] ";
	mess += get_current_date();
	mess += " ";
	mess += funcName;
	mess += " ";
	mess += format;

	va_start(arg, format);
	vfprintf(get_error_stream(), mess.c_str(), arg);
	fflush(get_error_stream());
	va_end(arg);

	m_p_mutex->unlock();
}

//=================================================================================================
void eve::messaging::Server::default_log_in_file_info(const char *funcName, const char *format, ...)
{
	m_p_mutex->lock();

	va_list arg;

	std::string mess = " [ INFO ] ";
	mess += get_current_date();
	mess += " ";
	mess += funcName;
	mess += " ";
	mess += format;

	va_start(arg, format);
	vfprintf(get_info_stream(), mess.c_str(), arg);
	fflush(get_info_stream());
	va_end(arg);

	m_p_mutex->unlock();
}

//=================================================================================================
void eve::messaging::Server::default_log_in_file_warning(const char *funcName, const char *format, ...)
{
	m_p_mutex->lock();

	va_list arg;

	std::string mess = " [ WARNING ] ";
	mess += get_current_date();
	mess += " ";
	mess += funcName;
	mess += " ";
	mess += format;

	va_start(arg, format);
	vfprintf(get_warning_stream(), mess.c_str(), arg);
	fflush(get_warning_stream());
	va_end(arg);

	m_p_mutex->unlock();
}

//=================================================================================================
void eve::messaging::Server::default_log_in_file_progress(const char *funcName, const char *format, ...)
{
	m_p_mutex->lock();

	va_list arg;

	std::string mess = " [ PROGRESS ] ";
	mess += get_current_date();
	mess += " ";
	mess += funcName;
	mess += " ";
	mess += format;

	va_start(arg, format);
	vfprintf(get_progress_stream(), mess.c_str(), arg);
	fflush(get_progress_stream());
	va_end(arg);

	m_p_mutex->unlock();
}

//=================================================================================================
void eve::messaging::Server::default_log_in_file_debug(const char *funcName, const char *format, ...)
{
	m_p_mutex->lock();

	va_list arg;

	std::string mess = " [ DEBUG ] ";
	mess += get_current_date();
	mess += " ";
	mess += funcName;
	mess += " ";
	mess += format;

	va_start(arg, format);
	vfprintf(get_debug_stream(), mess.c_str(), arg);
	fflush(get_debug_stream());
	va_end(arg);

	m_p_mutex->unlock();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::messaging::Server::set_log_in_file(bool p_bLogInFile)
{
	m_p_mutex->lock();

#if !defined(NDEBUG)
	EVE_ASSERT(!p_bLogInFile);

	// Default mode -> log in console if not in Release mode, else do nothing.
	m_p_server->m_pHandlerError		= &eve::messaging::Server::default_log_error;
	m_p_server->m_pHandlerWarning	= &eve::messaging::Server::default_log_warning;
	m_p_server->m_pHandlerInfo		= &eve::messaging::Server::default_log_info;
	m_p_server->m_pHandlerProgress	= &eve::messaging::Server::default_log_progress;
	m_p_server->m_pHandlerDebug		= &eve::messaging::Server::default_log_debug;
#else

	if (p_bLogInFile)
	{
		m_p_server->m_pHandlerError		= &eve::messaging::Server::default_log_in_file_error;
		m_p_server->m_pHandlerWarning	= &eve::messaging::Server::default_log_in_file_info;
		m_p_server->m_pHandlerInfo		= &eve::messaging::Server::default_log_in_file_warning;
		m_p_server->m_pHandlerProgress	= &eve::messaging::Server::default_log_in_file_progress;
		m_p_server->m_pHandlerDebug		= &eve::messaging::Server::default_log_in_file_debug;
	}
	else
	{
		m_p_server->m_pHandlerError		= &eve::messaging::Server::default_log_error;
		m_p_server->m_pHandlerWarning	= &eve::messaging::Server::default_log_warning;
		m_p_server->m_pHandlerInfo		= &eve::messaging::Server::default_log_info;
		m_p_server->m_pHandlerProgress	= &eve::messaging::Server::default_log_progress;
		m_p_server->m_pHandlerDebug		= &eve::messaging::Server::default_log_debug;
	}

#endif

	m_p_mutex->unlock();
}



//=================================================================================================
bool eve::messaging::Server::set_error_stream_path(const std::string & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = fopen(p_path.c_str(), "w+");
		set_error_stream(file);

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}

//=================================================================================================
bool eve::messaging::Server::set_warning_stream_path(const std::string & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = fopen(p_path.c_str(), "w+");
		set_warning_stream(file);

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}

//=================================================================================================
bool eve::messaging::Server::set_info_stream_path(const std::string & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = fopen(p_path.c_str(), "w+");
		set_info_stream(file);

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}

//=================================================================================================
bool eve::messaging::Server::set_progress_stream_path(const std::string & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = fopen(p_path.c_str(), "w+");
		set_progress_stream(file);

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}

//=================================================================================================
bool eve::messaging::Server::set_debug_stream_path(const std::string & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = fopen(p_path.c_str(), "w+");
		set_debug_stream(file);

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}

//=================================================================================================
bool eve::messaging::Server::set_msg_stream_path(const std::string & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = fopen(p_path.c_str(), "w+");
		set_msg_stream(file);

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}
