
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
#ifndef __EVE_MESSAGING_SERVER_H__
#define __EVE_MESSAGING_SERVER_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_FILES_INCLUDES_H__
#include "eve/files/Includes.h"
#endif

#ifndef __EVE_THREADING_INCLUDES_H__
#include "eve/thr/Includes.h"
#endif


namespace eve{ namespace app{ class App; } }


namespace eve
{
	namespace mess
	{
		/**
		* \class eve::mess::Server
		*
		* \brief Holds and manages creation and redirection of error/warning/info/debug messages.
		*
		* \note extends mem::Pointer
		*/
		class Server final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;
			friend class eve::app::App;

			//////////////////////////////////////
			//				TYPE				//
			//////////////////////////////////////

		public:
			typedef void(*handlerMethod)(const wchar_t *p_funcName, const wchar_t *p_format, ...);


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			static Server *					m_p_server;				//!< Unique instance.
			static eve::thr::SpinLock *		m_p_mutex;				//!< Message logging protection mutex.

			handlerMethod					m_pHandlerError;		//!< Error messages method pointer.
			handlerMethod					m_pHandlerWarning;		//!< Warning messages method pointer.
			handlerMethod					m_pHandlerInfo;			//!< Information messages method pointer.
			handlerMethod					m_pHandlerProgress;		//!< Progress messages method pointer.
			handlerMethod					m_pHandlerDebug;		//!< Debug messages method pointer.

			FILE *							m_pStreamError;			//!< Error message stream.
			FILE *							m_pStreamWarning;		//!< Warning message stream.
			FILE *							m_pStreamInfo;			//!< Info message stream.
			FILE *							m_pStreamProgress;		//!< Progress message stream.
			FILE *							m_pStreamDebug;			//!< Debug message stream.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Server)
			EVE_PROTECT_DESTRUCTOR(Server)

		private:
			/** \brief Create unique instance. */
			static Server * create_instance(const std::wstring & p_logFilePath=EVE_TXT(""));
			/** \brief Release unique instance */
			static void release_instance(void);


		private:
			/** \brief Class constructor. */
			Server(void);


		private:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Get buffer containing varying arguments size. */
			static int32_t get_buf_size(const wchar_t * format, va_list pargs);
			/** \brief Print message to output. */
			static void print_to_output(const wchar_t * p_message);


		private:
			/** \brief Format message to log and return a newly allocated buffer, do not forget to free it after use. */
			static wchar_t * format_message(const wchar_t * ptitle, const wchar_t * p_funcName, const wchar_t *p_format, va_list p_args);


		private:
			/** \brief Default error log method (in console). */
			static void default_log_error(const wchar_t *p_funcName, const wchar_t *p_format, ...);
			/** \brief Default info log method (in console). */
			static void default_log_info(const wchar_t *p_funcName, const wchar_t *p_format, ...);
			/** \brief Default warning log method (in console). */
			static void default_log_warning(const wchar_t *p_funcName, const wchar_t *p_format, ...);
			/** \brief Default progress log method (in console). */
			static void default_log_progress(const wchar_t *p_funcName, const wchar_t *p_format, ...);
			/** \brief Default debug log method (in console). */
			static void default_log_debug(const wchar_t *p_funcName, const wchar_t *p_format, ...);

			/** \brief Default in file error log method. */
			static void default_log_in_file_error(const wchar_t *p_funcName, const wchar_t *p_format, ...);
			/** \brief Default in file info log method. */
			static void default_log_in_file_info(const wchar_t *p_funcName, const wchar_t *p_format, ...);
			/** \brief Default in file warning log method. */
			static void default_log_in_file_warning(const wchar_t *p_funcName, const wchar_t *p_format, ...);
			/** \brief Default in file progress log method. */
			static void default_log_in_file_progress(const wchar_t *p_funcName, const wchar_t *p_format, ...);
			/** \brief Default in file debug log method. */
			static void default_log_in_file_debug(const wchar_t *p_funcName, const wchar_t *p_format, ...);


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Set log in file or not, if not than log in console if in DEBUG mode. */
			static void set_log_in_file(bool p_bLogInFile);


