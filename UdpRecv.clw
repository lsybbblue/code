; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUdpRecvDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "UdpRecv.h"

ClassCount=3
Class1=CUdpRecvApp
Class2=CUdpRecvDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CRecvUdp
Resource2=IDD_UDPRECV_DIALOG

[CLS:CUdpRecvApp]
Type=0
HeaderFile=UdpRecv.h
ImplementationFile=UdpRecv.cpp
Filter=N

[CLS:CUdpRecvDlg]
Type=0
HeaderFile=UdpRecvDlg.h
ImplementationFile=UdpRecvDlg.cpp
Filter=D
LastObject=IDC_fftBufferCount
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_UDPRECV_DIALOG]
Type=1
Class=CUdpRecvDlg
ControlCount=7
Control1=IDC_LIST1,SysListView32,1350631425
Control2=IDC_STATIC,static,1342308352
Control3=IDC_FRAMENUM,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_sourceID,edit,1350631552
Control6=IDC_fftBufferCount,edit,1350631552
Control7=IDC_STATIC,static,1342308352

[CLS:CRecvUdp]
Type=0
HeaderFile=RecvUdp.h
ImplementationFile=RecvUdp.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CRecvUdp

