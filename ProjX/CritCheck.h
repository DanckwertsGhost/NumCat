// CritCheck.h: interface for the CCritCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRITCHECK_H__15EE979C_7542_4003_987E_4CC642A11F96__INCLUDED_)
#define AFX_CRITCHECK_H__15EE979C_7542_4003_987E_4CC642A11F96__INCLUDED_

#include "stdafx.h"
#include <process.h>
#include <windows.h>
//#include <atlbase.h>

#ifndef NDEBUG
#include <map>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCritCheck
 {
  public:
	CCritCheck(CRITICAL_SECTION& csGiven):m_cs(csGiven)
	{
#ifndef NDEBUG
		map<CRITICAL_SECTION*,long>::iterator it;
		if (!m_pgmapCount)
			{
			m_pgmapCount = newtrack map<CRITICAL_SECTION*,long>;
			atexit(&CleanUp);
			}
		it = m_pgmapCount->find(&csGiven);
		if (it==m_pgmapCount->end())
			(*m_pgmapCount)[&csGiven] = 1;
			else
			it->second += 1;
		it = m_pgmapCount->find(&csGiven);
		ATLTRACE("About to start CS %d with count %d\n",&csGiven,it->second);
#endif
		EnterCriticalSection( &m_cs );
	}
	~CCritCheck()
	{
		LeaveCriticalSection( &m_cs );
#ifndef NDEBUG
		map<CRITICAL_SECTION*,long>::iterator it;
		it = m_pgmapCount->find(&m_cs);
		if (it==m_pgmapCount->end())
			ATLTRACE("Error tracking Criticalm sections %s %s\n",__FILE__,__LINE__);
			else
			{
			it->second -= 1;
			ATLTRACE("Exit Critical section %d count %d\n",&m_cs,it->second);
			}
#endif
	}
  private:
	CRITICAL_SECTION& m_cs;

#ifndef NDEBUG
	static void CleanUp(){ delete m_pgmapCount; }
    static map<CRITICAL_SECTION*,long>* m_pgmapCount;
#endif
 }; 



#endif // !defined(AFX_CRITCHECK_H__15EE979C_7542_4003_987E_4CC642A11F96__INCLUDED_)
