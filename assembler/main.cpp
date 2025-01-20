#include "parser/drv/drv.hpp"
#include "scanner/fastscanner.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, const char *argv[]) {
    std::cout << std::boolalpha;

    if (argc == 1) {
        std::cerr << "Need one argument: <filename>\n";
        std::exit(1);
    }

    auto filename = argv[1];
    std::ifstream file(filename);
    std::stringstream buf;
    buf << file.rdbuf();
    file.close();

    fast_scanner f(buf.str(), filename);

    auto r = f.run();
    if (r.index() != 0) {
        const auto errors = std::get<std::vector<fast_scanner::error>>(r);
        for (auto err : errors) {
            std::cout << "Error: " << err.to_string() << "\n";
        }

        return 1;
    }

    token_buf *tbuf = std::get<token_buf *>(r);
    parser_drv drv;
    srte_parser::parser p(*tbuf, drv, "<input>");
    const auto status = p.parse();

    if (!drv.get_errors().empty()) {
        for (std::vector<parse_error>::size_type i = 0; i < drv.get_errors().size(); i++) {
            std::cout << i << ": " << drv.get_errors()[i].message << "\n";
        }
    } else {
        drv.get_result()->print();
    }

    delete tbuf;
    return (drv.get_errors().empty() ? 0 : 1) || (status != 0 ? 1 : 0);
}
