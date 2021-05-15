// CritCheck.cpp: implementation of the CCritCheck class.
//
//////////////////////////////////////////////////////////////////////
#include "CritCheck.h"


// because it has to go somewhere
#ifndef NDEBUG
#ifndef MAP_CS
#define MAP_CS // otherwise will need a .cpp file for this
map<CRITICAL_SECTION*,long>* CCritCheck::m_pgmapCount = 0;
#endif
#endif