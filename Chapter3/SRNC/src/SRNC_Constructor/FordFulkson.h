// FordFulkson.h: interface for the CFordFulkson class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORDFULKSON_H__43D18C23_8D8D_4F0A_A84A_809ADBC2412A__INCLUDED_)
#define AFX_FORDFULKSON_H__43D18C23_8D8D_4F0A_A84A_809ADBC2412A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFordFulkson  
{
public:
	CFordFulkson();
	virtual ~CFordFulkson();

public:
	int nDes;
	int nSrc;
	bool Edmonds_Karp();
	int RunFF();
	void Initialize();

	CObList *pLinkList;
	
	UINT nNodeNum;
	INT **C;
	BOOL *Visit;
	int *PreNode;
	int	*Queue;
	int Route[20][20];

};

#endif // !defined(AFX_FORDFULKSON_H__43D18C23_8D8D_4F0A_A84A_809ADBC2412A__INCLUDED_)
