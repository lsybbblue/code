// RecvUdp.cpp : implementation file
//

#include "stdafx.h"
#include "UdpRecv.h"
#include "RecvUdp.h"
#include "UdpRecvDlg.h"
#include "glbs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecvUdp

extern _fbgResult_arary	mRecvData;
extern int g_num;//计数
extern byte g_sourceID;
extern int g_fftBufferCount;

char  mRecvData_Char[24000];
CRecvUdp::CRecvUdp()
{
}

CRecvUdp::~CRecvUdp()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRecvUdp, CSocket)
	//{{AFX_MSG_MAP(CRecvUdp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CRecvUdp member functions

void CRecvUdp::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnAccept(nErrorCode);
}

void CRecvUdp::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	static int num=0;
	int ch;
	_fbgResult_channel tempResultCh;
	_SensorfftBuffer tempFftBuffer;//加速度传感器缓存，
	CString sss;
// 	char *addChar;
// 	addChar=(char*)&mRecvData;
	//int temp1=CRecvUdp::Receive(&mRecvData,sizeof(mRecvData),0);
	//int aaa=sizeof(mRecvData);
	//int bbb=sizeof(_fbgResult_channel);
	int temp1=CRecvUdp::Receive(&mRecvData_Char,sizeof(mRecvData_Char),0);//
	switch (temp1)
	{
	case sizeof(mRecvData):
		g_num++;
		memcpy((char*)&mRecvData,&mRecvData_Char,sizeof(mRecvData));
		g_sourceID=mRecvData.result_ch[0].pcID;
		break;
	case sizeof(_fbgResult_channel):
		memcpy((char*)&tempResultCh,&mRecvData_Char,sizeof(_fbgResult_channel));
		ch=tempResultCh.fbgResult[0].chn;
		memcpy(&mRecvData.result_ch[ch],&tempResultCh,sizeof(_fbgResult_channel));
		num++;
		g_num=num/16;///16;
		//sss.Format("\n ch= %d  ",ch);ReportErr(&sss);
		break;
	case sizeof(_SensorfftBuffer)://加速度传感器的缓存   //大小416
		g_fftBufferCount++;
		memcpy((char*)&tempFftBuffer,&mRecvData_Char,sizeof(tempFftBuffer));	
		break;
	default:
		break;
	}
	//g_sourceID=mRecvData.result_ch[0].pcID;
	
	/*
	if (temp1==sizeof(mRecvData))//20608	
	{
		g_num++;
		memcpy((char*)&mRecvData,&mRecvData_Char,sizeof(mRecvData));	
	}
	else if (temp1==1288)	
	{	
		memcpy((char*)&tempResultCh,&mRecvData_Char,sizeof(_fbgResult_channel));
		ch=tempResultCh.fbgResult[0].chn;
		memcpy(&mRecvData.result_ch[ch],&tempResultCh,sizeof(_fbgResult_channel));
		num++;
		g_num=num/16;///16;
		sss.Format("\n ch= %d  ",ch);ReportErr(&sss);
	}
	else if (temp1==sizeof(_SensorfftBuffer))//加速度传感器的缓存   //大小416
	{
		g_fftBufferCount++;
		memcpy((char*)&tempFftBuffer,&mRecvData_Char,sizeof(tempFftBuffer));	
	}
	//sss.Format("g_num=  %d  num=  %d  ch= %d",g_num,num,ch);ReportErr(&sss);
	//int ss=sizeof(mRecvData_Char);
	
 	
	g_sourceID=mRecvData.result_ch[0].pcID;
	
	//sss.Format("temp1=%d",temp1);
	//AfxMessageBox(sss);
	*/
	
	CSocket::OnReceive(nErrorCode);
}
