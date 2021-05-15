// TempSetFix.h: interface for the CTempSetFix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEMPSETFIX_H__4D17A11C_A033_41CD_B981_EDEE087D93FD__INCLUDED_)
#define AFX_TEMPSETFIX_H__4D17A11C_A033_41CD_B981_EDEE087D93FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Token.h"
// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

// Tempory class to cover VC6 bug on nested STL containers .. therefore need 
// to implement set as a specialist class. Should be able to remove this
// when step up to latter compiler.
class CTempSetFix  
{
public:
	CTempSetFix();
	virtual ~CTempSetFix();
	setofwords::const_iterator insert(setofwords::const_iterator& cit );
	bool find(const setofwords::const_iterator& cit) const;

	friend ostream& operator << (ostream& os, const CTempSetFix& ctsf );

private:
	void add(setofwords::const_iterator& cit);

	setofwords::const_iterator* m_ppSetWords;
	long m_iLength;
	long m_iStep;

};

#endif // !defined(AFX_TEMPSETFIX_H__4D17A11C_A033_41CD_B981_EDEE087D93FD__INCLUDED_)
