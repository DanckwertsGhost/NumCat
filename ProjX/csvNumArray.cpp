// csvNumArray.cpp: implementation of the CcsvNumArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "csvNumArray.h"
#include "csvException.h"
#include <algorithm>
#include <functional>
#include <math.h>

#ifndef NCSVDEBUG
#include "assert.h"
#include <iostream>
#endif
_CSV_HANDLER_USING
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CcsvNumArray::CcsvNumArray(vector< vector< csvVariable > >& vvNum, vector< vector< CCell* > >& vvpCells ):m_bIsSquare(false)
{

	initialise(vvNum,vvpCells);
/*

What I'm looking for is 2 rows .. therefore can remove vector< vector < etce tce
*/
}

CcsvNumArray::~CcsvNumArray()
{

}


///////////////////////////////////////////////////////////
// Function name	: CcsvNumArray::initialise
// Description	    : 
// Return type		: void 
// Argument         : vector< vector< csvVariable > >& vvNum
///////////////////////////////////////////////////////////
void CcsvNumArray::initialise(vector< vector< csvVariable > >& vvNum, vector< vector< CCell* > >& vvpCells )
{

	vector< vector< csvVariable > >::iterator itV;
	vector< bool > vbRow;
	vector< vector< CCell* > >::const_iterator citR;
	vector< CCell* >::const_iterator citC;
	m_numArray.clear();
	m_numArray.reserve(vvNum.size());

	for (itV=vvNum.begin();itV!=vvNum.end();itV++)
			m_numArray.push_back(*itV);

	for (itV=m_numArray.begin();itV!=m_numArray.end();itV++)
			m_vpRows.push_back(&*(itV)); // remember pointer to the row ...

	#ifndef NCSVDEBUG
	assert(vvNum.size()==m_numArray.size());
	#endif

	m_vbIsANumber.clear();
	m_vbIsANumber.reserve(vvpCells.size());
	
	for(citR=vvpCells.begin();citR!=vvpCells.end();citR++)
		{
		vbRow.clear();
		vbRow.reserve(citR->size());
		for(citC=citR->begin();citC!=citR->end();citC++)
			vbRow.push_back((*citC)->isOfType(ectNum));
		m_vbIsANumber.push_back(vbRow);
		}

	checkIfSquare();
}


///////////////////////////////////////////////////////////
// Function name	: CcsvNumArray::checkIfSquare
// Description	    : Check if array is square.
// Return type		: bool 
///////////////////////////////////////////////////////////
bool CcsvNumArray::checkIfSquare()
{
	long iRLen;
	vector< vectorcsvVariableRow >::const_iterator cit;
	#ifndef NCSVDEBUG
	ostream_iterator<csvVariable> out(cout,","); // see p53 STL book
	long iLineCount=0;
	#endif

	if (m_numArray.size()<1)
		{
		m_bIsSquare=false;
		return m_bIsSquare;
		}
	cit = m_numArray.begin();

	iRLen = cit->size();
	m_bIsSquare = true;

	while((m_bIsSquare)&&(cit!=m_numArray.end()))
	{
	 if (iRLen!=cit->size())
		#ifndef NCSVDEBUG
		{
		cout <<"<Not Square> line no="<<iLineCount <<" size="<<cit->size()<<" contents = {";
		copy(cit->begin(),cit->end(),out);
		cout << "}"<<endl;
		m_bIsSquare=false;
		}
		#else
		m_bIsSquare=false;
		#endif
		else
		#ifndef NCSVDEBUG
		{
		iLineCount++;
		cit++;
		}
		#else
		cit++;
		#endif
	}
		

	return m_bIsSquare;
}

///////////////////////////////////////////////////////////
// Function name	: CcsvNumArray::getNum
// Description	    : Must handle potential CcsvExcpetions 
//                    being thrown.
// Return type		: csvVariable 
// Argument         : long iCol
// Argument         : long iRow
///////////////////////////////////////////////////////////
csvVariable CcsvNumArray::getNum( long iCol, long iRow ) const
{
	if ((iRow<0)||(iRow>=m_numArray.size()))
		throw newtrack CcsvException("CcsvNumArray::getNum error","Row requested does not exist");

	if ((iCol<0)||(iCol>=m_numArray[iCol].size()))
		throw newtrack CcsvException("CcsvNumArray::getNum error","Column requested does not exist");

	return m_numArray[iRow][iCol];
}



