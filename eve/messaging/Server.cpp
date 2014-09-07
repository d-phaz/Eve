
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

// Main header
#include "Eve/messaging/Server.h"





















#ifndef __EVE_MUTEX_H__
#include "Native_Mutex.h"
#endif //__EVE_SYSTEM_H__




#if defined(__MINGW32__)
int localtime_s(tm * _tm, const time_t * time)
{
	tm * posix_local_time_struct = localtime(time);
	if (posix_local_time_struct == NULL) return 1;
	*_tm = *posix_local_time_struct;
	return 0;
}
#endif //__MINGW32__

#if defined(EVE_OS_DARWIN)
int localtime_s(tm * _tm, const time_t * time)
{
	tm * posix_local_time_struct = localtime(time);
	if (posix_local_time_struct == NULL) return 1;
	*_tm = *posix_local_time_struct;
	return 0;
}
#endif //EVE_OS_DARWIN

/***************************/
/*			UTILS		   */
/***************************/

static time_t curTime;

static char strCurrDate[17];
struct tm timestamp;

static const char * log_file_rep_path = NULL;
static char *log_file_path = NULL;

bool Server::m_b_print_timing = true;

NativeT::Mutex s_mutex;


//=================================================================================================
static char * native_get_log_file_path( void )
{
	EVE_ASSERT( log_file_path!=NULL );

	return log_file_path;
}



static char *GetCurrentTimeCustom()
{

#ifdef EVE_OS_WIN
	static char strCurrTime[35];
	char timeline[26];
	struct _timeb timebuffer;
	_ftime64_s( &timebuffer );
	ctime_s( timeline, 26, & ( timebuffer.time ) );
	memset(strCurrTime, 0, sizeof(strCurrTime));
	sprintf_s(strCurrTime, sizeof(strCurrTime), "%.8s.%02hu", &timeline[11], timebuffer.millitm);
	//strftime(strCurrTime, sizeof(strCurrTime), "%Y-%m-%d %H:%M:%S", &timestamp);


#endif //EVE_OS_WIN

#ifdef EVE_OS_DARWIN
	time(&curTime);
	static char strCurrTime[32];
	localtime_s(&timestamp, &curTime);
	strftime(strCurrTime, sizeof(strCurrTime), "%Y-%m-%d %H:%M:%S", &timestamp);
#endif //EVE_OS_DARWIN


	return strCurrTime;
}

static char *GetCurrentDate( void )
{
	time(&curTime);

#ifdef EVE_OS_WIN32
	localtime_s(&timestamp, &curTime);
#endif //EVE_OS_WIN32

#ifdef EVE_OS_DARWIN
	localtime_s(&timestamp, &curTime);
#endif //EVE_OS_DARWIN

	memset(strCurrDate, 0, sizeof(strCurrDate));

#ifdef EVE_OS_WIN32
#if defined(__MINGW32__)
	sprintf(strCurrDate, "%04d%02d%02d%02d%02d", timestamp.tm_year+1900, timestamp.tm_mon+1, timestamp.tm_mday, timestamp.tm_hour, timestamp.tm_min);
#else //(__MINGW32__)
	sprintf_s(strCurrDate, sizeof(strCurrDate),  "%04d%02d%02d%02d%02d", timestamp.tm_year+1900, timestamp.tm_mon+1, timestamp.tm_mday, timestamp.tm_hour, timestamp.tm_min);
#endif //(__MINGW32__)
#endif //EVE_OS_WIN32

#ifdef EVE_OS_DARWIN
	sprintf(strCurrDate, "%04d%02d%02d%02d%02d", timestamp.tm_year+1900, timestamp.tm_mon+1, timestamp.tm_mday, timestamp.tm_hour, timestamp.tm_min);
#endif //EVE_OS_DARWIN



	return strCurrDate;
}

