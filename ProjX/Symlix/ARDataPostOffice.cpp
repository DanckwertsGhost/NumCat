// ARDataPostOffice.cpp: implementation of the CARDataPostOffice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ARDataPostOffice.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CARDataPostOffice* CARDataPostOffice::m_instance = NULL;


CARDataPostOffice::CARDataPostOffice()
{

}

CARDataPostOffice::~CARDataPostOffice()
{

}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::instance
// Description	    : Return a pointer to the instance, calling the consructor if necessary
// Return type		: CARDataPostOffice* 
///////////////////////////////////////////////////////////
CARDataPostOffice* CARDataPostOffice::instance()
{
  if (!m_instance)
		m_instance = makeInstance();

  return m_instance;
}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::cleanUpInstance
// Description	    : Called as component exits
// Return type		: void 
///////////////////////////////////////////////////////////
void CARDataPostOffice::cleanUpInstance()
{
  delete m_instance;
#ifndef NDEBUG
  delete m_instance; // to test my understanding is right here that delete NULL is acceptable
#endif
  m_instance = NULL; // just to be sure

}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::makeInstance
// Description	    : Helper function - call constructor
// Return type		: CARDataPostOffice* 
///////////////////////////////////////////////////////////
CARDataPostOffice* CARDataPostOffice::makeInstance()
{
    atexit(&cleanUpInstance);
    return (newtrack CARDataPostOffice());
}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::AddItem
// Description	    : Add item to storage with two keys
// Return type		: bool 
// Argument         : const char *sFirstKey
// Argument         : const char *sSecondKey
// Argument         : double vValue
///////////////////////////////////////////////////////////
bool CARDataPostOffice::AddItem(const char *sFirstKey, const char *sSecondKey, double vValue)
{
	CARDPKey key(sFirstKey,sSecondKey);

	if (find(key))
		return false; // don't overwrite - maybe I should ?

	m_mapValues[key] = vValue;

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::findItem
// Description	    : Is item available in storage ?
// Return type		: bool 
// Argument         : const char *sFirstKey
// Argument         : const char *sSecondKey
///////////////////////////////////////////////////////////
bool CARDataPostOffice::findItem(const char *sFirstKey, const char *sSecondKey)
{
	CARDPKey key(sFirstKey,sSecondKey);

	return find(key);
}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::retrieveItem
// Description	    : Item is deleted in storage after being returned
// Return type		: bool 
// Argument         : const char *sFirstKey
// Argument         : const char *sSecondKey
// Argument         : double &vValue
///////////////////////////////////////////////////////////
bool CARDataPostOffice::retrieveItem(const char *sFirstKey, const char *sSecondKey, double &vValue)
{
	CARDPKey key(sFirstKey,sSecondKey);

	if (!find(key))
		{
		vValue = NOT_FOUND;
		return false;
		}

	vValue = m_mapValues[key];
	m_mapValues.erase(key);
	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::find
// Description	    : helper function to locate a value item
// Return type		: bool 
// Argument         : const CARDPKey cardpk
///////////////////////////////////////////////////////////
bool CARDataPostOffice::find(const CARDPKey cardpk)
{
	mapkey::const_iterator it = m_mapValues.find(cardpk);

	if (it==m_mapValues.end())
		return false; // as a value is already there
	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::findText
// Description	    : helper function to locate a text item
// Return type		: bool 
// Argument         : const CARDPKey cardpk
///////////////////////////////////////////////////////////
bool CARDataPostOffice::findText(const CARDPKey cardpk)
{
	maptext::const_iterator it = m_mapTexts.find(cardpk);

	if (it==m_mapTexts.end())
		return false; // as a value is already there
	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::AddTextItem
// Description	    : Add a string with two keys
// Return type		: bool 
// Argument         : const char *sFirstKey
// Argument         : const char *sSecondKey
// Argument         : const string& sValue
///////////////////////////////////////////////////////////
bool CARDataPostOffice::AddTextItem(const char *sFirstKey, const char *sSecondKey, const string& sValue)
{
	CARDPKey key(sFirstKey,sSecondKey);

	if (findText(key))
		return false; // don't overwrite - maybe I should ?

	m_mapTexts[key] = sValue;

	return true;
}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::findTextItem
// Description	    : Do the two keys correspond to a stored value ?
// Return type		: bool 
// Argument         : const char *sFirstKey
// Argument         : const char *sSecondKey
///////////////////////////////////////////////////////////
bool CARDataPostOffice::findTextItem(const char *sFirstKey, const char *sSecondKey)
{
	CARDPKey key(sFirstKey,sSecondKey);

	return findText(key);
}


///////////////////////////////////////////////////////////
// Function name	: CARDataPostOffice::retrieveTextItem
// Description	    : Item is deleted in storage after being returned
// Return type		: bool 
// Argument         : const char *sFirstKey
// Argument         : const char *sSecondKey
// Argument         : strong &sValue
///////////////////////////////////////////////////////////
bool CARDataPostOffice::retrieveTextItem(const char *sFirstKey, const char *sSecondKey, string &sValue)
{
	CARDPKey key(sFirstKey,sSecondKey);

	if (!findText(key))
		{
		sValue = "";
		return false;
		}

	sValue = m_mapTexts[key];
	m_mapTexts.erase(key);
	return true;
}
