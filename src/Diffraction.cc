#include <iostream>
#include <cmath>
#include <gsl/gsl_integration.h>
#include <vector>
#include <fstream>
#include <string>

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

std::vector<double> Integrate (double u0, double u1)
{
  gsl_integration_workspace * w = gsl_integration_workspace_alloc(1000);

  std::vector<double> result(2);
  std::vector<double> error(2);

  gsl_function F;
  F.function = &f;

  gsl_integration_qags (&F, u0, u1, 0, 1e-7, 1000, w, &result[0], &error[0]);

  F.function = &g;

  gsl_integration_qags (&F, u0, u1, 0, 1e-7, 1000, w, &result[1], &error[1]);

  //integrate functions f and g using GSL routine

  return result;
}

void Fresnel(double D, std::string filename)
{
  double d = 10.0;
  double lambda = 1;
  double N = 1.0e4;
  double fraction;
  double limit = 20;
  double scale = sqrt(2 / (lambda * D));
  double x, u0, u1;
  std::vector<double> psi(2);
  double amplitude;
  double phase;
  double a0, p0;

  std::ofstream file;
  file.open (filename.c_str());
  //creates or opens file with name given in parameters

  u0 = (-0.5 * d) * scale;
  u1 = (0.5 * d) * scale;

  psi = Integrate(u0,u1);

  a0 = psi[0] * psi[0] + psi[1] * psi[1];
  p0 = atan2(psi[1],psi[0]);

  //evaluates integrals at x = 0 and stores amplitude and phase for normalisation

  for(double i = 0.0; i < N; i++)
    {
      fraction = i / N - 0.5;
      x = 2 * fraction * limit;

      u0 = (-0.5 * d + x) * scale;
      u1 = (0.5 * d + x) * scale;

      psi = Integrate(u0,u1);

      amplitude = (psi[0] * psi[0] + psi[1] * psi[1]) / a0;
      //divide by a0 to normalise relative amplitude
      phase = atan2(psi[1],psi[0]) - p0;
      //take away p0 so that phases are relative to centre

      file << x << "\t" << amplitude << "\t" << phase << "\n";
    }
  //for N values of x in the range -limit to +limit, evaluate the wavefunction and amplitudes and output these values to file

  file.close();

}

int main()
{
  Fresnel(30, "30cm Diffraction.txt");
  Fresnel(50, "50cm Diffraction.txt");
  Fresnel(100, "100cm Diffraction.txt");

  //run Fresnel diffraction routine for D = 30, 50 and 100.

  return 0;
}
