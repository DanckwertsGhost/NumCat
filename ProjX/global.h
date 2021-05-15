#ifndef _GLOBAL_DEFS
#define _GLOBAL_DEFS

//#include "StdAfxCommon.h"

#include <iostream>

#ifdef _NUMCAT_PRO
#define NUMCAT_DDE
#endif

#ifndef NDEBUG
#include "assert.h"
	#define ASSERT2 assert

#else
	#define ASSERT2 //
#endif

#ifndef NDEBUG
	#define _ND /**/
#else
	#define _ND //
#endif

#define ERROR_OS cerr
//#define NOT_FOUND -2147483648
const long NOT_FOUND =-2147483648;
//#define NOT_DEFINED NOT_FOUND+1
const long NOT_DEFINED=NOT_FOUND+1;
#define CANNOT_EVALUATE NOT_DEFINED+1
#define DEFAULT_TIME_STEP 1E-4
#define DEFAULT_TOLERANCE_STEP 1E-5
#define DEFAULT_SMALL_NUMBER 1E-7 // was 1E-5 but have reduced size
#define MIN_TIME_STEP 1E-7 // used to stop reduction of step size to unreasable levels

// charater defintions - needed as switch statements need const charaters
#define c_Expon 'E'
#define c_Minus '-'
#define c_Point '.'
#define c_Plus '+'
#define c_Mult '*'
#define c_Div '/'
#define c_Pow '^'
#define c_GT '>'
#define c_LT '<'


// move to contants loc latter
const char g_Eq[]="=";
const char g_Comment[]="//";
const char g_At[]="@";
const char g_Slash[]="/";
const char g_cDeriv='d';
const char g_OpenBracket[]="(";
const char g_CloseBracket[]=")";
const char g_OpenCurlyBracket[]="{";
const char g_CloseCurlyBracket[]="}";
const char g_OpenSquareBracket[]="[";
const char g_CloseSquareBracket[]="]";
const char g_Minus[]="-";
const char g_Neg[]="neg";
const char g_Plus[]="+";
const char g_Mult[]="*";
const char g_Div[]="/";
const char g_Pow[]="^";
const char g_Time[]="t";
const char g_Expon[]="E";
const char g_Point[]=".";
const char g_GT[]=">";
const char g_LT[]="<";
const char g_Space[]=" ";
const char g_IterationPostfix[]="'";

//const char g_Power[]="pow";
const char g_Exp[]="exp";
const char g_Ln[]="ln";
const char g_Sin[]="sin";
const char g_Cos[]="cos";
const char g_Tan[]="tan";
const char g_ASin[]="asin";
const char g_ACos[]="acos";
const char g_ATan[]="atan";
const char g_Log[]="log";
const char g_Abs[]="abs";

const char g_CSVDelim[]=",";
const char g_Comma[]=",";
const char g_FullColon[]=":";

static const char g_WildCard[]="#";

static const char g_As[]="as";
static const char g_Append[]="append";
static const char g_Every[]="every";
static const char g_Secs[]="secs";
static const char g_Sec[]="sec";
static const char g_For[]="for";
static const char g_RK3[]="RK3";
static const char g_RK3VS[]="RK3VS";
static const char g_RK4[]="RK4";
static const char g_RK4VS[]="RK4VS";
static const char g_RK4VSMT[]="RK4VSMT";
static const char g_RK5[]="RK5";
static const char g_RK5VS[]="RK5VS";
static const char g_Step[]="step";
static const char g_Steps[]="steps";
static const char g_Solver[]="solver";
static const char g_Tolerance[]="tolerance";
static const char g_Lookup[]="lookup";
static const char g_Switch[]="switch";
static const char g_Case[]="case";
static const char g_Default[]="default";
static const char g_From[]="from";
static const char g_In[]="in";
static const char g_Cache[]="cache";
static const char g_Include[]="#include";
static const char g_Define[]="#define";
static const char g_TagSub[]="#tag";
static const char g_TokenNoFile[]="<Inferred>";
static const char g_Dimension[]="dim";
static const char g_Min[]="min";
static const char g_Max[]="max";
static const char g_Units[]="units";
static const char g_Pace[]="pace";
static const char g_Start[]="start";
static const char g_Stop[]="stop";
static const char g_Record[]="record";
static const char g_Sync[]="sync";
static const char g_RegressionTest[]="regtest";
static const char g_Dump[]="dump";
static const char g_Last[]="last";
static const char g_RealTime[]="realtime";
static const char g_DDEserver[]="ddeserver";
static const char g_Sequence[]="sequence";
static const char g_Iteration[]="iteration";
static const char g_To[]="to";
static const char g_Array[]="array";
static const char g_LookupArray[]="arraylookup";
static const char g_Index[]="#index";
static const char g_JustIndex[]="index";
static const char g_Expand[]="#expand";
static const char g_Here[]="here";
static const char g_Equations[]="equations";
static const char g_Sum[]="sum";
static const char g_Count[]="count";
static const char g_Avrg[]="avrg";
static const char g_IntFunc[]="int";
static const char g_IntRoundUpFunc[]="intup";
static const char g_Once[]="once";
static const char g_Advance[]="advance";
static const char g_Alias[]="alias";
const char g_Quote[]="\"";

