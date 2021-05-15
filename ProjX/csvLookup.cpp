// csvLookup.cpp: implementation of the CcsvLookup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "csvLookup.h"
#include "ARFileReader.h"
#include "CellFactory.h"
#include "csvException.h"
#include <algorithm>
#include <math.h>
#include "csvHolderFactory.h"

#ifndef NCSVDEBUG
#include <assert.h>
#include <iostream>
//#define DEBUG_LOOKUP

#endif
_CSV_HANDLER_USING
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CcsvLookup::CcsvLookup():CcsvHolder(),m_pnumArray(NULL),m_iCacheNumber(CSVHOLDER_DEFAULT_CACHE_LEVEL)
{

}

CcsvLookup::CcsvLookup(const char* sFileName):CcsvHolder(),m_pnumArray(NULL),m_iCacheNumber(CSVHOLDER_DEFAULT_CACHE_LEVEL)
{
	ifstream is;

	is.open(sFileName);

	if (is.is_open())
		readStream(is);
}

CcsvLookup::CcsvLookup(IARStream* pIStream):CcsvHolder(),m_pnumArray(NULL),m_iCacheNumber(CSVHOLDER_DEFAULT_CACHE_LEVEL)
{
	ASSERT2(pIStream);

	if (pIStream)
		readStream(pIStream);

}

CcsvLookup::~CcsvLookup()
{
	delete m_pnumArray;
}




///////////////////////////////////////////////////////////
// Function name	: CcsvLookup::readStream
// Description	    : Populate m_vvCells from this stream
// Return type		: bool 
// Argument         : istream& is
///////////////////////////////////////////////////////////
bool CcsvLookup::readStream( istream& is)
{
	bool bCarryOn = true;
	bool bResult = false;
	vector< string > vLine;
	vector< string >::const_iterator citLine;
	vector< char > vDelim; // may be m_vDelim latter
	vector< CCell* > vRow;
	CCellFactory* pcf = CCellFactory::instance();
	CCell* pCell=NULL;

	vDelim.push_back(',');

	do
	{
	bCarryOn = readLine(is,vDelim,vLine);
	vRow.clear();
	long llen=vLine.size();

	if (bCarryOn)
		{
		for(citLine=vLine.begin();citLine!=vLine.end();citLine++)
				{
				 pCell = pcf->createCell(citLine->c_str());
				 #ifndef NCSVDEBUG
				 if (!pCell)
					cerr << "["<<citLine->c_str()<<"]"<<endl;
				 assert(pCell);
				 #endif
				 if (pCell)
					vRow.push_back(pCell);
				}

		if ((!bResult)&&(vRow.size()>0))
				bResult=true;
		m_vvCells.push_back(vRow);
		}

	}
	while(bCarryOn);

	vector<csvVariable> vNumRow;
	vector< vector< CCell* > >::const_iterator citVV;
	vector< CCell* >::const_iterator citR;

	for (citVV=m_vvCells.begin();citVV!=m_vvCells.end();citVV++)
		{
		vNumRow.clear();
		for (citR=citVV->begin();citR!=citVV->end();citR++)
			vNumRow.push_back((*citR)->getNumber());
		m_vvNumbers.push_back(vNumRow);
		#ifdef DEBUG_LOOKUP
		assert(vNumRow.size()>0); // not necessarily a mistake - would pass on release build
		#endif
		}	
	
	m_pnumArray = newtrack CcsvNumArray(m_vvNumbers,m_vvCells);
	
	return bResult;
}


