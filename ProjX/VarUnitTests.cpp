// VarUnitTests.cpp: implementation of the CVarUnitTests class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemLeakRecord.h"
#include "VarUnitTests.h"
#include "VarExp.h"
#include "VarValue.h"
#include "VarVariable.h"
#include "assert.h"
#include "VarClassFactory.h"
#include "Symlix/ErrorFactory.h"

#define ERROR_ALLOWED 1E-6

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVarUnitTests::CVarUnitTests()
{

}

CVarUnitTests::~CVarUnitTests()
{

}


bool CVarUnitTests::TestVarLibrary(ostream& os/*=cerr*/)
{
	try
	{
		try
		{
		xt_value xv1 = 10;
		xt_value xv2 = -2.5;
		xt_value xv3 = 34.001E15;
		xt_value xv4 = 4;
		xt_value xv5 = 5;
		xt_value xv6 = 0;
		xt_value xv7 = -0.000001;
		xt_value xvBuff;
		bool bTest;

//		xt_value xvBuff;

		vector< xt_value > vec;

		vec.push_back(xv1);  //	[0]
		vec.push_back(xv2);  //	[1]
		vec.push_back(xv3);  //	[2]
		vec.push_back(xv4);  //	[3]
		vec.push_back(xv5);  //	[4]
		vec.push_back(xv6);  //	[5]
		vec.push_back(xv7);  //	[6]

		CVarValue cvv1(xv1);

		assert(xv1==cvv1.getValue(vec));

		CVarVariable cva1(0);

		assert(xv1==cva1.getValue(vec));
		vec[0] = xv2; // check refernce link works
		assert(xv2==cva1.getValue(vec));
		vec[0] = xv1; // reset

		CVarVariable cva2(1);
		CVarVariable cva3(2);
		CVarVariable cva4(3);
		CVarVariable cva5(4);
		CVarVariable cva6(5);
		CVarVariable cva7(6);
		
		// Test CVarExpAdd
		CVarExpAdd cvea1(&cva1,&cva2);
		CVarExpAdd cvea2(cva1,cva2);
		assert( cvea1.getValue(vec)==cvea2.getValue(vec));
		assert( cvea1.getValue(vec)==cva1.getValue(vec)+cva2.getValue(vec));
		assert( cvea2.getValue(vec)==xv1+xv2);

		// practice life cycle for pointers
		CVarRoot* pcvr;
		pcvr = newtrack CVarExpAdd( new CVarVariable(0), new CVarValue(-100), true );
		assert( pcvr->getValue(vec)==vec[0]-100 );
		delete pcvr;

		// Test CVarExpDiv
		CVarExpDiv cved1(&cva1,&cva4);
		CVarExpDiv cved2(cva1,cva4);
		assert( cved1.getValue(vec)==cved2.getValue(vec));
		assert( cved1.getValue(vec)==cva1.getValue(vec)/cva4.getValue(vec));
		assert( cved2.getValue(vec)==xv1/xv4);
		bTest = false;
		try
		{
			vec[3]=0; // so will now result in Div by zero, which could not be check for at time of construction
			xvBuff = cved1.getValue(vec); // should throw exception


		}
		catch( CExceptionCVarRoot* evr )
		{
			#ifndef NDEBUG
			os << "IGNOR _ as required _ \n\t"<< (*evr) << endl;
			#endif
			bTest = true;
			delete evr;
		}
		assert(bTest);

		// Test CVarExpExp
		CVarExpExp cvee1(&cva2);
		CVarExpExp cvee2(cva2);
		assert( cvee1.getValue(vec)==cvee2.getValue(vec));
		assert( ERROR_ALLOWED > fabs(cvee1.getValue(vec)-exp(double(cva2.getValue(vec)))));
		assert( ERROR_ALLOWED > fabs(cvee2.getValue(vec)-exp(xv2)));

		// Test CVarExpLn
		CVarExpLn cvel1(&cva3);
		CVarExpLn cvel2(cva3);
		assert( cvel1.getValue(vec)==cvel2.getValue(vec));
		//os << xv3 << "\t" <<cvel1.getLeft()->getValue(vec) <<"\t";
		//os << cvel1.getValue(vec)<<"\t"<<log(double(cva3.getValue(vec)))<<endl; os.flush();
		assert( ERROR_ALLOWED > fabs(cvel1.getValue(vec)-log(double(cva3.getValue(vec)))));
		assert( ERROR_ALLOWED > fabs(cvel2.getValue(vec)-log(xv3)));

		// Test CVarExpMinus
		CVarExpMinus cvem1(&cva1,&cva2);
		CVarExpMinus cvem2(cva1,cva2);
		assert( cvem1.getValue(vec)==cvem2.getValue(vec));
		assert( cvem1.getValue(vec)==cva1.getValue(vec)-cva2.getValue(vec));
		assert( cvem2.getValue(vec)==xv1-xv2);

		// Test CVarExpMulti
		CVarExpMulti cveM1(&cva1,&cva2);
		CVarExpMulti cveM2(cva1,cva2);
		assert( cveM1.getValue(vec)==cveM2.getValue(vec));
		assert( cveM1.getValue(vec)==cva1.getValue(vec)*cva2.getValue(vec));
		assert( cveM2.getValue(vec)==xv1*xv2);

		// Test CVarExpPow
		CVarExpPow cvep1(&cva1,&cva2);
		CVarExpPow cvep2(cva1,cva2);
		assert( cvep1.getValue(vec)==cvep2.getValue(vec));
		assert( cvep1.getValue(vec)==pow(cva1.getValue(vec),cva2.getValue(vec)));
		assert( cvep2.getValue(vec)==pow(xv1,xv2));

		// Test CVarExpGT
		CVarExpGT cveGT1(&cva1,&cva2);
		CVarExpGT cveGT2(cva1,cva2);
		assert( cveGT1.getValue(vec)==cveGT2.getValue(vec));
		assert( cveGT1.getValue(vec)==xt_value(cva1.getValue(vec)>cva2.getValue(vec)));
		assert( cveGT2.getValue(vec)==xt_value(xv1>xv2));
		CVarExpGT cveGT3(&cva1,&cva1);
		assert(!cveGT3.getValue(vec));

		// Test CVarExpGT
		CVarExpLT cveLT1(&cva1,&cva2);
		CVarExpLT cveLT2(cva1,cva2);
		assert( cveLT1.getValue(vec)==cveLT2.getValue(vec));
		assert( cveLT1.getValue(vec)==xt_value(cva1.getValue(vec)<cva2.getValue(vec)));
		assert( cveLT2.getValue(vec)==xt_value(xv1<xv2));
		CVarExpLT cveLT3(&cva1,&cva1);
		assert(!cveLT3.getValue(vec));

		// test class factory

		CVarClassFactory* pcf1, *pcf2;
		pcf1 = CVarClassFactory::instance();
		pcf2 = CVarClassFactory::instance();
		assert(pcf1==pcf2);

		CVarRoot* pcvr1 = pcf1->createExpression("+",&cvv1,&cva1);
		assert(pcvr1->getValue(vec)==cvv1.getValue(vec)+cva1.getValue(vec));

		CVarRoot* pcvr2 = pcf1->createExpression("-",&cvv1,&cva1);
		assert(pcvr2->getValue(vec)==cvv1.getValue(vec)-cva1.getValue(vec));

		CVarRoot* pcvr3 = pcf1->createExpression("-",&cvv1,&cva1);
		assert(pcvr2!=pcvr3); // ie two distinct instances created

		CVarRoot* pcvr3p1 = pcf1->createExpression("neg",&cva2);
		assert(pcvr3p1->getValue(vec)==cva2.getValue(vec)*(-1));

		CVarRoot* pcvr4 = pcf1->createExpression("/",&cvv1,&cva1);
		assert(pcvr4->getValue(vec)==cvv1.getValue(vec)/cva1.getValue(vec)); // ie two distinct instances created

		CVarRoot* pcvr5 = pcf2->createExpression("*",&cvv1,&cva1);
		assert(pcvr5->getValue(vec)==cvv1.getValue(vec)*cva1.getValue(vec)); // ie two distinct instances created

		CVarRoot* pcvr6 = pcf2->createExpression("^",&cvv1,&cva1);
		assert(pcvr6->getValue(vec)==pow(cvv1.getValue(vec),cva1.getValue(vec))); // ie two distinct instances created

//		CVarRoot* pcvr7 = pcf2->createExpression(g_Power,&cvv1,&cva1);
//		assert(pcvr7->getValue(vec)==pcvr6->getValue(vec)); // ie two distinct instances created

		CVarRoot* pcvr8 = pcf2->createExpression("ln",&cvv1,&cva1);
		assert( ERROR_ALLOWED > fabs(pcvr8->getValue(vec)-log(cvv1.getValue(vec))));

		CVarRoot* pcvr9 = pcf2->createExpression("exp",&cvv1,&cva1);
		assert( ERROR_ALLOWED > fabs(pcvr9->getValue(vec)-exp(cvv1.getValue(vec))));

		CVarRoot* pcvrF = pcf2->createExpression("sin",&cvv1,&cva1);
		assert( ERROR_ALLOWED > fabs(pcvrF->getValue(vec)-sin(cvv1.getValue(vec))));

		pcvrF = pcf2->createExpression("cos",&cvv1,&cva1);
		assert( ERROR_ALLOWED > fabs(pcvrF->getValue(vec)-cos(cvv1.getValue(vec))));

		pcvrF = pcf2->createExpression("tan",&cvv1,&cva1);
		assert( ERROR_ALLOWED > fabs(pcvrF->getValue(vec)-tan(cvv1.getValue(vec))));

		pcvrF = pcf2->createExpression("log",&cvv1,&cva1);
		assert( ERROR_ALLOWED > fabs(pcvrF->getValue(vec)-log10(cvv1.getValue(vec))));

		pcvrF = pcf2->createExpression("abs",&cvv1,&cva1);
		assert( ERROR_ALLOWED > fabs(pcvrF->getValue(vec)-abs(cvv1.getValue(vec))));


		CVarRoot* pcvr10 = pcf1->createValue(xv3);
		CVarRoot* pcvr11 = pcf2->createVariable(2);
		assert(pcvr10->getValue(vec)==pcvr11->getValue(vec));

		// Need to check cache value function
		CVarRoot* pcvr12 = pcf1->createVariable(1);
		CVarRoot* pcvr13 = pcf1->createVariable(2);
		CVarRoot* pcvr14 = pcf1->createExpression("*",pcvr12,pcvr13);

		vec[1] = 10;
		vec[2] = 5;
		
		xt_value xtvBeforeVar, xtvBeforeProduct;

		cout << "Start cache tests\n";
		cout << vec[1] <<"\t"<<vec[2]<<endl;
		cout << pcvr12->getValue(vec) <<"\t"<< pcvr13->getValue(vec) <<"\t"<< pcvr14->getValue(vec)<<endl;
		vec[1] *= 1.015;
		cout << pcvr12->getValue(vec) <<"\t"<< pcvr13->getValue(vec) <<"\t"<< pcvr14->getValue(vec)<<endl;

		CVarRoot::stepGlobalCache();
		vec[1] *= 1.015;
		cout << pcvr12->getValue(vec) <<"\t"<< pcvr13->getValue(vec) <<"\t"<< pcvr14->getValue(vec)<<endl;

		xtvBeforeVar = pcvr12->getValue(vec);
		xtvBeforeProduct = pcvr14->getValue(vec);
		vec[1] *= 1.015;
		cout << pcvr12->getValue(vec) <<"\t"<< pcvr13->getValue(vec) <<"\t"<< pcvr14->getValue(vec)<<endl;
		assert(xtvBeforeVar!=pcvr12->getValue(vec));
		assert(xtvBeforeProduct==pcvr14->getValue(vec)); // as should return cached value
		CVarRoot::stepGlobalCache();
		assert(xtvBeforeProduct!=pcvr14->getValue(vec)); // as should recalc value
		cout << pcvr12->getValue(vec) <<"\t"<< pcvr13->getValue(vec) <<"\t"<< pcvr14->getValue(vec)<<endl;

		CVarRoot::switchCacheOff(); // other wise what follows won't work.
		}
		catch(CExceptionCVarRoot* evr)
		{
			os << (*evr) << endl;
			SYMERRORLITE2(evr->getHeading(),evr->getMessage(),errInternal);
			delete evr;
			return false;
		}
	}
	catch(...)
	{
	os << "<<Error*>> CVarUnitTests::TestVarLibrary failed for unhandled cause\n";
	SYMERRORLITE("Internal tests failed throwing an unkown fault",errInternal);
	return false;
	}




	return true;
}
