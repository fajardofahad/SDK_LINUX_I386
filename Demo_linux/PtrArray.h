// PtrArray.h: interface for the CPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PtrArray_H__2BE7C544_112E_4266_B787_77951C70E615__INCLUDED_)
#define AFX_PtrArray_H__2BE7C544_112E_4266_B787_77951C70E615__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#pragma warning( disable : 4786 )
#include <vector>

using namespace std;

class CPtrArray  
{
public:
	CPtrArray();
	virtual ~CPtrArray();

public:
	int Add( void* newElement );
	int GetSize();
	void RemoveAll();
	void* GetAt( int nIndex );
	void InsertAt( int nIndex, void* newElement);
	void RemoveAt( int nIndex);
	void SetSize(int nNewSize);
	void SetAt(int nIndex, void* newElement);
private:
	vector<void*> m_varray;
};

#endif // !defined(AFX_PtrArray_H__2BE7C544_112E_4266_B787_77951C70E615__INCLUDED_)