///////////////////////////////////////////////////////////
// Function name	: CcsvLookup::readStream
// Description	    : Read the contents of this stream
// Return type		: bool 
// Argument         : IARStream* pIStream
///////////////////////////////////////////////////////////
bool CcsvLookup::readStream( IARStream* pIStream)
{
	bool bCarryOn = true;
	bool bResult = false;
	vector< string > vLine;
	vector< string >::const_iterator citLine;
	vector< char > vDelim; // may be m_vDelim latter
	vector< CCell* > vRow;
	CCellFactory* pcf = CCellFactory::instance();
	CCell* pCell=NULL;

	vDelim.push_back(',');


	ASSERT2(pIStream); 
	if (!pIStream) // handle the screw up in the wild case
		return false;


	do
	{
	bCarryOn = readLine(pIStream,vDelim,vLine);
	vRow.clear();
	long llen=vLine.size();

	if (bCarryOn)
		{
		for(citLine=vLine.begin();citLine!=vLine.end();citLine++)
				{
				 pCell = pcf->createCell(citLine->c_str());
				 #ifndef NCSVDEBUG
				 if (!pCell)
					cerr << "["<<citLine->c_str()<<"]"<<endl;
				 assert(pCell);
				 #endif
				 if (pCell)
					vRow.push_back(pCell);
				}

		if ((!bResult)&&(vRow.size()>0))
				bResult=true;
		m_vvCells.push_back(vRow);
		}

	}
	while(bCarryOn);

	vector<csvVariable> vNumRow;
	vector< vector< CCell* > >::const_iterator citVV;
	vector< CCell* >::const_iterator citR;

	for (citVV=m_vvCells.begin();citVV!=m_vvCells.end();citVV++)
		{
		vNumRow.clear();
		for (citR=citVV->begin();citR!=citVV->end();citR++)
			vNumRow.push_back((*citR)->getNumber());
		m_vvNumbers.push_back(vNumRow);
		#ifdef DEBUG_LOOKUP
		assert(vNumRow.size()>0); // not necessarily a mistake - would pass on release build
		#endif
		}	
	
	m_pnumArray = newtrack CcsvNumArray(m_vvNumbers,m_vvCells);
	
	return bResult;
}

///////////////////////////////////////////////////////////
// Function name	: CcsvLookup::lookup
// Description	    : Finds two points closest to the locate one.
// Return type		: csvVariable 
// Argument         : const vector< long > vRefInd
// Argument         : const long iLook
// Argument         : const vector< csvVariable >& vValue
///////////////////////////////////////////////////////////
bool CcsvLookup::lookup( const vector< long >& vRefInd, const long& lookup, const vector< csvVariable >& vValueLookup, vectorcsvVariableRow** vppPoint1,  vectorcsvVariableRow** vppPoint2 )
{

	vector<vectorcsvVariableRow*> vpvpRows;	
	bool bResult;
	try
	{
		bResult=m_pnumArray->getClosestTwoVectors(vRefInd,lookup,vValueLookup,vpvpRows);
		#ifndef NCSVDEBUG
		assert(bResult);
		#endif
	}
	catch(CcsvException* pExcept)
	{
		cerr << pExcept->getMessage() <<"\n"<<pExcept->getDetails()<<endl;
		delete pExcept;
		return false;
	}

	long i = vpvpRows.size();
	if ((!bResult)||(vpvpRows.size()!=2))
			return false;

	if ((vpvpRows[0]==NULL)||(vpvpRows[1]==NULL))
			#ifndef NCSVDEBUG
			assert(false);
			#else
			return false;
			#endif
	(*vppPoint1) = vpvpRows[0];
	(*vppPoint2) = vpvpRows[1];

	#ifndef NCSVDEBUG
	assert((*vppPoint1)->size()>0);
	assert((*vppPoint2)->size()>0);
	#endif

	return true; 
}


