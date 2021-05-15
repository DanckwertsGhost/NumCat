/************************************************************************
  			cnumcell.cpp - Copyright tim

Here you can write a license for your code, some comments or any other
information you want to have in your generated code. To to this simply
configure the "headings" directory in uml to point to a directory
where you have your heading files.

or you can just replace the contents of this file with your own.
If you want to do this, this file is located at

/usr/share/apps/umbrello/headings/heading.cpp

-->Code Generators searches for heading files based on the file extension
   i.e. it will look for a file name ending in ".h" to include in C++ header
   files, and for a file name ending in ".java" to include in all generated
   java code.
   If you name the file "heading.<extension>", Code Generator will always
   choose this file even if there are other files with the same extension in the
   directory. If you name the file something else, it must be the only one with that
   extension in the directory to guarantee that Code Generator will choose it.

you can use variables in your heading files which are replaced at generation
time. possible variables are : author, date, time, filename and filepath.
just write %variable_name%

This file was generated on Fri Oct 7 2005 at 11:24:06
The original location of this file is 
**************************************************************************/
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <algorithm>

#include "NumCell.h"
_CSV_HANDLER_USING
// Constructors/Destructors
// Methods
 CNumCell::CNumCell ( const char* sData):CCell(),m_sValue(sData),m_vNumChars()
{
	string sNumChars(CSV_NUMCELL_ALLOWED_CHARS);
	char sTemp[32]; // reduced from 100 to save memory

	for(long iL=0;iL<sNumChars.length();iL++)
		m_vNumChars.push_back(sNumChars[iL]);

	m_ectType = ectNum;
	m_vValue = getNumber(sData);
	m_sValue = _gcvt(m_vValue,16,sTemp);

}

csvVariable CNumCell::getNumber( const char* sNum ) const
{
//	static char sBuff[255];
	csvVariable vReturn;
	vector< char >::const_iterator itEnd;
	long iLen = strlen(sNum);
	long iCount;

	itEnd = m_vNumChars.end();

	if (iLen>0)
		{
		for(iCount=0;iCount<iLen;iCount++)			
			if (std::find(m_vNumChars.begin(),m_vNumChars.end(),sNum[iCount])==itEnd)
				return CSV_NOT_DEFINED;

		vReturn = atof(sNum);
//        Decided to live with this case - will convert to numbers 
//			if (strcmp(sNum,_gcvt(vReturn,10,sBuff))!=0)
//			vReturn = 0;
		}	
		else
		vReturn = CSV_NOT_DEFINED;
	

	return vReturn;
}



///////////////////////////////////////////////////////////
// Function name	: CNumCell::find
// Description	    : check if expression equals number
// Return type		: bool 
// Argument         : const char* sExp
///////////////////////////////////////////////////////////
bool CNumCell::find( const char* sExp)
{
	csvVariable vSearch = getNumber(sExp);

	if (m_vValue==CSV_NOT_DEFINED) // to cover the unlikely case
		return (m_vValue==vSearch);

	return ((vSearch!=CSV_NOT_DEFINED)&&(m_vValue==vSearch));  

}

const char*  CNumCell::getString () const
{
	return m_sValue.c_str();
}

csvVariable  CNumCell::getNumber() const
{
	return m_vValue;
}


bool CNumCell::greaterThan(CCell* pCell) const
{
	if (!pCell->isOfType(ectNum))
		return greaterType(pCell->getType());

	return (m_vValue>pCell->getNumber());
}
