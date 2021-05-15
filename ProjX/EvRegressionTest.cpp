// EvRegressionTest.cpp: implementation of the CEvRegressionTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EvRegressionTest.h"
#include <math.h>
#include "Symlix/ErrorFactory.h"

#define ERROR_UNCHECKED_FORMAT "Unspecified fault in regression test event format"
#define SET_TOLERANCE 1E-5
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvRegressionTest::CEvRegressionTest( long iLeft, long iRight, vector< CToken* >& vecLine,ostream& oserr):
CEvRecorder(),m_vecCheckVal(),m_bFired(false)
{

//LOOK CLOSELY AT COPYING RECORDER EVENT - maybe should inherit
	ASSERT2(check(iLeft,iRight,vecLine,oserr));
	long iCount = iLeft;
	long iLimit = (iRight<vecLine.size()?iRight:vecLine.size());
	bool bValueNext = false;
		
	while ((iCount!=iLimit)&&(vecLine[iCount]->getString().compare(g_Append)!=0))
	{
		if (bValueNext)
			{
				if (vecLine[iCount]->IsOfType(ctNumber))
					{
					m_vecCheckVal.push_back(vecLine[iCount]->getNumber());
					bValueNext = false;
					}
			}
			else
			{
				if (vecLine[iCount]->IsOfTypeVariable())
					{
					m_vecRepTok.push_back(vecLine[iCount]);
					bValueNext = true;
					}
			}
	
		iCount++;
	}	
	
	
	m_ivecSizes = m_vecRepTok.size();
	m_vecResults.resize(m_ivecSizes,0);
		
	ASSERT2( m_vecRepTok.size()==m_vecCheckVal.size());

	iCount = getOneToRightOf(g_Quote,vecLine,iCount,iLimit);

	if ((iCount!=iLimit)&&(checkValidFileName(vecLine[iCount]->getString().c_str())))
			{
				m_sFile = vecLine[iCount]->getString();
			}		
			else
			{
			m_eState = cevError;
			m_sError = ERROR_UNCHECKED_FORMAT;
			}		

	iCount = getOneToRightOf(g_At,vecLine,iCount,iLimit);

	if ((iCount!=iLimit)&&(vecLine[iCount]->IsOfTypeVariable()))
			{
			 m_pctTrig = vecLine[iCount]->getRootTokenPt();
			}
			else
			{
			m_eState = cevError;
			m_sError = ERROR_UNCHECKED_FORMAT;
			}		

	iCount = getOneToRightOf(g_Eq,vecLine,iCount,iLimit);

	if ((iCount!=iLimit)&&(vecLine[iCount]->IsOfType(ctNumber)))
			{
			m_vStep = vecLine[iCount]->getNumber();
			}
			else
			{
			m_eState = cevError;
			m_sError = ERROR_UNCHECKED_FORMAT;
			}		

	if ((m_sFile.length()>0)&&(m_pctTrig)&&(m_vStep>0))
		{
		m_ofs.open(m_sFile.c_str(),ios::out|ios::app);
		if (m_ofs.is_open())
			m_eState=cevUninitiated;
			else
			{
			m_sError = "Unable to open file "+m_sFile;
			m_ofs.close();
			}
		}

}

CEvRegressionTest::~CEvRegressionTest()
{
	if (m_ofs.is_open())
		m_ofs.close();
}

