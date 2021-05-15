// ARDataPostOffice.h: interface for the CARDataPostOffice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARDATAPOSTOFFICE_H__1EB9E20B_32A1_41D1_A9A7_867AF152A63C__INCLUDED_)
#define AFX_ARDATAPOSTOFFICE_H__1EB9E20B_32A1_41D1_A9A7_867AF152A63C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "ARDPKey.h"
#include <map>
#include <string>

using namespace std;

#define mapkey map<CARDPKey,double,ltkey>
#define maptext map<CARDPKey,string,ltkey>

class CARDataPostOffice  
{

private:

struct ltkey
{
  bool operator()(const CARDPKey& s1, const CARDPKey& s2) const
  {
    return (s1<s2);
  }
};


public:
	bool retrieveItem(const char* sFirstKey, const char* sSecondKey, double& vValue);
	bool findItem(const char* sFirstKey, const char* sSecondKey);
	bool AddItem( const char* sFirstKey, const char* sSecondKey, double vValue);

	bool retrieveTextItem(const char* sFirstKey, const char* sSecondKey, string& sValue);
	bool findTextItem(const char* sFirstKey, const char* sSecondKey);
	bool AddTextItem( const char* sFirstKey, const char* sSecondKey, const string& sValue);

	
	static CARDataPostOffice* instance();
	static void forceKill(){ cleanUpInstance(); }

private:
	bool find(const CARDPKey cardpk );
	bool findText(const CARDPKey cardpk );
	static CARDataPostOffice* makeInstance();
	CARDataPostOffice();
	~CARDataPostOffice();

	static  void cleanUpInstance();

    static  CARDataPostOffice* m_instance;

	mapkey m_mapValues;
	maptext m_mapTexts;

};


// CARDDataPostOfficeLifeManager
// to control lifetime of CARDataPostOffice singleton,
// regardless of exit path chosen (including errors being thrown.
class CARDDataPostOfficeLifeManager
{
public:
	CARDDataPostOfficeLifeManager(){ CARDataPostOffice::instance(); }
	~CARDDataPostOfficeLifeManager(){ CARDataPostOffice::forceKill(); }
};

#endif // !defined(AFX_ARDATAPOSTOFFICE_H__1EB9E20B_32A1_41D1_A9A7_867AF152A63C__INCLUDED_)
