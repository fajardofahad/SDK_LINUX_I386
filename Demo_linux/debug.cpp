#include <stdarg.h>
#include "LinuxDef.h"
#include "debug.h"

#if defined(DEBUG) || defined(_DEBUG) || defined(LOGFILE)
//#elif defined(LOGFILE)

#define LOGFILESIZE			500*1024			//单个文件大小不超过500K
#define OUTPUTDIR			"/var/log/ipvslog"
#define OUTPUTSUBDIR		"NetClient"

static BOOL	 bOutputLog		 = TRUE;
static int   debugfilehandle = -1;

void debuginit()
{
	if (debugfilehandle != -1)
	{
		if (tell(debugfilehandle) >= LOGFILESIZE)  
		{
			close(debugfilehandle);
			debugfilehandle = -1;
		}
	}

	if (debugfilehandle == -1)
	{
		time_t	   tick = time(NULL);
        struct tm  *curTime;
        char       szFile[1024];
		
        curTime = localtime(&tick);

		sprintf(szFile,"%s",OUTPUTDIR);
		mkdir(szFile, 0755);
		sprintf(szFile,"%s/%s",OUTPUTDIR,OUTPUTSUBDIR);
		mkdir(szFile, 0755);
		sprintf(szFile,"%s/%s/%04d%02d%02d%02d%02d%02d.log",OUTPUTDIR,OUTPUTSUBDIR,
                curTime->tm_year+1900,
                curTime->tm_mon+1,
                curTime->tm_mday,
                curTime->tm_hour,
                curTime->tm_min,
                curTime->tm_sec);
        
        debugfilehandle = open(szFile, O_CREAT | O_RDWR , S_IREAD | S_IWRITE);
	}
}

void debugenable(BOOL bEanble)
{
	if( !bEanble && debugfilehandle != -1 )
	{
		debugtrace("****************Output Close By User****************\n");
		close(debugfilehandle);
		debugfilehandle = -1;
	}
	bOutputLog = bEanble;
}

void debugtrace(const char *format, ...)
{
    if( !bOutputLog ) return;

	char buff[1024];
	char szTime[200];
	time_t nowtime;

	try
    {
        debuginit();
        
        if( debugfilehandle == -1 ) return;
        
        int iRet;
        va_list vaList;
        va_start(vaList, format);
        iRet = vsprintf(buff,format,vaList);
        va_end(vaList);
        lseek(debugfilehandle,-1,SEEK_END);
        nowtime = time(NULL);
        sprintf(szTime,"%s",ctime(&nowtime));
        szTime[strlen(szTime)-1] = '\0';
        write(debugfilehandle,szTime,strlen(szTime) + 1);
        write(debugfilehandle,buff,iRet + 1);
    }
    catch(...)
    {
        char    szError[1024];
        sprintf(szError,"TRACE Error:%s\n",format);
        printf(szError);
    }
}

void debugend()
{
	if( debugfilehandle == -1 ) return;

	close(debugfilehandle);
	debugfilehandle = -1;
}

#endif //DEBUG_FILE

