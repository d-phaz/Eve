
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
#include "eve/mess/Server.h"

#include <sys/timeb.h>

#ifndef __EVE_OPENGL_DEBUG_H__
#include "eve/ogl/Debug.h"
#endif



//=================================================================================================
#if defined(EVE_OS_DARWIN)
int localtime_s(tm * _tm, const time_t * time)
{
	tm * posix_local_time_struct = localtime(time);
	if (!posix_local_time_struct) return 1;
	*_tm = *posix_local_time_struct;
	return 0;
}
#endif 

//=================================================================================================
static wchar_t * get_current_date(void)
{
	static wchar_t strCurrDate[17];
	static time_t curTime;
	time(&curTime);

	struct tm timestamp;
	localtime_s(&timestamp, &curTime);

	memset(strCurrDate, 0, sizeof(strCurrDate));
	swprintf(strCurrDate, sizeof(strCurrDate), EVE_TXT("[%04d-%02d-%02d %02d:%02d]"), timestamp.tm_year + 1900, timestamp.tm_mon + 1, timestamp.tm_mday, timestamp.tm_hour, timestamp.tm_min);

	return strCurrDate;
}


eve::mess::Server *	eve::mess::Server::m_p_server	= nullptr;
eve::thr::SpinLock *	eve::mess::Server::m_p_mutex	= nullptr;


//=================================================================================================
eve::mess::Server * eve::mess::Server::create_instance(const std::wstring & p_logFilePath)
{
	EVE_ASSERT(!m_p_server);
	EVE_ASSERT(!m_p_mutex);

	m_p_server	= EVE_CREATE_PTR(eve::mess::Server);
	m_p_mutex	= EVE_CREATE_PTR(eve::thr::SpinLock);

	if (p_logFilePath.size() > 0)
	{
		set_log_in_file(set_msg_stream_path(p_logFilePath));
	}

	return m_p_server;
}

//=================================================================================================
eve::mess::Server * eve::mess::Server::get_instance(void)
{
	EVE_ASSERT(m_p_server);
	return m_p_server;
}

//=================================================================================================
void eve::mess::Server::release_instance(void)
{
	EVE_ASSERT(m_p_server);
	EVE_RELEASE_PTR(m_p_server);

	EVE_ASSERT(m_p_mutex);
	EVE_RELEASE_PTR(m_p_mutex);
}



//=================================================================================================
eve::mess::Server::Server(void)
	
	// Inheritance
	: eve::mem::Pointer()

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
void eve::mess::Server::init(void)
{
	// Default mode -> log in console if not in Release mode, else do nothing.
	m_pHandlerError		= &eve::mess::Server::default_log_error;
	m_pHandlerWarning	= &eve::mess::Server::default_log_warning;
	m_pHandlerInfo		= &eve::mess::Server::default_log_info;
	m_pHandlerProgress	= &eve::mess::Server::default_log_progress;
	m_pHandlerDebug		= &eve::mess::Server::default_log_debug;
}

//=================================================================================================
void eve::mess::Server::release(void)
{
	// Nothing to do for now.
}



//=================================================================================================
int32_t eve::mess::Server::get_buf_size(const wchar_t * format, va_list pargs)
{
	int32_t retval;
	va_list argcopy;
	va_copy(argcopy, pargs);
	retval = vswprintf(NULL, 0, format, argcopy);
	va_end(argcopy);
	return retval;
}

//=================================================================================================
void eve::mess::Server::print_to_output(const wchar_t * p_message)
{
#if defined(EVE_OS_WIN)
	OutputDebugStringW(p_message);
#else
	fwprintf(stderr, p_message);
	fflush(stderr);
#endif
}



