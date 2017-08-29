#include <iostream>
#include <cmath>
#include <gsl/gsl_integration.h>
#include <vector>

double f (double x, void * params)
{
  const double pi = 3.14159265359;
  double z;

  z = 0.5 * pi * x * x;
  return cos(z);

  //evaluates integrand for C(u)
}

double g (double x, void * params)
{
  const double pi = 3.14159265359;
  double z;

  z = 0.5 * pi * x * x;
  return sin(z);

  //evaluates integrand for S(u)
}

std::vector<double> Integrate (double u)
{
  gsl_integration_workspace * w = gsl_integration_workspace_alloc(1000);

  std::vector<double> result(2);
  std::vector<double> error(2);

  gsl_function F;
  F.function = &f;

  gsl_integration_qags (&F, 0, u, 0, 1e-7, 1000, w, &result[1], &error[1]);

  F.function = &g;

  gsl_integration_qags (&F, 0, u, 0, 1e-7, 1000, w, &result[2], &error[2]);

  //integrate functions f and g using GSL routine

  std::cout << result[1] << "\t" << error[1] << "\t" << result[2] << "\t" << error[2] << "\n";
  //output results and errors

  return result;
}

int main ()
{
  double u;
  int N = 1e4;
  double ulimit = 8.0;
  double fraction;

  for (double i = 0; i < N+1; i++)
    {
      fraction = i/N - 0.5;
      u = 2 * ulimit * fraction;
      Integrate(u);
    }
  //for N values of u in the range -limit to +limit, find C(u) and S(u)

  return 0;
}
