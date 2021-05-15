// EvStop.cpp: implementation of the CEvStop class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvStop.h"
#include "Symlix/ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvStop::CEvStop(long iLeft, long iRight,vector<CToken*>& vecCT,ostream& oserr):m_refvecCT(vecCT),m_cvr(NULL),
m_iLeft(iLeft),m_iRight(iRight),m_oserr(oserr)
{
// some defensive checks
ASSERT2(m_iRight>m_iLeft);
ASSERT2(m_iLeft>=0);
ASSERT2(m_refvecCT.size()>=m_iRight);
m_eState = cevUninitiated;
}

CEvStop::~CEvStop()
{

}

bool CEvStop::setupEvent(list<CEquation*>* pvecpEquations)
{
	CVarClassFactory* pvcf = CVarClassFactory::instance();
	m_cvr = CEquation::createExpression(m_iLeft,m_iRight,m_refvecCT,m_oserr,pvecpEquations);
	if (m_cvr)
		m_eState = cevInitiated;

 return (m_eState==cevInitiated); 
}


eEventSignal CEvStop::trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast )
{
	if (willTrigger(pvecVars))
		return ceesEndSimulation;

	return ceesNoTrig;
}


bool CEvStop::willTrigger( vector< variable >* pvecVars )
{
	if (m_eState!=cevInitiated)
			return false;
	ASSERT2(m_cvr); // as state indicates this must be the case
#ifdef EXTRADEBUG
	cout << "CEvStop = " << m_cvr->getValue(*pvecVars) <<endl;
#endif
	return (m_cvr->getValue(*pvecVars)>0);
}

bool CEvStop::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{
	bool bResult = true;

	ASSERT2(iLeft<iRight);
	if (iLeft>=iRight)
			return false;

	if (vExpLine.size()<iRight)
			{
			if (vExpLine.size()>0)
				{
				SYMERRORTOK("Format error with Stop Event",errSyntax,vExpLine[0]);
				osErrReport <<"<Error*> format error with Stop Event on line "<<vExpLine[0]->getLine()<<" ."<<endl;
				}
				else
				{
				SYMERRORLITE("Format error with Stop Event",errSyntax);
				osErrReport <<"<Error*> format error with Stop Event on line."<<endl;
				}
			return false;
			}

	if ((iRight-iLeft)<3)
			{
			osErrReport << "<Error*> Event does not have enough information";
			if (vExpLine.size()>0)
				{
				osErrReport <<" on line "<< vExpLine[0]->getLine();
				SYMERRORTOK("Format error with Stop Event",errSyntax,vExpLine[0]);
				}
				else
				SYMERRORLITE("Format error with Stop Event",errInternal);
			osErrReport <<".\n";
			return false;
			}

	bResult = CEquation::IsWellFormedExpression(iLeft,iRight,vExpLine,osErrReport);

	// the left most term MUST be a variable // or derivative
	if (!vExpLine[iLeft]->IsOfTypeVariable())/*&&(!vExpLine[iLeft]->IsOfType(ctDerivative)))*/
			{
			osErrReport << "<Error*> The left hand side must be a variable. See '";
			osErrReport << vExpLine[iLeft]->getString().c_str() <<"' in line "<<vExpLine[iLeft]->getLine()<<".\n";
			SYMERRORTOK("The left hand side must be a variable ",errSyntax,vExpLine[iLeft]);
			bResult = false;
			}
	
	if ((bResult)&&((vExpLine[1+iLeft]->getString().compare(g_GT)!=0)&&(vExpLine[1+iLeft]->getString().compare(g_LT)!=0)))
			{
			osErrReport << "<Error*> Event must be either '"<<g_GT<<"' or '"<<g_LT<<"'\n";
			osErrReport <<"\ton line "<< vExpLine[0]->getLine()<<endl;
			SYMERRORTOK("Event must be greater than or less than",errSyntax,vExpLine[iLeft+1]);
			bResult = false;
			}
	return bResult;
}







