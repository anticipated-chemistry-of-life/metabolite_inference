//
// Created by caduffm on 5/11/23.
//

#ifndef METABOLITE_INFERENCE_TMETABOLITETYPES_H
#define METABOLITE_INFERENCE_TMETABOLITETYPES_H

#include "coretools/Types/commonWeakTypes.h"
#include "coretools/Types/probability.h"
#include "coretools/Types/weakTypesWithLogExp.h"
#include <cstdint>

//-------------------------------
// typedefs
//-------------------------------

// types of parameters/observations
typedef coretools::Positive<double> TypeGamma;
typedef coretools::Positive<double> TypeDelta;
typedef coretools::UnsignedInt<uint16_t> TypeLotus;

// ... add more

#endif // METABOLITE_INFERENCE_TMETABOLITETYPES_H