#define VectorLineTokenPts vector< vector < CToken* > > 
#define ListLineTokenPts list< vector < CToken* > > 

#include "StrongType.h"

//-----------------------------------------++
#define var_type double

#define variable var_type
#define varStrongType CStrongType<var_type>

#define time_secs variable

//-------------------------------------------

#define START_SIMULATION 0 // will need to be removed during development - tempory value

// allow assertions only on a debug build



	static const char g_cDelim[] = "=/*-+;";
	static const int g_iDelim = 21;//22;//21;//20;//14;
//	static const char* g_sDelim[] = {"//","=","/","*","-","+",";","limit",">",">=","<","<=","{","}"};
	static const char* g_sDelim[] = {"//","=","/","*","-","+",";",">",">=","<","<=",",","\"",/*"'",*/"(",")","@","^","{","}",g_Space,g_FullColon};

	static const int g_iFuncs = 12;
	static const long C_SinFunc = 601;
	static const long C_CosFunc = 602;
	static const long C_TanFunc = 603;
	static const long C_LnFunc = 604;
	static const long C_ExpFunc = 605;
	static const long C_PowFunc = 606;
	static const long C_Log10Func = 607;
	static const long C_AbsFunc = 608;
	static const long C_ASinFunc = 609;
	static const long C_ACosFunc = 610;
	static const long C_ATanFunc = 611;
	static const long C_IntFunc = 612;
	static const long C_IntRoundUpFunc = 613;
	static const long C_NotAFunc = 599;
	static const char* g_sFuncs[] = {g_Sin,g_Cos,g_Tan,g_Ln,g_Exp,/*g_Power,*/g_Log,g_Abs,g_ASin,g_ACos,g_ATan,g_IntFunc,g_IntRoundUpFunc};
	static const long g_cFuncs[] = {C_SinFunc,C_CosFunc,C_TanFunc,C_LnFunc,C_ExpFunc,/*C_PowFunc,*/C_Log10Func,C_AbsFunc,C_ASinFunc,C_ACosFunc,C_ATanFunc,C_IntFunc,C_IntRoundUpFunc};// used in map to indentify func	
	
#ifdef NUMCAT_DDE
	static const int g_iEvents = 23;
#else
	static const int g_iEvents = 22;
#endif
	static const long C_StartEvent=101;
	static const long C_StopEvent=102;
	static const long C_RecordEvent=103;
	static const long C_RegressionTest=104;
	static const long C_Pace=105;
	static const long C_Sync=106;
	static const long C_Dump=107;
	static const long C_RealTime=108;
	static const long C_DDEserver=109;
	static const long C_Iteration=110;
	static const long C_SequenceEvent=111;
	static const long C_OnceEvent=112;
	static const long C_NotAnEvent=99;
#ifdef NUMCAT_DDE
	static const char* g_sEvents[] = {g_Start,g_Stop,g_Record,g_As,g_Every,g_Secs,g_For,g_RegressionTest,g_Append,g_At,g_Pace,g_Sync,g_Dump,g_Last,g_Steps,g_RealTime,g_Sec,g_To,g_DDEserver,g_Iteration,g_Sequence,g_Equations,g_Once};
	static const long g_cEvents[] = {C_StartEvent,C_StopEvent,C_RecordEvent,C_NotAnEvent,C_NotAnEvent,C_NotAnEvent,C_NotAnEvent,C_RegressionTest,C_NotAnEvent,C_NotAnEvent,C_Pace,C_Sync,C_Dump,C_NotAnEvent,C_NotAnEvent,C_RealTime,C_NotAnEvent,C_NotAnEvent,C_DDEserver,C_Iteration,C_SequenceEvent,C_NotAnEvent,C_OnceEvent};// used in map to indetfiy event