///////////////////////////////////////////////////////////
// Function name	: CcsvNumArray::getClosestTwoVectors
// Description	    : gets the nearest two vectors based on the values passed
//                    for a single dependant variable.
// Can throw        : CcsvException* which must be deallocated when caught.
// Return type		: bool 
// Argument         : const vector<long>& vRefs - list of values to look up
// Argument         : const long lookup - value to assertain
// Argument         : const vector<csvVariable>& vValues - values of the refs
// Argument         : vector<vectorcsvVariableRow*>& vReturnRows - vector of pointer to the rows
///////////////////////////////////////////////////////////
bool CcsvNumArray::getClosestTwoVectors( const vector<long>& vRefs, const long lookup, const vector<csvVariable>& vValues, vector<vectorcsvVariableRow*>& vReturnRows)
{
	bool bResult=true;

	vReturnRows.clear();

/*	vector<long>::const_iterator citL;

	vReturnRows.clear();
	
	if (!m_bIsSquare) // will only operate on square lookup tables
		return m_bIsSquare;
	// check all vRefs are valid
	#ifndef NCSVDEBUG // only for Debug - code above should ensure vRefs are OK
	for (citL=vRefs.begin();citL!=vRefs.end();citL++)
		bResult&=(*citL<m_numArray[0].size());

	if (!bResult)
		throw newtrack CcsvException("CcsvNumArray::getClosestTwoVectors error","Referenced column does not exist");
	#endif
	
	// find closest two values for first point
	citL=vRefs.begin();

	vector<vectorcsvVariableRow*> vTempCopy(m_vpRows.begin(),m_vpRows.end());

	long iR = vTempCopy.size();
//NEED TO MAKE A COPY OF vReturnRows - to eliminate other rows from ....
	long iValue=0;

	while((citL!=vRefs.end())&&(!reduceTo2orMoreRows(citL,iValue,vValues,vTempCopy)))
	{
			#ifndef NCSVDEBUG
			cout << "------------------------------------\n";
			cout << vTempCopy.size()<<endl;
			cout << "------------------------------------\n";
			#endif
			citL++;
			iValue++;
	}
	iR = vTempCopy.size();

	#ifndef NCSVDEBUG
	cout << "Check sort - before\n";
	fDumpToStream(vTempCopy,cout);
	#endif
*/
	// NEW FUNCTION HERE ....
	vector<vectorcsvVariableRow*> vTempCopy;

	bResult = getClosestVectors( vRefs, lookup, vValues, vTempCopy);

	if (vTempCopy.size()>2) // only do it if we have to
		sort(vTempCopy.begin(),vTempCopy.end(),CSortAsClosest(vRefs,lookup,vValues,vTempCopy));

	#ifndef NCSVDEBUG
	cout << "Check sort - after\n";
	fDumpToStream(vTempCopy,cout);
	cout <<"vTempCopy.size() is "<<vTempCopy.size()<<endl;
	#endif

	vector<vectorcsvVariableRow*>::iterator itPoint1=vTempCopy.begin();
	vector<vectorcsvVariableRow*>::iterator itPoint2=vTempCopy.end();itPoint2--;

	vReturnRows.push_back(*itPoint1);
	if (itPoint1!=itPoint2)
		vReturnRows.push_back(*itPoint2);
		#ifndef NCSVDEBUG
		else // draw attention to this
		assert(itPoint1!=itPoint2);
		#endif

	#ifndef NCSVDEBUG
	assert(vReturnRows.size()==2);
	#endif
	if (vReturnRows.size()!=2)
			return false;

	return bResult;
}

