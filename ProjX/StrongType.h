// StrongType.h: interface for the CStrongType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRONGTYPE_H__F810B4AA_82D6_4FC3_948E_03FBCAE88DDC__INCLUDED_)
#define AFX_STRONGTYPE_H__F810B4AA_82D6_4FC3_948E_03FBCAE88DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include <iostream>
#include <math.h>
//#ifndef NDEBUG
#include "assert.h"
#include <ATLBASE.h>
//#endif

#pragma warning(disable:4786)

#ifndef ATLTRACE
#define ATLTRACE //
#endif

using namespace std;


// MACRO to ensure all math operators are handled correctly

#define OPERATOR_HANDLER(opX) \
	inline CStrongType<T> operator opX(const CStrongType<T>& cst) const \
				{ \
					CStrongType cstReturn; \
					cstReturn.m_dValue = m_dValue opX cst.m_dValue; \
					return cstReturn; \
				} \
\
	inline T operator opX(const double& dbl) const \
				{ \
					T dNewResult = m_dValue opX T(dbl); \
					return dNewResult; \
				} \
\
	inline T operator opX(const float& fbl) const \
				{ \
					return m_dValue opX T(fbl); \
				} \
\
	inline T operator opX(const long& lbl) const \
				{ \
					return m_dValue opX T(lbl); \
				} \
\
	inline T operator opX(const int& ibl) const \
				{ \
					return m_dValue opX T(ibl); \
				} \
\
	inline T operator opX(const short& sbl) const \
				{ \
					return m_dValue opX T(sbl); \
				} \
\
	inline T operator opX(const long double& ldbl) const \
				{ \
					return m_dValue opX T(ldbl); \
				} \
\
	CStrongType<T>& operator opX=(const CStrongType& cst) \
				{ \
				*this =  *this opX cst; \
				return *this; \
				} \
\
	CStrongType<T>& operator opX=(const double& dvl) \
				{ \
				*this =  *this opX dvl; \
				return *this; \
				} \
\
	CStrongType<T>& operator opX=(const float& fvl) \
				{ \
				*this =  *this opX fvl; \
				return *this; \
				} \
\
	CStrongType<T>& operator opX=(const long& lvl) \
				{ \
				*this =  *this opX lvl; \
				return *this; \
				} \
\
	CStrongType<T>& operator opX=(const int& ivl) \
				{ \
				*this =  *this opX ivl; \
				return *this; \
				} \
\
	CStrongType<T>& operator opX=(const short& svl) \
				{ \
				*this =  *this opX svl; \
				return *this; \
				} \
	CStrongType<T>& operator opX=(const long double& ldvl) \
				{ \
				*this =  *this opX ldvl; \
				return *this; \
				} \
	friend T operator opX(const double d, const CStrongType<T>& cst) \
				{ \
				return T(d) opX cst.m_dValue; \
				} \
	friend T operator opX(const float d, const CStrongType<T>& cst) \
				{ \
				return T(d) opX cst.m_dValue; \
				} \
	friend T operator opX(const long d, const CStrongType<T>& cst) \
				{ \
				return T(d) opX cst.m_dValue; \
				} \
	friend T operator opX(const int d, const CStrongType<T>& cst) \
				{ \
				return T(d) opX cst.m_dValue; \
				} \
	friend T operator opX(const short d, const CStrongType<T>& cst) \
				{ \
				return T(d) opX cst.m_dValue; \
				} \
	friend T operator opX(const unsigned long d, const CStrongType<T>& cst) \
				{ \
				return T(d) opX cst.m_dValue; \
				} \
	friend T operator opX(const long double d, const CStrongType<T>& cst) \
				{ \
				return T(d) opX cst.m_dValue; \
				}


#define OPERATOR_COMPARISON(opX) \
	inline bool operator opX (const double dv) const \
				{ \
				return (m_dValue opX T(dv)); \
				} \
\
	inline bool operator opX (const float dv) const \
				{ \
				return (m_dValue opX T(dv)); \
				} \
\
	inline bool operator opX (const long dv) const \
				{ \
				return (m_dValue opX T(dv)); \
				} \
\
	inline bool operator opX (const int dv) const \
				{ \
				return (m_dValue opX T(dv)); \
				} \
\
	inline bool operator opX (const short dv) const \
				{ \
				return (m_dValue opX T(dv)); \
				} \
\
	inline bool operator opX (const CStrongType<T> cst) const \
				{ \
				return (m_dValue opX cst.m_dValue); \
				} \
	friend bool operator opX (const double d, const CStrongType<T>& cst) \
				{ \
				return (T(d) opX cst.m_dValue); \
				} \
	friend bool operator opX (const float f, const CStrongType<T>& cst) \
				{ \
				return (T(f) opX cst.m_dValue); \
				} \
	friend bool operator opX (const long f, const CStrongType<T>& cst) \
				{ \
				return (T(f) opX cst.m_dValue); \
				} \
	friend bool operator opX (const int f, const CStrongType<T>& cst) \
				{ \
				return (T(f) opX cst.m_dValue); \
				} \
	friend bool operator opX (const short f, const CStrongType<T>& cst) \
				{ \
				return (T(f) opX cst.m_dValue); \
				} \
	friend bool operator opX (const unsigned long f, const CStrongType<T>& cst) \
				{ \
				return (T(f) opX cst.m_dValue); \
				}

