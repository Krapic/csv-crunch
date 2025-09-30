#include <iostream>
#include <fstream>
#include <string>

static void print_usage(const char *prog)
{
    std::cerr << "Usage: " << prog << " <file.csv> <column-name>\n";
}

static void trim_cr(std::string& s) {
    if (!s.empty() && s.back() == '\r') s.pop_back();
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        print_usage(argv[0]);
        return 1;
    }

    const char* path = argv[1];

    std::ifstream in(path);
    if (!in) {
        std::cerr << "Error: cannot open '" << path << "'\n";
        return 2;
    }

    std::string line;
    if (!std::getline(in, line)) {
        std::cerr <<"Error: empty file\n";
        return 3;
    }
    trim_cr(line);

    std::size_t rows = 0;
    while (std::getline(in, line)) {
        trim_cr(line);
        if (line.empty()) continue;
        ++rows;
    }

    std::cout << "Rows: " << rows << '\n';

    return 0;
}