#else
	static const char* g_sEvents[] = {g_Start,g_Stop,g_Record,g_As,g_Every,g_Secs,g_For,g_RegressionTest,g_Append,g_At,g_Pace,g_Sync,g_Dump,g_Last,g_Steps,g_RealTime,g_Sec,g_To/*,g_DDEserver*/,g_Iteration,g_Sequence,g_Equations,g_Once};
	static const long g_cEvents[] = {C_StartEvent,C_StopEvent,C_RecordEvent,C_NotAnEvent,C_NotAnEvent,C_NotAnEvent,C_NotAnEvent,C_RegressionTest,C_NotAnEvent,C_NotAnEvent,C_Pace,C_Sync,C_Dump,C_NotAnEvent,C_NotAnEvent,C_RealTime,C_NotAnEvent,C_NotAnEvent/*,C_DDEserver*/,C_Iteration,C_SequenceEvent,C_NotAnEvent,C_OnceEvent};// used in map to indetfiy event
#endif

	static const int g_iSolvers = 13;
	static const long C_RK4Solver=201;
	static const long C_RK4VSSolver=202;
	static const long C_RK5VSSolver=203;
	static const long C_RK5Solver=204;
	static const long C_RK4VSMTSolver=205;
	static const long C_RK3Solver=206;
	static const long C_RK3VSSolver=207;
	static const long C_SequenceSolver=208;
	static const long C_OnceSolver=209;
	static const long C_AdvanceSolver=210;
	static const long C_NotASolverDef=200;
	static const char* g_sSolvers[] = {g_Solver,g_RK3,g_RK3VS,g_RK4,g_RK4VS,g_RK5VS,g_Step,g_RK5,g_Tolerance,g_RK4VSMT,g_Sequence,g_Once,g_Advance};
	static const long g_cSolvers[] = {C_NotASolverDef,C_RK3Solver,C_RK3VSSolver,C_RK4Solver,C_RK4VSSolver,C_RK5VSSolver,C_NotASolverDef,C_RK5Solver,C_NotASolverDef,C_RK4VSMTSolver,C_SequenceSolver,C_OnceSolver,C_AdvanceSolver};

	static const int g_iEquations = 8;
	static const long C_EqLookup=301;
	static const long C_EqSwitch=302;
	static const long C_EqVanilla=303; // not included in string list as not keyword determined
//	static const long C_EqIterative=304;
	static const long C_NotAnEquationDef=300;
	static const char* g_sEquations[] = {g_Lookup,g_Switch,g_Case,g_Default,g_From,g_In,g_Cache,g_Alias};
	static const long g_cEquations[]={C_EqLookup,C_EqSwitch,C_NotAnEquationDef,C_NotAnEquationDef,C_NotAnEquationDef,C_NotAnEquationDef,C_NotAnEquationDef,C_NotAnEquationDef};

	static const int g_iMacros = 6;
	static const long C_MacInclude=401;
	static const long C_MacDefine=402;
	static const long C_MacIndex=403;
	static const long C_MacExpand=404;
	static const long C_NotAMacroDef=400;
	static const char* g_sMacros[] = {g_Include,g_Define,g_TagSub,g_Index,g_Expand,g_Here};
	static const long g_cMacros[]={C_MacInclude,C_MacDefine,C_NotAMacroDef,C_MacIndex,C_MacExpand,C_NotAMacroDef}; // not currently used

	static const int g_iTypeModifier = 4;
	static const long C_TM_Dimension=501;
	static const long C_TM_Max=502;
	static const long C_TM_Min=503;
	static const long C_NotTMDef=500;
	static const char* g_sTypeModifiers[]={g_Dimension,g_Min,g_Max,g_Units};
	static const long g_cTypeModifiers[]={C_TM_Dimension,C_TM_Min,C_TM_Max,C_NotTMDef};

	static const int g_iArrays = 5;
	static const long C_Array=601;
	static const long C_LookupArray=602;
	static const long C_NotArrayDef=600;
	static const char* g_sArrays[]={g_Array,g_LookupArray,g_Sum,g_Count,g_Avrg};
	static const long g_cArrays[]={C_Array,C_LookupArray,C_NotArrayDef,C_NotArrayDef,C_NotArrayDef};


	static const int g_iArrayFuncs = 3;
	static const long C_AF_Sum = 701;
	static const long C_AF_Count = 702;
	static const long C_AF_Avrg = 703;
	static const char* g_sArrayFuncs[]={g_Sum,g_Count,g_Avrg};
	static const long g_cArrayFuncs[]={C_AF_Sum,C_AF_Count,C_AF_Avrg};


	// Internal Error codes - to be given to users to allow software bugs to be understood
	// where further explaination to the user is unhelpful or inappropriate
	#define ERROR_EVENT_TRIGEVENT1 1001
	#define ERROR_EVENT_DEFAULT1 1002
	#define ERROR_EVENT_CEVENT1 1003
	#define ERROR_EQUATION_1 1004
	#define ERROR_EVENT_CEVENT2 1005
	#define ERROR_EVENT_CEVENT3 1006 // failure to pass Token pointer to constructor
	#define ERROR_EVENT_SOLVER_STATE_NOT_READY 1007



	static const long xlSheetHidden = 0;
	static const long xlSheetVeryHidden = 2;
	static const long xlSheetVisible = -1;

