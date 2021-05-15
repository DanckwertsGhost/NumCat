// ARDRM.h: interface for the CARDRM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARDRM_H__77748DD3_8FAF_4FFA_B56D_997C00C4CDBB__INCLUDED_)
#define AFX_ARDRM_H__77748DD3_8FAF_4FFA_B56D_997C00C4CDBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>


#ifndef NDEBUG // lets do this for debug only

#define DEBUGDRM

#endif

#ifdef DEBUGDRM
#include <fstream>

#define DRMTRACE(description) { m_os << description << endl; }
#define DRMTRACE1(description,bValue) { m_os << description << " m_bState = " << m_bState << endl; }
#define DRMTRACE2(description,fValue) { m_os << description << " = " << fValue <<endl; }
#define DRMTRACE3(descript1,descript2) { m_os << descript1 << " " << descript2 << endl; }

#else

#define DRMTRACE(description) {  }
#define DRMTRACE1(description,bValue) {  }
#define DRMTRACE2(description,fValue) {  }
#define DRMTRACE3(descript1,descript2) {  }

#endif


class CARDRM  
{
private:
	CARDRM();
	~CARDRM();

	static CARDRM* makeInstance(); 
	static void cleanupInstance();


	static CARDRM* m_instance;
public:
    static CARDRM* instance();

	string getUser() const { return m_sUser; }
	string getKey() const { return m_sKey; }
	bool getExpired() {
							DRMTRACE3("call to getExpired() returns ", int(m_bExpired) );
							return m_bExpired;
							}
	bool getVerified() {
							DRMTRACE3("call to getVerified() returns ", int(m_bVerified) );
							return m_bVerified;
							}
	long getDaysLeft() const { return m_iDaysLeft; }
	long getTotalUses() const { return m_iTotalUses; }
	bool hasErrors() const { return !m_bState; }
	string getFingerPrint() const { return m_sFingerPrint; }
	string getEnhancedFingerPrint() const { return m_sEnhancedFingerPrint; }
	void callBuyNowURL(HWND parent = NULL) const;
	bool installCode(const char *sName, const char *sCodestring);
	void showEnterKeyDialog(HWND parent) const;
	bool updateEnvironment();
	string getEnvironmentValue(const char* sEnvKey) const;

private:
	bool verifyKey( const char* sUser, const char* sKey );
	bool verifyStoredKey();
	virtual bool setArmadilloPath();
	bool m_bDaysLeft;
	string m_sKey;
	string m_sUser;
	long m_iDaysLeft;
	long m_iTotalUses;
	bool m_bExpired;
	bool m_bVerified;

	bool m_bState;
	string m_sFingerPrint;
	string m_sEnhancedFingerPrint;
	string m_sDLLLocation;

#ifdef DEBUGDRM
	ofstream m_os;
#endif


};

#endif // !defined(AFX_ARDRM_H__77748DD3_8FAF_4FFA_B56D_997C00C4CDBB__INCLUDED_)
