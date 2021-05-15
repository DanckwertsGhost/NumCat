// ArrayImplied.h: interface for the CArrayImplied class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRAYIMPLIED_H__01F756BE_E8C8_4516_A551_10E2353AD748__INCLUDED_)
#define AFX_ARRAYIMPLIED_H__01F756BE_E8C8_4516_A551_10E2353AD748__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Array.h"


// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

class CArrayImplied : public CArray  
{
public:
	CArrayImplied(CToken* pt);
	CArrayImplied(const CArray& ra, CToken* pt);
	virtual ~CArrayImplied();

	virtual bool CatArray(CArray* pa); 

protected:
	virtual void out( ostream& os ) const;
	eTokArrayType m_eTATOrig;

};

#endif // !defined(AFX_ARRAYIMPLIED_H__01F756BE_E8C8_4516_A551_10E2353AD748__INCLUDED_)