#define CONSTRUCTOR_FOR_TYPE(fType) \
	CStrongType(const fType cul):m_dHigh(0),m_dLow(0),m_dValue(T(cul)),bLimited(false),m_eState(eCSTUnlimited){}



enum eCSTMode{ eCSTUnlimited, eCSTHighLimit, eCSTLowLimit, eCSTRangeLimit };

template <class T=double>
class CStrongType
{
public:
	CStrongType(T dHigh, T dLow):m_dHigh(dHigh),m_dLow(dLow),m_dValue(-1),bLimited(true),m_eState(eCSTRangeLimit) {}

	CStrongType():m_dHigh(0),m_dLow(0),m_dValue(-1),bLimited(false),m_eState(eCSTUnlimited) {}

	CStrongType(const CStrongType<T>& cst):m_dHigh(0),m_dLow(0),m_dValue(-1) {copy(cst);}

	CONSTRUCTOR_FOR_TYPE(long double)
	CONSTRUCTOR_FOR_TYPE(double)
	CONSTRUCTOR_FOR_TYPE(float)
	CONSTRUCTOR_FOR_TYPE(long)
	CONSTRUCTOR_FOR_TYPE(int)
	CONSTRUCTOR_FOR_TYPE(short)
	CONSTRUCTOR_FOR_TYPE(unsigned long)

//	CStrongType(const unsigned long cul):m_dHigh(0),m_dLow(0),m_dValue(T(cul)),bLimited(false),m_eState(eCSTUnlimited){}

   ~CStrongType(){}

	inline void copy(const CStrongType<T>& cst)
				{
					m_dHigh = cst.m_dHigh;
					m_dLow = cst.m_dLow;
					m_dValue = cst.m_dValue;
					bLimited = cst.bLimited;
					m_eState = cst.m_eState;
				}	

	void setType( eCSTMode eMode, T d1, T d2=0)
	{
		ATLTRACE("void setType( eCSTMode eMode, T d1, T d2=0)\n");
		switch(eMode)
		{
		case eCSTUnlimited:
			m_eState = eCSTUnlimited;
			break;
		case eCSTHighLimit:
			m_eState = eCSTHighLimit;
			m_dHigh = d1;
			if (m_dValue>m_dHigh)
				m_dValue = m_dHigh;
			break;
		case eCSTLowLimit:
			m_eState = eCSTLowLimit;
			m_dLow = d1;
			if (m_dValue<m_dLow)
				m_dValue=m_dLow;
			break;
		case eCSTRangeLimit:
			m_eState = eCSTRangeLimit;
			if (d2>d1)
				{
				m_dHigh = d1;
				m_dLow = d2;
				}
				else
				{
				m_dLow = d1;
				m_dHigh = d2;
				}
			if (m_dValue<m_dLow)
				m_dValue = m_dLow;
				else
				if (m_dValue>m_dHigh)
					m_dValue = m_dHigh;
			break;
		default:
			#ifndef NDEBUG
			assert(false); // stop here as this case is not handled
			#endif
			m_eState = eCSTUnlimited;
			break;
		}

	}

	eCSTMode getType() const { return m_eState; }

	// set the lower limit and change states accordingly - will set to high if range mismtach
	bool setLow( T d1 )
	{
		
	m_dLow = d1;	
	if (m_dValue<m_dLow)
			m_dValue=m_dLow;
		switch(m_eState)
		{
		case eCSTUnlimited:
			m_eState=eCSTLowLimit;
			break;
		case eCSTHighLimit:
			m_eState=eCSTRangeLimit;
			break;			
		case eCSTLowLimit:
			break;
		default:
			m_eState=eCSTLowLimit;
			ATLTRACE("Unrecognised m_eState in setLow( T d1 )\n");
			return false;
			break;
		}

	if (m_dLow>m_dHigh)
		{
		m_dValue=m_dHigh=m_dLow;
		}

	return true;

	}

	// set the lower limit and change states accordingly - will set to high if range mismtach
	bool setHigh( T d1 )
	{
		
	m_dHigh = d1;	
	if (m_dValue>m_dHigh)
			m_dValue=m_dHigh;
		switch(m_eState)
		{
		case eCSTUnlimited:
			m_eState=eCSTHighLimit;
			break;
		case eCSTLowLimit:
			m_eState=eCSTRangeLimit;
			break;			
		case eCSTHighLimit:
			break;
		default:
			m_eState=eCSTHighLimit;
			ATLTRACE("Unrecognised m_eState in setHigh( T d1 )\n");
			return false;
			break;
		}

	if (m_dLow>m_dHigh)
		{
		m_dValue=m_dLow=m_dHigh;
		}

	return true;

	}

