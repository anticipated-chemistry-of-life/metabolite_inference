//
// Created by caduffm on 5/11/23.
//

#include "TMetabolitePrior.h"

TMetabolitePrior::TMetabolitePrior(stattools::TParameterTyped<TypeGamma, 1> *Gamma,
                                   stattools::TParameterTyped<TypeDelta, 1> *Delta, std::string Prefix)
    : _gamma(Gamma), _delta(Delta), _out(Prefix) {
	addPriorParameter({_gamma, _delta});
}

void TMetabolitePrior::_simulateUnderPrior(Storage *Data) {
	// TODO: write simulation
}

void TMetabolitePrior::initializeInferred() {
	// set the size of your parameters
	_gamma->initStorage(); // by default: size = 1
	_delta->initStorage();
	// ... add more
}

std::string TMetabolitePrior::name() const { return "metabolite_prior"; }

void TMetabolitePrior::estimateInitialPriorParameters() {
	_gamma->setInitial(1.0);
	_delta->setInitial(1.0);
}

double TMetabolitePrior::getSumLogPriorDensity(const Storage &) const {
	// returns likelihood
	// TODO: implement later
	return 0.0;
}

void TMetabolitePrior::_updateGamma() {
	if (_gamma->update()) {         // propose a new value
		const double LLRatio = 0.0; // TODO: calculate the log-likelihood ratio -> implement
		const double logH    = LLRatio + _gamma->getLogPriorRatio();
		_gamma->acceptOrReject(logH, 0);
	}
}

void TMetabolitePrior::_updateDelta() {
	if (_delta->update()) {
		const double LLRatio = 0.0;
		const double logH = LLRatio + _delta->getLogPriorRatio();
		_delta->acceptOrReject(logH, 0);
	}
}

void TMetabolitePrior::updateParams() {
	_updateGamma();
	_updateDelta();
	_updateX();
}
