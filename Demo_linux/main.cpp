#include <stdio.h>
#include "LinuxDef.h"
#include "launet.h"

long s_pushtest = -1;

static void s_messagecallback(LONG hHandle,int wParam,int lParam,void *context)
{
	switch(wParam)
	{
	case  LAUMSG_LINKMSG:
		{
			if(lParam == 0)
			{
//				sMsgData = "连接成功";
                printf("connect successful\n");
//              VSNET_ClientStartMp4Capture(hHandle, "/root/Desktop/rec/linuxrec.mp4");
			}
			else if(lParam ==1)
			{
//				sMsgData = "用户停止了连接";
                printf("user stop connect\n");
			}
			else if(lParam ==2)
			{
//				sMsgData = "连接失败";
                printf("connect failed\n");
			}
			else if(lParam == 3)
			{
				//sMsgData = "连接断开";
                printf("connect dislinked\n");
			}
			else if(lParam == 4)
			{
				//sMsgData = "端口冲突";
                printf("port assert\n");
			}
			else if(lParam == 5)
			{
				//sMsgData = "分配内存失败";
                printf("memory assign failed\n");
			}
			else if(lParam == 6)
			{
				//sMsgData = "连接域名服务器失败";
                printf("connect dns failed\n");
			}
			else if(lParam == -102)
			{
				//sMsgData = "用户名密码错误";
                printf("username or password wrong\n");
			}
			else if(lParam == -103)
			{
				//sMsgData = "系统用户满员";
				printf("system user full\n");
			}
			else if(lParam == -105)
			{
				//sMsgData = "通道用户满员";
				printf("channel user full\n");
			}
			else if(lParam == -106)
			{
			//	sMsgData = "没有指定的通道";
			printf("no such channel\n");
			}
			else if(lParam == -112)
			{
				//sMsgData = "没有找到服务器";
                printf("not find server\n");
			}
			else
			{
				//sMsgData = "未知";
			}
			break;
		}
	case LAUMSG_VIDEOMOTION:
//	    sMsgType = "视频移动报警";
        printf("video motion alarm\n");
		break;
	case LAUMSG_VIDEOLOST:
//	    sMsgType = "视频丢失报警";
        printf("video lost alarm\n");
		break;
	case LAUMSG_ALARM:
		{
//	        sMsgType = "探头报警:";
        printf("sensor alarm\n");
			break;
		}
	case LAUMSG_OUTPUTSTATUS:
//	    sMsgType = "报警输出状态";
        printf("alarmout status\n");
		break;
	case LAUMSG_CURSWITCHCHAN:
//		sMsgType = "当前切换通道";
        printf("curswitch\n");
		break;
	case LAUMSG_HIDEALARM:
//		sMsgType = "图像遮挡报警";
        printf("video hiden alarm\n");
		break;

	default:
//		sMsgType = "未知";
		break;
	}
    return;
}

static int   s_RedirectUserCheckcallback(char *m_url,char *username,char *password)
{
    return VSNET_USER_RIGHT_ADMIN;
}
static int g_UserConnectcallback(char *m_sername,int channel,BOOL bStart,char *m_userurl,char *username,char *password,int transtype,long handle)
{
    if (bStart)
    {
        printf("user connect sername:%s, channel:%d, userurl:%s, username:%s, password:%s, transtype:%d \n", m_sername, channel, m_userurl, username, password, transtype);
    }
    else
    {
        printf("user checkout sername:%s, channel:%d, userurl:%s, username:%s, password:%s, transtype:%d \n", m_sername, channel, m_userurl, username, password, transtype);
    }
    return 0;
}
static void LoadRedirectorParam()
{
	VSNET_REDIRECTORINFO pRedireInfo;


    pRedireInfo.m_audiobuff = 50;
    pRedireInfo.m_videobuff = 50;
    pRedireInfo.m_channuser = 102400;//50
    sprintf(pRedireInfo.m_multiip,"%s","234.5.6.7");
    pRedireInfo.m_totaluser = 102400;
    pRedireInfo.m_wLocaport = 3000;
    pRedireInfo.m_wMultiPort= 6000;
    pRedireInfo.m_UserConnectcallback = g_UserConnectcallback;
    pRedireInfo.m_UserCheckcallback = s_RedirectUserCheckcallback;

    VSNET_SetRedirectorInfo(&pRedireInfo);
    if(VSNET_StartListenClient(NULL) != 0)
        {
            printf("START redirector listen wrong\n");
        }

}

static int WINAPI serchancheck(const char *sername, const char *url, WORD port,
							   const char *serialno, unsigned char pyhmac[6],
							   int channels, int AlarmInNum, int AlarmOutNum, int ch, int bLogin, long hChHandle)
{
	if (bLogin)
	{
//		if (s_pushtest != -1) return 0;
		printf("serchancheck login sername: %s\n", sername);
		VSNET_RVSRegMsgCallback(hChHandle, s_messagecallback, (void*)0X88FF);
		VSNET_RVSSetChanServerID(hChHandle, (char*)sername);
		VSNET_ClientMediaData(hChHandle, TRUE);
//		s_pushtest = hChHandle;
	}
	else
	{
	    printf("serchancheck logout sername: %s\n", sername);
//	    s_pushtest = -1;
	}
	return 0;
}

int main()
{
    printf("11111\n");
	VSNET_ClientStartup(0,NULL);
	VSNET_ClientWaitTime(30,4);
	LoadRedirectorParam();

	VSNET_RVSRegSerCheckCallback(serchancheck);
	VSNETRVSINFO rvsinfo;
	rvsinfo.m_rvsbindurl = NULL;
	rvsinfo.m_rvsbindport = 3004;
	VSNET_RVSStartServer(&rvsinfo);
/*
    char password[40],username[40],url[40],sername[40];
    strcpy(sername, "vs");
    strcpy(username, "888888");
    strcpy(password, "888888");
    strcpy(url, "192.168.1.97");

   	CHANNEL_CLIENTINFO m_chinfo;
    m_chinfo.m_sername = sername;
    m_chinfo.m_username = username;
    m_chinfo.m_password = password;
    m_chinfo.m_buffnum = 50;
    m_chinfo.m_ch = 0;
    m_chinfo.m_hChMsgWnd = NULL;
    m_chinfo.m_hVideohWnd = NULL;
    m_chinfo.m_nChmsgid = 0;
    m_chinfo.m_playstart = FALSE;
    m_chinfo.m_tranType = 3;
    m_chinfo.m_useoverlay = FALSE;
    m_chinfo.nColorKey = 0x00FF00FF;
    m_chinfo.context = (void*)2;
    m_chinfo.m_messagecallback = s_messagecallback;

    LONG m_hchann = VSNET_ClientStart(url, &m_chinfo);
	VSNET_ClientSetRedirectDelayTime(m_hchann, 10);
*/
    printf("222222\n");
    getchar();
 //   usleep(1000 * 1000 * 5);
 //   VSNET_ClientStopMp4Capture(m_hchann);
    printf("3333333\n");
//    VSNET_ClientStop(m_hchann);
	VSNET_RVSStopServer();
    printf("4444444\n");
	VSNET_StopListenClient();
	printf("555555555\n");
	VSNET_ClientCleanup();

    return 0;
}
