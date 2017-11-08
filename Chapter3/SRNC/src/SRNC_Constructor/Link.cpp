// Link.cpp: implementation of the CLink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SRNC_Constructor.h"
#include "Link.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLink::CLink()
{
	nLinkNum = 0;
	
	nShared = 0;
	nStartAt = 0;
	nEndAt = 0;
	bAssigned = false;
	bInSubGraph = false;
	bSel = false;


	for (int i=0; i<10; i++)
	{
		nPreLink[i] = -1;
	}
	for (i=0; i<20; i++)
	{
		GCV[i] = -1;
		LCV[i] = -1;
	}
	nInputLink = 0;

	bAddToRouteTable = false;
}

CLink::~CLink()
{

}