static void initLogFilePath()
{
	// Test log files amount and erase file if needed
	std::vector<std::string> vec = NATIVESYSTEM::listDirectoryFiles( log_file_rep_path );
	if( vec.size() > 13 )
	{
		std::string target = log_file_rep_path;
		target += vec[ vec.size()-2 ];

		if( remove( target.c_str() ) != 0 ) {
			native_error_msg( "initLogFilePath", "Error deleting file" );
		}
	}


	log_file_path = (EVE_char8_t *)realloc(log_file_path, strlen(log_file_rep_path) + strlen("native_yyyymmddhhmm_n.txt") + 1 );

	strcpy(log_file_path, log_file_rep_path);
	strcat(log_file_path, "log_");
	strcat(log_file_path, GetCurrentDate());
	strcat(log_file_path, "_1.txt");
}

#if defined(_MSC_VER)
std::string getErrorMsg()
{ 

	return getErrorMsg(GetLastError());

}

std::string getErrorMsg(DWORD err)
{

	std::string returnString;

	char buffer[2048]; 
	try
	{
		DWORD len = 0;
		LPWSTR msg = NULL;

		len = FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&msg, 0, NULL);
		if (len > 0)
		{
			snprintf(buffer, 2048 , "error (%d): %s\n",  err, msg);
		}
		else
		{
			snprintf(buffer, 2048 , "error code: %d.\n",  err);
		}

		returnString = std::string(buffer);

		if (msg != NULL) LocalFree(msg);

	} 
	catch(...)
	{
		returnString = "Can't get Win32 error message";
	}
	return returnString;
}
#endif //defined(_MSC_VER)

/*************************************/
/* DECLARATION OF A MESSAGING SERVER */
/* WITH GLOBAL SCOPE                 */
/*************************************/

/*Initialise pointer to MsgServer instance */
Server * Server::p_my_msg_server = NULL;

/*Initialise FILE * for MsgServer instance */
FILE * Server::fid = NULL;

/***************************/
/* CONSTRUCTORS/DESTRUCTOR */
/***************************/

/********************/
/* Void constructor */
Server::Server( void )
{

	/* Allocate the standard std::string buffer */
	if ( ( stdBuff = (char*) calloc( EVE_DEFAULT_STDBUFF_SIZE, sizeof(char) ) ) == NULL )
	{
		exit( 0 );
	}
	/* Set the related values */
	stdBuffSize = EVE_DEFAULT_STDBUFF_SIZE;
	currentMsgType = EVE_MSG_NULL;

	/* Set the default handler */
	errorHandler = warningHandler = infoHandler = progressHandler = EVE_FLUSH;
#ifndef NDEBUG
 	/* Initialize the debug mask to "all messages" */
	debugHandler = EVE_FLUSH;
	debugMask = EVE_DEBUG_ALL;
#else
	 /* Initialize the debug mask to "none" */
	debugHandler = EVE_IGNORE;
	debugMask = EVE_DEBUG_NONE;
#endif
	/* Initialize the stack */
	msgStack = NULL;
	msgTypeStack = NULL;
	stackSize = 0;
	maxStackSize = 0;
}

/**************/
/* destructor */
Server::~Server() 
{

	if (log_file_path) free ( log_file_path );

	/* Free the standard std::string buffer */
	if ( stdBuff ) free( stdBuff );

	/* Free the msg stack */
	if ( stackSize != 0 ) {
		unsigned long int i;
		for ( i = 0; i < stackSize; i++ ) {
			if ( msgStack[i] ) free ( msgStack[i] );
		}
	}
	if ( msgStack ) free( msgStack );
	if ( msgTypeStack ) free( msgTypeStack );

	displayFunction.clear();
}

/**************/
/* release msg server */
void Server::release_msg_server()
{
	if (Server::p_my_msg_server!=NULL)
	{
		delete Server::p_my_msg_server;
		Server::p_my_msg_server = NULL;
	}
}


/***********/
/* METHODS */
/***********/

/* TODO: push/pop messages to/from the stack. */