///////////////////////////////////////////////////////////
// Function name	: CcsvLookup::lookupTopRow
// Description	    : Assumes top row has character names. Looks up 2 appopriate
//                    points for linear approximation given values of independant
//                    variables
// Return type		: bool 
// Argument         : const vector< string >& vRefInd
// Argument         : const string& sLookup
// Argument         : const vector< csvVariable >& vValueLookup
// Argument         : vectorcsvVariableRow** vppPoint1
// Argument         : vectorcsvVariableRow** vppPoint2
///////////////////////////////////////////////////////////
bool CcsvLookup::lookupTopRow( const vector< string >& vRefInd, const string& sLookup, const vector< csvVariable >& vValueLookup, vectorcsvVariableRow** vppPoint1,  vectorcsvVariableRow** vppPoint2 )
{

	vector<long> vRef;
	CCell* pCell;
	long iTarget;
	vector< string >::const_iterator cit = vRefInd.begin();

	while(cit!=vRefInd.end())
	{
		pCell = this->findFirstInRow(0,cit->c_str());
		if (pCell==NULL)
			return false;
		vRef.push_back(this->getFocusCol());
		cit++;

	}
	

	pCell = this->findFirstInRow(0,sLookup.c_str());
	if (pCell==NULL)
		return false;

	iTarget = this->getFocusCol();


	return this->lookup(vRef,iTarget,vValueLookup,vppPoint1,vppPoint2);
}



///////////////////////////////////////////////////////////
// Function name	: CcsvLookup::interpolate
// Description	    : 
// Return type		: csvVariable 
// Argument         :  const vector< long >& vRefInd
// Argument         : const long& lookup
// Argument         : const vector< csvVariable >& vValueLookup
///////////////////////////////////////////////////////////
csvVariable CcsvLookup::interpolate( const vector< long >& vRefInd, const long& lookup, const vector< csvVariable >& vValueLookup )
{
	vector<vectorcsvVariableRow*> vpvpRows;	
	bool bResult;

	try
	{
		bResult=m_pnumArray->getClosestVectors(vRefInd,lookup,vValueLookup,vpvpRows);
		#ifndef NCSVDEBUG
		assert(bResult);
		#endif
	}
	catch(CcsvException* pExcept)
	{
		cerr << pExcept->getMessage() <<"\n"<<pExcept->getDetails()<<endl;
		delete pExcept;
		return CSV_CANNOT_EVALUATE;
	}

	// check enough rows have been returned
	#ifndef NCSVDEBUG
	assert(vpvpRows.size()==pow(2,vRefInd.size()));
	#endif
	if (vpvpRows.size()!=pow(2,vRefInd.size()))
				return CSV_NOT_DEFINED;

//NEED TO WORK BACK HERE TO UNDERSTAND MECHANISM. ALSO NEED INFOR ON VARIABLE BEING INTERPOLATE FOR 
//WHICH NEED TO BE ADDED TO THE FUNCTIONAL HEADER.


	switch (vRefInd.size()) // as small interpolations can be dealt with much faster
	{
	case 0:
			return CSV_NOT_DEFINED;
			break;
	case 1: // should have 2 points
			return ((*vpvpRows[0])[lookup] + ((*vpvpRows[1])[lookup]-(*vpvpRows[0])[lookup])*(vValueLookup[0]-(*vpvpRows[0])[vRefInd[0]])/
																		((*vpvpRows[1])[vRefInd[0]]-(*vpvpRows[0])[vRefInd[0]]));
			break;
/*	case 2:
			{
				csvVariable x21,x22,v21,v22,f1,f2;
				
				f1 = (vValueLookup[0]-(*vpvpRows)[0][RefInd[0]])/((*vpvpRows)[1][RefInd[0]]-(*vpvpRows)[0][RefInd[0]]);
				// need to think how the are sorted....
			}
			break;*/

	default:
			{
				vector< vector< csvVariable > > vvVars;
				vvVars.reserve(vpvpRows.size());
				vector<vectorcsvVariableRow*>::const_iterator citVV;
				vector< csvVariable >::const_iterator citEndValueLookup = vValueLookup.end();
				vector< csvVariable >::const_iterator citValueLookup = vValueLookup.begin();

				#ifndef NCSVDEBUG
				cerr << "+++Before+++\n";
				fDumpToStream(vpvpRows,cerr);
				#endif
				
				sortRowsInOrder(vRefInd,vpvpRows);

				#ifndef NCSVDEBUG
				cerr << "+++After+++\n";
				fDumpToStream(vpvpRows,cerr);
				#endif

				for(citVV=vpvpRows.begin();citVV!=vpvpRows.end();citVV++)
					{
					vector< csvVariable > vVars;
					vVars.resize((*citVV)->size());
					copy((*citVV)->begin(),(*citVV)->end(),vVars.begin());
					vvVars.push_back(vVars);
					}

				return reduceToInterpolatedValue(vRefInd,lookup,vvVars,vRefInd.begin(),citEndValueLookup,citValueLookup);

			}

	}
	
	return CSV_CANNOT_EVALUATE;
}


