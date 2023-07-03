//
// Created by caduffm on 5/11/23.
//

#ifndef METABOLITE_INFERENCE_TMETABOLITEPRIOR_H
#define METABOLITE_INFERENCE_TMETABOLITEPRIOR_H

#include "TMetaboliteTypes.h"
#include "stattools/ParametersObservations/TObservationTyped.h"
#include "stattools/ParametersObservations/TParameterTyped.h"
#include "stattools/Priors/TPriorBase.h"

class TMetabolitePrior : public stattools::prior::TBaseLikelihoodPrior<stattools::TObservationBase, TypeLotus, 2> {
private:
	using typename stattools::prior::TBaseLikelihoodPrior<stattools::TObservationBase, TypeLotus, 2>::Storage;
	using typename stattools::prior::TBaseLikelihoodPrior<stattools::TObservationBase, TypeLotus, 2>::UpdatedStorage;

protected:
	// data
	stattools::TObservationTyped<TypeLotus, 2> *_lotus = nullptr;

	// parameters
	stattools::TParameterTyped<TypeGamma, 1> *_gamma = nullptr;
	stattools::TParameterTyped<TypeDelta, 1> *_delta = nullptr;
	stattools::TParameterTyped<TypeX, 2> *_trueX     = nullptr;
	stattools::TParameterTyped<TypeMu, 1> *_mu       = nullptr;
	// ... add more

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

public : TMetabolitePrior(stattools::TParameterTyped<TypeGamma, 1> *Gamma,
	                              stattools::TParameterTyped<TypeDelta, 1> *Delta, std::string Prefix);
	~TMetabolitePrior() override = default;

	void initializeInferred() override;

	[[nodiscard]] std::string name() const override;

	// estimate initial values
	void estimateInitialPriorParameters() override;

	// full log densities
	double getSumLogPriorDensity(const Storage &) const override;

	// update all parameters
	void updateParams() override;
};

#endif // METABOLITE_INFERENCE_TMETABOLITEPRIOR_H