void Server::register_display_function(const char* functionType, void (*displayFunctionPointer)(const char *format, ...))
{
	if (functionType)
		Server::displayFunction[functionType]=displayFunctionPointer;
}

void (*Server::get_display_function( const char* functionType )) (const char *format, ...) 
{

	return Server::get_msg_server()->displayFunction[functionType];

}

void Server::set_print_timing_status(bool p_bValue)
{
	m_b_print_timing = p_bValue;
}

Server * Server::get_msg_server(bool p_bUseDefaultFile, std::string p_sLogPath)
{
	if (!Server::p_my_msg_server)
	{
		Server::p_my_msg_server = new Server();

#if defined (OPTION_BUILD_LOG_IN_FILE)
		if (p_sLogPath == "")
			init_log_in_file(p_bUseDefaultFile, NATIVESYSTEM::getPathLogDedicated());
		else
			init_log_in_file(p_bUseDefaultFile, p_sLogPath);
#else //OPTION_BUILD_LOG_IN_FILE
		p_my_msg_server->register_display_function("info_message_display",&Server::default_display_error_function);
		p_my_msg_server->register_display_function("error_message_display",&Server::default_display_error_function);
		p_my_msg_server->register_display_function("warning_message_display",&Server::default_display_error_function);
		p_my_msg_server->register_display_function("progress_message_display",&Server::default_display_error_function);
		p_my_msg_server->register_display_function("debug_message_display",&Server::default_display_error_function);
#endif //OPTION_BUILD_LOG_IN_FILE      
	}
	return  Server::p_my_msg_server;
}

#if defined (OPTION_BUILD_LOG_IN_FILE)
bool Server::init_log_in_file(bool p_bUseDefaultFile, std::string p_sLogPath )
{
	bool bReturn = true;

	if(p_bUseDefaultFile)
	{
		log_file_rep_path = p_sLogPath.c_str();
		initLogFilePath();
	}
	else
	{
		log_file_path = (EVE_char8_t *)realloc(log_file_path, p_sLogPath.size() + 1 );
		strcpy(log_file_path, p_sLogPath.c_str());
	}


	fid = fopen( log_file_path, "wt" );
	if (fid!=NULL)
	{		
		p_my_msg_server->errorStream = fid;
		p_my_msg_server->warningStream = fid;
		p_my_msg_server->infoStream = fid;
		p_my_msg_server->progressStream = fid;
		p_my_msg_server->debugStream = fid;

		p_my_msg_server->register_display_function("info_message_display",&Server::default_display_in_file_info_function);
		p_my_msg_server->register_display_function("error_message_display",&Server::default_display_in_file_info_function);
		p_my_msg_server->register_display_function("warning_message_display",&Server::default_display_in_file_info_function);
		p_my_msg_server->register_display_function("progress_message_display",&Server::default_display_in_file_info_function);
		p_my_msg_server->register_display_function("debug_message_display",&Server::default_display_in_file_info_function);

	} else bReturn = false;


	return bReturn;
}
#endif //OPTION_BUILD_LOG_IN_FILE
/***********************/
/* MESSAGE HANDLERS    */
/***********************/

