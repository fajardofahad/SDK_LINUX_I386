// PtrArray.cpp: implementation of the CPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#include "PtrArray.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPtrArray::CPtrArray()
{
	m_varray.clear();
}

CPtrArray::~CPtrArray()
{
	m_varray.clear();
}

int CPtrArray::Add(void* newElement )
{
	m_varray.push_back(newElement);
	return m_varray.size()-1;
}

int CPtrArray::GetSize()
{
	return m_varray.size();
}

void CPtrArray::RemoveAll()
{
	m_varray.clear();
}

void* CPtrArray::GetAt(int nIndex )
{
	return m_varray.at(nIndex);
}

void CPtrArray::InsertAt(int nIndex, void* newElement)
{
	m_varray.insert(m_varray.begin()+nIndex, newElement);
}

void CPtrArray::RemoveAt(int nIndex)
{
	m_varray.erase(m_varray.begin()+nIndex);
}

void CPtrArray::SetSize(int nNewSize)
{
	m_varray.resize(nNewSize);
}

void CPtrArray::SetAt(int nIndex, void* newElement)
{
	m_varray[nIndex] = newElement;
}

