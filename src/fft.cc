#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <fftw3.h>
#include <cerrno>
#include "out_file.hh"

#define N 1024
#define LAMBDA 5.0e-7
#define SLIT_WIDTH 1.0e-4
#define D 1.0
#define L 5.0e-3
#define DELTA L/N
#define PI 3.14159265359


void fft(std::vector<double>& inp, std::vector<double>& out, bool forward);
void build_slit(std::vector<double> &slit);
void output_values(std::ofstream &out_file, std::vector<double> &psi);

// Run FFTW on given input.
void fft(std::vector<double>& inp, std::vector<double>& out, bool forward = true)
{
    fftw_plan plan = fftw_plan_dft_1d (
        inp.size() / 2,
        (fftw_complex *) &inp[0],
        (fftw_complex *) &out[0],
        forward ? FFTW_FORWARD : FFTW_BACKWARD,
        FFTW_ESTIMATE);

    fftw_execute(plan);
    fftw_destroy_plan(plan);
}

void build_slit(std::vector<double> &slit)
{
    std::vector<double> x(N);

    for (int i = 0; i < N; i++)
    {
        x[i] = (i - (N / 2)) * DELTA;

        // Set points within +/- SLIT_WIDTH from the centre to 1, others to 0.
        if ((x[i] * x[i]) < (0.25 * SLIT_WIDTH * SLIT_WIDTH))
        {
            slit[2 * i] = 1.0;
        }
        else
        {
            slit[2 * i] = 0.0;
        }

        // All complex parts of the slit function are 0.
        slit[2 * i + 1] = 0.0;
    }
}

void output_values(std::ofstream &out_file, std::vector<double> &psi)
{
    double amplitude_0;

    // Store centre amplitude for normalisation.
    amplitude_0 = psi[0]*psi[0] + psi[1]*psi[1];

    // Sort positive and negative 'frequency' components of FFT.
    for (int i = 0; i < N; i++)
    {
        double y;
        double amplitude;
        double phase;
        int j;
        double z, amp_theory;

        if (i < N /2)
	    {
	        y = - (N / 2 - i) * D * LAMBDA / L;
	        j = N + 2 * i;
	    }
        else
	    {
	        y = (i - (N / 2)) * D * LAMBDA / L;
	        j = 2 * i - N;
	    }

        // Calculate modulus squared and argument of complex wavefunction.
        amplitude = psi[j] * psi[j] + psi[j + 1] * psi[j + 1];
        amplitude /= amplitude_0;

        phase = atan2(psi[j + 1], psi[j]);

        // Calculate theoretical amplitude.
        z = 200 * PI * y;
        amp_theory = sin(z) / z;
        amp_theory = amp_theory * amp_theory;

        // Output results.
        out_file << y << "," <<
                 psi[j] << "," <<
                 psi[j + 1] << "," <<
                 amplitude << "," <<
                 phase << "," <<
                 amp_theory << std::endl;
    }
}

int main(int argc, char **argv)
{
    std::vector<double> slit(2 * N);
    std::vector<double> psi(2 * N);
    std::ofstream out_file;

    open_outfile(out_file, argc, argv);
    if (!out_file.is_open())
    {
      std::cerr << "Error, could not open specified file." << std::endl;
      return EINVAL;
    }

    build_slit(slit);
    fft(slit, psi, true);
    output_values(out_file, psi);

    out_file.close();

    return 0;
}

