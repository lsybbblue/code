#if !defined(AFX_RECVUDP_H__89BA7819_061C_4875_A02A_05CBC2C91A77__INCLUDED_)
#define AFX_RECVUDP_H__89BA7819_061C_4875_A02A_05CBC2C91A77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecvUdp.h : header file
//
struct _SensorfftBuffer   //加速度传感器的数据结构
{
	byte pcID;//本机ID
	char chn;//传感器通道
	char num;//传感器序号
	char sensorID[10];//传感器ID号
	float buffer[100];//最新100个数据
};

typedef struct frequncy         //频率的结构体
{ 	
	float f;  //频率
	float amplitude;//幅度 
}FREQUENCY;

struct _fbgResult  //光栅的结果数据。
{
	char chn;		      //通道号
	char num;		      //顺序号
	char sensorID[10];//传感器ID
	char sensorType[10];   //传感器类型
	char unit[2];//结果单位
	float result;   
	float wavelength;//传感器的波长
	float fbgPower;//传感器的能量
	char alarmStatus; //-1无传感器 0 正常 1丢失 2.丢失(无配对波长) 3预警  4报警 	
	frequncy fout[4];     //频率的结果 
};
struct _fbgResult_channel
{
	DWORD frameNo;//帧号
	byte pcID; //本机ID号
	_fbgResult fbgResult[20];
};

struct _fbgResult_arary  //光栅的结果数据。
{
	_fbgResult_channel result_ch[16];
};

/////////////////////////////////////////////////////////////////////////////
// CRecvUdp command target

class CRecvUdp : public CSocket
{
// Attributes
public:

// Operations
public:
	CRecvUdp();
	virtual ~CRecvUdp();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecvUdp)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRecvUdp)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECVUDP_H__89BA7819_061C_4875_A02A_05CBC2C91A77__INCLUDED_)
