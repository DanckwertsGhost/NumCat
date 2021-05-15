// EvProgFeedback.h: interface for the CEvProgFeedback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVPROGFEEDBACK_H__39F520AF_7E20_4DA6_866D_3D46E165D3FD__INCLUDED_)
#define AFX_EVPROGFEEDBACK_H__39F520AF_7E20_4DA6_866D_3D46E165D3FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"
#include <sys/types.h>
#include <sys/timeb.h>
#include <time.h>
#include <vector>
#include "Symlix/Symlix.h"

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

class CEvProgFeedback : public CEventImpl  
{
public:
	CEvProgFeedback(vector<long>& vecInds,INumCatHostCallBack* pINumCatHostCallBack);
	virtual ~CEvProgFeedback();

// from CEventImpl
//	virtual bool willTriggerOverTime( const variable& vValue, const variable& vValueStep, const string& sTrig = g_Time);
	virtual eEventSignal trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast  );
//	virtual bool willTrigger( vector< variable >* pvecVars );
	virtual bool isActive(){ return false; } 
//	virtual bool isInError() const{	return m_eState==cevError;}
//	virtual bool isReady() const;
//	virtual bool isCorrect() const{	return m_eState!=cevError;}
	virtual bool isOfType(eEventType eet) const{ return eet==ceetNoValueChange;}
	virtual eEventType giveEventType() const{ return ceetNoValueChange;}
//	virtual CToken* canChange(){ return NULL;}
//	virtual bool setupEvent(list<CEquation*>* pvecpEquations); // no action required
	virtual void reset();

//	virtual bool hasAPeriodUpperLimit(){return true;};
//	virtual variable getPeriodUpperLimit(){return m_vStep;};
	virtual void simulationEnd();
	virtual void finalRelease(); // tidy up any COM dependent stuff as COM service is closing before object destroyed

// end from CEventImpl

protected:
	INumCatHostCallBack* m_pINumCatHostCallBack;
	struct _timeb m_tLast;
	struct _timeb m_tNow;
	vector< long > m_vecInds;
	bool m_bFireInds;
	SAFEARRAY* m_psaVals;
	SAFEARRAY* m_psaInds;
private:
	vector< long >::const_iterator m_cit; // to optimise speed
	VARIANT_BOOL m_vb;
	long m_iStart;
	long m_iEnd;
	UINT m_iElems;
	bool m_bReleased;


};

#endif // !defined(AFX_EVPROGFEEDBACK_H__39F520AF_7E20_4DA6_866D_3D46E165D3FD__INCLUDED_)
