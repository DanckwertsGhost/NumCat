// SolOneStep.cpp: implementation of the CSolOneStep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SolOneStep.h"
#include "Symlix/ErrorFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSolOneStep::CSolOneStep():CSolver(),m_iSize(NOT_DEFINED)
{
	m_tstep = 1;
	m_tmax = 1; // not really necessary
	m_bState=true; // as defining with default values
}


CSolOneStep::~CSolOneStep()
{

}

xt_value CSolOneStep::step(vectorValues* pvecValues,vectorConstrainedValues* pvecConST )
{
	long iT;

#ifndef NDEBUG // clearly don't want to do this in release solve mode
	assert(m_iSize!=NOT_DEFINED);
	assert(m_pIModelSim);
	assert(m_pIModelSim->isReady());
#endif


	// back up start position for variables
//	copy(&(*pvecValues)[m_iVarStart],&(*pvecValues)[m_iVarEnd],m_startpos.begin());
	
	m_pIModelSim->updateValue(pvecValues);

	if (m_iSize>0) // usually this should not be the case
	{
		(*pvecValues)[m_iIndVar] += m_tstep/2;
		for(iT=0;iT<m_iSize;iT++)
			(*pvecValues)[m_iVarStart+iT] += m_tstep*(*pvecValues)[m_iDerivStart+iT]; // this is a very bad aprox - only here to cover the users mistake
		(*pvecValues)[m_iIndVar] += m_tstep/2;
		m_pIModelSim->updateValue(pvecValues);

		// Note it is only necessary to enforce pvecConST strong types here as the RHD of the key expressions are already constrained
		// else where. Possibly this code should be move to a common implementation level to avoid replicatio - or at least the constraint part of it.
		// not decided yet.

		for(iT=0;iT<m_iSize;iT++)
			(*pvecValues)[m_iVarStart+iT] = (*pvecConST)[m_iVarStart+iT] = (*pvecValues)[m_iVarStart+iT];		
	}
	else
	(*pvecValues)[m_iIndVar] += m_tstep;



	return (*pvecValues)[m_iIndVar];
}


///////////////////////////////////////////////////////////
// Function name	: CSolOneStep::setup
// Description	    : 
// Return type		: bool 
// Argument         : CIModelSim* pims
///////////////////////////////////////////////////////////
bool CSolOneStep::setup(CIModelSim* pims)
{

#ifndef NDEBUG
	assert(pims);
#endif

	if ((!pims)||(!pims->isReady()))
			return false;

	pims->getModelIndexs(m_iIndVar,m_iDerivStart,m_iDerivEnd,m_iVarStart,m_iVarEnd);
#ifndef NDEBUG
	assert((m_iDerivEnd-m_iDerivStart)==(m_iVarEnd-m_iVarStart));
#endif
	if ((m_iDerivEnd-m_iDerivStart)!=(m_iVarEnd-m_iVarStart))
				return false;
	m_iSize = m_iVarEnd-m_iVarStart;

	if (m_iSize)
		SYMERRORLITE("Derivatives found with unsuitable solver - results will be poor",errWarning); 

	// let get ready for solving

	m_pIModelSim=pims;

	return true;
}
