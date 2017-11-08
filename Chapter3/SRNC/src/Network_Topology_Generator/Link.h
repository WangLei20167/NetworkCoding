// Link.h: interface for the CLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINK_H__E126D3A4_BAD4_4BC8_8451_D3A9A21A97B4__INCLUDED_)
#define AFX_LINK_H__E126D3A4_BAD4_4BC8_8451_D3A9A21A97B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLink  
{
public:
	CLink();
	virtual ~CLink();
	CPoint posStartPos;
	CPoint posEndPos;

	int nLinkNum;

};

#endif // !defined(AFX_LINK_H__E126D3A4_BAD4_4BC8_8451_D3A9A21A97B4__INCLUDED_)
