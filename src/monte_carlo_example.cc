// Find an aproximate value to the following integral numerically:
//
// 10^6 * Integrate(sin(x_0 + x_1 + x_2 + x_3 + x_4 + x_5 + x_6 + x_7)
//                  dx_0 dx_1 dx_2 dx_2 dx_3 dx_4 dx_5 dx_6 dx_7)
// With all integration variables taking values from 0 to S = pi/8.
//
// Use Monte-Carlo estimation to sample pseudo-random points over the 8D
// integral space and provide an estimate for the integral value and error.

#include "monte_carlo.hh"

double integrand(double *x);

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

double integrand(double *x)
{
    return sin(x[0]+x[1]+x[2]+x[3]+x[4]+x[5]+x[6]+x[7]);
}

