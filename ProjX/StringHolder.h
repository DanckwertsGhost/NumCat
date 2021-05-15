// StringHolder.h: interface for the CStringHolder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGHOLDER_H__3CABBDEA_EBF2_43F1_8216_A230DD4B8590__INCLUDED_)
#define AFX_STRINGHOLDER_H__3CABBDEA_EBF2_43F1_8216_A230DD4B8590__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <fstream>

#pragma warning(disable:4786)


using namespace std;

class CStringHolder  
{
public:
	CStringHolder();
	CStringHolder(const CStringHolder& csh);
	CStringHolder(const string& str);
	CStringHolder(const char* sIn );
	virtual ~CStringHolder();

	const char* c_str() const;
	void getString(string& str) const { str=m_string;}
	bool operator == (const CStringHolder& csh ) const;
	inline bool operator == (const char* s ) const { return (m_string.compare(s)==0); }
	inline bool operator != (const char* s ) const { return (m_string.compare(s)!=0); }
	bool operator()(const CStringHolder&csh1, const CStringHolder& csh2) const {return csh1 < csh2;} //needed for std::set
	bool operator < (const CStringHolder& csh ) const;
	CStringHolder& operator = (const CStringHolder& csh ){ Copy(csh); return *this; }
	inline long len() const{ return m_string.length();}

	friend ostream& operator <<( ostream& os, const CStringHolder& csh );

private:
	void Init(); // in case any init functions are required latter.
	string m_string;
	void Copy( const CStringHolder& csh );

};

struct ltSTRhld
{
	bool operator()(const CStringHolder& c1, const CStringHolder& c2 ) const
		{
		return c1 < c2;
		}
};

#endif // !defined(AFX_STRINGHOLDER_H__3CABBDEA_EBF2_43F1_8216_A230DD4B8590__INCLUDED_)
