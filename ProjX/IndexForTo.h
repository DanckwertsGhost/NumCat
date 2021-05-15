// IndexForTo.h: interface for the CIndexForTo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INDEXFORTO_H__75F1FA1E_F9B5_4B2D_B306_99DAF3F5CF6E__INCLUDED_)
#define AFX_INDEXFORTO_H__75F1FA1E_F9B5_4B2D_B306_99DAF3F5CF6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Index.h"
#include "Equation.h"

class CIndexForTo : public CIndex, public CNavTokens   
{
public:
	CIndexForTo(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport=cerr);
	virtual ~CIndexForTo();

	static bool check(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport);

	#ifndef NDEBUG
	static bool unitTests();
	#endif

#ifdef NDEBUG
	virtual long getValue() const { return m_iCurrent; }
#else
	virtual long getValue() const;
#endif
	virtual bool first(){ m_iCurrent = m_iFrom; return IsReady(); }
	virtual bool last(){ m_iCurrent=m_iTo; return IsReady();}
#ifdef NDEBUG
	virtual bool next(){ m_iCurrent += m_iStep; return (m_bNeg?(m_iCurrent>=m_iTo):(m_iCurrent<=m_iTo));}
	virtual bool previous(){ m_iCurrent -= m_iStep; return (m_bNeg?(m_iCurrent<=m_iFrom):(m_iCurrent>=m_iFrom));}
#else
	virtual bool next();
	virtual bool previous();
#endif
	virtual long size(){ return abs((m_iTo-m_iFrom)/m_iStep);}



protected:
	bool m_bNeg;
	long m_iFrom;
	long m_iTo;
	long m_iStep;
	long m_iCurrent;
};

#endif // !defined(AFX_INDEXFORTO_H__75F1FA1E_F9B5_4B2D_B306_99DAF3F5CF6E__INCLUDED_)