bool CcsvNumArray::getClosestVectors( const vector<long>& vRefs, const long lookup, const vector<csvVariable>& vValues, vector<vectorcsvVariableRow*>& vReturnRows)
{
	bool bResult=true;
	vector<long>::const_iterator citL;
	vector<vectorcsvVariableRow*>::iterator itRowsValStart = m_vpRows.begin();itRowsValStart++;

	vReturnRows.clear();
	vReturnRows.resize(m_vpRows.size()-1); // as copying one less row !

	if (!m_bIsSquare) // will only operate on square lookup tables
		return m_bIsSquare;
	// check all vRefs are valid
	#ifndef NCSVDEBUG // only for Debug - code above should ensure vRefs are OK
	for (citL=vRefs.begin();citL!=vRefs.end();citL++)
		bResult&=(*citL<m_numArray[0].size());

	if (!bResult)
		throw newtrack CcsvException("CcsvNumArray::getClosestTwoVectors error","Referenced column does not exist");
	#endif
	
	// find closest two values for first point
	citL=vRefs.begin();

//	vector<vectorcsvVariableRow*> vTempCopy(m_vpRows.begin(),m_vpRows.end());
	copy(itRowsValStart,m_vpRows.end(),vReturnRows.begin());
	


	long iR = vReturnRows.size();
//NEED TO MAKE A COPY OF vReturnRows - to eliminate other rows from ....
	long iValue=0;

	while((citL!=vRefs.end())&&(!reduceTo2orMoreRows(citL,iValue,vValues,vReturnRows)))
	{
			#ifndef NCSVDEBUG
			cout << "------------------------------------\n";
			cout << vReturnRows.size()<<endl;
			cout << "------------------------------------\n";
			#endif
			citL++;
			iValue++;
	}
	iR = vReturnRows.size();

	#ifndef NCSVDEBUG
	cout << "vReturnRows from CcsvNumArray::getClosestVectors\n";
	fDumpToStream(vReturnRows,cout);
	#endif

	return true;
}
///////////////////////////////////////////////////////////
// Function name	: fDumpToStream
// Description	    : Tempry function for debug purposes
// Return type		: void 
// Argument         : vector<vectorcsvVariableRow*>& vpRow
// Argument         : ostream& os
///////////////////////////////////////////////////////////
void fDumpToStream(const vector<vectorcsvVariableRow*>& vpRow,ostream& os)
{
	vector<vectorcsvVariableRow*>::const_iterator ciV;
	vectorcsvVariableRow::const_iterator ciR;
	
	for (ciV=vpRow.begin();ciV!=vpRow.end();ciV++)
		{
		for(ciR=(*ciV)->begin();ciR!=(*ciV)->end();ciR++)
			os << (*ciR)<<",";
		os << endl;
		}	

}

///////////////////////////////////////////////////////////
// Function name	: CcsvNumArray::reduceTo2orMoreRows
// Description	    : Remove from vReturnRows all rows except the nearest two to the point
//                    identified. If only 2 rows left will return anyway.
// Return type		: bool - returns true if only 2 rows left
// Argument         : vector<long>::const_iterator cit
// Argument         : const long& iOffSet - the position in the vValues vector to use for comparison
// Argument         : const vector<csvVariable>&vValues
// Argument         : vector<vectorcsvVariableRow*>& vReturnRows
///////////////////////////////////////////////////////////
bool CcsvNumArray::reduceTo2orMoreRows(vector<long>::const_iterator cit,const long& iOffset, 
                                       const vector<csvVariable>&vValues, vector<vectorcsvVariableRow*>& vReturnRows)
{
	bool bPositive;
	csvVariable dNearest;
	csvVariable dNextNearest;
	csvVariable dFurthest;
	csvVariable dApproach;
	vector<vectorcsvVariableRow*>::iterator itVNewEnd;
//	vector<csvVariable>::const_iterator citV = vValues[*cit];
	vector<vectorcsvVariableRow*>::iterator it=vReturnRows.begin();
	vector<vectorcsvVariableRow*>::const_iterator citpRows=m_vpRows.begin();

	if (vReturnRows.size()==2)
			return true;

	#ifndef NCSVDEBUG
	assert(it!=vReturnRows.end());
	#endif

	if (it==vReturnRows.end()) // lets handle it correctly anyway
			return false;

	#ifndef NCSVDEBUG
	long iL = *cit;
	long itLen = (*it)->size();
	long ivValvesSize=vValues.size();
	assert((*it)->size()>(*cit));
	assert(vValues.size()>iOffset); //NEED TO THINK THIS THROUGH HERE -perhaps not right
	#endif

	// find closest value
	csvVariable vVal = vValues[iOffset];
	dFurthest=dNearest=(**it)[*cit]-vValues[iOffset];
	#ifndef NCSVDEBUG
	csvVariable vTempLook = (**it)[*cit];
	cout << "(**it)[*cit] = "<<vTempLook<<" vValues[iOffset] = "<<vVal<<endl;
	fDumpToStream(m_vpRows,cout);
	cout <<"vReturnRows before - below \n";
	fDumpToStream(vReturnRows,cout);
	#endif
	it++;
	#ifndef NCSVDEBUG
	assert(it!=vReturnRows.end());
	#endif
	for(;it!=vReturnRows.end();it++)
		{
		dApproach = (**it)[*cit]-vValues[iOffset];
		if (fabs(dApproach)<fabs(dNearest))
				dNearest=dApproach;
		if (fabs(dApproach)>fabs(dFurthest))
				dFurthest=dApproach;
		}

	bPositive=bool(dNearest>=0);

	dNextNearest=dFurthest; // need to be careful about same as dNearest

	// find closest value  of opposite sign
	for(it=vReturnRows.begin();it!=vReturnRows.end();it++)
		{
		dApproach = (**it)[*cit]-vValues[iOffset];
		if ((bPositive&&(!bool(dApproach>=0)))&&(dApproach!=dNearest)&&(fabs(dApproach)<fabs(dNextNearest)))
				dNextNearest=dApproach;
		}

	// maybe there were no points with an opposite sign - in which case search for the 
	// next best point
	if (dNextNearest==dFurthest)
		{
			for(it=vReturnRows.begin();it!=vReturnRows.end();it++)
				{
				dApproach = (**it)[*cit]-vValues[iOffset];
				if ((dApproach!=dNearest)&&(fabs(dApproach)<fabs(dNextNearest)))
						dNextNearest=dApproach;
				}
		}

	vector< vector< bool > >::const_iterator citB = m_vbIsANumber.begin();

	vector<vectorcsvVariableRow*> vpRToRemove;
	//long iLCheck = vReturnRows.size();
	for (it=m_vpRows.begin();it!=m_vpRows.end();it++)
		{
		#ifndef NCSVDEBUG
		assert(citB!=m_vbIsANumber.end());
		#endif
		if (!(*citB)[*cit]) // if its there - try to remove it.
			{
			itVNewEnd = remove(vReturnRows.begin(),vReturnRows.end(),*it);
			vReturnRows.erase(itVNewEnd,vReturnRows.end());
			}
		citB++;
		}


	//iLCheck = vReturnRows.size();

	csvVariable vRemove1 = (vVal+dNearest);
	csvVariable vRemove2 = (vVal+dNextNearest);



	itVNewEnd = remove_if(vReturnRows.begin(),vReturnRows.end(),CIsNotOneOf((vVal+dNearest),(vVal+dNextNearest),*cit));
	vReturnRows.erase(itVNewEnd,vReturnRows.end());

	#ifndef NCSVDEBUG
	cout << endl;
	fDumpToStream(vReturnRows,cout);
	#endif

	return (vReturnRows.size()==2);

}