			/** \brief Set the error msg handler. */
			static void set_error_handler(handlerMethod p_method);
			/** \brief Set the warning msg handler. */
			static void set_warning_handler(handlerMethod p_method);
			/** \brief Set the info msg handler. */
			static void set_info_handler(handlerMethod p_method);
			/** \brief Set the progress msg handler. */
			static void set_progress_handler(handlerMethod p_method);
			/** \brief Set the debug msg handler. */
			static void set_debug_handler(handlerMethod p_method);
			/** \brief Set all the msg handlers. */
			static void set_msg_handler(handlerMethod p_method);

			/** \brief Get the error msg handler. */
			static handlerMethod get_error_handler(void);
			/** \brief Get the warning msg handler. */
			static handlerMethod get_warning_handler(void);
			/** \brief Get the info msg handler. */
			static handlerMethod get_info_handler(void);
			/** \brief Get the progress msg handler. */
			static handlerMethod get_progress_handler(void);
			/** \brief Get the debug msg handler. */
			static handlerMethod get_debug_handler(void);



			/** \brief Redirect the error messages to target file \p_pFile. */
			static void set_error_stream(FILE * p_pFile);
			/** \brief Redirect the warning messages to target file \p_pFile. */
			static void set_warning_stream(FILE * p_pFile);
			/** \brief Redirect the info messages to target file \p_pFile. */
			static void set_info_stream(FILE * p_pFile);
			/** \brief Redirect the progress messages to target file \p_pFile. */
			static void set_progress_stream(FILE * p_pFile);
			/** \brief Redirect the debug messages to target file \p_pFile. */
			static void set_debug_stream(FILE * p_pFile);
			/** \brief Redirect all the messages target file \p_pFile. */
			static void set_msg_stream(FILE * p_pFile);

			/** \brief Redirect the error messages to target file path \p_path. */
			static bool set_error_stream_path(const std::wstring & p_path);
			/** \brief Redirect the warning messages to target file path \p_path. */
			static bool set_warning_stream_path(const std::wstring & p_path);
			/** \brief Redirect the info messages to target file path \p_path. */
			static bool set_info_stream_path(const std::wstring & p_path);
			/** \brief Redirect the progress messages to target file path \p_path. */
			static bool set_progress_stream_path(const std::wstring & p_path);
			/** \brief Redirect the debug messages to target file path \p_path. */
			static bool set_debug_stream_path(const std::wstring & p_path);
			/** \brief Redirect all the messages target file path \p_path. */
			static bool set_msg_stream_path(const std::wstring & p_path);

			/** \brief Get the current (FILE*) error stream. */
			static FILE * get_error_stream(void);
			/** \brief Get the current (FILE*) warning stream. */
			static FILE * get_warning_stream(void);
			/** \brief Get the current (FILE*) info stream. */
			static FILE * get_info_stream(void);
			/** \brief Get the current (FILE*) progress stream. */
			static FILE * get_progress_stream(void);
			/** \brief Get the current (FILE*) debug stream. */
			static FILE * get_debug_stream(void);
			
		}; // class Server

	} // namespace mess

} // namespace eve


//=================================================================================================
inline void eve::mess::Server::set_error_handler(handlerMethod p_method)		{ m_p_mutex->lock(); m_p_server->m_pHandlerError	= p_method; 	m_p_mutex->unlock(); }
inline void eve::mess::Server::set_warning_handler(handlerMethod p_method)		{ m_p_mutex->lock(); m_p_server->m_pHandlerWarning	= p_method; 	m_p_mutex->unlock(); }
inline void eve::mess::Server::set_info_handler(handlerMethod p_method)			{ m_p_mutex->lock(); m_p_server->m_pHandlerInfo		= p_method; 	m_p_mutex->unlock(); }
inline void eve::mess::Server::set_progress_handler(handlerMethod p_method)		{ m_p_mutex->lock(); m_p_server->m_pHandlerProgress = p_method;		m_p_mutex->unlock(); }
inline void eve::mess::Server::set_debug_handler(handlerMethod p_method)		{ m_p_mutex->lock(); m_p_server->m_pHandlerDebug	= p_method; 	m_p_mutex->unlock(); }
inline void eve::mess::Server::set_msg_handler(handlerMethod p_method)
{
	m_p_mutex->lock();
	m_p_server->m_pHandlerError		= p_method; 
	m_p_server->m_pHandlerWarning	= p_method;
	m_p_server->m_pHandlerInfo		= p_method;
	m_p_server->m_pHandlerProgress	= p_method;
	m_p_server->m_pHandlerDebug		= p_method;
	m_p_mutex->unlock();
}

