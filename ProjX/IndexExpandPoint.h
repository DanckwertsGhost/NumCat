// IndexExpandPoint.h: interface for the CIndexExpandPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INDEXEXPANDPOINT_H__2009524A_09D6_404C_847E_343065CECEA7__INCLUDED_)
#define AFX_INDEXEXPANDPOINT_H__2009524A_09D6_404C_847E_343065CECEA7__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "Token.h"
#include <ostream>
#include <list>
#include "global.h"
#include "equation.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;


class CIndexExpandPoint : public CNavTokens 
{
public:
	CIndexExpandPoint( long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport=cerr );
	virtual ~CIndexExpandPoint();

	inline bool isReady() const{ return m_pTokenExpandPoint!=NULL; }
	inline CToken* getLocationTokenPt() const{ return m_pTokenExpandPoint; }

	inline long addOffset(){ return ++m_iOffsetLines; }

	static bool check(long iLeft,long iRight,vector<CToken*>& vExpLine, ostream& osErrReport);

	bool lessThan(const CToken& rct) const { return (*this)<rct; }

	bool operator < (const CToken& rct ) const;
	bool operator > (const CToken& rct ) const;

private:
	CToken* m_pTokenExpandPoint;
	long m_iOffsetLines;
};

#endif // !defined(AFX_INDEXEXPANDPOINT_H__2009524A_09D6_404C_847E_343065CECEA7__INCLUDED_)
