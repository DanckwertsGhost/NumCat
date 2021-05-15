// ArrayImplied.cpp: implementation of the CArrayImplied class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArrayImplied.h"
#include <algorithm>
#include "Symlix\ErrorFactory.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArrayImplied::CArrayImplied(CToken* pt):CArray()
{
	ASSERT2(m_pToken==NULL);
	m_pToken = pt;
	ASSERT2(m_pToken);
	if (!m_pToken)
		m_eState = carError;

	// lets make the token an array
	m_eTATOrig = m_pToken->getArrayType(); // in case needs to be restored when destroyed
	m_pToken->setAsArray();
}

CArrayImplied::CArrayImplied(const CArray& ra, CToken* pt):CArray()
{
	copy(ra);
	m_pToken = pt;
	ASSERT2(m_pToken);
	if (!m_pToken)
		m_eState = carError;

	// lets make the token an array
	m_eTATOrig = m_pToken->getArrayType(); // in case needs to be restored when destroyed
	m_pToken->setAsArray();
}


CArrayImplied::~CArrayImplied()
{
	ASSERT2(m_pToken);
	try // since this had inherent risks
	{
	if (m_pToken) // perhaps its the end of the world
		m_pToken->setArrayType(m_eTATOrig); // since this object can be volatile and need to restore
	}
	catch(...)
	{
	}
}


bool CArrayImplied::CatArray(CArray* pa)
{

	ASSERT2(pa);
	if (!pa)
		return false;

	ASSERT2(m_pToken);
	if (!m_pToken)
		{
		m_eState = carError;
		return false;
		}

	// is this array in a good state ?

	if (!pa->IsReady())
			return false;

	// if this array hasn't already been indialised then copy the indicies
	if (!this->IsReady())
		{
		m_vecIndicies.clear();
		m_vecIndicies = pa->getIndicies();
		}
		else
		{
		vector<long> vecIntersec(m_vecIndicies.size());
		vector<long>::iterator itv;
		const vector<long>& rpaIndicies = pa->getIndicies();
		itv = set_intersection(m_vecIndicies.begin(),m_vecIndicies.end(),rpaIndicies.begin(),rpaIndicies.end(),vecIntersec.begin());
		vecIntersec.erase(itv,vecIntersec.end());
		m_vecIndicies = vecIntersec;
		}

	if (m_vecIndicies.size()==0)
		{
		SYMERRORTOK("The array size implied here has zero size ",errWarning,m_pToken);
		}

	m_eState = carIntiated;

 return true;
 
}

void CArrayImplied::out( ostream& os ) const
{
	int iCount=0;
	vector<long>::const_iterator cind;
	if (!m_pToken)
		{
		os << "[CArrayImplied] Token Error"<<endl;
		return;
		}
	os << "[CArrayImplied] Token '"<<m_pToken->getString().c_str()<<"'";
	os << " Array size "<<m_vecIndicies.size()<<"\n";

	cind=m_vecIndicies.begin();

	while(cind!=m_vecIndicies.end())
	{
		if (iCount<ARRAY_LINE_COUNT)
			{
			os <<"["<<*cind<<"] "<<"\t";
			iCount++;
			}
			else
			{
			os <<"["<<*cind<<"] "<<"\n";
			iCount=0;
			}
	cind++;
	}
	if (iCount!=0)
		os<<"\n";

}