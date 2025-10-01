#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

static void print_usage(const char *prog)
{
    std::cerr << "Usage: " << prog << " <file.csv> <column-name>\n";
}

static void trim_cr(std::string& s) {
    if (!s.empty() && s.back() == '\r') s.pop_back();
}

std::vector<std::string> parse_line(std::string_view line) {
    std::vector<std::string> out;

    const std::size_t estimated_fields = static_cast<std::size_t>(std::count(line.begin(), line.end(), ',')) + 1;
    out.reserve(estimated_fields);

    std::string current;
    for (const char ch : line) {
        if (ch == ',') {
            out.emplace_back(std::move(current));
            current.clear();
        } else current.push_back(ch);
    }
    out.emplace_back(std::move(current));
    return out;
}

int main(const int argc, char **argv)
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

    std::cout << "rows: " << rows << '\n';

#ifdef DEBUG
    auto dump = [](std::string_view s) {
        auto toks = parse_line(s);
        std::cout << s << "  ->  ";
        for (std::size_t i = 0; i < toks.size(); ++i) {
            std::cout << "[" << toks[i] << "]";
            if (i + 1 < toks.size()) std::cout << "|";
        }
        std::cout << "\n";
    };

    dump("a,b,c");        // [a]|[b]|[c]
    dump("x,,y");         // [x]|[]|[y]
    dump(",");            // []|[]
    dump("");             // []
    dump("Alice,30,72.5"); // [Alice]|[30]|[72.5]
    dump(" a , b ");      // [ a ]|[ b ]  (bez trimanja)
#endif

    return 0;
}