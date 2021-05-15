// VarExp.cpp: implementation of the CVarExp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemLeakRecord.h"
#include "VarExp.h"
#include "VarRoot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
CVarExp::CVarExp()
{

}

CVarExp::~CVarExp()
{

}*/

#include <limits>

xt_value CVarExpDiv::getNewValue( const vectorValues& vec )
{
 xt_value xtRight = m_pvrRight->getValue(vec);
 
#ifdef EXTRADEBUG
	cout <<"CVarExpDiv::getNewValue m_pvrLeft->getValue(vec) / m_pvrRight->getValue(vec);"<<endl;
	cout <<"  m_pvrLeft->getValue(vec) = "<<m_pvrLeft->getValue(vec)<<"\n";
	cout <<"  m_pvrRight->getValue(vec) = "<<m_pvrRight->getValue(vec)<<endl;
	if (xtRight==0)
			cout <<"About to throw exception"<<endl;	
    cout <<"Limits "<<numeric_limits<xt_value>::signaling_NaN()<<endl;
	if (xtRight==numeric_limits<xt_value>::signaling_NaN())
			cout<<"Is equal to NaN "<<xtRight<<"\t=\t"<<numeric_limits<xt_value>::signaling_NaN()<<endl;
#endif 
 
  if (xtRight==numeric_limits<xt_value>::signaling_NaN())
		throw newtrack CExceptionCVarRoot("Out of bounds numerical value ",m_pvrLeft->getValue(vec),numeric_limits<xt_value>::signaling_NaN());


 if (xtRight==0)
		throw newtrack CExceptionCVarRoot("Attempted divide by zero ",m_pvrLeft->getValue(vec),xtRight);	
 
 return m_pvrLeft->getValue(vec) / m_pvrRight->getValue(vec); 
 
}

#ifdef DEBUGVARS
xt_value CVarExpMinus::getNewValue( const vectorValues& vec )
{
 return m_pvrLeft->getValue(vec) - m_pvrRight->getValue(vec); 
 
}
#endif

#ifdef DEBUGVARS
xt_value CVarExpGT::getNewValue( const vectorValues& vec )
{
  xt_value xtResult;
  xt_value xtLHV = m_pvrLeft->getValue(vec);
  xt_value xtRHV = m_pvrRight->getValue(vec);

#ifdef EXTRADEBUG
  //cout <<"CVarExpGT left= "<<xtLHV<<" and Right= "<<xtRHV<<" giving > "<<(xtLHV > xtRHV)<<endl;
#endif
	ATLTRACE(" %E > %E = ",xtLHV,xtRHV);
	if (xtLHV>xtRHV)
			{
			ATLTRACE("true\n");
			ATLTRACE("Error = %E\n",(xtLHV-xtRHV)/xtLHV);
			}
		else
			ATLTRACE("false\n");

	xtResult =  (xtLHV > xtRHV);
/*	if (xtResult>0)
		{
//		problems here
		ATLTRACE("fabs((xtLHV-xtRHV)/xtLHV) = %E\n",fabs((xtLHV-xtRHV)/xtLHV));
		if ((fabs((xtLHV-xtRHV)/xtLHV))<1E-8)
			xtResult=0;
		}*/

	return xtResult; 
}
#endif