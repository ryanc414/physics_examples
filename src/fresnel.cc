#include <iostream>
#include <cmath>
#include <gsl/gsl_integration.h>
#include <vector>
#include "monte_carlo.hh"

#define PI 3.14159265359
#define EPSREL 1e-7
#define LIMIT 1000
#define N 10000
#define ULIMIT 8.0

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

void integrate(double u, ESTIMATE *estimates)
{
    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(LIMIT);
    gsl_function func_c;
    gsl_function func_s;
  
    // Integrate functions c and s using GSL routine.
    func_c.function = &c;
    gsl_integration_qags(&func_c, 0, u, 0, EPSREL, LIMIT, workspace,
                         &estimates[0].value, &estimates[0].error);

    func_s.function = &s;
    gsl_integration_qags(&func_s, 0, u, 0, EPSREL, LIMIT, workspace,
                         &estimates[1].value, &estimates[1].error);
}

int main(void)
{
    double u;
    double fraction;
    unsigned int i;
    ESTIMATE estimates[2];

    // Print out headings
    std::cout << "u,c value,c error,s value,s error\n"; 
    
    //for N values of u in the range -limit to +limit, find C(u) and S(u)
    for (i = 0; i <= N; i++) {
        fraction = ((double) i)/N - 0.5;
        u = 2 * ULIMIT * fraction;
        integrate(u, estimates);
      
        //output values and errors
        std::cout << u << ","
                  << estimates[0].value << "," << estimates[0].error << ","
                  << estimates[1].value << "," << estimates[1].error << "\n";
    }

    return 0;
}

