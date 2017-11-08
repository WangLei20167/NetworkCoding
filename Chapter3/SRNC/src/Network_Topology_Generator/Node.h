// Node.h: interface for the CNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_H__CEB98D54_AC86_4C69_B160_92651CE2D4B5__INCLUDED_)
#define AFX_NODE_H__CEB98D54_AC86_4C69_B160_92651CE2D4B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNode  
{
public:
	CNode();
	virtual ~CNode();


	UINT nXPos;
	UINT nYPos;
	COLORREF Color;
	CString strType;
	UINT nNodeID;

};

#endif // !defined(AFX_NODE_H__CEB98D54_AC86_4C69_B160_92651CE2D4B5__INCLUDED_)
