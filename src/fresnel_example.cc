#include "fresnel.hh"
#include "cmd_options.hh"

int main(int argc, char **argv)
{
    gsl_integration_workspace *workspace;
    std::vector<double> u_limits(2);
    std::ofstream out_file;
    const char *out_filename;
    std::string out_filename_str;

    out_filename = get_cmd_options(argc, argv, "-f");

    if (out_filename == NULL)
    {
        std::cout << "Enter output file name: ";
        std::cin >> out_filename_str;
        out_filename = out_filename_str.c_str();
    }

    out_file.open(out_filename, std::ios::out);
    if (!out_file.is_open())
    {
      std::cerr << "Error, could not open specified file." << std::endl;
      return EINVAL;
    }

    workspace = gsl_integration_workspace_alloc(LIMIT);

    // Set the lower limit to 0 for all the integrals.
    u_limits[0] = 0.0;

    // Print out headings
    out_file << "u,c value,c error,s value,s error" << std::endl;

    // For N values of u in the range -limit to +limit, find C(u) and S(u).
    for (unsigned int i = 0; i <= N; i++)
    {
        ESTIMATE estimates[2];
        double fraction = ((double) i)/N - 0.5;

        u_limits[1] = 2 * MAX_ULIMIT * fraction;
        fresnel_integrate(estimates, u_limits, workspace);

        // Output values and errors.
        out_file << u_limits[1] << ","
                 << estimates[0].value << "," << estimates[0].error << ","
                 << estimates[1].value << "," << estimates[1].error << std::endl;
    }

    std::cout << "Done" << std::endl;

    gsl_integration_workspace_free(workspace);
    out_file.close();

    return 0;
}