/***********************************************************/
/* Handler which flushes the output to the relevant stream */
void native_msg_handler_flush( void )
{
	void (*errorDisplay)( const char *format, ...) = NULL;
	void (*infoDisplay)( const char *format, ...) = NULL;
	void (*warningDisplay)( const char *format, ...) = NULL;
	void (*progressDisplay)( const char *format, ...) = NULL;
	void (*debugDisplay)( const char *format, ...) = NULL;
	switch ( Server::get_msg_server()->currentMsgType )
	{

	case EVE_MSG_NULL:
		std::cerr << EVE_LIB_STR_PRINT_PREFIX << 
			" WARNING -- native_msg_handler_flush() -" <<
			" A NULL message type reached the native_msg_handler_flush() handler." <<
			" Ignoring this message.\n" 
			<< std::flush;
		break;

	case EVE_ERROR:
		errorDisplay = Server::get_msg_server()->get_display_function("error_message_display");
		if (errorDisplay)errorDisplay(Server::get_msg_server()->stdBuff);
		else {fprintf( stderr, EVE_LIB_STR_PRINT_PREFIX  " ERROR -- native_msg_handler_flush() -"
			" error cb_display is not define.\n");
		fflush( stderr );}
		break;

	case EVE_WARNING:
		warningDisplay = Server::get_msg_server()->get_display_function("warning_message_display");
		if (warningDisplay)warningDisplay(Server::get_msg_server()->stdBuff); 
		else {fprintf( stderr, EVE_LIB_STR_PRINT_PREFIX  " ERROR -- native_msg_handler_flush() -"
			" warning cb_display is not define.\n");
		fflush( stderr );}
		break;

	case EVE_INFO:
		infoDisplay = Server::get_msg_server()->get_display_function("info_message_display");
		if (infoDisplay)infoDisplay(Server::get_msg_server()->stdBuff);
		else {fprintf( stderr, EVE_LIB_STR_PRINT_PREFIX  " ERROR -- native_msg_handler_flush() -"
			" info cb_display is not define.\n");
		fflush( stderr );}
		break;

	case EVE_PROGRESS:
		progressDisplay = Server::get_msg_server()->get_display_function("progress_message_display");
		if (progressDisplay)progressDisplay(Server::get_msg_server()->stdBuff);
		else { fprintf( stderr, EVE_LIB_STR_PRINT_PREFIX  " ERROR -- native_msg_handler_flush() -"
			" progress cb_display is not define.\n");
		fflush( stderr );}
		break;

	default:
		if ( Server::get_msg_server()->currentMsgType > EVE_MSG_LAST_TYPE ) {
			fprintf( stderr, EVE_LIB_STR_PRINT_PREFIX  " ERROR -- native_msg_handler_flush() -"
				" Invalid message type handled by native_msg_handler_flush()."
				" Ignoring the message.\n" );
			fflush( stderr );}
		else {
			if ( !(Server::get_msg_server()->currentMsgType & Server::get_msg_server()->debugMask) )
				return; /* If the message type does not fit the mask,
						stop here and do nothing. */
			debugDisplay = Server::get_msg_server()->get_display_function("debug_message_display");
			if (debugDisplay)debugDisplay(Server::get_msg_server()->stdBuff);
			else {fprintf( stderr, EVE_LIB_STR_PRINT_PREFIX  " ERROR -- native_msg_handler_flush() -"
				" debug cb_display is not define.\n");
			fflush( stderr );}
			break;

		}
	}
	return;
}

/*********************************************/
/* Handler which ignores the current message */
void native_msg_handler_ignore( void )
{
	return;
}


/***********************/
/* MESSAGING FUNCTIONS */
/***********************/

