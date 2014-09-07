
/*
 Copyright (c) 2014, The Eve Project
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
#include "Eve/core/Includes.h"
#endif


namespace eve
{
	namespace messaging
	{
		/**
		* \class eve::messaging::Server
		*
		* \brief holds and manages creation and redirection of error/warning/info/debug messages.
		*
		* \note extends memory::Pointer
		*/
		class Server
			: public eve::memory::Pointer
		{

			friend class eve::memory::Pointer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			static Server *			m_p_server;			//<! Unique instance.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Server)
			EVE_PROTECT_DESTRUCTOR(Server)

		public:
			/** \brief Create unique instance. */
			static Server * create_instance(void);
			/** \brief Release unique instance */
			static void release_instance(void);


		protected:
			/** \brief Class constructor. */
			Server(void);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;






		private:
			/** \brief mutex set lock when a instance of the message server is used */
			static FILE *fid;



		public:

			static bool m_b_print_timing;

			std::map<const char*, void(*)(const char *format, ...), EVE_ltstring> displayFunction;

			/** \brief A default buffer, to store the current message std::string. */
			char *stdBuff;

			/** \brief The size of the default message-storing buffer. */
			size_t stdBuffSize;
			/** \brief The type of the current message (see constants above). */
			unsigned long int currentMsgType;

			/** \brief The handler function associated with the error messages. */
			void(*errorHandler)(void);
			/** \brief The handler function associated with the warning messages. */
			void(*warningHandler)(void);
			/** \brief The handler function associated with the info messages. */
			void(*infoHandler)(void);
			/** \brief The handler function associated with the progress messages. */
			void(*progressHandler)(void);
			/** \brief The handler function associated with the debug messages. */
			void(*debugHandler)(void);

			/** \brief The output stream associated with error messages. */
			void * errorStream;
			/** \brief The output stream associated with warning messages. */
			void * warningStream;
			/** \brief The output stream associated with info messages. */
			void *infoStream;
			/** \brief The output stream associated with progress messages. */
			void *progressStream;
			/** \brief The output stream associated with debug messages. */
			void *debugStream;

			/** \brief A binary mask to sort the DEBUG messages */
			unsigned long int debugMask;

			/** \brief A message stack **/
			char **msgStack;
			unsigned long int *msgTypeStack;
			unsigned long int stackSize;
			unsigned long int maxStackSize;
			/** \brief Granularity before a realloc of the msg stack occurs */




			/***********/
			/* METHODS */
			/***********/

			/***************************/
			/* CONSTRUCTORS/DESTRUCTOR */
			/***************************/


		public:
			static void default_display_error_function(const char *format, ...);
			static void default_display_in_file_error_function(const char *format, ...);
			static void default_display_in_file_info_function(const char *format, ...);
			static void default_display_in_file_warning_function(const char *format, ...);
			static void default_display_in_file_debug_function(const char *format, ...);
			static void default_display_in_file_progress_function(const char *format, ...);
			/** \brief Method to get the EVE_Atom_Factory_c */
			static Server * get_msg_server(bool p_bUseDefaultFile = true, std::string p_sLogPath = "");

			static void set_print_timing_status(bool p_bValue);

			/** \brief A plain constructor **/
			static void release_msg_server();

#if defined OPTION_BUILD_LOG_IN_FILE
			static bool init_log_in_file(bool p_bUseDefaultFile, std::string p_sLogPath);
#endif //OPTION_BUILD_LOG_IN_FILE
			/** \brief A plain destructor **/
			virtual ~Server(void);

			/** \brief display function **/
			void register_display_function(const char* functionType, void(*displayFunctionPointer)(const char *format, ...));
			void(*get_display_function(const char* functionType))(const char *format, ...);

#if defined(_MSC_VER)

			static inline int native_vsnprintf(char *_inputString, size_t size, const char *format, va_list ap)
			{
				if (_inputString != NULL)
				{
					//Version "secure" microsoft (VS2005 ou supérieur requis)
					_vsnprintf_s(_inputString, size, _TRUNCATE, format, ap);

					//Version "ancienne"
					//_vsnprintf( _inputString, size, format, ap );
					_inputString[size - 1] = '\0';
				}
				return _vscprintf(format, ap);
			}
#else

			static inline int native_vsnprintf(char *_inputString, size_t size, const char *format, va_list ap)
			{
				return vsnprintf(_inputString, size, format, ap);
			}

#endif

		}; // class Server

	} // namespace messaging

} // namespace eve