///////////////////////////////////////////////////////////
// Function name	: CcsvLookup::interpolate
// Description	    : This version using string refs to create the indexes before calling
//					  csvVariable CcsvLookup::interpolate( const vector< long >& vRefInd, const long& lookup, const vector< csvVariable >& vValueLookup )
// Return type		: csvVariable 
// Argument         :  const vector< string >& vRefInd
// Argument         : const string& sLookup
// Argument         : const vector< csvVariable >& vValueLookup
///////////////////////////////////////////////////////////
csvVariable CcsvLookup::interpolate( const vector< string >& vRefInd, const string& sLookup, const vector< csvVariable >& vValueLookup )
{

	vector<long> vRef;
	CCell* pCell;
	long iTarget;
	vector< string >::const_iterator cit = vRefInd.begin();

	while(cit!=vRefInd.end())
	{
		pCell = this->findFirstInRow(0,cit->c_str());
		if (pCell==NULL)
			return CSV_NOT_DEFINED;
		vRef.push_back(this->getFocusCol());
		cit++;

	}
	

	pCell = this->findFirstInRow(0,sLookup.c_str());
	if (pCell==NULL)
		return CSV_NOT_DEFINED;

	iTarget = this->getFocusCol();


	return this->interpolate(vRef,iTarget,vValueLookup);

}

///////////////////////////////////////////////////////////
// Function name	: interpolate
// Description	    : For the case were there is only one variable to be interpolated before calling
//					  csvVariable CcsvLookup::interpolate( const vector< long >& vRefInd, const long& lookup, const vector< csvVariable >& vValueLookup )
// Return type		: csvVariable 
// Argument         :  const string& sRefInd
// Argument         : const string& sLookup
// Argument         : const csvVariable& csvValueLookup
///////////////////////////////////////////////////////////
csvVariable CcsvLookup::interpolate( const string& sRefInd, const string& sLookup, const csvVariable& rcsvValueLookup )
{

	vector<long> vRef;
	vector< csvVariable > vValueLookup;
	CCell* pCell;
	long iTarget;

	vValueLookup.push_back(rcsvValueLookup);

	pCell = this->findFirstInRow(0,sRefInd.c_str());
	if (pCell==NULL)
			return CSV_NOT_DEFINED;
	vRef.push_back(this->getFocusCol());
	

	pCell = this->findFirstInRow(0,sLookup.c_str());
	if (pCell==NULL)
		return CSV_NOT_DEFINED;

	iTarget = this->getFocusCol();


	return this->interpolate(vRef,iTarget,vValueLookup);
}


///////////////////////////////////////////////////////////
// Function name	: CcsvLookup::checkFile
// Description	    : do basic checks on a potential file name
// Return type		: bool 
// Argument         : const char* sFile
///////////////////////////////////////////////////////////
/*static*/ bool CcsvLookup::checkFile( const char* sFile )
{
 bool bResult = false;

 if (!sFile)
		return false;
 
 if (strlen(sFile)<5) // then its not a csv file
		return false;

 // could add a test to see if a csv file here

 // could also attempt to open the file then close again .... to see if exists
 ifstream is;

 is.open(sFile);

 if (is.is_open())
	bResult = true;

 is.close();

 return bResult;
 
 
}