bool CEvRegressionTest::check(long iLeft, long iRight, vector<CToken*>& vExpLine, ostream& osErrReport )
{

	vector< CToken* >::iterator itpCT;
	// itpCTRight is fouud this way as I'm not sure &vExp[iRight] would produce the same result in all conditions
	vector< CToken* >::const_iterator itpCTRight = getRightWithoutComments(iLeft,iRight,vExpLine);
	bool bResult = true;
	bool bDelim = true;
	bool bValue = true;

	itpCT = &vExpLine[iLeft];

	while((itpCT!=itpCTRight)&&(((*itpCT)->getStringRef().compare(g_Append)!=0)&&((*itpCT)->getStringRef().compare(g_Quote)!=0)))
	{
		if (bDelim)
			{
			if (bValue)
					{
					if ((*itpCT)->IsOfTypeVariable())
						{
						bDelim=false; // should be a ctDelim next
						bValue=false; // and a number should follow that
						}
						else
						{
						bResult=false; // fail this check
						osErrReport << "<Error*> Event in not properly formed - see "<<(*itpCT)->getStringRef().c_str()<< " on line "<< (*itpCT)->getLine()<<endl;
						SYMERRORTOK("Event in not properly formed",errSyntax,(*itpCT));
						}
					}
					else
					{
					if ((*itpCT)->IsOfType(ctNumber))
						{
						bDelim=false; // should be a ctDelim next
						bValue=true; // and a variable may follow that
						}
						else
						{
						bResult=false; // fail this check
						osErrReport << "<Error*> Event in not properly formed - see "<<(*itpCT)->getStringRef().c_str()<< " on line "<< (*itpCT)->getLine()<<endl;
						SYMERRORTOK("Event in not properly formed - was expecting a number",errSyntax,(*itpCT));
						}
					}			
			}
			else
			{
			if ((*itpCT)->IsOfType(ctDelim))
				bDelim=true;
				else
				{
				bResult=false;
				osErrReport << "<Error*> Event in not properly formed - see "<<(*itpCT)->getStringRef().c_str()<< " on line "<< (*itpCT)->getLine()<<endl;
				SYMERRORTOK("Event in not properly formed",errSyntax,(*itpCT));
				}

			}
		itpCT++;
	}

	if (!bValue)
		{
		osErrReport << "<Error*> Each variable must have a corresponding value, see line "<<(*itpCT)->getLine()<<endl;
		SYMERRORTOK("Each variable must have a corresponding value",errSyntax,(*itpCT));
		bResult=false;
		}

	if (itpCT==itpCTRight)
		{
		osErrReport << "<Error*> Part of event statement is missing on line "<<vExpLine[iLeft]->getLine()<<endl;
		SYMERRORTOK("Part of event statement is missing",errSyntax,vExpLine[iLeft]);
		bResult=false;
		}

	if (!bResult)
			return bResult;

	if ((*itpCT)->getString().compare(g_Append)==0)
			itpCT++;

	if (itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,vExpLine[iLeft]);
			osErrReport << "<Error*> Part of event statement is missing on line "<<vExpLine[iLeft]->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_Quote)==0))
			{
			osErrReport << "<Error*> Stream name not in quotes on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Stream name not in quotes",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!(*itpCT)->IsOfType(ctName))
			{
			osErrReport << "<Error*> Name of regression stream has an error on "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Name of regression stream has an error",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_Quote)==0))
			{
			osErrReport << "<Error*> Stream name not in quotes on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Stream name not in quotes",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<", hint: was expecting '@' here."<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_At)==0))
			{
			osErrReport << "<Error*> @ was expected after quotes on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2(g_At," was expected after quotes",errSyntax,(*itpCT));
			return false;
			}


	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<", hint: was expecting a variable here after "<<g_At<<"."<<endl;
			return false;
			}

	if (!(*itpCT)->IsOfTypeVariable())
			{
			osErrReport << "<Error*> Variable expected rather than '"<< (*itpCT)->getString().c_str() <<"' on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Variable expected",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<", hint: was expecting a variable here after "<<g_At<<"."<<endl;
			return false;
			}

	if (!((*itpCT)->getString().compare(g_Eq)==0))
			{
			osErrReport << "<Error*> = was expected rather than '"<< (*itpCT)->getString().c_str() <<"'after variable on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK2(g_Eq," was expected here",errSyntax,(*itpCT));
			return false;
			}


	if (++itpCT==itpCTRight)
			{
			SYMERRORTOK("Part of event statement is missing",errSyntax,(*--itpCT));
			osErrReport << "<Error*> Part of event statement is missing on line "<<(*itpCT)->getLine()<<", hint: was expecting a variable here after "<<g_At<<"."<<endl;
			return false;
			}

	if (!(*itpCT)->IsOfType(ctNumber))
			{
			osErrReport << "<Error*> Number expected rather than '"<< (*itpCT)->getString().c_str() <<"' on line "<<(*itpCT)->getLine()<<endl;
			SYMERRORTOK("Number expected",errSyntax,(*itpCT));
			return false;
			}

	if (++itpCT!=itpCTRight)
			{
			SYMERRORTOK("Unexpected statments",errSyntax,(*itpCT));
			osErrReport << "<Error*> Unexpected statments on line "<<(*itpCT)->getLine()<<endl;
			return false;
			}


	return bResult;
}

eEventSignal CEvRegressionTest::trigger( vector< variable >* pvecVars, vector< variable >* pvecVarsLast  )
{

	eEventSignal eesResult = CEvRecorder::trigCalc(pvecVars,pvecVarsLast);

	if (eesResult==ceesTrig)
		{
		bool bPass = true;
		for(long iCount=0;iCount<m_ivecSizes;iCount++)
			{
			if (!AreClose(m_vecResults[iCount],m_vecCheckVal[iCount]))
				{
				bPass = false;
//				m_ofs << float(fabs(float(m_vecResults[iCount]) - float(m_vecCheckVal[iCount]))/fabs(m_vecResults[iCount]))<<"@";
				m_ofs << float(m_vecResults[iCount]) <<":"<<float(m_vecCheckVal[iCount])<<" , ";
				}
			}
		if (bPass)
			m_ofs << "<Passed>\n";
			else
			m_ofs << "<Failed>\n";
		m_ofs.flush();
		m_bFired = true;
		}
	return eesResult;
}


bool CEvRegressionTest::willTrigger( vector< variable >* pvecVars )
{
	if (m_bFired) // so only fires once !
		return false;

	return CEvRecorder::willTrigger(pvecVars);
}

bool CEvRegressionTest::AreClose( float f1, float f2)
{

	if (f1!=0)
		return (fabs(f1-f2)/f1<SET_TOLERANCE?true:false);
		else
		if (f2!=0)
			return (fabs(f2-f1)/f2<SET_TOLERANCE?true:false);
	return (f1==f2?true:false);
}
