#ifndef __DEBUG_FILE_H__
#define __DEBUG_FILE_H__

#if defined(DEBUG) || defined(_DEBUG)
	#define TRACE(fmt, args...) printf(fmt, ## args);debugtrace(fmt, ## args)
	void debugtrace(const char *format, ...);
	void debuginit();
	void debugend();
	void debugenable(int bEanble);
#elif defined(LOGFILE)
	#define TRACE debugtrace
	void debugtrace(const char *format, ...);
	void debuginit();
	void debugend();
	void debugenable(int bEanble);
#else
	#define TRACE(fmt, args...)
#endif

#endif //__DEBUG_FILE_H__

