#include "fresnel.hh"

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

void fresnel_integrate(ESTIMATE *estimates,
                       std::vector<double> u_limits,
                       gsl_integration_workspace *workspace)
{
    gsl_function func_c;
    gsl_function func_s;
  
    // Integrate functions c and s using GSL routine.
    func_c.function = &c;
    gsl_integration_qags(&func_c, u_limits[0], u_limits[1], 0, EPSREL, LIMIT, workspace,
                         &estimates[0].value, &estimates[0].error);

    func_s.function = &s;
    gsl_integration_qags(&func_s, u_limits[0], u_limits[1], 0, EPSREL, LIMIT, workspace,
                         &estimates[1].value, &estimates[1].error);
}

