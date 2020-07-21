// UdpRecvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UdpRecv.h"
#include "UdpRecvDlg.h"
#include "RecvUdp.h"
#include "glbs.h"

CRecvUdp	mUdpSocket;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

   //每通道最多传感器数量为20个。
/////////////////////////////////////////////////////////////////////////////
// CUdpRecvDlg dialog

struct _fbgResult_arary mRecvData;//struct _fbgResult mRecvData[16][20];
int g_num;//计数
int g_fftBufferCount;//FFT包计数。
byte g_sourceID;//数据来源机器的ID号 0~255

CUdpRecvDlg::CUdpRecvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUdpRecvDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUdpRecvDlg)
	m_NumFrame=0;
	m_sourceID = 0;
	m_fftBufferCount = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUdpRecvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUdpRecvDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListChannelRes);
	DDX_Text(pDX, IDC_FRAMENUM, m_NumFrame);
	DDX_Text(pDX, IDC_sourceID, m_sourceID);
	DDX_Text(pDX, IDC_fftBufferCount, m_fftBufferCount);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUdpRecvDlg, CDialog)
	//{{AFX_MSG_MAP(CUdpRecvDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUdpRecvDlg message handlers

BOOL CUdpRecvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//	if(!mUdpSocket.Create(0x7500,SOCK_DGRAM,"192.168.0.9"))
	if(!mUdpSocket.Create(0x8001,SOCK_DGRAM,NULL))
		AfxMessageBox("UDP Socket Create error");
	else
	{
		int value,len;
		int nRecBuf=900*1024;
		len=sizeof(value);
		mUdpSocket.SetSockOpt(SO_RCVBUF,&nRecBuf,sizeof(nRecBuf));//设置接收缓存大小。
		mUdpSocket.GetSockOpt(SO_RCVBUF,(char*)&value,&len); //增大后明显降低丢包率。		
	}
	
	HWND hWnd=m_ListChannelRes.m_hWnd;	         //获取句柄
	DWORD dwStyle = GetWindowLong(hWnd,GWL_STYLE);		//获取显示格式
	if( (dwStyle&LVS_TYPEMASK)!=LVS_REPORT) 
		SetWindowLong(hWnd,GWL_STYLE,(dwStyle&~LVS_TYPEMASK|LVS_REPORT));//设置显示格式
	m_ListChannelRes.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_TYPEMASK);//加坐标线,全选一行 
	//m_ListChannelRes.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_TYPEMASK|LVS_SHOWSELALWAYS);//加坐标线
	

	m_ListChannelRes.DeleteAllItems();
	m_ListChannelRes.InsertColumn(0,"序号",LVCFMT_CENTER,40);
	m_ListChannelRes.InsertColumn(1,"通道1",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(2,"通道2",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(3,"通道3",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(4,"通道4",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(5,"通道5",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(6,"通道6",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(7,"通道7",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(8,"通道8",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(9,"通道9",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(10,"通道10",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(11,"通道11",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(12,"通道12",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(13,"通道13",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(14,"通道14",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(15,"通道15",LVCFMT_LEFT,72);
	m_ListChannelRes.InsertColumn(16,"通道16",LVCFMT_LEFT,72);
	//m_ListChannelRes.InsertColumn(17,"通道18",LVCFMT_LEFT,72);

	CString	temp;
	int i;
	for(i=0;i<maxChannelSensor;i++) {
		temp.Format("%d",i+1);
		m_ListChannelRes.InsertItem(i+1,temp);
	}
	SetTimer(1,1000,NULL);

	if(errReportFile.m_hFile==CFile::hFileNull)
		errReportFile.Open("错误日志.txt" ,CFile::modeCreate|CFile::modeReadWrite);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUdpRecvDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUdpRecvDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUdpRecvDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 1:
		ListWaveandEng();
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void	CUdpRecvDlg::ListWaveandEng()
{
	CString	temp,tempUnit;
	int i,j,num;
	for(i=0;i<16;i++) 
	{		
		for(j=0;j<maxChannelSensor;j++)//清空
		{
			m_ListChannelRes.SetItemText(j, i+1, "");			
		}
		for(j=0;j<maxChannelSensor;j++)
		{			
			if (mRecvData.result_ch[i].fbgResult[j].alarmStatus==-1) //0 正常  1 丢失(无光栅数据) 2.丢失(无配对波长) 3预警  4报警  -1无此参数
				temp="";
			else if (mRecvData.result_ch[i].fbgResult[j].alarmStatus==1)//丢失
				temp="      #";
			else
			{
				//if (mRecvData.fbgResult[i][j].sensorType=="ACCE"||mRecvData.fbgResult[i][j].sensorType=="加速度计")			
				if (strcmp(mRecvData.result_ch[i].fbgResult[j].sensorType,"ACCE")==0 || strcmp(mRecvData.result_ch[i].fbgResult[j].sensorType,"加速度计")==0)			
					temp.Format("%9.4f",mRecvData.result_ch[i].fbgResult[j].fout[0].f);
				else
					temp.Format("%9.1f",mRecvData.result_ch[i].fbgResult[j].result);
				//tempUnit.Format("%s",mRecvData.result_ch[i].fbgResult[j].unit);
				//temp=temp+tempUnit;
			}
			m_ListChannelRes.SetItemText(j, i+1, temp);			
		}
	}
	m_NumFrame=g_num;
	m_sourceID=g_sourceID;
	m_fftBufferCount=g_fftBufferCount;
	UpdateData(FALSE);
}