//=================================================================================================
wchar_t * eve::mess::Server::format_message(const wchar_t * ptitle, const wchar_t * p_funcName, const wchar_t *p_format, va_list p_args)
{
	std::wstring mess = ptitle;
	mess += get_current_date();
	mess += EVE_TXT(" ");
	mess += p_funcName;
	mess += EVE_TXT(" ");
	mess += p_format;
	mess += EVE_TXT("\n");

	int size		= eve::mess::Server::get_buf_size(p_format, p_args);
	size_t msize	= (size + mess.length()) * sizeof(wchar_t);
	wchar_t * buf	= (wchar_t*)malloc(msize);

	vswprintf(buf, msize, mess.c_str(), p_args);

	return buf;
}



//=================================================================================================
void eve::mess::Server::default_log_error(const wchar_t *p_funcName, const wchar_t *p_format, ...)
{
#if !defined(NDEBUG)

	m_p_mutex->lock();

	va_list arg;
	va_start(arg, p_format);
	wchar_t * mess = eve::mess::Server::format_message(EVE_TXT("[ ERROR   ]"), p_funcName, p_format, arg);
	va_end(arg);

	eve::mess::Server::print_to_output(mess);
	free(mess);

	m_p_mutex->unlock();

#endif
}

//=================================================================================================
void eve::mess::Server::default_log_info(const wchar_t *p_funcName, const wchar_t *p_format, ...)
{
#if !defined(NDEBUG)
	
	m_p_mutex->lock();	

	va_list arg;
	va_start(arg, p_format);
	wchar_t * mess = eve::mess::Server::format_message(EVE_TXT("[ INFO    ]"), p_funcName, p_format, arg);
	va_end(arg);

	eve::mess::Server::print_to_output(mess);
	free(mess);

	m_p_mutex->unlock();

#endif
}

//=================================================================================================
void eve::mess::Server::default_log_warning(const wchar_t *p_funcName, const wchar_t *p_format, ...)
{
#if !defined(NDEBUG)

	m_p_mutex->lock();

	va_list arg;
	va_start(arg, p_format);
	wchar_t * mess = eve::mess::Server::format_message(EVE_TXT("[ WARNING ]"), p_funcName, p_format, arg);
	va_end(arg);

	eve::mess::Server::print_to_output(mess);
	free(mess);

	m_p_mutex->unlock();

#endif
}

//=================================================================================================
void eve::mess::Server::default_log_progress(const wchar_t *p_funcName, const wchar_t *p_format, ...)
{
#if !defined(NDEBUG)

	m_p_mutex->lock();

	va_list arg;
	va_start(arg, p_format);
	wchar_t * mess = eve::mess::Server::format_message(EVE_TXT("[ PROGRESS]"), p_funcName, p_format, arg);
	va_end(arg);

	eve::mess::Server::print_to_output(mess);
	free(mess);

	m_p_mutex->unlock();

#endif
}

//=================================================================================================
void eve::mess::Server::default_log_debug(const wchar_t *p_funcName, const wchar_t *p_format, ...)
{
#if !defined(NDEBUG)

	m_p_mutex->lock();

	va_list arg;
	va_start(arg, p_format);
	wchar_t * mess = eve::mess::Server::format_message(EVE_TXT("[ DEBUG   ]"), p_funcName, p_format, arg);
	va_end(arg);

	eve::mess::Server::print_to_output(mess);
	free(mess);

	m_p_mutex->unlock();

#endif
}



//=================================================================================================
void eve::mess::Server::default_log_in_file_error(const wchar_t *p_funcName, const wchar_t *p_format, ...)
{
	m_p_mutex->lock();

	va_list arg;
	va_start(arg, p_format);
	wchar_t * mess = eve::mess::Server::format_message(EVE_TXT("[ ERROR   ]"), p_funcName, p_format, arg);
	va_end(arg);

	fwprintf(get_error_stream(), mess);
	fflush(get_error_stream());
	free(mess);

	m_p_mutex->unlock();
}

