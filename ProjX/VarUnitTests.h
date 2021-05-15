// VarUnitTests.h: interface for the CVarUnitTests class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARUNITTESTS_H__A774015E_F045_48BC_B26A_3ADFB717FF1C__INCLUDED_)
#define AFX_VARUNITTESTS_H__A774015E_F045_48BC_B26A_3ADFB717FF1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VarExp.h"
#include <fstream>
#include <iostream>

class CVarUnitTests  
{
public:
	CVarUnitTests();
	virtual ~CVarUnitTests();
	bool TestVarLibrary(ostream& os=cerr);

};

#endif // !defined(AFX_VARUNITTESTS_H__A774015E_F045_48BC_B26A_3ADFB717FF1C__INCLUDED_)
