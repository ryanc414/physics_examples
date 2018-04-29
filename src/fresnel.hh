// Header file for Fresnel integral numerical solver
#include <iostream>
#include <fstream>
#include <cmath>
#include <gsl/gsl_integration.h>
#include <vector>
#include <assert.h>
#include <cerrno>
#include "estimate.hh"

#define PI 3.14159265359
#define EPSREL 1e-7
#define LIMIT 1000
#define N 10000
#define MAX_ULIMIT 8.0

double c(double x, void *params);
double s(double x, void *params);
void fresnel_integrate(ESTIMATE *estimates,
                       const std::vector<double> &u_limits,
                       gsl_integration_workspace *workspace);

