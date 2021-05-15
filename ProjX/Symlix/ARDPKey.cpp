// ARDPKey.cpp: implementation of the CARDPKey class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ARDPKey.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CARDPKey::CARDPKey( const char* sFirstKey, const char* sSecondKey ):m_sFirstKey(sFirstKey),m_sSecondKey(sSecondKey)
{
	m_iLenFK = m_sFirstKey.length();
	m_c2ndLast = sFirstKey[m_iLenFK-2];
	m_cLast = sFirstKey[m_iLenFK-1];
}

CARDPKey::~CARDPKey()
{

}

void CARDPKey::copy( const CARDPKey& cardpk )
{

	m_sFirstKey = cardpk.m_sFirstKey;
	m_sSecondKey = cardpk.m_sSecondKey;
	m_iLenFK = cardpk.m_iLenFK;
	m_cLast = cardpk.m_cLast;
	m_c2ndLast = cardpk.m_c2ndLast;

}

bool CARDPKey::operator < (const CARDPKey& cardpk ) const
{
	if (m_iLenFK<cardpk.m_iLenFK)
		return true;

	if (m_cLast<cardpk.m_cLast)
		return true;

	if (m_c2ndLast<cardpk.m_c2ndLast)
		return true;

	if (m_sFirstKey.compare(cardpk.m_sFirstKey)<0)
		return true;

	if (m_sSecondKey.compare(cardpk.m_sSecondKey)<0)
		return true;

	return false;
}