///////////////////////////////////////////////////////////
// Function name	: CcsvLookup::setCache
// Description	    : Updates chache level and returns current
//                    level. Only 'legal' values allowed.
// Return type		: long 
// Argument         : const long iCacheValue
///////////////////////////////////////////////////////////
long CcsvLookup::setCache( const long iCacheValue )
{

	if ((iCacheValue>=getLowCacheNum())&&(iCacheValue<=getHighCacheNum()))
				m_iCacheNumber=iCacheValue;

	return m_iCacheNumber;
} 



///////////////////////////////////////////////////////////
// Function name	: CcsvLookup::sortRowsInOrder
// Description	    : 
// Return type		: bool 
// Argument         : vector<long> refInd
// Argument         : vector<vectorcsvVariableRow*> vpvpRows
///////////////////////////////////////////////////////////
void CcsvLookup::sortRowsInOrder(vector<long> refInd,vector<vectorcsvVariableRow*>& vpvpRows)
{

	bool bResult=true;
	
	#ifndef NCSVDEBUG
	cout << "\nBefore sort\n";
	fDumpToStream(vpvpRows,cout);
	#endif

	sort(vpvpRows.begin(),vpvpRows.end(),CSortRows(refInd));
	
	#ifndef NCSVDEBUG
	cout << "After sort\n";
	fDumpToStream(vpvpRows,cerr);
	#endif

}

