/*
 * TExampleTask.cpp
 *
 *  Created on: May 15, 2023
 *      Author: mvisani
 */

#include "TCore.h"
#include "coretools/Main/TError.h"
#include "coretools/Storage/TDataFile.h"
#include "stattools/MCMC/TMCMC.h"
#include "stattools/Priors/TPriorExponential.h"
#include "stattools/Priors/TPriorNormal.h"

using namespace coretools::instances;

//--------------------------------------
// TMetaboliteModel
//--------------------------------------
