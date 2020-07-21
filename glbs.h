// glbs.h: interface for the glbs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLBS_H__D753B12A_8C32_4FE5_B267_A3D888ABE39F__INCLUDED_)
#define AFX_GLBS_H__D753B12A_8C32_4FE5_B267_A3D888ABE39F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern CStdioFile	errReportFile;
extern BOOL	ReportErr(CString *pString);

class glbs  
{
public:
	glbs();
	virtual ~glbs();

};

#endif // !defined(AFX_GLBS_H__D753B12A_8C32_4FE5_B267_A3D888ABE39F__INCLUDED_)
