/*
 * TExampleTask.h
 *
 *  Created on: Nov 30, 2020
 *      Author: phaentu
 */

#ifndef TEXAMPLETASK_H_
#define TEXAMPLETASK_H_

#include "TMetaboliteTypes.h"
#include "TTree.h"
#include "coretools/Main/TParameters.h"
#include "coretools/Main/TTask.h"
#include "stattools/DAG/TDAGBuilder.h"
#include "stattools/ParametersObservations/TObservationTyped.h"
#include "stattools/ParametersObservations/TParameterTyped.h"

//--------------------------------------
// TExample
//--------------------------------------

class TMetaboliteModel {
private:
	// parameters
	stattools::TParameterTyped<TypeGamma, 1> _gamma;
	stattools::TParameterTyped<TypeDelta, 1> _delta;
	stattools::TParameterTyped<TypeX, 2> _trueX;
	stattools::TParameterTyped<TypeMu, 1> _mu;

	// data
	stattools::TObservationTyped<TypeLotus, 2> _lotus;

public:
	TMetaboliteModel(coretools::TMultiDimensionalStorage<TypeLotus, 2> &Data, stattools::TDAGBuilder &DAGBuilder,
	                 const std::string &Filename);
};

class TMetaboliteCore {
private:
	coretools::TMultiDimensionalStorage<TypeLotus, 2> _readData();

public:
	TMetaboliteCore();

	void infer();
};

//--------------------------------------
// Tasks
//--------------------------------------

class TTask_infer : public coretools::TTask {
public:
	// constructor must fill explanation shown to users
	TTask_infer() { _explanation = "Inferring metabolite presence in all the species there are on this planet!!"; };

	// a task must overload the run function that takes two arguments:
	// coretools::TParameters & Parameters, coretools::TLog* Logfile Usually, a
	// task creates an object and calls its function
	void run() override {
		TMetaboliteCore core;
		core.infer();
	};
};

#endif /* TEXAMPLETASK_H_ */