/***************************************************************/
/* Generic pretty-printing and "parking" of the message std::string */
/* 
* This function formats the passed message and
* stores it in stdBuff in the global messaging server.
*/
size_t make_msg_str( const char *strMsgType, const char *funcName, const char *format, va_list arg ) 
{
	size_t finalSize;
	size_t beginSize;

	/* Pretty-print the beginning of the std::string */
	if(Server::m_b_print_timing)
		beginSize = snprintf( Server::get_msg_server()->stdBuff, Server::get_msg_server()->stdBuffSize,
		EVE_LIB_STR_PRINT_PREFIX "-%s--%s-%s ", GetCurrentTimeCustom(), strMsgType, funcName );
	else 
		beginSize = snprintf( Server::get_msg_server()->stdBuff, Server::get_msg_server()->stdBuffSize,
		"%s-%s ", strMsgType, funcName );

	/* Check if the std::string overflows the message buffer; if yes, just message */
	if ( beginSize >= Server::get_msg_server()->stdBuffSize ) {
		fprintf( stderr, EVE_LIB_STR_PRINT_PREFIX " %s -- native_msg() - Function name [%s] has been truncated.\n",
			strMsgType, funcName );
		fflush( stderr );
	}

	/* Typeset the rest of the std::string, with the variable argument list */
	finalSize = beginSize + Server::get_msg_server()->native_vsnprintf( Server::get_msg_server()->stdBuff + beginSize,
		Server::get_msg_server()->stdBuffSize - beginSize,
		format, arg );

	/* Check if the std::string overflows the message buffer; if yes, realloc the buffer and re-typeset */
	if ( finalSize >= Server::get_msg_server()->stdBuffSize ) {
		char *tmp;
		if ( ( tmp = (char*)realloc( Server::get_msg_server()->stdBuff, finalSize+1 ) ) == NULL ) {
			fprintf( stderr, EVE_LIB_STR_PRINT_PREFIX " ERROR -- native_msg() - Can't realloc the message buffer."
				" The current message will be truncated.\n" );
			fflush( stderr );
		}
		else {
			Server::get_msg_server()->stdBuff = tmp;
			finalSize = beginSize + Server::get_msg_server()->native_vsnprintf( Server::get_msg_server()->stdBuff + beginSize,
				Server::get_msg_server()->stdBuffSize - beginSize,
				format, arg );
		}
	}

	/* Return the final message size */
	return( finalSize );
}


/******************/
/* Error messages */
/******************/

/******************/
/* Using handler: */
size_t native_error_msg( const char *funcName, const char *format, ...  ) 
{

	va_list arg;
	size_t done = 0;

	s_mutex.Lock();

	/* If the handler is EVE_IGNORE, stop here and do nothing. */
	if ( Server::get_msg_server()->errorHandler != EVE_IGNORE )
	{
		/* Store the message type in the server */
		Server::get_msg_server()->currentMsgType = EVE_ERROR;
		/* Make the message std::string */
		va_start ( arg, format );
		done = make_msg_str( "ERROR", funcName, format, arg );
		va_end ( arg );
		/* Launch the message handler */
		(Server::get_msg_server()->errorHandler)();
	}

	s_mutex.Unlock();

	return( done );
}

/**********************/
/* Bypassing handler: */
size_t native_error_msg( FILE *fid, const char *funcName, const char *format, ...  ) 
{

	va_list arg;
	size_t done;

	s_mutex.Lock();

	/* Make the message std::string */
	va_start ( arg, format );
	done = make_msg_str( "ERROR", funcName, format, arg );
	va_end ( arg );
	/* Print the std::string */
	if ( fid == NULL ) return( 0 );
	fprintf( fid, "%s", Server::get_msg_server()->stdBuff );
	fflush( fid );

	s_mutex.Unlock();

	return( done );
}


/********************/
/* Warning messages */
/********************/

/******************/
/* Using handler: */
size_t native_warning_msg( const char *funcName, const char *format, ...  ) 
{

	va_list arg;
	size_t done = 0;

	s_mutex.Lock();

	/* If the handler is EVE_IGNORE, stop here and do nothing. */
	if ( Server::get_msg_server()->warningHandler != EVE_IGNORE )
	{
		/* Store the message type in the server */
		Server::get_msg_server()->currentMsgType = EVE_WARNING;
		/* Make the message std::string */
		va_start ( arg, format );
		done = make_msg_str( "WARNING", funcName, format, arg );
		va_end ( arg );
		/* Launch the message handler */
		(Server::get_msg_server()->warningHandler)();
	}

	s_mutex.Unlock();

	return( done );
}

/**********************/
/* Bypassing handler: */
size_t native_warning_msg( FILE *fid, const char *funcName, const char *format, ...  ) 
{

	va_list arg;
	size_t done;

	s_mutex.Lock();

	/* Make the message std::string */
	va_start ( arg, format );
	done = make_msg_str( "WARNING", funcName, format, arg );
	va_end ( arg );
	/* Print the std::string */
	if ( fid == NULL ) return( 0 );
	fprintf( fid, "%s", Server::get_msg_server()->stdBuff );
	fflush( fid );

	s_mutex.Unlock();

	return( done );
}