	OPERATOR_HANDLER(+)
	OPERATOR_HANDLER(-)
	OPERATOR_HANDLER(*)
	OPERATOR_HANDLER(/)

    OPERATOR_COMPARISON(>)
    OPERATOR_COMPARISON(<)
    OPERATOR_COMPARISON(>=)
    OPERATOR_COMPARISON(<=)
    OPERATOR_COMPARISON(==)
    OPERATOR_COMPARISON(!=)

	inline bool operator !()
	{
		return (!m_dValue);
	}

	CStrongType<T>& operator =(const CStrongType<T>& cst)
				{

					switch(m_eState) 
					{ 
						case eCSTUnlimited: 
							m_dValue = cst.m_dValue; 
							return 	*this; 
						case eCSTHighLimit: 
							(cst.m_dValue>m_dHigh?m_dValue=m_dHigh:m_dValue=cst.m_dValue); 
							return *this; 
						case eCSTLowLimit: 
							(cst.m_dValue<m_dLow?m_dValue=m_dLow:m_dValue=cst.m_dValue); 
							return *this; 
						case eCSTRangeLimit: 
							if (cst.m_dValue>=m_dLow) 
								{ 
								if (cst.m_dValue<=m_dHigh) 
									m_dValue = cst.m_dValue; 
									else 
									m_dValue = m_dHigh; 
								} 
								else 
								m_dValue = m_dLow; 
							return *this; 
						default: 
							break;
					}
					m_dValue=-99;
					return *this; 

				}

	CStrongType<T>& operator =(const int& iNV)
				{
					*this=double(iNV);
					return *this;
				}
	CStrongType<T>& operator =(const long& lNV)
				{
					*this=double(lNV);
					return *this;
				}
	CStrongType<T>& operator =(const float& fNV)
				{
					*this=double(fNV);
					return *this;
				}

	CStrongType<T>& operator =(const unsigned long& fNV)
				{
					*this=double(fNV);
					return *this;
				}

	CStrongType<T>& operator =(const long double& fNV)
				{
					*this=double(fNV);
					return *this;
				}

	inline CStrongType<T>& operator =(const double& dNV)
				{

					switch(m_eState) 
					{ 
						case eCSTUnlimited: 
							m_dValue = T(dNV); 
							return 	*this; 
						case eCSTHighLimit: 
							(dNV>m_dHigh?m_dValue=m_dHigh:m_dValue=T(dNV)); 
							return *this; 
						case eCSTLowLimit: 
							(dNV<m_dLow?m_dValue=m_dLow:m_dValue=T(dNV)); 
							return *this; 
						case eCSTRangeLimit: 
							if (dNV>=m_dLow) 
								{ 
								if (dNV<=m_dHigh) 
									m_dValue = T(dNV); 
									else 
									m_dValue = m_dHigh; 
								} 
								else 
								m_dValue = m_dLow; 
							return *this; 
						default: 
							break;
					}
					m_dValue=-99;
					return *this; 

				}

	inline operator long double() const
				{
					return long double(m_dValue);
				}

	inline operator double() const
				{
					return double(m_dValue);
				}

	inline operator float() const
				{
					return float(m_dValue);
				}

	inline operator long() const
				{
					return long(m_dValue);
				}

	inline operator int() const
				{
					return int(m_dValue);
				}

	inline operator short() const
				{
					return short(m_dValue);
				}

	friend ostream& operator << (ostream& os, const CStrongType<T>& cst)
				{
					cst.write(os);
					return os;
				}

	friend istream& operator >> (istream& is, CStrongType<T>& cst)
				{
					T valueIn;
					is >> valueIn;
					cst = valueIn; // so if cst has restrictions they are respected
					return is;
				}

	void writeAll( ostream& os ) const
		{
		write(os);
		os <<" [";
		switch(m_eState)
			{
			case eCSTUnlimited:
				os << "eCSTUnlimited";
				break;
			case eCSTHighLimit:
				os << "eCSTHighLimit";
				break;
			case eCSTLowLimit:
				os << "eCSTLowLimit";
				break;
			case eCSTRangeLimit:
				os << "eCSTRangeLimit";
				break;
			default:
				ASSERT2(false);
				break;
			}
		os <<"]";
		}

protected:
	void write( ostream& os ) const{ os << double(*this); }

	T m_dHigh;
	T m_dLow;
	T m_dValue;

	eCSTMode m_eState;
	bool bLimited;
};

#endif // !defined(AFX_STRONGTYPE_H__F810B4AA_82D6_4FC3_948E_03FBCAE88DDC__INCLUDED_)