//=================================================================================================
void eve::mess::Server::default_log_in_file_info(const wchar_t *p_funcName, const wchar_t *p_format, ...)
{
	m_p_mutex->lock();

	va_list arg;
	va_start(arg, p_format);
	wchar_t * mess = eve::mess::Server::format_message(EVE_TXT("[ INFO    ]"), p_funcName, p_format, arg);
	va_end(arg);

	fwprintf(get_info_stream(), mess);
	fflush(get_info_stream());
	free(mess);

	m_p_mutex->unlock();
}

//=================================================================================================
void eve::mess::Server::default_log_in_file_warning(const wchar_t *p_funcName, const wchar_t *p_format, ...)
{
	m_p_mutex->lock();

	va_list arg;
	va_start(arg, p_format);
	wchar_t * mess = eve::mess::Server::format_message(EVE_TXT("[ WARNING ]"), p_funcName, p_format, arg);
	va_end(arg);

	fwprintf(get_warning_stream(), mess);
	fflush(get_warning_stream());
	free(mess);

	m_p_mutex->unlock();
}

//=================================================================================================
void eve::mess::Server::default_log_in_file_progress(const wchar_t *p_funcName, const wchar_t *p_format, ...)
{
	m_p_mutex->lock();

	va_list arg;
	va_start(arg, p_format);
	wchar_t * mess = eve::mess::Server::format_message(EVE_TXT("[ PROGRESS]"), p_funcName, p_format, arg);
	va_end(arg);

	fwprintf(get_progress_stream(), mess);
	fflush(get_progress_stream());
	free(mess);

	m_p_mutex->unlock();
}

//=================================================================================================
void eve::mess::Server::default_log_in_file_debug(const wchar_t *p_funcName, const wchar_t *p_format, ...)
{
	m_p_mutex->lock();

	va_list arg;
	va_start(arg, p_format);
	wchar_t * mess = eve::mess::Server::format_message(EVE_TXT("[ DEBUG   ]"), p_funcName, p_format, arg);
	va_end(arg);

	fwprintf(get_debug_stream(), mess);
	fflush(get_debug_stream());
	free(mess);

	m_p_mutex->unlock();
}



