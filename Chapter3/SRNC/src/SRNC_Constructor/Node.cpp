// Node.cpp: implementation of the CNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SRNC_Constructor.h"
#include "Node.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNode::CNode()
{
	bDecodable = FALSE;
	nXPos = 0;
	nYPos = 0;
	Color = RGB(0, 0, 255);
	nNodeID = 0;
	nMaxflow = 0;
	nOriginalMaxflow = 0;

	for (int i=0; i<30; i++)
	{
		for (int j=0; j<30; j++)
		{
			nRoutes[i][j] = -1;
		}
	}

	nI = -1;
}

CNode::~CNode()
{

}
