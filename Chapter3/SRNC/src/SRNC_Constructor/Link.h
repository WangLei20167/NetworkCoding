// Link.h: interface for the CLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINK_H__99EB8515_DB5C_44C9_9EF6_680A4DAFBD8D__INCLUDED_)
#define AFX_LINK_H__99EB8515_DB5C_44C9_9EF6_680A4DAFBD8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLink  
{
public:
	CLink();
	virtual ~CLink();

	// used to import topology.
	CPoint posStartPos;
	CPoint posEndPos;
	int nLinkNum;
	
	bool bSel;
	bool bInSubGraph;
	
	int nPreLink[10];
	int nInputLink;
	int GCV[20];
	int LCV[20];

	UINT nStartAt;
	UINT nEndAt;

	int nShared;
	bool bAssigned;

	bool bAddToRouteTable;	// only used when obtaining multipath for the sink node.

};

#endif // !defined(AFX_LINK_H__99EB8515_DB5C_44C9_9EF6_680A4DAFBD8D__INCLUDED_)