///////////////////////////////////////////////////////////
// Function name	: CSortAsClosest::greaterThan
// Description	    : Method used to determine greater of two rows give variables being
//                    inspected. Greatest value is placed on the first variable
// Return type		: bool 
// Argument         : vectorcsvVariableRow* pvRow1
// Argument         : vectorcsvVariableRow* pvRow2
///////////////////////////////////////////////////////////
bool CSortAsClosest::greaterThan(vectorcsvVariableRow* pvRow1, vectorcsvVariableRow* pvRow2) 
{
	bool bResult = false;
	csvVariable vDiff1;
	csvVariable vDiff2;

	m_citvR = m_vRefs.begin();
	m_citvV = m_vValues.begin();

	#ifndef NCSVDEBUG
	assert(pvRow1);
	assert(pvRow2);
	assert(m_vRefs.size()==m_vValues.size());
	#endif

	while((!bResult)&&(m_citvR!=m_vRefs.end())&&(m_citvV!=m_vValues.end()))
		{

		vDiff1 = abs((*m_citvV)-(*pvRow1)[*m_citvR]);
		vDiff2 = abs((*m_citvV)-(*pvRow2)[*m_citvR]);

		if (vDiff1!=vDiff2)
			bResult=true;
			else
			{
			m_citvR++;
			m_citvV++;
			}

		}

	return (vDiff1>vDiff2);
}



///////////////////////////////////////////////////////////
// Function name	: CSortRows::greaterThan
// Description	    : 
// Return type		: bool 
// Argument         : vectorcsvVariableRow* pvRow1
// Argument         : vectorcsvVariableRow* pvRow2
///////////////////////////////////////////////////////////
bool CSortRows::greaterThan(vectorcsvVariableRow* pvRow1, vectorcsvVariableRow* pvRow2)
{
 
 m_citvR = m_vRefs.begin();
 
 while(m_citvR!=m_vRefs.end())
 {
	if ((*pvRow1)[*m_citvR]>(*pvRow2)[*m_citvR])
				return true;
	if ((*pvRow1)[*m_citvR]<(*pvRow2)[*m_citvR])
				return false;
	m_citvR++;
 }

 // if here then all are equal
 
 return false;
}


