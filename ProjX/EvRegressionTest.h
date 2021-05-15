// EvRegressionTest.h: interface for the CEvRegressionTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVREGRESSIONTEST_H__14CD0403_CA1E_493F_8368_B8F1F753D860__INCLUDED_)
#define AFX_EVREGRESSIONTEST_H__14CD0403_CA1E_493F_8368_B8F1F753D860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <fstream>

#include "EvRecorder.h"

class CEvRegressionTest : public CEvRecorder
{ 
public:
	CEvRegressionTest( long iLeft, long iRight, vector< CToken* >& vecLine,ostream& oserr);
	virtual ~CEvRegressionTest();
	static bool check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport=cerr );
	virtual bool isActive(){ return false; }
	virtual eEventType giveEventType() const{ return ceetNoValueChange; }
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast  );
	virtual bool willTrigger( vector< variable >* pvecVars );
	virtual void finalRelease(){} // as inherit from CEvRecorder which uses this
protected:
	virtual bool AreClose( float v1, float v2);
	vector<variable> m_vecCheckVal;
	bool m_bFired;
	std::ofstream m_ofs;
};

#endif // !defined(AFX_EVREGRESSIONTEST_H__14CD0403_CA1E_493F_8368_B8F1F753D860__INCLUDED_)
