// csvNumArray.h: interface for the CcsvNumArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSVNUMARRAY_H__E7C88C1A_8D03_410A_A3A0_384608126FE3__INCLUDED_)
#define AFX_CSVNUMARRAY_H__E7C88C1A_8D03_410A_A3A0_384608126FE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cell.h"
#include <vector>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;
_CSV_HANDLER_BEGIN

// predeclare
void fDumpToStream(const vector<vectorcsvVariableRow*>& vpRow,ostream& os);


class CcsvNumArray  
{
public:
	CcsvNumArray(vector< vector< csvVariable > >& vvNum,vector< vector< CCell* > >& vvpCells );
	virtual ~CcsvNumArray();

	csvVariable getNum( long iCol, long iRow ) const;
	bool getClosestTwoVectors( const vector<long>& vRefs, const long lookup, const vector<csvVariable>& vValues, vector<vectorcsvVariableRow*>& vReturnRows);
	bool getClosestVectors( const vector<long>& vRefs, const long lookup, const vector<csvVariable>& vValues, vector<vectorcsvVariableRow*>& vReturnRows);
protected:
	void initialise(vector< vector< csvVariable > >& vvNum, vector< vector< CCell* > >& vvpCells );
	bool checkIfSquare();
    bool reduceTo2orMoreRows(vector<long>::const_iterator cit,const long& iOffset,const vector<csvVariable>&vValues,vector<vectorcsvVariableRow*>& vReturnRows);

	vector< vector< csvVariable > > m_numArray;
	vector<vectorcsvVariableRow*> m_vpRows;
	vector< vector< bool > > m_vbIsANumber;

	bool m_bIsSquare;

};


// utility class used for remove_if
class CIsNotOneOf
{
private:
	csvVariable m_dVal1;
	csvVariable m_dVal2;
	long m_iOffset;
public: 
	CIsNotOneOf(const csvVariable& dVal1, const csvVariable& dVal2, const long& iOffset):m_dVal1(dVal1),m_dVal2(dVal2),m_iOffset(iOffset){}
	CIsNotOneOf(){}
	bool operator()(vectorcsvVariableRow* pvRow) const { return !(((*pvRow)[m_iOffset]==m_dVal1)||((*pvRow)[m_iOffset]==m_dVal2)); }


};

class CSortAsClosest
{
private:
	const vector<long>& m_vRefs;
	const long& m_lookup;
	const vector<csvVariable>& m_vValues;
	vector<long>::const_iterator m_citvR;
	vector<csvVariable>::const_iterator m_citvV;
	bool greaterThan(vectorcsvVariableRow* pvRow1, vectorcsvVariableRow* pvRow2);

public: 
	CSortAsClosest(const vector<long>& vRefs, const long lookup, const vector<csvVariable>& vValues, vector<vectorcsvVariableRow*>& vReturnRows):
	m_vRefs(vRefs),m_lookup(lookup),m_vValues(vValues){}
	~CSortAsClosest(){}
	bool operator()(vectorcsvVariableRow* pvRow1, vectorcsvVariableRow* pvRow2) { return greaterThan(pvRow1,pvRow2); }


};


class CSortRows
{
private:
	const vector<long>& m_vRefs;
	vector<long>::const_iterator m_citvR;
	vector<csvVariable>::const_iterator m_citvV;
	bool greaterThan(vectorcsvVariableRow* pvRow1, vectorcsvVariableRow* pvRow2);

public: 
	CSortRows(const vector<long>& refInd):m_vRefs(refInd){}
	~CSortRows(){}
	bool operator()(vectorcsvVariableRow* pvRow1, vectorcsvVariableRow* pvRow2){ return greaterThan(pvRow1,pvRow2); }

};

_CSV_HANDLER_END
#endif // !defined(AFX_CSVNUMARRAY_H__E7C88C1A_8D03_410A_A3A0_384608126FE3__INCLUDED_)