/*****************/
/* Info messages */
/*****************/

/******************/
/* Using handler: */
size_t native_info_msg( const char *funcName, const char *format, ...  ) 
{

	va_list arg;
	size_t done = 0;

	s_mutex.Lock();

	/* If the handler is EVE_IGNORE, stop here and do nothing. */
	if ( Server::get_msg_server()->infoHandler != EVE_IGNORE )
	{
		/* Store the message type in the server */
		Server::get_msg_server()->currentMsgType = EVE_INFO;
		/* Make the message std::string */
		va_start ( arg, format );
		done = make_msg_str( "INFO", funcName, format, arg );
		va_end ( arg );
		/* Launch the message handler */
		(Server::get_msg_server()->infoHandler)();
	}

	s_mutex.Unlock();

	return( done );
}

/**********************/
/* Bypassing handler: */
size_t native_info_msg( FILE *fid, const char *funcName, const char *format, ...  ) 
{

	va_list arg;
	size_t done;

	s_mutex.Lock();

	/* Make the message std::string */
	va_start ( arg, format );
	done = make_msg_str( "INFO", funcName, format, arg );
	va_end ( arg );
	/* Print the std::string */
	if ( fid == NULL ) return( 0 );
	fprintf( fid, "%s", Server::get_msg_server()->stdBuff );
	fflush( fid );

	s_mutex.Unlock();

	return( done );
}


/*****************/
/* Progress messages */
/*****************/

/******************/
/* Using handler: */
size_t native_progress_msg( const char *funcName, const char *format, ...  ) 
{

	va_list arg;
	size_t done = 0;

	s_mutex.Lock();

	/* If the handler is EVE_IGNORE, stop here and do nothing. */
	if ( Server::get_msg_server()->progressHandler != EVE_IGNORE )
	{
		/* Store the message type in the server */
		Server::get_msg_server()->currentMsgType = EVE_PROGRESS;
		/* Make the message std::string */
		va_start ( arg, format );
		done = make_msg_str( "PROGRESS", funcName, format, arg );
		va_end ( arg );
		/* Launch the message handler */
		(Server::get_msg_server()->progressHandler)();
	}

	s_mutex.Unlock();

	return( done );
}

/**********************/
/* Bypassing handler: */
size_t native_progress_msg( FILE *fid, const char *funcName, const char *format, ...  ) 
{

	va_list arg;
	size_t done;

	s_mutex.Lock();

	/* Make the message std::string */
	va_start ( arg, format );
	done = make_msg_str( "PROGRESS", funcName, format, arg );
	va_end ( arg );
	/* Print the std::string */
	if ( fid == NULL ) return( 0 );
	fprintf( fid, "%s", Server::get_msg_server()->stdBuff );
	fflush( fid );

	s_mutex.Unlock();

	return( done );
}


/******************/
/* Debug messages */
/******************/

/* ---- "Ghost" debug functions */
//#ifndef NDEBUG

/******************/
/* Using handler: */
size_t native_debug_msg( const unsigned long int msgType, const char *funcName, const char *format, ...  )
{

	va_list arg;
	size_t done = 0;

	s_mutex.Lock();

	/* If the handler is EVE_IGNORE, stop here and do nothing. */
	if ( Server::get_msg_server()->debugHandler != EVE_IGNORE )
	{
		/* If the message type does not fit the mask, stop here and do nothing. */
		if ( (msgType & Server::get_msg_server()->debugMask) )
		{
			/* Store the message type in the server */
			Server::get_msg_server()->currentMsgType = msgType;
			/* Make the message std::string */
			va_start ( arg, format );
			done = make_msg_str( "DEBUG", funcName, format, arg );
			va_end ( arg );
			/* Launch the message handler */
			(Server::get_msg_server()->debugHandler)();
		}
	}

	s_mutex.Unlock();

	return( done );
}

