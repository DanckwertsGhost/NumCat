// ARFileReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ARFileReader.h"
#include <atlbase.h>
_CSV_HANDLER_USING

bool readLine( istream& is, const vector< char >& vDelim, vector< string >& vLine )
{
	vLine.clear(); // to be sure
	long iLimit = 10;
	char sTemp[10];
	vector< char >::const_iterator cit;

	string sExp="";
	sTemp[1]=NULL;

	is.read(sTemp,1);

	while((!is.eof())&&(sTemp[0]!=LF))
	{
	cit =find(vDelim.begin(),vDelim.end(),sTemp[0]);
	if (cit!=vDelim.end()) // found it
		{
		vLine.push_back(sExp);
		sExp = "";
		}
		else
		sExp += sTemp;
	is.read(sTemp,1);
	}

	if (sExp.length()>0)
		vLine.push_back(sExp);

	return (!is.eof()); 
}

bool readLine( IARStream* pIStream, const vector< char >& vDelim, vector< string >& vLine )
{
	vLine.clear(); // to be sure
	CComBSTR cbLine;
	long iLimit = 10;
	char sTemp[10];
	string sLine;
	long iLength = 0;
	vector< char >::const_iterator cit;

	string sExp="";
	sTemp[1]=NULL;

	ASSERT2(pIStream); // shouldn't get this far - so draw attention nif debug
	if (!pIStream)	   // or handle quietly if this is a build version
		return false;

	enumARStream ess;
	HRESULT hr = pIStream->get_StreamState(&ess);

	if (FAILED(hr))
		return false;

	if ((ess!=streamReadline)&&(ess!=streamLoaded))
			{
			if (ess==streamEnd)
				ATLTRACE("Readline has got to streamEnd");
				else
				ATLTRACE("Failed to read stream - state = %d.\n",ess);
			return false;
			}
	
	hr = pIStream->readLine(&(cbLine.m_str));

	iLength = cbLine.Length();

	{
	USES_CONVERSION;
	sLine = OLE2A(cbLine.m_str);
	}

	long iT=0;

	ASSERT2(iLength==sLine.length());

	while(iT<iLength)
	{
		cit =find(vDelim.begin(),vDelim.end(),sLine[iT]);
		if (cit!=vDelim.end()) // found it
			{
			vLine.push_back(sExp);
			sExp = "";
			}
			else
			sExp += sLine[iT];
		iT++;
	}

	if (sExp.length()>0) // whats left
		vLine.push_back(sExp);

	return (vLine.size()>0); 
}
