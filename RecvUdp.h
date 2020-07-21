#if !defined(AFX_RECVUDP_H__89BA7819_061C_4875_A02A_05CBC2C91A77__INCLUDED_)
#define AFX_RECVUDP_H__89BA7819_061C_4875_A02A_05CBC2C91A77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecvUdp.h : header file
//
struct _SensorfftBuffer   //���ٶȴ����������ݽṹ
{
	byte pcID;//����ID
	char chn;//������ͨ��
	char num;//���������
	char sensorID[10];//������ID��
	float buffer[100];//����100������
};

typedef struct frequncy         //Ƶ�ʵĽṹ��
{ 	
	float f;  //Ƶ��
	float amplitude;//���� 
}FREQUENCY;

struct _fbgResult  //��դ�Ľ�����ݡ�
{
	char chn;		      //ͨ����
	char num;		      //˳���
	char sensorID[10];//������ID
	char sensorType[10];   //����������
	char unit[2];//�����λ
	float result;   
	float wavelength;//�������Ĳ���
	float fbgPower;//������������
	char alarmStatus; //-1�޴����� 0 ���� 1��ʧ 2.��ʧ(����Բ���) 3Ԥ��  4���� 	
	frequncy fout[4];     //Ƶ�ʵĽ�� 
};
struct _fbgResult_channel
{
	DWORD frameNo;//֡��
	byte pcID; //����ID��
	_fbgResult fbgResult[20];
};

struct _fbgResult_arary  //��դ�Ľ�����ݡ�
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
