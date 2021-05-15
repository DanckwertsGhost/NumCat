// csvLookup.h: interface for the CcsvLookup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSVLOOKUP_H__E5784616_E284_4968_803C_A2E13327D643__INCLUDED_)
#define AFX_CSVLOOKUP_H__E5784616_E284_4968_803C_A2E13327D643__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cell.h"
#include "csvHolder.h"
#include <ostream>
#include "csvNumArray.h"

#ifndef _AREXCELFUNC
#include "SymlixStore.h" // otherwise via import
#endif

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;
_CSV_HANDLER_BEGIN

class CcsvLookup : public CcsvHolder  
{
public:
	CcsvLookup(const char* sFileName);
	CcsvLookup(IARStream* pIStream);
	virtual ~CcsvLookup();

	static bool checkFile( const char* sFile );
	static long getLowCacheNum(){ return CSVHOLDER_DEFAULT_CACHE_LEVEL; } // used to set cache values - to be implmented latter
	static long getHighCacheNum(){ return CSVHOLDER_DEFAULT_CACHE_LEVEL; } // as getLowCacheNum

	// CcsvLookup methods
	virtual bool lookup( const vector< long >& vRefInd, const long& lookup, const vector< csvVariable >& vValueLookup, vectorcsvVariableRow** vppPoint1,  vectorcsvVariableRow** vppPoint2 );
	virtual bool lookupTopRow( const vector< string >& vRefInd, const string& sLookup, const vector< csvVariable >& vValueLookup, vectorcsvVariableRow** vppPoint1,  vectorcsvVariableRow** vppPoint2 );

	virtual csvVariable interpolate( const vector< long >& vRefInd, const long& lookup, const vector< csvVariable >& vValueLookup );
	virtual csvVariable interpolate( const vector< string >& vRefInd, const string& sLookup, const vector< csvVariable >& vValueLookup );
	virtual csvVariable interpolate( const string& sRefInd, const string& sLookup, const csvVariable& rcsvValueLookup );
 
	virtual long setCache( const long iCacheValue );
	virtual long getCacheLevel() const {return m_iCacheNumber; }

	friend ostream& operator << ( ostream& os, const CcsvLookup& lup ){ return lup.writeToStream(os); }
	friend ostream& operator << ( ostream& os, CcsvLookup* plup ){ return plup->writeToStream(os); }

/*
	When a column is requested as an independant variable an index will be created
	and held until this object is destroyed or its removal is commanded.

	Locating a point will be by finding two closest points in N dimensional space.

*/
protected:
	CcsvLookup(); // not sure this should be used at all
	bool readStream( istream& is);
	bool readStream( IARStream* pIStream);
	void sortRowsInOrder(vector<long> refInd,vector<vectorcsvVariableRow*>& vpvpRows);
	csvVariable reduceToInterpolatedValue(const vector<long>& refInd,const long& lookup, vector< vector< csvVariable > >& vvVars, vector<long>::const_iterator itIndex, const vector< csvVariable >::const_iterator& citEndValueLookup, vector< csvVariable >::const_iterator& citValueLookup);

	vector< vector< csvVariable > > m_vvNumbers;
	CcsvNumArray* m_pnumArray;	
	long m_iCacheNumber;
};
_CSV_HANDLER_END
#endif // !defined(AFX_CSVLOOKUP_H__E5784616_E284_4968_803C_A2E13327D643__INCLUDED_)
