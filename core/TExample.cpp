/*
 * TExampleTask.cpp
 *
 *  Created on: Nov 30, 2020
 *      Author: phaentu
 */

#include "TExample.h"
#include "TError.h"

using namespace coretools::instances;

//--------------------------------------
// TExample
//--------------------------------------
TExample::TExample() {
	_argument = parameters().getParameter<size_t>("argument");
	logfile().list("Will use argument ", _argument, ".");
}

void TExample::doSomething() const {
	logfile().startIndent("Drawing ", _argument, " random values:");
	for (size_t i = 0; i < _argument; ++i) { logfile().list(randomGenerator().getRand()); }
	logfile().endIndent();
}
