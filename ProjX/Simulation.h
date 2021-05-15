// Simulation.h: interface for the CSimulation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMULATION_H__FAD50993_8C91_4FF6_ACFD_464AED39CA3D__INCLUDED_)
#define AFX_SIMULATION_H__FAD50993_8C91_4FF6_ACFD_464AED39CA3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>

#include "Token.h"
#include "EvValue.h"
#include "EvOutsideGetData.h"
#include "EvOutsideSetdata.h"
#include "Model.h"
#include "Solver.h"
#include "SimRun.h"
#include "Index.h"

#include "SymlixStore.h"

#ifndef NDEBUG
//#define DEBUGEXPAND
#endif

#define CSIMULATION_SIZE 255

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

using namespace std;

#include "global.h"

enum eSimulationState{cessUninitated,cessHasFile,cessHasLines,cessInitiated};




class CTokeniser; // declare

class CSimulation  
{
public:
	CSimulation();
	CSimulation(const string& sFileLoc );

	CSimulation(IARDataStore* pIStore, const string& sFileLoc);

	virtual ~CSimulation();	

	bool setUpSimulation();
	bool runSimulation(CIDataServicesCallBack* iSCB=NULL);
	bool getCopyVariableList(vector< string >& vecVL );
	long findIndexOfVar( const string& sFind );
	bool requestEndOfSimulation();
	eSimulationState getSimulationState() const { return m_eState; }
	bool addUserEvents( const vector<long>& vecInd, const vector<variable>& vecValue, const vector<eUserEvents>& vecEvType );
	void setTag(const string& sNewTag);
	void getCurrentValues( vector< variable>& rvecValues ){ m_OutsideGetData.getValues(rvecValues); };
	bool addRunTimeEvent( CEvent* pEvCallBack );
protected:
	void wipeFactories();
	bool makeArrays(ostream& osErrReport);
	bool checkArrays(ostream& osErrReport);
	bool setFile(const string& sFileLoc );

	virtual /*was static*/ bool checkFileExists(const string& sFile);
	virtual bool expandAndSubstituteNextInclude(list<CToken>& listTokens, CTokeniser& cTokeniser, ostream& oserr, bool& bFormatError);

	virtual bool isModelSquare();
	virtual void GenerateStructure();
	virtual void GenerateLines();
	virtual void clearSimulation(bool bButNotRecognisedFileNames = false);
	virtual void setLineToComment(VectorLineTokenPts::iterator itLine);
	virtual void unifyEquationTokens();
	virtual bool checkModel(ostream& osErrReport ); // returns true if model is ready to be solved
	virtual bool checkEquations(ostream& osErrReport ); // ensure equations are well formed
	virtual bool checkValues(ostream& osErrReport ); // ensure the model has sufficient information to be solved
	virtual bool checkEvents(ostream& osErrReport ); // ensure the model has sufficient information to be solved
	virtual bool checkSolver(ostream& osErrReport ); // ensure the model has sufficient information to be solved
	virtual bool checkTypes(ostream& osErrReport );  // ensure the model has sufficient information to be solved

	virtual bool processifDerivative(list<CToken>::iterator& it);
	virtual bool processifContainsNames(list<CToken>::iterator it);

	virtual void cascadeTokenTypes();
	virtual void assignStatusofVariables();
	virtual bool assertEquationsUnique(){return false;};
	virtual bool makeValues(ostream& osErrReport);
	virtual bool makeEquations(ostream& osErrReport);
	virtual bool makeEvents(ostream& osErrReport);
	virtual bool makeSolverChoices(ostream& osErrReport);
	virtual bool makeTypes(ostream& osErrReport);

	virtual long findPlaceInLine(const vector< CToken* >& vptLine, const string& sFind) const;

	bool setUpSimulationPass(bool bFirstPass, mapUserDefinedKeys& mapUDK);
	void expandUserDefinedMacros(mapUserDefinedKeys& mapUDK);

	static void copySetpttoStream(SetPtCToken& setptTokens, ostream& os);
	static void copySetptSearchtoStream(SetPtCTokenStringSearch& setptTokens, ostream& os);
	static void copySetpttoStream(vector<CToken*>& vecptTokens, ostream& os);
	void assignTokenTypes(vector<CToken*>& vec, eTokenType eT );
	CEvent* addSystemEvent(const eSysEvents eNewSysEvent, ostream& osErrReport,vector<CEvent*>& rvEvents); 
	
	string m_sFile;
	string m_sTag; // a tag that can be used for adding info to a deck programmatically
	IARDataStore* m_pIARDataStore;
	list<CToken> m_ltTokens;
	vector< list<CToken>::iterator > m_vpRemove;
	eSimulationState m_eState;
	VectorLineTokenPts m_vecLines;

	ListLineTokenPts m_vecLinesofIntrestEq;
	VectorLineTokenPts m_vecLinesofIntrestTv; // Type variation
	VectorLineTokenPts m_vecLinesofIntrestSV; // set value
	VectorLineTokenPts m_vecLinesofIntrestEt; // Event
	VectorLineTokenPts m_vecLinesofIntrestSl; // Solver
	VectorLineTokenPts m_vecLinesofIntrestAr; // Array
	VectorLineTokenPts m_vecLinesofIntrestIn; // Index lines

	list<CEquation*> m_vpEquations;
	vector<CEvent*> m_vpEvents; // note life time mamnaged by class factory
	CEvent* m_pOutsideStop; // note life time mamnaged by class factory
	CEvOutsideSetData m_OutsideSetData;
	CEvOutsideGetData m_OutsideGetData;


	SetPtCTokenStringSearch m_setPtUniqueTokens; // set of pointers to unique tokens
	// note also that these tokens are all the Parents of any duplicate tokens.
	setofwords m_setRecognisedFileNames;
	setofwords::const_iterator m_itNoFileName; // needed to create not recognised file

	vector<CToken*> m_vecOrderedVarTokens;

	CModel m_cmModel;
	CSolver* m_pSolver;
private:
	bool instantiateIndexEquation( CIndex* pIndex, list< ListLineTokenPts::iterator >::iterator& ritLL, list< ListLineTokenPts::iterator >& rvecLTP_partArrays, bool& rbNewLines );
	bool expandIndecies( ostream& osErr );
	bool expandArrays( ostream& osErr );

#ifdef DEBUGEXPAND
	void writeEquationsInfo( ostream& os, list< ListLineTokenPts::iterator >& rListPtEq, const char* sTag ); 
    void writeEveryEquation( ostream& os );
#endif
};

#endif // !defined(AFX_SIMULATION_H__FAD50993_8C91_4FF6_ACFD_464AED39CA3D__INCLUDED_)
