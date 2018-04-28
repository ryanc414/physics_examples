#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <cmath>
#include <iostream>
#include <cstdint>

#define PI 3.14159265359
#define N 10000000
#define OMEGA 2.0/3.0
#define T_LIMIT 10 * 2 * PI
#define AMPLITUDE 0.01
#define Q 1.0
#define F 1.0

// Parameters used by ODE function.
struct ParamsContainer
{
    // Damping factor
    double q;

    // Driving force amplitude
    double f;

    // Driving force frequency
    double omega;
};

int calc_odes(double t, const double *x, double *dxdt, void *vparams);
int jac(double t, const double *x, double *dfdy, double *dfdt, void *vparams);
void print_values(double *x, double t, double amplitude);

// Calculate the values of both ODEs for given t and x inputs.
int calc_odes(double t, const double *x, double *dxdt, void *vparams)
{
    ParamsContainer *params = (ParamsContainer *)vparams;

    dxdt[0] = x[1];
    dxdt[1] = -sin(x[0]) - params->q * x[1] + params->f * sin(params->omega * t);

    return GSL_SUCCESS;
}

// Calculate Jacobian of the ODE system.
int jac(double t, const double *x, double *dfdy, double *dfdt, void *vparams)
{
    ParamsContainer *params = (ParamsContainer *)vparams;
    gsl_matrix_view dfdy_mat; 
    gsl_matrix *m;

    dfdy_mat = gsl_matrix_view_array(dfdy, 2, 2);
    m = &dfdy_mat.matrix;

    gsl_matrix_set(m, 0, 0, 0.0);
    gsl_matrix_set(m, 0, 1, 1.0);
    gsl_matrix_set(m, 1, 0, -cos(x[0]));
    gsl_matrix_set(m, 1, 1, -params->q);

    dfdt[0] = 0.0;
    dfdt[1] = params->f * cos(params->omega * t);

    return GSL_SUCCESS;
}

int main()
{
    ParamsContainer params = {.q = Q, .f = F, .omega = OMEGA};
    double t_0 = 0.0;

    // x[0] and x[1] represent the position and velocity of the pendulum respectively.
    double x[] = {AMPLITUDE, 0.0};
    gsl_odeiv2_system sys;
    gsl_odeiv2_driver *driver;

    // Define the ODE system for GSL and set the required precision.
    sys = {calc_odes, jac, 2, &params};
    driver = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);

    // Print headers.
    std::cout << "t,x,v,energy,x theory" << std::endl;

    for (uint32_t i = 1; i<= N; i++)
    {
        double t;
        int status;

        t = (i * T_LIMIT) / N;
        
        // TODO understand why this needs t_0
        status = gsl_odeiv2_driver_apply(driver, &t_0, t, x);
        if (status != GSL_SUCCESS)
        {
            std::cout << "Error, step " << i << " failed with return code = " << status << std::endl;
            break;
        }
    
        // Output data every 100 steps.
        if (i % 100 == 0)
        {
            print_values(x, t, AMPLITUDE);
        }
    }

    gsl_odeiv2_driver_free(driver);
    
    return 0;
}

void print_values(double *x, double t, double amplitude)
{
    double energy;
    double x_theory;

    // Calculate energy using m = g = l = 1 for simplicity.
    energy = 0.5 * x[1] * x[1] + 1 - cos(x[0]);

    // Calculate theoretical value of SHM for undamped free oscillations
    x_theory = amplitude * cos(t);	  

    std::cout << t << "," << x[0] << "," << x[1] << 
                 "," << energy << "," << x_theory << std::endl;
}

