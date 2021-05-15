// ErrorFactory.h: interface for the CErrorFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERRORFACTORY_H__EBB041F2_694D_4DEE_97AA_6128676F24FD__INCLUDED_)
#define AFX_ERRORFACTORY_H__EBB041F2_694D_4DEE_97AA_6128676F24FD__INCLUDED_

#include <process.h>

#include "SymlixErrorRun.h"
#include "..\Token.h"
#include "..\CritCheck.h"



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

class CErrorFactory  
{

public:
	void clearErrors();
  void addError( const char* sDescription, enumNumCatErrorCode eLevel,  const char* sSource, long iLine, long iX, const char* sCodeSource=NULL, long iCodeLine=NOT_DEFINED );
  void addError( const char* sDescription, enumNumCatErrorCode eLevel,  const CToken& cTok, const char* sCodeSource=NULL, long iCodeLine=NOT_DEFINED );
  static CErrorFactory* instance ();
  INumCatErrorRun* getErrorRun();
  void newErrorRun();
  bool isOK() const {return m_bIsOK;}
  static void forceKill(){ cleanUpInstance(); }
  long numberOfCurrentErrors();

private:
	void deleteErrorRun();
	bool createErrorRun();
  CErrorFactory();
  ~CErrorFactory();
  static  CErrorFactory* m_instance;
  // Operations
  static CErrorFactory*  makeInstance ();
  static void cleanUpInstance ();
  CSymlixErrorRun* m_pErrorRun; // will be cast from COM object to allow access to methods
  INumCatErrorRun* m_pIErrorRun;
  bool m_bIsOK; // an internal error to the factory
  CRITICAL_SECTION m_csErrorUpdates;

};

/*
	To prevent the Error Factory outliving the COM instance there needs to be a way of forcing its end in
	the event an unplanned exit.
*/

class CErrorFactoryLifeManager // so life is managed in scope
{
public:
	CErrorFactoryLifeManager(){ CErrorFactory::instance(); }
	~CErrorFactoryLifeManager(){ CErrorFactory::forceKill(); }

};

#endif // !defined(AFX_ERRORFACTORY_H__EBB041F2_694D_4DEE_97AA_6128676F24FD__INCLUDED_)

 
