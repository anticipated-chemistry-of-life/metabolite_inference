/*
 * TExampleTask.cpp
 *
 *  Created on: Nov 30, 2020
 *      Author: phaentu
 */

#include "TExample.h"

//--------------------------------------
// TExample
//--------------------------------------
TExample::TExample(TParameters & Parameters, TLog* Logfile){
	_logfile = Logfile;
	_argument = Parameters.getParameterInt("argument");

	_logfile->list("Will use argument " + toString(_argument) + ".");
};

void TExample::doSomething(TRandomGenerator* Randomgenerator){
	_logfile->startIndent("Drawing " + toString(_argument) + " random values:");
	for(int i=0; i<_argument; ++i){
		_logfile->list(Randomgenerator->getRand());
	}
	_logfile->endIndent();
};