/*********************/
/* DEFAULT MSG TYPES */
/*********************/
/* - NULL type: */
#define EVE_MSG_NULL   0
/* - General types: */
#define EVE_ERROR      1
#define EVE_WARNING    (1 << 1)
#define EVE_INFO       (1 << 2)
#define EVE_PROGRESS   (1 << 3)
/* - Reserved for future use: */
#define EVE_RESERVED_1 (1 << 4)
#define EVE_RESERVED_2 (1 << 5)
#define EVE_DEBUG_FILE_DB (1 << 6)
/* - Debugging types (up to 24 types): */
/* these types can be used to fine tune which debug messages should
   or should not be printed at runtime. See the set_debug_mask() macro. */
/* -- general purpose: */
#define EVE_DEBUG         (1 << 7)
#define EVE_DEBUG_GENERAL EVE_DEBUG
/* -- when entering/exiting functions: */
#define EVE_DEBUG_FUNC_ENTER (1 << 8)
#define EVE_DEBUG_FUNC_EXIT  (1 << 9)
#define EVE_DEBUG_FUNC_BOUNDARIES ( EVE_DEBUG_FUNC_ENTER | EVE_DEBUG_FUNC_EXIT )
/* -- information emitted during loops: */
#define EVE_DEBUG_ABUNDANT  (1 << 10)  /* for intensive loops (lots of output, e.g. in composants) */
#define EVE_DEBUG_MEDIUM    (1 << 11) /* for medium frequency loops */
#define EVE_DEBUG_SPARSE    (1 << 12) /* loops with sparse output (e.g., dictionary browsing) */
/* -- information related to file I/O: */
#define EVE_DEBUG_FILE_IO   (1 << 13)
/* -- construction/deletion of objects: */
#define EVE_DEBUG_CONSTRUCTION (1 << 14)
#define EVE_DEBUG_DESTRUCTION  (1 << 15)
#define EVE_DEBUG_OBJ_LIFE ( EVE_DEBUG_CONSTRUCTION | EVE_DEBUG_DESTRUCTION )
/* -- Matching Pursuit iterations: */
#define EVE_DEBUG_EVE_ITERATIONS (1 << 16)
/* -- Specific for cryptographic function */
#define EVE_DEBUG_CRYPTOGRAPHIE  (1 << 17)
/* -- Specific for function create_atom()array bounds check: */
#define EVE_DEBUG_ARRAY_BOUNDS  (1 << 18)
/* -- Argument parsing in utils: */
#define EVE_DEBUG_PARSE_ARGS    (1 << 19)
/* -- NATIVE loop in utils: */
#define EVE_DEBUG_LOOP      (1 << 20)
/* -- Specific for internal atom operations: */
#define EVE_DEBUG_ATOM          (1 << 21)
/* -- Specific for addressing issues */
#define EVE_DEBUG_ADDR          (1 << 22)

#define EVE_MSG_LAST_TYPE EVE_DEBUG_ADDR

#define EVE_DEBUG_ALL  ULONG_MAX
#define EVE_DEBUG_NONE 0

#define EVE_MSG_STACK_GRANULARITY 128
#define EVE_DEFAULT_STDBUFF_SIZE 2048











/**
* @brief get log file path
* @return path as char pointer
*/
static char * native_get_log_file_path( void );


#if defined(_MSC_VER)
std::string getErrorMsg(DWORD err);
std::string getErrorMsg();
#endif

/***************************************/
/* DEFINITION OF SOME MESSAGE HANDLERS */
/***************************************/

/** \brief A message handler which sends the incoming message
    to the appropriate pre-set stream. */
#define EVE_FLUSH native_msg_handler_flush
/** \brief Instanciation of the EVE_FLUSH handler. */
void native_msg_handler_flush( void );

