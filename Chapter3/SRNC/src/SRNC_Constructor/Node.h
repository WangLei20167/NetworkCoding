// Node.h: interface for the CNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_H__C3D2CE89_5F0A_4293_A9E8_9234ACA9ABAB__INCLUDED_)
#define AFX_NODE_H__C3D2CE89_5F0A_4293_A9E8_9234ACA9ABAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNode  
{
public:
	int nOriginalMaxflow;
	
	CNode();
	virtual ~CNode();
	int nI;
	UINT nXPos;
	UINT nYPos;

	COLORREF Color;
	CString strType;
	UINT nNodeID;
	UINT nMaxflow;
	bool bDecodable;
	int nRoutes[30][30];

	UINT **nRM;

};

#endif // !defined(AFX_NODE_H__C3D2CE89_5F0A_4293_A9E8_9234ACA9ABAB__INCLUDED_)