#ifndef NCSVDEBUG
#define DBG_INTER
#endif
///////////////////////////////////////////////////////////
// Function name	: CcsvLookup::reduceToInterpolatedValue
// Description	    : Recurses until one value found for index lookup
// Return type		: csvVariable 
// Argument         : const vector<long>& refInd
// Argument         : const long& lookup
// Argument         : vector< vector< csvVariable > >& vvVars
// Argument         : vector<long>::const_iterator itIndex
// Argument         : const vector< csvVariable >::const_iterator& citEndValueLookup
// Argument         : const vector< csvVariable >::const_iterator& citValueLookup
///////////////////////////////////////////////////////////
csvVariable CcsvLookup::reduceToInterpolatedValue(const vector<long>& refInd,const long& lookup, vector< vector< csvVariable > >& vvVars, vector<long>::const_iterator itIndex, const vector< csvVariable >::const_iterator& citEndValueLookup, vector< csvVariable >::const_iterator& citValueLookup)
{

//	vector<long>::const_iterator citRef;
	vector< vector< csvVariable >* >::iterator itVL;
	vector< vector< csvVariable >* >::iterator itVR;
	vector< vector< csvVariable > >::iterator itOrigEnd = vvVars.end();
	vector< vector< csvVariable > > vvNext;
	long iCount;
	long lRecs = vvVars.size();
	#ifndef NCSVDEBUG
	assert(0==lRecs%2);	
	#endif
	lRecs /= 2;
	vector< vector< csvVariable >* > vLeft;//(vvVars.begin(),&(vvVars[lRecs]));
	vector< vector< csvVariable >* > vRight;//(&(vvVars[lRecs]),vvVars.end());

	for(iCount=0;iCount<lRecs;iCount++)
			vLeft.push_back(&vvVars[iCount]);

	for(iCount=lRecs;iCount<vvVars.size();iCount++)
			vRight.push_back(&vvVars[iCount]);

	#ifndef NCSVDEBUG
	assert(vLeft.size()==vRight.size());
	#ifdef DBG_INTER
	cerr <<"Lookup index = "<<(*itIndex)<<endl;
	cerr << "vLeft\n";
	fDumpToStream(vLeft,cerr);
	cerr << "vRight\n";
	fDumpToStream(vRight,cerr);
	cerr << endl;
	#endif
	#endif

	itVL = vLeft.begin();
	itVR = vRight.begin();
	vector< csvVariable > vNew;

	while((itVL!=vLeft.end())&&(itVR!=vRight.end()))
	{
		vNew.clear();
//		vector< csvVariable >::iterator itRowLeft;
//		vector< csvVariable >::iterator itRowRight;
		csvVariable& dLeft=(**itVL)[*itIndex];
		csvVariable& dRight=(**itVR)[*itIndex];
		#ifndef NCSVDEBUG
		assert(dLeft!=dRight); // otherwise div by zero latter
		#endif
		csvVariable  dActual=(*citValueLookup);//vValueLookup[refInd[*itIndex]];
		csvVariable  dFrac = (dActual-dLeft)/(dRight-dLeft);
		#ifdef DBG_INTER
		cerr << "dFrac = (dActual-dLeft)/(dRight-dLeft)\n";
		cerr << "dActual="<<dActual<<"\tdLeft="<<dLeft<<"\tdRigh="<<dRight<<endl;
		cerr << "dActual=(*citValueLookup)\n";
//		cerr << "refInd[*itIndex]="<<(refInd[*itIndex])<<"\tvValueLookup.size()="<<vValueLookup.size()<<endl;
		#endif		
		csvVariable dNew;

		dNew = (**itVL)[lookup] + ((**itVR)[lookup]-(**itVL)[lookup])*dFrac;
		#ifdef DBG_INTER
		cerr <<"dNew="<<dNew<<"\t(**itVL)[lookup]="<<(**itVL)[lookup];
		cerr <<"\t(**itVR)[lookup]="<<(**itVR)[lookup]<<"\tdFrac="<<dFrac<<endl;
		#endif

		for(iCount=0;iCount<(*itVL)->size();iCount++)
			{
				if (iCount==lookup)
					vNew.push_back(dNew);
					else
					if (iCount==(*itIndex))
						vNew.push_back(dActual);
						else
						vNew.push_back((**itVL)[iCount]);
			}

		vvNext.push_back(vNew);
//		vvVars.push_back(vNew); INVALIDATES- WILL NEED ANOTHER VECTOR

		itVL++;itVR++;
	}
	#ifdef DBG_INTER
	cerr << endl;	
	#endif
/*	vvVars.erase(vvVars.begin(),itOrigEnd);
	vvVars.resize(vvNext.size());
	copy(vvNext.begin(),vvNext.end(),vvVars.begin());
*/
	itIndex++;
	citValueLookup++;

#ifndef NCSVDEBUG
	long iSize = vvNext.size();
#ifdef DBG_INTER
	cerr << "vvVars.size() = "<<iSize<<endl;
#endif
	if (itIndex==refInd.end())
		assert(vvNext.size()==1); // as it should be
		else
		assert(vvNext.size()>1);
#endif
	
	if (itIndex==refInd.end())
		{
#ifdef DBG_INTER
		cerr <<"vvNext size = "<<vvNext.size()<<" , first row length = "<<vvNext[0].size();
		cerr <<" and value = "<< vvNext[0][lookup] <<endl;
		cerr <<" Lookup = "<<lookup<<endl;
#endif
		return vvNext[0][lookup];
		}

	if (citValueLookup==citEndValueLookup) // then this should go no further
			{
			#ifndef NCSVDEBUG
#ifdef DBG_INTER
			cerr << "citValueLookup==citEndValueLookup"<<endl;
#endif
			assert(citValueLookup!=citEndValueLookup);
			#endif
			return CSV_NOT_DEFINED;

			}

#ifdef DBG_INTER
	csvVariable vReturn = reduceToInterpolatedValue(refInd,lookup,vvNext,itIndex,citEndValueLookup,citValueLookup);
	cerr << vReturn << endl;
	return vReturn;
#else
	return reduceToInterpolatedValue(refInd,lookup,vvNext,itIndex,citEndValueLookup,citValueLookup);
#endif
} 