// Macros for handling errors

//#include "Symlix/ErrorFactory.h" // as they will all need access to this

#ifdef _SYMLIX


#ifdef NDEBUG
#define SYMERROR(description,level,stream,line,position) { CErrorFactory* cef = CErrorFactory::instance(); \
		ASSERT2(cef); \
		if (cef)  \
			cef->addError(description,level,stream,line,position,__FILE__,__LINE__);}
#else
//#include <iostream>
#define SYMERROR(description,level,stream,line,position) { CErrorFactory* cef = CErrorFactory::instance(); \
		ASSERT2(cef); \
		if (cef) \
			cef->addError(description,level,stream,line,position,__FILE__,__LINE__); \
		cerr << "<Error++> " << description<<endl; }
#endif

#define SYMERRORTOK(description,level,token) { CErrorFactory* cef = CErrorFactory::instance(); \
		ASSERT2(cef); \
		if (cef)  \
			if (token) \
				cef->addError(description,level,*(token),__FILE__,__LINE__); \
				else \
				cef->addError("Failed to pass on Token to error system",errInternal,"",NOT_DEFINED,NOT_DEFINED,__FILE__,__LINE__); \
				}

#define SYMERRORTOK2(description1,description2,level,token) { CErrorFactory* cef = CErrorFactory::instance(); \
		ASSERT2(cef); \
		if (cef)  \
			if (token) \
				{ \
				string sErr = description1; \
				sErr.append(description2); \
				cef->addError(sErr.c_str(),level,*(token),__FILE__,__LINE__); \
				} \
				else \
				cef->addError("Failed to pass on Token to error system",errInternal,"",NOT_DEFINED,NOT_DEFINED,__FILE__,__LINE__); \
				}

#define SYMERRORLITE(description,level) { CErrorFactory* cef = CErrorFactory::instance(); \
		ASSERT2(cef); \
		if (cef)  \
			cef->addError(description,level,"",NOT_DEFINED,NOT_DEFINED,__FILE__,__LINE__);}

#define SYMERRORLITE2(description1,description2,level) { CErrorFactory* cef = CErrorFactory::instance(); \
		ASSERT2(cef); \
		if (cef)  \
			{ \
			string sErr = description1; \
			sErr.append(" "); \
			sErr.append(description2); \
			cef->addError(sErr.c_str(),level,"",NOT_DEFINED,NOT_DEFINED,__FILE__,__LINE__);}}
/**/

#else // ie NDEF _SYMLIX =========================================================================

#include <iostream>

#define SYMERROR(description,level,stream,line,position) { cerr << "<SYMERROR> "<< description; \
		cerr <<" "<< stream <<" "<<line<<" : "<<position<<endl;}

#define SYMERRORTOK(description,level,token) { cerr << "<SYMERRORTOK> "<<description <<" "; \
	    cerr << __FILE__<<" "<<__LINE__<<endl;}

#define SYMERRORTOK2(description1,description2,level,token) {  cerr << "<SYMERRORTOK2> "<<description1; \
		cerr <<" "<<description2<< __FILE__<<" "<<__LINE__<<endl;}

#define SYMERRORLITE(description,level) { cerr << "<SYMERRORLITE> "<< description; \
		cerr <<" "<< __FILE__<<" "<<__LINE__<<endl;}

#define SYMERRORLITE2(description1,description2,level)  { cerr << "<SYMERRORLITE> "<< description1; \
		cerr <<" "<<description2<<" "<< __FILE__<<" "<<__LINE__<<endl;}

/**/
#endif // _SYMLIX

#endif // _GLOBAL_DEFS