//LinuxDef.h
#ifndef __LinuxDef_h__
#define __LinuxDef_h__

#ifdef SYS_LINUX
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include "PtrArray.h"
#include "debug.h"

#define WINAPI
#define __stdcall
#define INFINITE            0xFFFFFFFF  // Infinite timeout
#define TRUE				1
#define FALSE				0
#define CNET_APIIMPORT
#define THREAD_PRIORITY_ABOVE_NORMAL	1
#define THREAD_PRIORITY_NORMAL			0
#define FIONBIO				1
#define MAX_PATH			256

#ifndef FD_SETSIZE_TRANS
#define FD_SETSIZE_TRANS      FD_SETSIZE
#endif /* FD_SETSIZE_TRANS */
#define FD_SET_TRANS		FD_SET
#define FD_ZERO_TRANS		FD_ZERO
#define fd_set_trans		fd_set

/* ·ÅÔÚdebug.hÖÐ
#if defined(DEBUG) || defined(_DEBUG)
#define TRACE(fmt, args...) printf(fmt, ## args)
#else
#define TRACE(fmt, args...)
#endif//DEBUG
*/

#define	CSOCK_OK				0
#define	CSOCK_ERROR				-1
#define CSOCK_HANDLE			SOCKET
#define CSOCK_INVALIDHANDLE		-1
#define	CSOCK_SHUTRD			SHUT_RD
#define	CSOCK_SHUTWR			SHUT_WR
#define	CSOCK_SHUTBOTH			SHUT_RDWR
#define CSOCK_CLOSE				close
#define CSOCK_SHUTDOWN			shutdown
//#define INADDR_NONE             0xffffffff
#define CSOCK_SAVECLOSE(sock)		if(sock > 0 && sock != CSOCK_INVALIDHANDLE) {CSOCK_SHUTDOWN(sock,2); CSOCK_CLOSE(sock); sock = CSOCK_INVALIDHANDLE; }
#define CSOCK_SAVESHUT(sock,how)	if(sock > 0 && sock != CSOCK_INVALIDHANDLE) {CSOCK_SHUTDOWN(sock,how); }
#define SOCKET_ERROR		(-1)
#define WSAEWOULDBLOCK          EWOULDBLOCK
#define WSAEINPROGRESS          EINPROGRESS
#define WSAEALREADY             EALREADY
#define WSAENOTSOCK             ENOTSOCK
#define WSAEDESTADDRREQ         EDESTADDRREQ
#define WSAEMSGSIZE             EMSGSIZE
#define WSAEPROTOTYPE           EPROTOTYPE
#define WSAENOPROTOOPT          ENOPROTOOPT
#define WSAEPROTONOSUPPORT      EPROTONOSUPPORT
#define WSAESOCKTNOSUPPORT      ESOCKTNOSUPPORT
#define WSAEOPNOTSUPP           EOPNOTSUPP
#define WSAEPFNOSUPPORT         EPFNOSUPPORT
#define WSAEAFNOSUPPORT         EAFNOSUPPORT
#define WSAEADDRINUSE           EADDRINUSE
#define WSAEADDRNOTAVAIL        EADDRNOTAVAIL
#define WSAENETDOWN             ENETDOWN
#define WSAENETUNREACH          ENETUNREACH
#define WSAENETRESET            ENETRESET
#define WSAECONNABORTED         ECONNABORTED
#define WSAECONNRESET           ECONNRESET
#define WSAENOBUFS              ENOBUFS
#define WSAEISCONN              EISCONN
#define WSAENOTCONN             ENOTCONN
#define WSAESHUTDOWN            ESHUTDOWN
#define WSAETOOMANYREFS         ETOOMANYREFS
#define WSAETIMEDOUT            ETIMEDOUT
#define WSAECONNREFUSED         ECONNREFUSED
#define WSAELOOP                ELOOP
#define WSAENAMETOOLONG         ENAMETOOLONG
#define WSAEHOSTDOWN            EHOSTDOWN
#define WSAEHOSTUNREACH         EHOSTUNREACH
#define WSAENOTEMPTY            ENOTEMPTY
#define WSAEPROCLIM             EPROCLIM
#define WSAEUSERS               EUSERS
#define WSAEDQUOT               EDQUOT
#define WSAESTALE               ESTALE
#define WSAEREMOTE              EREMOTE

#define C_OPEN					open
#define C_CLOSE					close
#define C_SEEK					lseek
#define	C_TELL					tell
#define C_READ					read
#define C_WRITE					write
#define _O_CREAT				O_CREAT
#define _O_TRUNC				O_TRUNC
#define _O_RDWR					O_RDWR
#define _O_BINARY				0
#define _S_IREAD				S_IREAD
#define _S_IWRITE				S_IWRITE

//MIN16384(16K) 0x1c000 128K(923) 0x3c000 256K(8xx) 0xc000 64K(1105) 0x4000 32K(1181)
#define PTHREAD_MYSTACKSIZE		0x3c000

#define MAX_EVENTS				32

#define new	new(std::nothrow)

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef void*				HWND;
typedef void*				HDC;
typedef void*				HANDLE;
typedef long				LONG;
typedef unsigned long		ULONG;
typedef unsigned int		UINT;
typedef int					SOCKET;
typedef DWORD				COLORREF;
typedef char CHAR;
typedef CHAR *LPSTR, *PSTR;
typedef LPSTR				PTSTR, LPTSTR, PUTSTR, LPUTSTR;

typedef struct tagRECT
{
    long    left;
    long    top;
    long    right;
    long    bottom;
} RECT;//, *PRECT, NEAR *NPRECT, FAR *LPRECT;


void Sleep(unsigned int dwMilliseconds);
DWORD GetTickCount();
DWORD timeGetTime(void);
off_t tell(int fildes);
int ioctlsocket (SOCKET sock, long cmd, unsigned long *argp);
int WSAGetLastError(void);


#endif	// SYS_LINUX
#endif	// __LinuxDef_h__
