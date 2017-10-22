// Find an aproximate value to the following integral numerically:
//
// 10^6 * Integrate(sin(x_0 + x_1 + x_2 + x_3 + x_4 + x_5 + x_6 + x_7)
//                  dx_0 dx_1 dx_2 dx_2 dx_3 dx_4 dx_5 dx_6 dx_7)
// With all integration variables taking values from 0 to S = pi/8.
//
// Use Monte-Carlo estimation to sample pseudo-random points over the 8D
// integral space and provide an estimate for the integral value and error.
#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>
#include <vector>
#include <assert.h>
#include "estimate.hh"

#define N_DIMENSIONS 8
#define S M_PI/N_DIMENSIONS
#define V pow(S, N_DIMENSIONS)
#define PRE_CONST pow(10, 6)

void estimate_integral(ESTIMATE *result,
                       gsl_rng* rng,
                       int n_samples,
                       double (*integrand)(const std::vector<double> &));
double integrand(const std::vector<double> &x);

int main(void)
{
    gsl_rng* rng = gsl_rng_alloc(gsl_rng_default);
    ESTIMATE result;

    estimate_integral(&result, rng, 100, integrand);
    result.value *= PRE_CONST;
    result.error *= PRE_CONST;

    std::cout << result.value << "\t" << result.error << "\n";

    return 0;
}

// The function to be integrated numerically.
double integrand(const std::vector<double> &x)
{
    assert(x.size() == N_DIMENSIONS);
    return sin(x[0]+x[1]+x[2]+x[3]+x[4]+x[5]+x[6]+x[7]);
}

// Numerically estimate the integral value.
void estimate_integral(ESTIMATE *result,
                       gsl_rng* rng,
                       int n_samples,
                       double (*integrand)(const std::vector<double> &))
{
    std::vector<double> x(N_DIMENSIONS);
    double f;
    double f_sum = 0.0;
    double f_sq_sum = 0.0;
    double f_average;
    double f_sq_average;

    for (int ii = 0; ii < n_samples; ii++)
    {
        // Generate random points in 8D space within integration limits.
        for (int jj = 0; jj < 8; jj++)
        {
            x[jj] = S * gsl_rng_uniform(rng);
        }

        // Update running total of intergrand.
        f = integrand(x);
        f_sum += f;
        f_sq_sum += f * f;
    }
    
    // Calculate the average of f and of f squared.
    f_average = (f_sum / n_samples);
    f_sq_average = (f_sq_sum / n_samples);

    // Store the estimated value and error in the result struct.
    result->value = V * f_average;
    result->error = V * sqrt((f_sq_average - (f_average * f_average)) / n_samples);
}

