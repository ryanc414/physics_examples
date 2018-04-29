#include <algorithm>
#include <string>

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

