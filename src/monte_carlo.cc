#include "monte_carlo.hh"

void estimate_integral(ESTIMATE *result,
                       gsl_rng* rng,
                       int n_samples,
                       double (*integrand)(double *))
{
    double x[N_DIMENSIONS];
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

