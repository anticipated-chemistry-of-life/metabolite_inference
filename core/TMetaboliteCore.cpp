/*
 * TExampleTask.cpp
 *
 *  Created on: May 15, 2023
 *      Author: mvisani
 */

#include "TMetaboliteCore.h"
#include "TMetabolitePrior.h"
#include "coretools/Main/TError.h"
#include "coretools/Storage/TDataFile.h"
#include "stattools/MCMC/TMCMC.h"
#include "stattools/Priors/TPriorBernouilli.h"
#include "stattools/Priors/TPriorExponential.h"
#include "stattools/Priors/TPriorNormal.h"

using namespace coretools::instances;

//--------------------------------------
// TMetaboliteModel
//--------------------------------------

TMetaboliteModel::TMetaboliteModel(coretools::TMultiDimensionalStorage<TypeLotus, 2>& Data,
                                   stattools::TDAGBuilder& DAGBuilder, const std::string& Filename)
    : _gamma("gamma", std::make_shared<stattools::prior::TExponentialFixed<stattools::TParameterBase, TypeGamma, 1>>(),
             {Filename, "1"}),
      _delta("delta", std::make_shared<stattools::prior::TExponentialFixed<stattools::TParameterBase, TypeDelta, 1>>(),
             {Filename, "1"}),
      _trueX("X", std::make_shared<stattools::prior::TBernouilliFixed<stattools::TParameterBase, TypeX, 2>>(),
             {Filename, "1"}),
      _mu("mu", std::make_shared<stattools::prior::TNormalFixed<stattools::TParameterBase, TypeMu, 1>>(),
          {Filename, "1"}),
      _lotus("lotus", std::make_shared<TMetabolitePrior>(&_gamma, &_delta, Filename), Data, {}) {
	DAGBuilder.addToDAG({&_gamma, &_delta});
	DAGBuilder.addToDAG(&_lotus);

	DAGBuilder.buildDAG();
}

//--------------------------------------
// TMetaboliteCore
//--------------------------------------

TMetaboliteCore::TMetaboliteCore() {}

coretools::TMultiDimensionalStorage<TypeLotus, 2> TMetaboliteCore::_readData() {
	std::string filename = parameters().getParameterFilename("lotus");

	// prepare names
	auto moleculeNames = std::make_shared<coretools::TNamesStrings>();
	auto speciesNames  = std::make_shared<coretools::TNamesStrings>();

	// prepare data storage
	coretools::TMultiDimensionalStorage<TypeLotus, 2> data;

	// read file: fill into data
	coretools::TDataReaderBase<TypeLotus, 2> reader;
	reader.read(filename, &data, {moleculeNames, speciesNames}, {'\n', '\t'}, {true, true}, {0, 0}, {false, false}, 100,
	            coretools::colNames_multiline);

	return data;
}

void TMetaboliteCore::infer() {
	// read prefix for writing
	std::string outname = parameters().getParameterWithDefault("out", "metabolite");
	logfile().list("Will write files with prefix '", outname, "'. (parameter 'out')");

	// read data
	auto data = _readData();

	// build model
	stattools::TDAGBuilder dagBuilder;
	TMetaboliteModel model(data, dagBuilder, outname);

	// run MCMC
	stattools::TMCMC mcmc;
	mcmc.runMCMC(outname, &dagBuilder);
}