//=================================================================================================
void __stdcall eve::mess::Server::ogl_debug_output(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* userParam)
{
	std::wstring debSource;
	if (source == GL_DEBUG_SOURCE_API_ARB)
		debSource = EVE_TXT("OpenGL");
	else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
		debSource = EVE_TXT("Windows");
	else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
		debSource = EVE_TXT("Shader Compiler");
	else if (source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
		debSource = EVE_TXT("Third Party");
	else if (source == GL_DEBUG_SOURCE_APPLICATION_ARB)
		debSource = EVE_TXT("Application");
	else if (source == GL_DEBUG_SOURCE_OTHER_ARB)
		debSource = EVE_TXT("Other");
	else
		EVE_ASSERT_FAILURE;

	std::wstring debType;
	if (type == GL_DEBUG_TYPE_ERROR)
		debType = EVE_TXT("error");
	else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)
		debType = EVE_TXT("deprecated behavior");
	else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
		debType = EVE_TXT("undefined behavior");
	else if (type == GL_DEBUG_TYPE_PORTABILITY)
		debType = EVE_TXT("portability");
	else if (type == GL_DEBUG_TYPE_PERFORMANCE)
		debType = EVE_TXT("performance");
	else if (type == GL_DEBUG_TYPE_OTHER)
		debType = EVE_TXT("message");
	else if (type == GL_DEBUG_TYPE_MARKER)
		debType = EVE_TXT("marker");
	else if (type == GL_DEBUG_TYPE_PUSH_GROUP)
		debType = EVE_TXT("push group");
	else if (type == GL_DEBUG_TYPE_POP_GROUP)
		debType = EVE_TXT("pop group");
	else
		EVE_ASSERT_FAILURE;

	std::wstring debSev;
	if (severity == GL_DEBUG_SEVERITY_HIGH_ARB)
		debSev = EVE_TXT("high");
	else if (severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
		debSev = EVE_TXT("medium");
	else if (severity == GL_DEBUG_SEVERITY_LOW_ARB)
		debSev = EVE_TXT("low");
	else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		debSev = EVE_TXT("notification");
	else
		EVE_ASSERT_FAILURE;
	
	eve::mess::Server::get_debug_handler()(EVE_TXT("ogl_debug_output()"), EVE_TXT("%s: %s(%s) %d: %s."), debSource, debType, debSev, id, message);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::mess::Server::set_log_in_file(bool p_bLogInFile)
{
	m_p_mutex->lock();

#if !defined(NDEBUG)
	// Default mode -> log in console if not in Release mode, else do nothing.
	m_p_server->m_pHandlerError		= &eve::mess::Server::default_log_error;
	m_p_server->m_pHandlerWarning	= &eve::mess::Server::default_log_warning;
	m_p_server->m_pHandlerInfo		= &eve::mess::Server::default_log_info;
	m_p_server->m_pHandlerProgress	= &eve::mess::Server::default_log_progress;
	m_p_server->m_pHandlerDebug		= &eve::mess::Server::default_log_debug;
#else

	if (p_bLogInFile)
	{
		m_p_server->m_pHandlerError		= &eve::mess::Server::default_log_in_file_error;
		m_p_server->m_pHandlerWarning	= &eve::mess::Server::default_log_in_file_info;
		m_p_server->m_pHandlerInfo		= &eve::mess::Server::default_log_in_file_warning;
		m_p_server->m_pHandlerProgress	= &eve::mess::Server::default_log_in_file_progress;
		m_p_server->m_pHandlerDebug		= &eve::mess::Server::default_log_in_file_debug;
	}
	else
	{
		m_p_server->m_pHandlerError		= &eve::mess::Server::default_log_error;
		m_p_server->m_pHandlerWarning	= &eve::mess::Server::default_log_warning;
		m_p_server->m_pHandlerInfo		= &eve::mess::Server::default_log_info;
		m_p_server->m_pHandlerProgress	= &eve::mess::Server::default_log_progress;
		m_p_server->m_pHandlerDebug		= &eve::mess::Server::default_log_debug;
	}

#endif

	m_p_mutex->unlock();
}



//=================================================================================================
bool eve::mess::Server::set_error_stream_path(const std::wstring & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = _wfopen(p_path.c_str(), EVE_TXT("w+"));
		m_p_server->m_pStreamError = file;

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}

//=================================================================================================
bool eve::mess::Server::set_warning_stream_path(const std::wstring & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = _wfopen(p_path.c_str(), EVE_TXT("w+"));
		m_p_server->m_pStreamWarning = file;

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}

//=================================================================================================
bool eve::mess::Server::set_info_stream_path(const std::wstring & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = _wfopen(p_path.c_str(), EVE_TXT("w+"));
		m_p_server->m_pStreamInfo = file;

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}

//=================================================================================================
bool eve::mess::Server::set_progress_stream_path(const std::wstring & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = _wfopen(p_path.c_str(), EVE_TXT("w+"));
		m_p_server->m_pStreamProgress = file;

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}

//=================================================================================================
bool eve::mess::Server::set_debug_stream_path(const std::wstring & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = _wfopen(p_path.c_str(), EVE_TXT("w+"));
		m_p_server->m_pStreamDebug = file;

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}

//=================================================================================================
bool eve::mess::Server::set_msg_stream_path(const std::wstring & p_path)
{
	bool bret = false;
	m_p_mutex->lock();

	if (eve::files::exists(p_path))
	{
		FILE * file = _wfopen(p_path.c_str(), EVE_TXT("w+"));
		m_p_server->m_pStreamError		= file;
		m_p_server->m_pStreamWarning	= file;
		m_p_server->m_pStreamInfo		= file;
		m_p_server->m_pStreamProgress	= file;
		m_p_server->m_pStreamDebug		= file;

		bret = true;
	}

	m_p_mutex->unlock();
	return bret;
}
