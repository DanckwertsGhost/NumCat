// Index.h: interface for the CIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INDEX_H__838403AF_78B9_4FC7_8255_D6EFED6C7E7A__INCLUDED_)
#define AFX_INDEX_H__838403AF_78B9_4FC7_8255_D6EFED6C7E7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "Token.h"
#include <ostream>
#include <list>
#include "global.h"
#include "IndexExpandPoint.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

enum eIndexState{cindUninitated,cindError,cindIntiated};


class CIndex  
{
public:
	CIndex();
	virtual ~CIndex();

	virtual long getValue() const=0;
	virtual bool first()=0;
	virtual bool next()=0;
	virtual bool last()=0;
	virtual bool previous()=0;
	virtual long size()=0;

	virtual bool IsInError() const{ return (m_eState==cindError); }
	virtual bool IsReady() const{ return (m_eState==cindIntiated); }
	virtual string getIndexName() const { return m_sIndex; }
	virtual string getValueString() { return _ltoa(getValue(),m_sBuff,10);}
	virtual bool operator < (const CIndex* cI) const {return cI != NULL ? cI->m_sIndex.compare(m_sIndex)>0: false; }
	virtual bool operator < (const string sTest) const {return (sTest.compare(m_sIndex)>0); }
	virtual bool operator > (const CIndex* cI) const {return cI != NULL ? cI->m_sIndex.compare(m_sIndex)<0: false; }
	virtual bool operator > (const string sTest) const {return (sTest.compare(m_sIndex)<0); }
	virtual bool operator == (const CIndex* cI) const {return cI != NULL ? cI->m_sIndex.compare(m_sIndex)==0: false; }
	virtual bool operator == (const string sTest) const {return (sTest.compare(m_sIndex)==0); }
	virtual void setPointInEqList(ListLineTokenPts::iterator& rit){m_itFirstUseIndex=rit; m_bHaveFirstUse=true;}
	virtual bool getPointInEqList(ListLineTokenPts::iterator& rit){rit=m_itFirstUseIndex;return m_bHaveFirstUse; }
	virtual void setExpansionPoint( CIndexExpandPoint* pExpand ){ m_pExpand = pExpand; }
	virtual bool hasExpansionPoint() const { return (m_pExpand!=NULL); }
	virtual CIndexExpandPoint* getExpansionPoint() const { return m_pExpand;}

	static long checkForExpression(vector< CToken* >::iterator& ritpCT, vector< CToken* >::const_iterator citEnd);

	friend ostream& operator << (ostream& os,  const CIndex* pI);
	friend ostream& operator << (ostream& os,  const CIndex& rI){ os << &rI; return os; }


protected:
//	virtual void copy( const CIndex& rci );
	virtual void out( ostream& os ) const { os << " CIndex type undefined\n"; }

	eIndexState m_eState;
	string m_sError;
	bool bIndiciesSet;
	string m_sIndex;
	bool m_bHaveFirstUse;
	ListLineTokenPts::iterator m_itFirstUseIndex;
	CIndexExpandPoint* m_pExpand;
private:
	char m_sBuff[32];

};

#endif // !defined(AFX_INDEX_H__838403AF_78B9_4FC7_8255_D6EFED6C7E7A__INCLUDED_)
