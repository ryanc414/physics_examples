#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include "out_file.hh"

void open_outfile(std::ofstream &out_file, int argc, char **argv)
{
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
}

// Retrieve the value after given option flag, or NULL if none is found.
// Credit to: https://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c
char *get_cmd_options(int argc, char **argv, const std::string &option)
{
    char **end = argv + argc;
    char **itr = std::find(argv, end, option);

    if ((itr != end) && (++itr != end))
    {
      return *itr;
    }

    return NULL;
}

