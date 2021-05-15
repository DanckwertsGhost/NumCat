#include "stdafx.h"

#include "CellFactory.h"
#include "MemLeakRecord.h"

#ifndef NCSVDEBUG
#include "assert.h"
#endif
_CSV_HANDLER_USING

CCellFactory* CCellFactory::m_instance = NULL;


///////////////////////////////////////////////////////////
// Function name	: CCellFactory::CCellFactory
// Description	    : 
// Return type		: 
///////////////////////////////////////////////////////////
CCellFactory::CCellFactory() /*:m_EmptyCell()*/
{
  	m_mapTypes[CCFEMPTY]=ccfEmpty;
	m_mapTypes[CCFNUMBER]=ccfNum;
	m_mapTypes[CCFSTRING]=ccfString;

}


///////////////////////////////////////////////////////////
// Function name	: CCellFactory::~CCellFactory
// Description	    : 
// Return type		: 
///////////////////////////////////////////////////////////
CCellFactory::~CCellFactory() 
{
  vector< CCell* >::iterator itv;
  
  for (itv=m_vCells.begin();itv!=m_vCells.end();itv++)
		delete *itv;

}


///////////////////////////////////////////////////////////
// Function name	: CCellFactory::instance
// Description	    : return a pointer to the CCellFactory 
//                    singleton instance - create one if
//                    none exists.
// Return type		: CCellFactory*
///////////////////////////////////////////////////////////
CCellFactory* CCellFactory::instance() 
{
  if (!m_instance)
		m_instance = makeInstance();

  return m_instance;
}



///////////////////////////////////////////////////////////
// Function name	: CCellFactory::makeInstance
// Description	    : 
// Return type		: CCellFactory* 
///////////////////////////////////////////////////////////
CCellFactory* CCellFactory::makeInstance() 
{
    atexit(&cleanUpInstance);
    return (newtrack CCellFactory());
}


///////////////////////////////////////////////////////////
// Function name	: CCellFactory::cleanUpInstance 
// Description	    : static method to remove instance
// Return type		: void 
///////////////////////////////////////////////////////////
void CCellFactory::cleanUpInstance() 
{
  delete m_instance;
  m_instance = NULL; // just to be sure
}


///////////////////////////////////////////////////////////
// Function name	: CCellFactory::createCell
// Description	    : Create appropriate cell type
//                    life time of pointed to object is managed
//                    by the factory though destructor and remove cell
//                    methods.
// Return type		: CCell* 
// Argument         : const char* sType
// Argument         : const char* sContents
///////////////////////////////////////////////////////////
CCell* CCellFactory::createCell(/*long iRow, long iCol,*/ const char* sContents, const char* sType) 
{
  string sCellType;
  CCell* pcell=NULL;
 
  if (strlen(sContents)<1) 
		sCellType=CCFEMPTY;
		else
		{
		  if (sType)
			sCellType=sType;
			else
			{
			string sCellContents(sContents);

			// is it empty
			if (sCellContents.length()==0)
					sCellType=CCFEMPTY;
					else
					{
					// is it a number ... ?
					if (((sCellContents[0]>47)&&(sCellContents[0]<58))||
						((sCellContents[0]=='-')||(sCellContents[0]=='+')))
						sCellType=CCFNUMBER;
						else
						sCellType=CCFSTRING; // default
					}

			}
		}

  MapStringIndexCCF::const_iterator mip;
  mip = m_mapTypes.find(sCellType.c_str());

  if (mip==m_mapTypes.end())
				return NULL;

  switch(mip->second)
	{
	case ccfEmpty:
	  pcell = newtrack CEmptyCell();
     break;

	case ccfNum:
	  pcell = newtrack CNumCell(/*iCol,iRow,*/sContents);
     break;

	case ccfString:
	  pcell = newtrack CStringCell(/*iCol,iRow,*/sContents);
     break;
	default:
	  #ifndef NCSVDEBUG
	  assert(false);
	  #endif
	  return NULL; // have to behave 

	}

  if (!pcell)
		{
		#ifndef NCSVDEBUG
		assert(false);
		#endif
		return NULL;
		}

  vector< CCell* >::iterator itv=m_vCells.begin();
  vector< CCell* >::iterator itvFind=m_vCells.end();


  while (itv!=m_vCells.end())
	{
	if ((*itv)==pcell)
		{
		itvFind=itv;
		itv = m_vCells.end();
		}
		else
		itv++;
	}	
 
  if (m_vCells.size()==0)
		m_vCells.push_back(pcell); // life time will be managed in factory
		else  
		  if ((itvFind==m_vCells.end())&&pcell)
				m_vCells.push_back(pcell); // life time will be managed in factory
				else
				{
				delete pcell; // this is a duplicate object - get ride of it
				pcell = *itv;
				pcell->addLock();
				}

  return pcell;

}

bool CCellFactory::removeCell (CCell* pCCellRemove) 
{
  vector< CCell* >::iterator itv=m_vCells.begin();

  while ((itv!=m_vCells.end())&&((*itv)!=pCCellRemove))
	itv++;

  if (itv==m_vCells.end())
		return false;
		
  if ((*itv)->removeLock()<1)
		{
		delete *itv;
		m_vCells.erase(itv);
		}

  return true;
}

ostream& operator << (ostream& os, CCellFactory* pcf)
{
	os << "CCellFactory number of Cells = " << pcf->m_vCells.size()<<endl;
	vector< CCell* >::const_iterator citv = pcf->m_vCells.begin();
	while (!(pcf->m_vCells.end()==citv))
		{
		(*citv)->writeType(os);
		os << ":"<<**citv <<"\t";
		citv++;
		}

	return os;
}


