// MemLeakRecord.h: interface for the CMemLeakRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMLEAKRECORD_H__CFBFA411_46DB_4F49_81C2_2BDC1FF982E2__INCLUDED_)
#define AFX_MEMLEAKRECORD_H__CFBFA411_46DB_4F49_81C2_2BDC1FF982E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUGMEM
//#pragma init_seg(compiler)

	#include "crtdbg.h"
	//#ifdef _DEBUG
	#ifdef _DEBUGMEM
//	#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
//	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define newtrack new(_NORMAL_BLOCK, __FILE__, __LINE__)

	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
	class CMemLeakRecord
	{
	private:
		_CrtMemState m_checkpoint;
	public:
		CMemLeakRecord()
		{
			_CrtMemCheckpoint(&m_checkpoint);
		};
		~CMemLeakRecord()
		{
			_CrtMemState checkpoint;
			_CrtMemCheckpoint(&checkpoint);
			_CrtMemState diff;
			_CrtMemDifference(&diff, &m_checkpoint, &checkpoint);
			_CrtMemDumpStatistics(&diff);
			_CrtMemDumpAllObjectsSince(&diff);
		};
	};

#else // do nothing

	#define newtrack new

	class CMemLeakRecord
	{
	public:
		CMemLeakRecord(){};
		~CMemLeakRecord(){};
	};
	#endif

#endif // !defined(AFX_MEMLEAKRECORD_H__CFBFA411_46DB_4F49_81C2_2BDC1FF982E2__INCLUDED_)