/** \brief A message handler which ignores the incoming message. */
#define EVE_IGNORE native_msg_handler_ignore
/** \brief Instanciation of the EVE_IGNORE handler. */
void native_msg_handler_ignore( void );

/* TODO: EVE_QUEUE, EVE_RELEASE_QUEUE_AFTER_NEXT */

/**********************************/
/* MESSAGE HANDLER SETTING MACROS */
/**********************************/
/** \brief Set the error msg handler. */
#define set_error_handler( H )   ( Server::get_msg_server()->errorHandler = H )
/** \brief Set the warning msg handler. */
#define set_warning_handler( H ) ( Server::get_msg_server()->warningHandler = H )
/** \brief Set the info msg handler. */
#define set_info_handler( H )    ( Server::get_msg_server()->infoHandler = H )
/** \brief Set the progress msg handler. */
#define set_progress_handler( H )    ( Server::get_msg_server()->progressHandler = H )
/** \brief Set the debug msg handler. */
#define set_debug_handler( H )   ( Server::get_msg_server()->debugHandler = H )
/** \brief Set all the msg handlers (except debug). */
#define set_msg_handler( H )		\
	set_error_handler( H );			\
	set_warning_handler( H );		\
	set_info_handler( H );			\
	set_progress_handler( H );

/** \brief Get the error msg handler. */
#define get_error_handler()   ( Server::get_msg_server()->errorHandler )
/** \brief Get the warning msg handler. */
#define get_warning_handler() ( Server::get_msg_server()->warningHandler )
/** \brief Get the info msg handler. */
#define get_info_handler()    ( Server::get_msg_server()->infoHandler )
/** \brief Get the progress msg handler. */
#define get_progress_handler()    ( Server::get_msg_server()->progressHandler )
/** \brief Get the debug msg handler. */
#define get_debug_handler()   ( Server::get_msg_server()->debugHandler )


/*************************/
/* STREAM SETTING MACROS */
/*************************/
/** \brief Redirect the error messages to (FILE*) F. */
#define set_error_stream( F )   ( Server::get_msg_server()->errorStream = F )
/** \brief Redirect the warning messages to (FILE*) F. */
#define set_warning_stream( F ) ( Server::get_msg_server()->warningStream = F )
/** \brief Redirect the info messages to (FILE*) F. */
#define set_info_stream( F )    ( Server::get_msg_server()->infoStream = F )
/** \brief Redirect the progress messages to (FILE*) F. */
#define set_progress_stream( F )    ( Server::get_msg_server()->progressStream = F )
/** \brief Redirect the debug messages to (FILE*) F. */
#define set_debug_stream( F )   ( Server::get_msg_server()->debugStream = F )
/** \brief Redirect all the messages (except the debug messages) to (FILE*) F. */
#define set_msg_stream( F )   set_error_stream( F );   \
                              set_warning_stream( F ); \
                              set_info_stream( F )

/** \brief Get the current (FILE*) error stream. */
#define get_error_stream()   ( Server::get_msg_server()->errorStream )
/** \brief Get the current (FILE*) warning stream. */
#define get_warning_stream() ( Server::get_msg_server()->warningStream )
/** \brief Get the current (FILE*) info stream. */
#define get_info_stream()    ( (FILE*)Server::get_msg_server()->infoStream )
/** \brief Get the current (FILE*) progress stream. */
#define get_progress_stream()    ( Server::get_msg_server()->progressStream )
/** \brief Get the current (FILE*) debug stream. */
#define get_debug_stream()   ( Server::get_msg_server()->debugStream )


/***********************/
/* DEBUG MASK          */
/***********************/

/** \brief Set a mask to sort the printed debug messages.
 *
 *  \param M an unsigned long int made of an assembly of debug message types,
 *  e.g. ( EVE_DEBUG_FUNC_ENTER | EVE_DEBUG_FUNC_EXIT ). See Native_Messaging.h for
 *  a list of available debug message types.
 */
#define set_debug_mask( M ) ( Server::get_msg_server()->debugMask = M )


/***********************/
/* MESSAGING FUNCTIONS */
/***********************/


