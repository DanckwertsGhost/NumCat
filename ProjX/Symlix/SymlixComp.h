// SymlixComp.h : Declaration of the CSymlix

#ifndef __SYMLIX_H_
#define __SYMLIX_H_

#include "resource.h"       // main symbols
#include "SymlixCP.h"
#include "..\Simulation.h"
#include <process.h>


//declare
class ATL_NO_VTABLE CSymlix;

class CISymlixDataServicesCallBack :
	public CIDataServicesCallBack
{
public:
	CISymlixDataServicesCallBack(CSymlix& cs):m_cSymlix(cs){};
	virtual ~CISymlixDataServicesCallBack(){}
	virtual void startDataServices();
	virtual void endDataServices();

private:
	CSymlix& m_cSymlix;
};

#define XCONNECTIONPOINTS
/////////////////////////////////////////////////////////////////////////////
// CSymlix
class ATL_NO_VTABLE CSymlix : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSymlix, &CLSID_NumCat>,
	public ISupportErrorInfo,
#ifdef CONNECTIONPOINTS
	public IConnectionPointContainerImpl<CSymlix>,
#endif
	public IDispatchImpl<INumCat, &IID_INumCat, &LIBID_NumCatLib>
#ifdef CONNECTIONPOINTS
	,public CProxy_INumCatEvents< CSymlix >
#endif
{
public:
	CSymlix():m_essState(blank),m_psimulation(NULL),m_pICallBack(NULL),m_bBkgrndSolverRun(FALSE),m_eDDEState(esddeStop),m_cbRunTag("")
	{
		m_hEvent1 = CreateEvent(NULL,TRUE,FALSE,NULL);
		m_hEventEndSimThread = CreateEvent(NULL,TRUE,FALSE,NULL);
		InitializeCriticalSection(&m_csModelRunningState);
		InitializeCriticalSection(&m_csSimulationRunning);
		m_pINumCatDataServicesCB = newtrack CISymlixDataServicesCallBack(*this);
	}
	void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SYMLIX)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSymlix)
	COM_INTERFACE_ENTRY(INumCat)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
#ifdef CONNECTIONPOINTS
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
#endif
END_COM_MAP()

#ifdef CONNECTIONPOINTS
BEGIN_CONNECTION_POINT_MAP(CSymlix)
CONNECTION_POINT_ENTRY(DIID__INumCatEvents)
END_CONNECTION_POINT_MAP()
#endif

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// INumCat
public:
	STDMETHOD(get_VersionDescription)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_RunTag)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_RunTag)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_LicenseState)(/*[out, retval]*/ enumLicenseState *pVal);
	STDMETHOD(GiveErrors)(/*[out,retval]*/ INumCatErrorRun** ppINumCatErrorRun);
	STDMETHOD(StopModel)();
	STDMETHOD(GiveVariableIndex)(/*[in]*/ BSTR* sVariable, /*[out,retval]*/ long* piIndex);
	STDMETHOD(get_CurrentModelValues)(/*[out,retval]*/ SAFEARRAY **ppsaVals);
	STDMETHOD(get_VariableNames)(/*[out,retval]*/ SAFEARRAY **ppsaVars);
	STDMETHOD(ResetModel)(/*[in]*/ VARIANT_BOOL bEvenIfRunning, /*[out,retval]*/  VARIANT_BOOL* pvbResult);
	STDMETHOD(ClearModel)(/*[in]*/ VARIANT_BOOL bEvenIfRunning, /*[out,retval]*/ VARIANT_BOOL* pvbResult);
	STDMETHOD(get_ModelStatus)(/*[out, retval]*/ enumNumCatStatus *pVal);
	STDMETHOD(RunModel)(/*[in]*/long hInstance, /*[defaultvalue(NULL)]*/ INumCatHostCallBack* pINumCatHostCallBack, /*[out,retval]*/ VARIANT_BOOL* pvbResult);
	STDMETHOD(LoadModel)(/*[in]*/ BSTR* sFileName,/*[in]*/ IARDataStore* pIStore, /*[out,retval]*/ VARIANT_BOOL* pvbResult);
//	STDMETHOD(CheckFile)(/*[in]*/ BSTR* sFileName, /*[out,retval]*/ VARIANT_BOOL*  pvbResult);
	STDMETHOD(AddUserEvents)(/*[in]*/ SAFEARRAY **ppsaVars, /*[in]*/ SAFEARRAY **ppsaVals, /*[in]*/ SAFEARRAY **ppsaEvTypes, /*[out,retval]*/ VARIANT_BOOL* pvbResult);
	
	friend void SimRunThread( void* pParams );

	inline void eventDDEStatus(enumNumCatDDE esddeStatus){
#ifdef CONNECTIONPOINTS
	Fire_DDEStatus(esddeStatus);
#endif
	}

private:
	void killThreads();
	bool m_bBkgrndSolverRun;
	enumNumCatStatus m_essState;
	CSimulation* m_psimulation;
	INumCatHostCallBack* m_pICallBack;
	HANDLE m_hEvent1;
	HANDLE m_hEventEndSimThread;
	CRITICAL_SECTION m_csModelRunningState;
	CRITICAL_SECTION m_csSimulationRunning;
	enumNumCatDDE m_eDDEState;
	CISymlixDataServicesCallBack* m_pINumCatDataServicesCB;
	CComBSTR m_cbRunTag;
//	static bool CheckSimulationFile(string& sFileName, CSimulation* pSim);
protected:
	long findVariableIndex(BSTR *pbstr );
};



#endif //__SYMLIX_H_
