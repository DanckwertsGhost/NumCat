// ARDPKey.h: interface for the CARDPKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARDPKEY_H__236448D5_6F72_44BB_83BD_ED023493EA11__INCLUDED_)
#define AFX_ARDPKEY_H__236448D5_6F72_44BB_83BD_ED023493EA11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

#include <string>

class CARDPKey  
{
public:
	CARDPKey( const char* sFirstKey, const char* sSecondKey );
	CARDPKey(const CARDPKey& cardpk){ copy(cardpk); }
	virtual ~CARDPKey();
	virtual bool operator < (const CARDPKey& cardpk ) const;
	virtual bool operator > (const CARDPKey& cardpk ) const{ return cardpk < (*this); }
protected:
	virtual void copy(const CARDPKey& cardpk);
	string m_sFirstKey;
	string m_sSecondKey;
	long m_iLenFK;		// used to speed up comparisons
	char m_c2ndLast;	// used to speed up comparisons
	char m_cLast;		// used to speed up comparisons

};

#endif // !defined(AFX_ARDPKEY_H__236448D5_6F72_44BB_83BD_ED023493EA11__INCLUDED_)
