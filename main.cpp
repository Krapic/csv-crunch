#include <iostream>

static void print_usage(const char *prog)
{
    std::cerr << "Usage: " << prog << " <file.csv <column-name>\n";
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}