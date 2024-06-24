//
// Created by caduffm on 5/11/23.
//

#ifndef METABOLITE_INFERENCE_TMETABOLITETYPES_H
#define METABOLITE_INFERENCE_TMETABOLITETYPES_H

#include "coretools/Types/commonWeakTypes.h"
#include "coretools/Types/probability.h"
#include <cstdint>

//-------------------------------
// typedefs
//-------------------------------

// types of parameters/observations
typedef coretools::Positive TypeGamma;
typedef coretools::Positive TypeDelta;
typedef coretools::UnsignedInt16 TypeLotus;
typedef coretools::Boolean TypeX;
typedef coretools::Unbounded TypeMu;
typedef coretools::Positive TypeSigma;
typedef coretools::Positive TypeAlpha;
// ... add more

#endif // METABOLITE_INFERENCE_TMETABOLITETYPES_H