//=================================================================================================
inline eve::mess::Server::handlerMethod eve::mess::Server::get_error_handler(void)			{ return m_p_server->m_pHandlerError;		}
inline eve::mess::Server::handlerMethod eve::mess::Server::get_warning_handler(void)		{ return m_p_server->m_pHandlerWarning;		}
inline eve::mess::Server::handlerMethod eve::mess::Server::get_info_handler(void)			{ return m_p_server->m_pHandlerInfo;		}
inline eve::mess::Server::handlerMethod eve::mess::Server::get_progress_handler(void)		{ return m_p_server->m_pHandlerProgress;	}
inline eve::mess::Server::handlerMethod eve::mess::Server::get_debug_handler(void)			{ return m_p_server->m_pHandlerDebug;		}



//=================================================================================================
inline void eve::mess::Server::set_error_stream(FILE * p_pFile)			{ m_p_mutex->lock(); m_p_server->m_pStreamError		= p_pFile;		m_p_mutex->unlock(); }
inline void eve::mess::Server::set_warning_stream(FILE * p_pFile)		{ m_p_mutex->lock(); m_p_server->m_pStreamWarning	= p_pFile; 		m_p_mutex->unlock(); }
inline void eve::mess::Server::set_info_stream(FILE * p_pFile)			{ m_p_mutex->lock(); m_p_server->m_pStreamInfo		= p_pFile;		m_p_mutex->unlock(); }
inline void eve::mess::Server::set_progress_stream(FILE * p_pFile)		{ m_p_mutex->lock(); m_p_server->m_pStreamProgress	= p_pFile; 		m_p_mutex->unlock(); }
inline void eve::mess::Server::set_debug_stream(FILE * p_pFile)			{ m_p_mutex->lock(); m_p_server->m_pStreamDebug		= p_pFile;		m_p_mutex->unlock(); }
inline void eve::mess::Server::set_msg_stream(FILE * p_pFile)			
{ 
	m_p_mutex->lock();
	m_p_server->m_pStreamError		= p_pFile;
	m_p_server->m_pStreamWarning	= p_pFile;
	m_p_server->m_pStreamInfo		= p_pFile;
	m_p_server->m_pStreamProgress	= p_pFile;
	m_p_server->m_pStreamDebug		= p_pFile;
	m_p_mutex->unlock();
}

//=================================================================================================
inline FILE * eve::mess::Server::get_error_stream(void)			{ return m_p_server->m_pStreamError;		}
inline FILE * eve::mess::Server::get_warning_stream(void)		{ return m_p_server->m_pStreamWarning;		}
inline FILE * eve::mess::Server::get_info_stream(void)			{ return m_p_server->m_pStreamInfo;			}
inline FILE * eve::mess::Server::get_progress_stream(void)		{ return m_p_server->m_pStreamProgress;		}
inline FILE * eve::mess::Server::get_debug_stream(void)			{ return m_p_server->m_pStreamDebug;		}



#define EVE_LOG_ERROR(format, ...)		eve::mess::Server::get_error_handler()(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT(format), __VA_ARGS__);
#define EVE_LOG_WARNING(format, ...)	eve::mess::Server::get_warning_handler()(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT(format), __VA_ARGS__);
#define EVE_LOG_INFO(format, ...)		eve::mess::Server::get_info_handler()(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT(format), __VA_ARGS__);
#define EVE_LOG_PROGRESS(format, ...)	eve::mess::Server::get_progress_handler()(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT(format), __VA_ARGS__);
#define EVE_LOG_DEBUG(format, ...)		eve::mess::Server::get_debug_handler()(EVE_TXT_ENFORCE(__FUNCTION__), EVE_TXT(format), __VA_ARGS__);

#endif // __EVE_MESSAGING_SERVER_H__
