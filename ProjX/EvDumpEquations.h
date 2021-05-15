// EvDumpEquations.h: interface for the CEvDumpEquations class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVDUMPEQUATIONS_H__3E385CA5_7B50_488C_8E66_9E6FAEAF5906__INCLUDED_)
#define AFX_EVDUMPEQUATIONS_H__3E385CA5_7B50_488C_8E66_9E6FAEAF5906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"
#include "Equation.h"
#include <fstream>

class CEvDumpEquations : public CEventImpl, public CNavTokens  
{
public:
	CEvDumpEquations( long iLeft, long iRight, vector< CToken* >& vecLine,ostream& oserr,ListLineTokenPts& rvecEqVecs);
	virtual ~CEvDumpEquations();
	virtual bool setupEvent(list<CEquation*>* pvecpEquations); // no action required
	virtual bool isOfType(eEventType eet) const{ return eet==ceetNoValueChange; }

	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );


};

#endif // !defined(AFX_EVDUMPEQUATIONS_H__3E385CA5_7B50_488C_8E66_9E6FAEAF5906__INCLUDED_)
