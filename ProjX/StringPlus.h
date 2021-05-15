// StringPlus.h: interface for the CStringPlus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGPLUS_H__44DE5B60_C198_4DB6_B84C_1CAC89F2DE8B__INCLUDED_)
#define AFX_STRINGPLUS_H__44DE5B60_C198_4DB6_B84C_1CAC89F2DE8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

class CStringPlus : public string
{
public:
	virtual string getBetweenSqrBrackets() const;
	virtual string getSubsIntoSqrBrackets(const char* sInsert) const;
#ifdef UNITTESTS
	static bool runUnitTests();
#endif
	CStringPlus();
	CStringPlus(const CStringPlus& csh);
	CStringPlus(const string& s);
	CStringPlus(const char* sIn );
	virtual ~CStringPlus(){}

	virtual bool isNumber();
	virtual bool isIterative() const;
	virtual double getNumber(); // returns NOT_FOUND is not number
	virtual string getLessDerivative() const;
	virtual string withBracketedIndex(const long iIndex) const;
	virtual string withDerivBracketedIndex(const long iIndex) const;
	virtual string getLessIterative() const;
protected:
	virtual bool isExponent() const;
	virtual long countOccurances(const char* sItem) const;
	virtual double substringNumber(long lFrom, long lTo);

	long m_lMinus1,m_lMinus2,m_lMinusCount; // first minus and second - if exponent
	long m_lPoint,m_lPointCount; // where the decimal point it
	long m_lExp,m_lExpCount;	// where the exponent is
	bool bRequestOnNumber; // this is true when number request is made - and helper functions check for it.
	static string m_sEmpty;	
};


#endif // !defined(AFX_STRINGPLUS_H__44DE5B60_C198_4DB6_B84C_1CAC89F2DE8B__INCLUDED_)
