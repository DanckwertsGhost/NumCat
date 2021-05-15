// csvHolder.h: interface for the CcsvHolder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSVHOLDER_H__E8E14DF2_693E_4370_B00C_6CA5BA327F36__INCLUDED_)
#define AFX_CSVHOLDER_H__E8E14DF2_693E_4370_B00C_6CA5BA327F36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CellFactory.h"
#include <vector>
#include <fstream>

#define CSVHOLDER_DEFAULT_CACHE_LEVEL 0
#define CSVH_NOTSET -1

enum eHolderType{ ehtNum, ehtString, ehtDate, ehtEmpty, ehtNotDefined };

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;
_CSV_HANDLER_BEGIN


class CcsvHolder  
{
public:
	CcsvHolder();
	virtual ~CcsvHolder();

	CCell* getCell(long iRow, long iCol) const;
	bool getColumn(long iCol, vector< CCell* >& vCol);
	bool getRow(long iRow, vector< CCell* >& vRow);
	CCell* findFirstInRow(long iRow, const char* sExp);
	CCell* findNextInRow(long iRow, const char* sExp);
	CCell* findFirstInCol(long iCol, const char* sExp);
	CCell* findFirstInCol(long iCol, const long iFind);
	CCell* findNextInCol(long iCol, const char* sExp);
	long getFocusRow(){ return m_iRowWithFocus; }
	long getFocusCol(){ return m_iColWithFocus; }

	// defined - to be implemented else where
	virtual bool lookup( const vector< long >& vRefInd, const long& lookup, const vector< csvVariable >& vValueLookup, vectorcsvVariableRow** vppPoint1,  vectorcsvVariableRow** vppPoint2 ){ return false; }
	virtual bool lookupTopRow( const vector< string >& vRefInd, const string& sLookup, const vector< csvVariable >& vValueLookup, vectorcsvVariableRow** vppPoint1,  vectorcsvVariableRow** vppPoint2 ){ return false; }
	virtual long setCache( const long iCacheValue ){return CSVHOLDER_DEFAULT_CACHE_LEVEL;} // implement where this means something
	virtual long getCacheLevel() const {return CSVHOLDER_DEFAULT_CACHE_LEVEL; }
	virtual csvVariable interpolate( const vector< long >& vRefInd, const long& lookup, const vector< csvVariable >& vValueLookup ){ return CSV_CANNOT_EVALUATE; }
	virtual csvVariable interpolate( const vector< string >& vRefInd, const string& sLookup, const vector< csvVariable >& vValueLookup ){ return CSV_CANNOT_EVALUATE; }
	virtual csvVariable interpolate( const string& sRefInd, const string& sLookup, const csvVariable& rcsvValueLookup ){ return CSV_CANNOT_EVALUATE; }

	friend ostream& operator << ( ostream& os, const CcsvHolder& hld ){ return hld.writeToStream(os); }
	friend ostream& operator << ( ostream& os, CcsvHolder* phld ){ return phld->writeToStream(os); }


protected:
	virtual ostream& writeToStream(ostream& os) const;

	vector< vector< CCell* > > m_vvCells;	

	long m_iRowWithFocus;
	long m_iColWithFocus;
	vector< vector< CCell* > >::const_iterator m_citvCol;
	vector< CCell* >::const_iterator m_citRow;
};

_CSV_HANDLER_END
#endif // !defined(AFX_CSVHOLDER_H__E8E14DF2_693E_4370_B00C_6CA5BA327F36__INCLUDED_)
