// SymEdLine.h: interface for the CSymEdLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYMEDLINE_H__20BECFD7_88D7_401E_AD70_2982DAB6AE53__INCLUDED_)
#define AFX_SYMEDLINE_H__20BECFD7_88D7_401E_AD70_2982DAB6AE53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <fstream>

#pragma warning(disable:4786)

using namespace std;


class CSymEdLine  
{
public:
	bool hasFunction() const;
	CSymEdLine();
	CSymEdLine(const CSymEdLine& cEdLine );
	virtual ~CSymEdLine();
	virtual CSymEdLine& operator = (const CSymEdLine& cSEL);
	virtual bool operator == (const CSymEdLine& cSEL) const;
	virtual bool operator > (const CSymEdLine& cSEL) const;
	virtual bool operator < (const CSymEdLine& cSEL) const;
	inline const char* getNotes() const { return m_sNotes.c_str(); }
	inline const char* getOldRev() const { return m_sOldRev.c_str(); }
	inline const char* getFormula() const { return m_sFormula.c_str(); }
	inline long getErrorRef() const { return m_iErrorRef; }
	inline void setNotes(const char* sNotes){ m_sNotes = sNotes; }
	inline void setOldRev(const char* sOldRev){ m_sOldRev = sOldRev; }
	inline void setFormula(const char* sFormula){ m_sFormula = sFormula; }
	inline long getCurrentLine() const { return m_iCurLine; }
	inline long getOldLine() const { return m_iOldLine; }
	inline void setCurrentLine( long iCur ){ m_iCurLine = iCur; }
	inline void setOldLine( long iOld ){ m_iOldLine = iOld; }
	inline void setBothLine( long i ){ m_iCurLine = m_iOldLine = i; }
	inline void setErrorRef( long iRef ){ m_iErrorRef = iRef; m_bHasError = true; }
	inline bool hasError() const { return m_bHasError; }
	virtual void reset();
	ostream& write( ostream& os ) const;
	friend ostream& operator << (ostream& os,  const CSymEdLine& cSEL);


private:
	long m_iOldLine;
	long m_iCurLine;
	void copy(const CSymEdLine& cEdLine );
	string m_sNotes;
	string m_sFormula;
	string m_sOldRev;
	long m_iErrorRef; // this is the error ref to send back to the Error list window
	bool m_bHasError;

};

#endif // !defined(AFX_SYMEDLINE_H__20BECFD7_88D7_401E_AD70_2982DAB6AE53__INCLUDED_)
