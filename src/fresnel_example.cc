#include "fresnel.hh"

int main(void)
{
    double fraction;
    unsigned int i;
    ESTIMATE estimates[2];
    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(LIMIT);
    std::vector<double> u_limits(2);

    // Set the lower limit to 0 for all the integrals.
    u_limits[0] = 0.0;

    // Print out headings
    std::cout << "u,c value,c error,s value,s error\n"; 
    
    // For N values of u in the range -limit to +limit, find C(u) and S(u).
    for (i = 0; i <= N; i++) {
        fraction = ((double) i)/N - 0.5;
        u_limits[1] = 2 * MAX_ULIMIT * fraction;
        fresnel_integrate(estimates, u_limits, workspace);
      
        // Output values and errors.
        std::cout << u_limits[1] << ","
                  << estimates[0].value << "," << estimates[0].error << ","
                  << estimates[1].value << "," << estimates[1].error << "\n";
    }

    gsl_integration_workspace_free(workspace);

    return 0; 
}

