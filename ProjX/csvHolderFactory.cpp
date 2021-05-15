// csvHolderFactory.cpp: implementation of the CcsvHolderFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "csvHolderFactory.h"
#include "csvLookup.h"
#ifndef NDEBUG
#include <assert.h>
#endif
#include "Symlix/ErrorFactory.h"



_CSV_HANDLER_USING
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CcsvHolderFactory* CcsvHolderFactory::m_instance = NULL;


CcsvHolderFactory::CcsvHolderFactory()
{
  	m_mapTypes[CCFHEMPTY]=ccfHEmpty;
  	m_mapTypes[CCFHLOOKUP]=ccfHLookup;

}

CcsvHolderFactory::~CcsvHolderFactory()
{
  vector< CcsvHolder* >::iterator itv;
  
  for (itv=m_pvcsvHolders.begin();itv!=m_pvcsvHolders.end();itv++)
		delete *itv;

}


///////////////////////////////////////////////////////////
// Function name	: CCellFactory::instance
// Description	    : return a pointer to the CCellFactory 
//                    singleton instance - create one if
//                    none exists.
// Return type		: CCellFactory*
///////////////////////////////////////////////////////////
CcsvHolderFactory* CcsvHolderFactory::instance() 
{
  if (!m_instance)
		m_instance = makeInstance();

  return m_instance;
}

///////////////////////////////////////////////////////////
// Function name	: CcsvHolderFactory::makeInstance
// Description	    : 
// Return type		: CcsvHolderFactory* 
///////////////////////////////////////////////////////////
CcsvHolderFactory* CcsvHolderFactory::makeInstance() 
{
    atexit(&cleanUpInstance);
    return (newtrack CcsvHolderFactory());
}


///////////////////////////////////////////////////////////
// Function name	: CcsvHolderFactory::cleanUpInstance 
// Description	    : static method to remove instance
// Return type		: void 
///////////////////////////////////////////////////////////
void CcsvHolderFactory::cleanUpInstance() 
{
  delete m_instance;
  m_instance = NULL; // just to be sure
}


///////////////////////////////////////////////////////////
// Function name	: CcsvHolderFactory::create
// Description	    : Create a csv holder to be managed by the factory
// Return type		: CcsvHolder* 
// Argument         : const char* sType
// Argument         : IARStream* pIStream =NULL by default
///////////////////////////////////////////////////////////
CcsvHolder* CcsvHolderFactory::create( const char* sType, IARStream* pIStream /*=NULL*/ )
{

	 CcsvHolder* pcsvH = NULL;
	 MapStringIndexHolderCCF::const_iterator mip;
	 mip = m_mapTypes.find(sType);

	 if (mip==m_mapTypes.end())
					return NULL;

	 switch(mip->second)
	 {
	   case ccfHEmpty:
			// nyi
			return false;
			break;
	   case	ccfHLookup:
		/* old file based approach
			if (CcsvLookup::checkFile(sFile))
					pcsvH = newtrack CcsvLookup(sFile);
					else
					pcsvH = NULL; // no necessary - but makes code easy to read*/
			// assume file exists as stream exits
			if (pIStream)
				pcsvH = newtrack CcsvLookup(pIStream);
				else
				pcsvH = NULL;
			break;
	   default:
			#ifndef NDEBUG
			assert(false); // should never happen
			#endif
			return NULL;

	 }

	 if (pcsvH)
			m_pvcsvHolders.push_back(pcsvH);

	 return pcsvH; 
}

