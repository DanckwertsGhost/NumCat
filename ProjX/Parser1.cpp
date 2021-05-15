// Parser1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Simulation.h"
#include "VarUnitTests.h"

#include <objbase.h>
#include "SymlixStore.h"
#include "Symlix/ErrorFactory.h"

using namespace std;

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)


CMemLeakRecord* pcmlrFind;

void cleanupMemRecord()
{
	delete pcmlrFind;
};

int main(int argc, char* argv[])
{
	pcmlrFind = newtrack CMemLeakRecord;
	atexit(cleanupMemRecord);

	CSimulation* simulation;
	CVarUnitTests varUnitTests; // maths code unit tests
	fstream isf;
	const int SIZE = 81;
	char sBuf[SIZE];
	//char ch;
	const char filetoopen[] = "InputDeck.txt";

	isf.open(filetoopen,ios::in);

	if (!isf.is_open())
	{
		cerr << "Failed to open file " << filetoopen << "\n ";
		exit(1);
	}
//	isf.close();
//	exit(1);
	
	while(isf.rdstate()==0)
	{
		//cout << isf.rdstate();
		
		isf.getline(sBuf,SIZE);
		cout << sBuf; cout << endl;cout.flush();
	}

	isf.close();

// lets do this with COM just to check

	HRESULT hr;
	IARDataStore* pIStore = NULL;

	hr = CoInitialize(NULL);

	if (SUCCEEDED(hr))
		{
		hr = CoCreateInstance(CLSID_ARFileDataStore,NULL,CLSCTX_INPROC_SERVER,IID_IARDataStore,(void**)&pIStore);
		
		if (FAILED(hr))
			{
			cout << "Unable to create file Symlix store\n";
			CoUninitialize();
			exit(1);
			}




		}

	{ // start of COM scope

//	CErrorFactoryLifeManager eflm; // so don't release after CoUninitialize

		{ // a small error test zone
//			CErrorFactoryLifeManager eflm; // so don't release after CoUninitialize

			SYMERROR("Test",errDevWarning,"Woof",5,10);
		}

	
//	while(isf.get(ch))
//	{
//		//isf.getline(sBuf,SIZE);
//		cout << ch;
//	}
	
	if (!varUnitTests.TestVarLibrary(cerr))
		{
		cerr << "<Error#> unit test on Var Library failed\n";
		pIStore->Release();
		CoUninitialize();
		exit(1);
		}

//	simulation = newtrack CSimulation(filetoopen);
	simulation = newtrack CSimulation(pIStore,filetoopen);
	if (!simulation)
		{
		cerr << "<Error#> failed to create simulation - unable to assign memory\n";
		pIStore->Release();
		CoUninitialize();
		exit(1);
		}

	if (!simulation->setUpSimulation())
		cerr << "<Error#> Problems found setting up simulation - cannot run simulation\n";
		else
		if (!simulation->runSimulation())
			cerr << "<Error#> Simulation failed to run or finish properly.\n";

	CErrorFactory::forceKill();
	} // endof Error scope
	delete simulation;
	pIStore->Release();



	CoUninitialize();

	return 0;
}

