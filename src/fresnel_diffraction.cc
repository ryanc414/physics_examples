#include <vector>
#include <fstream>
#include <string>
#include "fresnel.hh"

#define SCREEN_DISTANCE 10.0
#define LAMBDA 1.0
#define N_POINTS 10000
#define X_LIMIT 20.0
#define INTEGRATOR_LIMIT 1000

void calculate_amplitude_and_phase(double &amplitude,
                                   double &phase,
                                   double x_pos,
                                   double slit_width,
                                   gsl_integration_workspace *workspace);

void calculate_diffraction(double slit_width,
                           const std::string &filename,
                           gsl_integration_workspace *workspace);

// Calculate the amplitude and phase of the light at a given x position,
// storing the values at the amplitude and phase references provided.
void calculate_amplitude_and_phase(double &amplitude,
                                   double &phase,
                                   double x_pos,
                                   double slit_width,
                                   gsl_integration_workspace *workspace)
{
    ESTIMATE psi[2];
    std::vector<double> u_limits(2);
    double scale = sqrt(2 / (LAMBDA * slit_width));
  
    u_limits[0] = ((-0.5 * SCREEN_DISTANCE) + x_pos) * scale;
    u_limits[1] = ((0.5 * SCREEN_DISTANCE) + x_pos) * scale;

    fresnel_integrate(psi, u_limits, workspace);

    amplitude = psi[0].value * psi[0].value + psi[1].value * psi[1].value;
    phase = atan2(psi[1].value, psi[0].value);
}

// Calculate the diffraction pattern for a given slit width. Output the
// amplitude and phase of the diffracted light as a function of x position
// to the named file.
void calculate_diffraction(double slit_width,
                           const std::string &filename,
                           gsl_integration_workspace *workspace)
{
    double fraction;
    double x_pos;
    double amplitude;
    double phase;
    double amplitude0;
    double phase0;
    unsigned int i;

    // Create or open output file.
    std::ofstream file;
    file.open(filename.c_str());
    file << "x,amplitude,phase\n";
    
    // Evaluate integral at x = 0 and stores amplitude and phase for normalisation.
    calculate_amplitude_and_phase(amplitude0, phase0, 0, slit_width, workspace);

    // For N values of x in the range -X_LIMIT to +X_LIMIT, evaluate the wavefunction
    // and amplitudes and output these values to file.
    for (i = 0; i < N; i++) {
        fraction = ((double) i) / N - 0.5;
        x_pos = 2 * fraction * X_LIMIT;
        calculate_amplitude_and_phase(amplitude, phase, x_pos, slit_width, workspace);

        // Normalise the amplitude and phase relative to the values at x = 0.
        amplitude /= amplitude0;
        phase -= phase0;

        // Output the values to file.
        file << x_pos << "," << amplitude << "," << phase << "\n";
    }

    file.close();
}

int main()
{
    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(INTEGRATOR_LIMIT);

    // Run Fresnel diffraction routine for D = 30, 50 and 100.
    calculate_diffraction(30, "data/30cm_diffraction.csv", workspace);
    calculate_diffraction(50, "data/50cm_diffraction.csv", workspace);
    calculate_diffraction(100, "data/100cm_diffraction.csv", workspace);

    gsl_integration_workspace_free(workspace);

    return 0;
}

