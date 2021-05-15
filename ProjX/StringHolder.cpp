// StringHolder.cpp: implementation of the CStringHolder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringHolder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringHolder::CStringHolder():m_string()
{
	Init();
}

CStringHolder::CStringHolder(const CStringHolder& csh):m_string()
{
	Copy(csh);
}

CStringHolder::CStringHolder(const string& str):m_string()
{
	Init();
	m_string = str;
}

CStringHolder::CStringHolder(const char* sIn):m_string()
{
	Init();
	if ((sIn!=NULL)&&(strlen(sIn)>0))
				m_string = sIn;
}

CStringHolder::~CStringHolder()
{

}

void CStringHolder::Copy(const CStringHolder &csh)
{
	m_string = csh.m_string;
}

const char* CStringHolder::c_str() const
{
	return m_string.c_str();
}

void CStringHolder::Init()
{

}

bool CStringHolder::operator <(const CStringHolder& csh) const
{
	// need to ensure that short string are less than long ones -regardless
	
	if (this->len()<csh.len())
					return true;
	if (this->len()==csh.len())
					return m_string.compare(csh.m_string)<0;	
	return false;
}

bool CStringHolder::operator ==( const CStringHolder& csh) const
{
	bool bResult = m_string.compare(csh.m_string)==0;
	return bResult;
}

ostream& operator << ( ostream& os, const CStringHolder& csh) 
{
	os << csh.c_str();
	return os;
}