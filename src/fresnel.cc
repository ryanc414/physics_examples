#include "fresnel.hh"

// Fresnel integral functions C(x) and S(x).
double c(double x, void *params)
{
    double z = 0.5 * PI * x * x;
    return cos(z);
}

double s(double x, void *params)
{
    double z = 0.5 * PI * x * x;
    return sin(z);
}

// Make an estimate of the Fresnel integrals between given limits. Output
// values into estimates param.
void fresnel_integrate(ESTIMATE *estimates,
                       const std::vector<double> &u_limits,
                       gsl_integration_workspace *workspace)
{
    gsl_function func_c;
    gsl_function func_s;

    assert(u_limits.size() == 2);

    // Integrate functions c and s using GSL routine.
    func_c.function = &c;
    gsl_integration_qags(&func_c, u_limits[0], u_limits[1], 0, EPSREL, LIMIT, workspace,
                         &estimates[0].value, &estimates[0].error);

    func_s.function = &s;
    gsl_integration_qags(&func_s, u_limits[0], u_limits[1], 0, EPSREL, LIMIT, workspace,
                         &estimates[1].value, &estimates[1].error);
}

