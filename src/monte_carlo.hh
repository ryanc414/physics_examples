// Header file for Monte Carlo integrator. Provides interface for numerically
// integrating using the Monte Carlo method.

#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>
#include <vector>

#define N_DIMENSIONS 8
#define S M_PI/N_DIMENSIONS
#define V pow(S, N_DIMENSIONS)
#define PRE_CONST pow(10, 6)

// Stores an estimated value and approximate error.
typedef struct estimate
{
    double value;
    double error;
} ESTIMATE;

// Numerically estimate a given integrand. Estimate value and error is stored
// in the result struct.
void estimate_integral(ESTIMATE *result,
                       gsl_rng* rng,
                       int n_samples,
                       double (*integrand)(double *));