/**********************/
/* Bypassing handler: */
size_t native_debug_msg( FILE *fid, const unsigned long int msgType, const char *funcName, const char *format, ...  )
{

	va_list arg;
	size_t done;

	s_mutex.Lock();

	/* Make the message std::string */
	va_start ( arg, format );
	done = make_msg_str( "DEBUG", funcName, format, arg );
	va_end ( arg );
	/* If the message type does not fit the mask, stop here and do nothing. */
	if ( !(msgType & Server::get_msg_server()->debugMask) )
	{
		/* Print the std::string */
		if ( fid == NULL ) return( 0 );
		fprintf( fid, "%s", Server::get_msg_server()->stdBuff );
		fflush( fid );
	}

	s_mutex.Unlock();

	return( done );
}

//#endif /* #ifndef NDEBUG */

/*---- "Forced" debug functions */

/******************/
/* Using handler: */
size_t native_debug_msg_forced( const unsigned long int msgType, const char *funcName, const char *format, ...  ) 
{

	va_list arg;
	size_t done = 0;

	s_mutex.Lock();

	/* If the handler is EVE_IGNORE, stop here and do nothing. */
	if ( Server::get_msg_server()->debugHandler != EVE_IGNORE )
	{
		/* NOTE: In this version, the mask is ignored, the message is output in any case. */
		/* Store the message type in the server */
		Server::get_msg_server()->currentMsgType = msgType;
		/* Make the message std::string */
		va_start ( arg, format );
		done = make_msg_str( "DEBUG", funcName, format, arg );
		va_end ( arg );
		/* Launch the message handler */
		(Server::get_msg_server()->debugHandler)();
	}

	s_mutex.Unlock();

	return( done );
}

/**********************/
/* Bypassing handler: */
size_t native_debug_msg_forced( FILE *fid, const unsigned long int /* msgType */,const char *funcName, const char *format, ...  ) 
{

	va_list arg;
	size_t done;

	s_mutex.Lock();

	/* Make the message std::string */
	va_start ( arg, format );
	done = make_msg_str( "DEBUG", funcName, format, arg );
	va_end ( arg );
	/* NOTE: In this version, the mask is ignored, the message is output in any case. */
	/* Print the std::string */
	if ( fid == NULL ) return( 0 );
	fprintf( fid, "%s", Server::get_msg_server()->stdBuff );
	fflush( fid );

	s_mutex.Unlock();

	return( done );
}

void Server::default_display_error_function(const char *format, ...)
{
	va_list arg;

	va_start ( arg, format );

	fprintf( stderr, format, arg );
	fflush( stderr );
}

void Server::default_display_in_file_error_function(const char *format, ...)
{
	va_list arg;

	va_start ( arg, format );
	fprintf( (FILE*)get_error_stream(), format, arg );
	fflush(  (FILE*)get_error_stream() );
}

void Server::default_display_in_file_info_function(const char *format, ...)
{
	va_list arg;

	va_start ( arg, format );
	fprintf( (FILE*)get_info_stream(), format, arg  );
	fflush(  (FILE*)get_info_stream() );
}

void Server::default_display_in_file_warning_function(const char *format, ...)
{
	va_list arg;

	va_start ( arg, format );
	fprintf( (FILE*)get_warning_stream(), format, arg );
	fflush(  (FILE*)get_warning_stream() );
}

void Server::default_display_in_file_debug_function(const char *format, ...)
{
	va_list arg;

	va_start ( arg, format );
	fprintf( (FILE*)get_debug_stream(), format, arg  );
	fflush(  (FILE*)get_debug_stream() );
}

void Server::default_display_in_file_progress_function(const char *format, ...)
{
	va_list arg;

	va_start ( arg, format );
	fprintf( (FILE*)get_progress_stream(), format, arg  );
	fflush(  (FILE*)get_progress_stream() );
}

