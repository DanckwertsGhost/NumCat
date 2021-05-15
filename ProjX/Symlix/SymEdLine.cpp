// SymEdLine.cpp: implementation of the CSymEdLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SymEdLine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSymEdLine::CSymEdLine():m_iCurLine(NOT_DEFINED),m_iOldLine(NOT_DEFINED),m_sFormula(""),m_sNotes(""),m_sOldRev(""),m_bHasError(false),m_iErrorRef(NOT_DEFINED)
{

}

CSymEdLine::CSymEdLine(const CSymEdLine& cEdLine )
{
	copy(cEdLine);

}


CSymEdLine::~CSymEdLine()
{

}

void CSymEdLine::copy(const CSymEdLine& cEdLine )
{
	m_iCurLine = cEdLine.m_iCurLine;
	m_iOldLine = cEdLine.m_iOldLine;
	m_sFormula = cEdLine.m_sFormula;
	m_sNotes = cEdLine.m_sNotes;
	m_sOldRev = cEdLine.m_sOldRev;
	m_bHasError = cEdLine.m_bHasError;
	m_iErrorRef = cEdLine.m_iErrorRef;

}

CSymEdLine& CSymEdLine::operator = (const CSymEdLine& cSEL)
{
	copy(cSEL);
	return *this;
}

bool CSymEdLine::operator == (const CSymEdLine& cSEL) const
{
	if (((*this)>cSEL)||((*this)<cSEL))
		return false;
	return true;
}

bool CSymEdLine::operator > (const CSymEdLine& cSEL) const
{
	return (cSEL<(*this));
}

bool CSymEdLine::operator < (const CSymEdLine& cSEL) const
{
    return (m_iOldLine < cSEL.m_iOldLine);
}

ostream& CSymEdLine::write( ostream& os ) const
{
	os << "[" << m_iCurLine << "]  - old line = " << m_iOldLine << "\n";
	os << "\tFormula = '" << m_sFormula.c_str() << "'\n";
	os << "\tNotes = '" << m_sNotes.c_str() << "'\n";
	os << "\tOldRev = '" << m_sOldRev.c_str() << "'\n";
	if (m_bHasError)
			os << "\tHas error, ref no = "<<m_iErrorRef<<"\n";

	return os;
}

ostream& operator << (ostream& os, const CSymEdLine& cSEL)
{ return cSEL.write(os);}



bool CSymEdLine::hasFunction() const
{
	return (m_sFormula.size()>0);
}


///////////////////////////////////////////////////////////
// Function name	: CSymEdLine::reset
// Description	    : Get ride of all other data on this object
// Return type		: void 
///////////////////////////////////////////////////////////
void CSymEdLine::reset()
{
	m_iOldLine = NOT_DEFINED;
	m_sFormula = m_sNotes = "";

}
