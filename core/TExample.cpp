/*
 * TExampleTask.cpp
 *
 *  Created on: Nov 30, 2020
 *      Author: phaentu
 */

#include "TExample.h"
#include "TError.h"

//--------------------------------------
// TExample
//--------------------------------------
TExample::TExample() {
	using namespace coretools::instances;

	_argument = parameters().getParameter<size_t>("argument");
	logfile().list("Will use argument " + coretools::str::toString(_argument) + ".");
}

void TExample::doSomething() const {
	using namespace coretools::instances;

	logfile().startIndent("Drawing " + coretools::str::toString(_argument) + " random values:");
	for (size_t i = 0; i < _argument; ++i) { logfile().list(randomGenerator().getRand()); }
	logfile().endIndent();
}
