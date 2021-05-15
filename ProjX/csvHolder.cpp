// csvHolder.cpp: implementation of the CcsvHolder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "csvHolder.h"

#ifndef NCSVDEBUG
#include "assert.h"
#endif

_CSV_HANDLER_USING
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CcsvHolder::CcsvHolder():m_iRowWithFocus(CSVH_NOTSET),m_iColWithFocus(CSVH_NOTSET)
{

}

CcsvHolder::~CcsvHolder()
{

}


///////////////////////////////////////////////////////////
// Function name	: CcsvHolder::getCell
// Description	    : Return pointer to cell - if available
//                    otherwise return NULL
// Return type		: CCell* 
// Argument         : long iRow
// Argument         : long iCol
///////////////////////////////////////////////////////////
CCell* CcsvHolder::getCell(long iRow, long iCol) const
{
	if ((iRow<0)||(iCol<0))
		return NULL;

	if (m_vvCells.size()<=iRow)
		return NULL;
	if (m_vvCells[iRow].size()<=iCol)
		return NULL;

	return m_vvCells[iRow][iCol];
}


///////////////////////////////////////////////////////////
// Function name	: CcsvHolder::getColumn
// Description	    : return vector if all column avaialbel - other wise empty 
//                    vCol and return false.
// Return type		: bool 
// Argument         : long iCol
// Argument         : vector< CCell* >& vCol
///////////////////////////////////////////////////////////
bool CcsvHolder::getColumn(long iCol, vector< CCell* >& vCol)
{
	bool bResult = true;
	vCol.clear();

	vector< vector< CCell* > >::const_iterator citvRow;

	if (iCol<0)
		return false;

	vCol.reserve(m_vvCells.size()); // since we know its going to be this size at max
	citvRow = m_vvCells.begin();

	while ((bResult)&&(citvRow!=m_vvCells.end()))
	{
		if ((*citvRow).size()<=iCol)
			bResult=false;
			else
			{
			vCol.push_back((*citvRow)[iCol]);
			citvRow++;
			}
	}
	
	if (!bResult)
		{
		vCol.clear();
		return false;
		}

	return true;

}

bool CcsvHolder::getRow(long iRow, vector< CCell* >& vRow)
{
	vRow.clear();
	if ((iRow<0)||(iRow>=m_vvCells.size()))
		return false;
	vRow.resize(m_vvCells[iRow].size());

	vRow = m_vvCells[iRow];

//	copy(m_vvCells[iRow].begin(),m_vvCells[iRow].end(),vRow.begin());

	return true;
}




///////////////////////////////////////////////////////////
// Function name	: CcsvHolder::findFirstInRow
// Description	    : Locate first instance in this row
//                    otherwise return NULL.
// Return type		: CCell* 
// Argument         : long iRow
// Argument         : const char* sExp
///////////////////////////////////////////////////////////
CCell* CcsvHolder::findFirstInRow(long iRow, const char* sExp)
{
	vector< CCell* >::const_iterator citR;
	bool bNotFound = true;
	m_iRowWithFocus=iRow;

	if ((iRow<0)||(iRow>=m_vvCells.size()))
			return NULL;

	citR = m_vvCells[iRow].begin();

	m_iColWithFocus=0;
	m_iRowWithFocus=iRow;

	while((bNotFound)&&(citR!=m_vvCells[iRow].end()))
	{
		if ((*citR)->find(sExp))
			bNotFound = false;
			else
			{
			m_iColWithFocus++;
			citR++;
			}
	}

	if (bNotFound)
		return NULL;
	#ifndef NCSVDEBUG
	assert(citR!=m_vvCells[iRow].end()); // as bNotFound should have been true
	#endif
	m_citRow = citR;

	return *citR;
}


///////////////////////////////////////////////////////////
// Function name	: CcsvHolder::findNextInRow
// Description	    : Locate next instance in this row
//                    otherwise return NULL. ( Remebers last 
//                    search. If row changes then starts at beginning again.
// Return type		: CCell* 
// Argument         : long iRow
// Argument         : const char* sExp
///////////////////////////////////////////////////////////
CCell* CcsvHolder::findNextInRow(long iRow, const char* sExp)
{
	vector< CCell* >::const_iterator citR;
	bool bNotFound = true;

	if (iRow!=m_iRowWithFocus)
			return findFirstInRow(iRow,sExp);

	citR = m_citRow;
	#ifndef NCSVDEBUG
	assert(citR!=NULL);
	#endif
	if (citR==m_vvCells[iRow].end())
			return NULL;

	while((bNotFound)&&(citR!=m_vvCells[iRow].end()))
	{
		if ((*citR)->find(sExp))
			bNotFound = false;
			else
			{
			m_iColWithFocus++;
			citR++;
			}
	}

	if (bNotFound)
		return NULL;
	#ifndef NCSVDEBUG
	assert(citR!=m_vvCells[iRow].end()); // as bNotFound should have been true
	#endif
	m_citRow = citR;

	return *citR;



}

