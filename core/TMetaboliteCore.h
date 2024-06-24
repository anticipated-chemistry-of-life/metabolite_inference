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
#include "coretools/Types/TStringHash.h"
#include "stattools/DAG/TDAGBuilder.h"
#include "stattools/ParametersObservations/TDefinition.h"
#include "stattools/ParametersObservations/TNodeBase.h"
#include "stattools/ParametersObservations/TObservation.h"
#include "stattools/ParametersObservations/TParameter.h"
#include "stattools/ParametersObservations/spec.h"
#include "stattools/Priors/TPriorBernoulli.h"
#include "stattools/Priors/TPriorExponential.h"
#include "stattools/Priors/TPriorNormal.h"
#include "stattools/Priors/TPriorPoisson.h"
#include <memory>

//--------------------------------------
// TExample
//--------------------------------------

class TMetaboliteModel {
private:
	// parameters
	// gamma
	using BoxOnGamma = stattools::prior::TExponentialFixed<stattools::TParameterBase, TypeGamma, 1>;
	using SpecGamma  = stattools::ParamSpec<TypeGamma, stattools::Hash<coretools::toHash("gamma")>, BoxOnGamma>;
	stattools::TParameter<SpecGamma, BoxOnGamma> _gamma;

	// delta
	using BoxOnDelta = stattools::prior::TExponentialFixed<stattools::TParameterBase, TypeDelta, 1>;
	using SpecDelta  = stattools::ParamSpec<TypeDelta, stattools::Hash<coretools::toHash("delta")>, BoxOnDelta>;
	stattools::TParameter<SpecDelta, BoxOnDelta> _delta;

	// trueX
	using BoxOnX = stattools::prior::TBernoulliFixed<stattools::TParameterBase, TypeX, 2>;
	using SpecX  = stattools::ParamSpec<TypeX, stattools::Hash<coretools::toHash("X")>, BoxOnX, stattools::NumDim<2>>;
	stattools::TParameter<SpecX, BoxOnX> _trueX;

	// mu
	using BoxOnMu = stattools::prior::TNormalFixed<stattools::TParameterBase, TypeMu, 1>;
	using SpecMu =
	    stattools::ParamSpec<TypeMu, stattools::Hash<coretools::toHash("mu")>, BoxOnMu, stattools::NumDim<1>>;
	stattools::TParameter<SpecMu, BoxOnMu> _mu;

	// data
	using BoxOnLotus = stattools::prior::TPoissonFixed<stattools::TObservationBase, TypeLotus, 2>;
	using SpecLotus  = stattools::TObservation<TypeLotus, 2, BoxOnLotus>;
	std::shared_ptr<BoxOnLotus> _boxOnLotus;
	std::shared_ptr<SpecLotus> _specLotus;

	// now we create the constructor for TMetaboliteModel
public:
	TMetaboliteModel(coretools::TMultiDimensionalStorage<TypeLotus, 2> &Data, stattools::TDAGBuilder &DAGBuilder,
	                 const std::string &Filename);

	// we need to add the DAGBuilder to the DAG
	// we need to add the parameters to the DAG
	// we need to build
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
