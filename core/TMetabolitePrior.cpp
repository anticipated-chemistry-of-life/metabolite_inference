//
// Created by caduffm on 5/11/23.
//

#include "TMetabolitePrior.h"
#include "coretools/Storage/TDimension.h"

TMetabolitePrior::TMetabolitePrior(stattools::TParameter<SpecGamma, BoxOnGamma> *Gamma,
                                   stattools::TParameter<SpecDelta, BoxOnDelta> *Delta, std::string Prefix)
    : _gamma(Gamma), _delta(Delta), _out(Prefix) {
	addPriorParameter({_gamma, _delta});
}

void TMetabolitePrior::_simulateUnderPrior(Storage *Data) {
	// TODO: write simulation
}

std::string TMetabolitePrior::name() const { return "metabolite_prior"; }

void TMetabolitePrior::estimateInitialPriorParameters() {
	_gamma->set(1.0);
	_delta->set(1.0);
}

double TMetabolitePrior::getSumLogPriorDensity(const Storage &) const {
	// returns likelihood
	// TODO: implement later
	return 0.0;
}

void TMetabolitePrior::_updateGamma() {
	if (_gamma->isUpdated()) {      // propose a new value
		const double LLRatio = 0.0; // TODO: calculate the log-likelihood ratio -> implement
		const double logH    = LLRatio + _gamma->getLogRatio();
		_gamma->acceptOrReject(logH, coretools::TRange(0));
	}
}

void TMetabolitePrior::_updateDelta() {
	if (_delta->isUpdated()) {
		const double LLRatio = 0.0;
		const double logH    = LLRatio + _delta->getLogRatio();
		_delta->acceptOrReject(logH, coretools::TRange(0));
	}
}

void TMetabolitePrior::_updateMu() {
	if (_mu->isUpdated()) {
		const double LLratio = 0.0;
		const double logH    = LLratio + _mu->getLogRatio();
		_mu->acceptOrReject(logH, coretools::TRange(0));
	}
}

void TMetabolitePrior::updateParams() {
	_updateGamma();
	_updateDelta();
	_updateMu();
}

double TMetabolitePrior::_LLRatio(const TypeX *trueX, const TypeLotus *lotus, const TypeGamma *gamma,
                                  const TypeDelta *delta, const TypeGamma *gamma_new, const TypeDelta *delta_new) {}