//#define DBGFINDFIRST
#ifdef DBGFINDFIRST
#include <iostream>
#endif


///////////////////////////////////////////////////////////
// Function name	: CcsvHolder::findFirstInCol
// Description	    : 
// Return type		: CCell* 
// Argument         : long iCol
// Argument         : const char* sExp
///////////////////////////////////////////////////////////
CCell* CcsvHolder::findFirstInCol(long iCol, const char* sExp)
{
	bool bNotFound = true;

	if ((m_vvCells.size()==0)||(m_vvCells[0].size()<=iCol))
			return NULL; // as there's nothing to see

	vector< vector< CCell* > >::const_iterator citC = m_vvCells.begin();

	m_iColWithFocus=iCol;
	m_iRowWithFocus=0;

	while((bNotFound)&&(citC!=m_vvCells.end())&&(citC->size()>iCol))
		{
		#ifdef DBGFINDFIRST
		cout << (*(*citC)[iCol]);
		(*citC)[iCol]->writeType(cout);
		cout<<" "<<endl;
		#endif
		if ((*citC)[iCol]->find(sExp))
				bNotFound=false;
				else
				{
				m_iRowWithFocus++;
				citC++;
				}
		}

	if (bNotFound)
		return NULL;
		
	#ifndef NCSVDEBUG
	assert(citC!=m_vvCells.end()); // as bNotFound should have been true
	#endif

	m_citvCol = citC;
	m_iColWithFocus=iCol;

	return (*citC)[iCol];
}


///////////////////////////////////////////////////////////
// Function name	: CcsvHolder::findFirstInCol - may be a case for templates if other types used
// Description	    : 
// Return type		: CCell* 
// Argument         : long iCol
// Argument         : const long iFind
///////////////////////////////////////////////////////////
CCell* CcsvHolder::findFirstInCol(long iCol, const long iFind )
{
	bool bNotFound = true;

	if ((m_vvCells.size()==0)||(m_vvCells[0].size()<=iCol))
			return NULL; // as there's nothing to see

	vector< vector< CCell* > >::const_iterator citC = m_vvCells.begin();

	m_iColWithFocus=iCol;
	m_iRowWithFocus=0;

	while((bNotFound)&&(citC!=m_vvCells.end())&&(citC->size()>iCol))
		{
		#ifdef DBGFINDFIRST
		cout << (*(*citC)[iCol]);
		(*citC)[iCol]->writeType(cout);
		cout<<" "<<endl;
		#endif
		if ((*citC)[iCol]->find(iFind))
				bNotFound=false;
				else
				{
				m_iRowWithFocus++;
				citC++;
				}
		}

	if (bNotFound)
		return NULL;
		
	#ifndef NCSVDEBUG
	assert(citC!=m_vvCells.end()); // as bNotFound should have been true
	#endif

	m_citvCol = citC;
	m_iColWithFocus=iCol;

	return (*citC)[iCol];
}
///////////////////////////////////////////////////////////
// Function name	: CcsvHolder::findNextInCol
// Description	    : 
// Return type		: CCell* 
// Argument         : long iCol
// Argument         : const char* sExp
///////////////////////////////////////////////////////////
CCell* CcsvHolder::findNextInCol(long iCol, const char* sExp)
{
	bool bNotFound = true;
	vector< vector< CCell* > >::const_iterator citC;

	if (iCol!=m_iColWithFocus)
			return findFirstInCol(iCol,sExp);

	citC = m_citvCol;
	#ifndef NCSVDEBUG
	assert(citC!=NULL);
	#endif


	if (m_vvCells.size()==0)
			return NULL; // as there's nothing to see

	while((bNotFound)&&(citC!=m_vvCells.end())&&(citC->size()>iCol))
		{
		if ((*citC)[iCol]->find(sExp))
				bNotFound=false;
				else
				{
				m_iRowWithFocus++;
				citC++;
				}
		}

	if (bNotFound)
		return NULL;
		
	#ifndef NCSVDEBUG
	assert(citC!=m_vvCells.end()); // as bNotFound should have been true
	#endif

	m_citvCol = citC;

	return (*citC)[iCol];

}

ostream& CcsvHolder::writeToStream(ostream& os) const
{
	vector< vector<  CCell* > >::const_iterator citVR;
	vector< CCell* >::const_iterator citC;

	for(citVR=m_vvCells.begin();citVR!=m_vvCells.end();citVR++)
		{
		for(citC=citVR->begin();citC!=citVR->end();citC++)
			{
			if (citC!=citVR->begin())
					os <<",";
			os << (*citC)->getString(); 
			}
		os << endl;
		}

	return os;

}