#ifndef NDEBUG
///////////////////////////////////////////////////////////
// Function name	: CcsvHolderFactory::testAllHolders
// Description	    : Run tests on holder types
//                    note its necessary to write files to test
//                    with this code.
// Return type		: bool 
// Argument         : ostream& osErr - where the error messages go
///////////////////////////////////////////////////////////
bool CcsvHolderFactory::testAllHolders( ostream& osErr )
{
	bool bResult = true;
	char sFileName[]="TestCSVFile.csv";
	char sFileNameWrong[]="TestCSVFile.txt";

	ofstream os;
	os.open(sFileName);
	if (!os.is_open())
		{
		osErr << "<Internal Error*> Unable to open test csv stream "<<sFileName<<endl;	
		SYMERRORLITE("Unable to open test csv stream",errInternal);
		os.close();
		return false;
		}
		

	os <<"x1,Text,x4,l,x2,dummy,var,Row\n";
	os <<"100,,100,1,100,-99,200.0083314,1\n";
	os <<"0,bark,100,2,100,-7,100.0090029,2\n";
	os <<"-100,four,100,3,100,0,0.001397228,3\n";
	os <<"100,,100,4,0,-99,199.2431975,4\n";
	os <<"0,no,100,5,0,-7,99.04107573,5\n";
	os <<"-100,yes,100,6,0,0,-0.279415498,6\n";
	os <<"100,,100,7,-100,-99,199.9933638,7\n";
	os <<"0,,100,8,-100,-7,99.99000648,8\n";
	os <<"-100,,100,9,-100,0,-0.004162813,9\n";
	os <<"100,\'single quotes\',0,10,100,-99,99.99461365,10\n";
	os <<"0,eak,0,11,100,-7,-0.009900893,11\n";
	os <<"-100,in quotes,0,12,100,0,-100.0053126,12\n";
	os <<"100,,0,13,0,-99,100.420167,13\n";
	os <<"0,\"\"\"\"\"\",0,14,0,-7,0.990607356,14\n";
	os <<"-100,,0,15,0,0,-99.34971216,15\n";
	os <<"100,,0,16,-100,-99,100.0029081,16\n";
	os <<"0,',0,17,-100,-7,0.009711086,17\n";
	os <<"-100,,0,18,-100,0,-99.99241427,18\n";
	os <<"100,,-100,19,100,-99,0.001483933,19\n";
	os <<"0,,-100,20,100,-7,-99.99096094,20\n";
	os <<"-100,,-100,21,100,0,-199.9917163,21\n";
	os <<"100,oh dear,-100,22,0,-99,-0.008851309,22\n";
	os <<"0,,-100,23,0,-7,-100.8462204,23\n";
	os <<"-100,woops,-100,24,0,0,-200.9055784,24\n";
	os <<"100,,-100,25,-100,-99,0.001336886,25\n";
	os <<"0,,-100,26,-100,-7,-100.0077026,26\n";
	os <<"-100,end,-100,27,-100,0,-200.0096604,27\n";
	os.flush();

	os.close();
	// CcsvLookup tests start
	// 1.1 Check file test method works
	assert(!CcsvLookup::checkFile("AFileThatDoesntExist12345.csv"));
	assert(!CcsvLookup::checkFile(sFileNameWrong));
	assert(CcsvLookup::checkFile(sFileName));
	
	// 1.2 create object and test success
	CcsvLookup* pLookup = newtrack CcsvLookup(sFileName);
	assert(pLookup);

	// 1.3 confirm can read all cells
	vector< CCell* > vRow;
	vector< CCell* > vCol;
	CCell* pCell = NULL;
	int iR,iC,iX,iY;

	assert(pLookup->getRow(0,vRow));
	assert(pLookup->getColumn(0,vCol));

	iR = vRow.size();
	iC = vCol.size();

	assert(iR==8);
	assert(iC==28);

	for(iX=0;iX<iR;iX++)
		for(iY=0;iY<iC;iY++)
			{
			osErr <<"Find "<<iX<<","<<iY<<endl;
			pCell = pLookup->getCell(iY,iX);
			assert(pCell);
			}

	// 1.4 confirm can find certain values
	pCell = pLookup->findFirstInCol(0,"-100");
	assert(pCell);
	assert(pLookup->getFocusCol()==0);
	assert(pLookup->getFocusRow()==3);

	pCell = pLookup->findFirstInRow(0,"dummy");
	assert(pCell);
	assert(pLookup->getFocusRow()==0);
	assert(pLookup->getFocusCol()==5);

	// 1.5 confirm can interpolate correctly

	vector<string> vHeadings;
	vector<csvVariable> vValues;
	string sGet;
	vectorcsvVariableRow* vP1=NULL;
	vectorcsvVariableRow* vP2=NULL;

	vHeadings.push_back("x1");	vValues.push_back(-0.1);
	vHeadings.push_back("x4");	vValues.push_back(0);
	vHeadings.push_back("x2");	vValues.push_back(100);
	sGet = "var";

	assert(pLookup->lookupTopRow(vHeadings,sGet,vValues,&vP1,&vP2));

/*	osErr << "vP1->size() == "<<vP1->size() << endl;
	osErr << "vP2->size() == "<<vP2->size() << endl;
	osErr << "x1 vP1 " << (*vP1)[0] << " vP2 " <<(*vP2)[0]  <<endl;
	osErr << "x4 vP1 " << (*vP1)[2] << " vP2 " <<(*vP2)[2]  <<endl;
	osErr << "x2 vP1 " << (*vP1)[4] << " vP2 " <<(*vP2)[4]  <<endl;
	osErr << "var vP1 " << (*vP1)[6] << " vP2 " <<(*vP2)[6]  <<endl;
*/
	assert((*vP1)[0]==-100);
	assert((*vP1)[2]==100);
	assert((*vP1)[4]==0);
	assert((*vP1)[6]==-0.279415498);

	assert((*vP2)[0]==0);
	assert((*vP2)[2]==0);
	assert((*vP2)[4]==100);
	assert((*vP2)[6]==-0.009900893);

	long iLookup = 6;
	csvVariable vR = pLookup->interpolate(vHeadings,sGet,vValues);
	osErr << "Interpolation result = " << vR << endl;

	delete pLookup;

	return bResult;
}
#endif