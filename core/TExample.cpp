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
TExample::TExample(coretools::TParameters &Parameters,
		   coretools::TLog *Logfile) {
	_logfile  = Logfile;
	_argument = Parameters.getParameter<int>("argument");

	_logfile->list("Will use argument " + coretools::str::toString(_argument) +
		       ".");
};

void TExample::doSomething(coretools::TRandomGenerator *Randomgenerator) {
	_logfile->startIndent("Drawing " + coretools::str::toString(_argument) +
			      " random values:");
	for (int i = 0; i < _argument; ++i) {
		_logfile->list(Randomgenerator->getRand());
	}
	_logfile->endIndent();
};
