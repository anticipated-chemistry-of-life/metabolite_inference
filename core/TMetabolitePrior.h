//
// Created by caduffm on 5/11/23.
//

#ifndef METABOLITE_INFERENCE_TMETABOLITEPRIOR_H
#define METABOLITE_INFERENCE_TMETABOLITEPRIOR_H

#include "TMetaboliteTypes.h"
#include "coretools/Types/TStringHash.h"
#include "stattools/ParametersObservations/TNodeBase.h"
#include "stattools/ParametersObservations/TNodeTyped.h"
#include "stattools/ParametersObservations/TObservation.h"
#include "stattools/ParametersObservations/TParameter.h"
#include "stattools/Priors/TPriorBase.h"
#include "stattools/Priors/TPriorBernoulli.h"
#include "stattools/Priors/TPriorExponential.h"
#include "stattools/Priors/TPriorNormal.h"
#include <sys/_types/_int64_t.h>

class TMetabolitePrior : public stattools::prior::TBaseLikelihoodPrior<stattools::TObservationBase, TypeLotus, 2> {
private:
	using typename stattools::prior::TBaseLikelihoodPrior<stattools::TObservationBase, TypeLotus, 2>::Storage;
	using typename stattools::prior::TBaseLikelihoodPrior<stattools::TObservationBase, TypeLotus, 2>::UpdatedStorage;

protected:
	// data
	// stattools::TObservation<TypeLotus, 2> *_lotus = nullptr;
	// ... add more

	// parameters
	// gamma
	using BoxOnGamma = stattools::prior::TExponentialFixed<stattools::TParameterBase, TypeGamma, 1>;
	using SpecGamma  = stattools::ParamSpec<TypeGamma, stattools::Hash<coretools::toHash("gamma")>, BoxOnGamma>;
	stattools::TParameter<SpecGamma, BoxOnGamma> *_gamma = nullptr;

	// delta
	using BoxOnDelta = stattools::prior::TExponentialFixed<stattools::TParameterBase, TypeDelta, 1>;
	using SpecDelta  = stattools::ParamSpec<TypeDelta, stattools::Hash<coretools::toHash("delta")>, BoxOnDelta>;
	stattools::TParameter<SpecDelta, BoxOnDelta> *_delta = nullptr;

	// trueX
	using BoxOnX = stattools::prior::TBernoulliFixed<stattools::TParameterBase, TypeX, 2>;
	using SpecX  = stattools::ParamSpec<TypeX, stattools::Hash<coretools::toHash("X")>, BoxOnX, stattools::NumDim<2>>;
	stattools::TParameter<SpecX, BoxOnX> *_trueX = nullptr;

	// mu
	using BoxOnMu = stattools::prior::TNormalFixed<stattools::TParameterBase, TypeMu, 1>;
	using SpecMu =
	    stattools::ParamSpec<TypeMu, stattools::Hash<coretools::toHash("mu")>, BoxOnMu, stattools::NumDim<1>>;
	stattools::TParameter<SpecMu, BoxOnMu> *_mu = nullptr;

	// prefix for writing
	std::string _out;
	void _simulateUnderPrior(Storage *Data) override;

	// update functions
	void _updateGamma();
	void _updateDelta();
	static void _updateX();
	void _updateMu();
	double _LLRatio(const TypeX *trueX, const TypeLotus *lotus, const TypeGamma *gamma, const TypeDelta *delta,
	                const TypeGamma *gamma_new, const TypeDelta *delta_new);

public:
	TMetabolitePrior(stattools::TParameter<SpecGamma, BoxOnGamma> *Gamma,
	                 stattools::TParameter<SpecDelta, BoxOnDelta> *Delta, std::string Prefix);
	~TMetabolitePrior() override = default;

	[[nodiscard]] std::string name() const override;

	// estimate initial values
	void estimateInitialPriorParameters();

	// full log densities
	double getSumLogPriorDensity(const Storage &) const override;

	// update all parameters
	void updateParams();
};

#endif // METABOLITE_INFERENCE_TMETABOLITEPRIOR_H
