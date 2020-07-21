// UdpRecvDlg.h : header file
//

#if !defined(AFX_UDPRECVDLG_H__FEB66650_E5FC_4CD2_9FC5_A29C52D98555__INCLUDED_)
#define AFX_UDPRECVDLG_H__FEB66650_E5FC_4CD2_9FC5_A29C52D98555__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUdpRecvDlg dialog
#define  maxChannelSensor 20


class CUdpRecvDlg : public CDialog
{
// Construction
public:
	CUdpRecvDlg(CWnd* pParent = NULL);	// standard constructor
	void	ListWaveandEng();
// Dialog Data
	//{{AFX_DATA(CUdpRecvDlg)
	enum { IDD = IDD_UDPRECV_DIALOG };
	CListCtrl	m_ListChannelRes;
	int		m_NumFrame;
	BYTE	m_sourceID;
	int		m_fftBufferCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUdpRecvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUdpRecvDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPRECVDLG_H__FEB66650_E5FC_4CD2_9FC5_A29C52D98555__INCLUDED_)