/** \brief Pretty-printing of the error messages
 *
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 *
 * \sa set_error_stream(), set_error_handler().
 */
size_t native_error_msg( const char *funcName, const char *format, ... );

/** \brief Pretty-printing of the error messages to a specific stream
 *
 * \param fid the (FILE*) stream to write to
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 */
size_t native_error_msg( FILE *fid, const char *funcName, const char *format, ... );



/** \brief Pretty-printing of the warning messages
 *
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 *
 * \sa set_warning_stream(), set_warning_handler().
 */
size_t native_warning_msg( const char *funcName, const char *format, ... );

/** \brief Pretty-printing of the warning messages to a specific stream
 *
 * \param fid the (FILE*) stream to write to
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 */
size_t native_warning_msg( FILE *fid, const char *funcName, const char *format, ... );



/** \brief Pretty-printing of the info messages
 *
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 *
 * \sa set_info_stream(), set_info_handler().
 */
size_t native_info_msg( const char *funcName, const char *format, ... );

/** \brief Pretty-printing of the info messages to a specific stream
 *
 * \param fid the (FILE*) stream to write to
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 */
size_t native_info_msg( FILE *fid, const char *funcName, const char *format, ... );



/** \brief Pretty-printing of the progress messages
 *
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 *
 * \sa set_progress_stream(), set_progress_handler().
 */
size_t native_progress_msg( const char *funcName, const char *format, ... );

/** \brief Pretty-printing of the progress messages to a specific stream
 *
 * \param fid the (FILE*) stream to write to
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 */
size_t native_progress_msg( FILE *fid, const char *funcName, const char *format, ... );



/** \brief Pretty-printing of the debug messages
 *
 * \param msgType a message type, defined in Native_Messaging.h, which allows to
 * sort the debug output according to the mask set with set_debug_mask()
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 *
 * \note The native_debug_msg functions are not compiled when the flag -DNDEBUG is used.
 *
 * \sa native_debug_msg_forced(), set_debug_stream(), set_debug_handler(), set_debug_mask().
 */
size_t native_debug_msg( const unsigned long int msgType, const char *funcName, const char *format, ... );

/** \brief Pretty-printing of the debug messages to a specific stream
 *
 * \param fid the (FILE*) stream to write to
 * \param msgType a message type, defined in Native_Messaging.h, which allows to
 * sort the debug output according to the mask set with set_debug_mask()
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 *
 * \note The native_debug_msg functions are not compiled when the flag -DNDEBUG is used.
 *
 * \sa native_debug_msg(), set_debug_stream(), set_debug_handler(), set_debug_mask().
 */
size_t native_debug_msg( FILE *fid, const unsigned long int msgType, const char *funcName, const char *format, ... );

/** \brief Forced pretty-printing of the debug messages
 *
 * \param msgType a message type, defined in Native_Messaging.h. For this function,
 * the debug messages mask is ignored.
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 *
 * \note This function is always compiled in (no interaction with -DNDEBUG). This "alias"
 * can be used to force the output of a particular debug function.
 *
 * \sa native_msg_debug(), set_debug_stream(), set_debug_handler(), set_debug_mask().
 */
size_t native_debug_msg_forced( const unsigned long int msgType, const char *funcName, const char *format, ... );

/** \brief Forced pretty-printing of the debug messages to a specific stream
 *
 * \param fid the (FILE*) stream to write to
 * \param msgType a message type, defined in Native_Messaging.h, which allows to
 * sort the debug output according to the mask set with set_debug_mask()
 * \param funcName the name of the calling function
 * \param format a format std::string similar to the printf formats
 * \param ... a variable list of arguments to be printed according to the format
 *
 * \note This function is always compiled in (no interaction with -DNDEBUG). This "alias"
 * can be used to force the output of a particular debug function.
 *
* \sa native_msg_debug(), set_debug_stream(), set_debug_handler(), set_debug_mask().
 */
size_t native_debug_msg_forced( FILE *fid, const unsigned long int msgType, const char *funcName, const char *format, ... );


#endif // __EVE_MESSAGING_SERVER_H__
