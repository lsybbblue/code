// glbs.cpp: implementation of the glbs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UdpRecv.h"
#include "glbs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CStdioFile	errReportFile;
BOOL ReportErr(CString *pString)
{
	if(errReportFile.m_hFile==CFile::hFileNull)
		return FALSE;
	char ccc[512];
	memset(ccc,0,512);
	memcpy(ccc,pString->GetBuffer(pString->GetLength()),pString->GetLength());
	errReportFile.Write(ccc,strlen(ccc));
	return TRUE;
}

glbs::glbs()
{

}

glbs::~glbs()
{

}
