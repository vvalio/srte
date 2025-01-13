#include "parser/drv/drv.hpp"
#include "scanner/fastscanner.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Testing scanner\n";

    std::string line;
    std::getline(std::cin, line, static_cast<char>(EOF));
    fast_scanner f(line, "<input>");

    auto r = f.run();
    if (r.index() != 0) {
        const auto errors = std::get<std::vector<fast_scanner::error>>(r);
        for (auto err : errors) {
            std::cout << "Error: " << err.to_string() << "\n";
        }

        return 1;
    }

    token_buf *tbuf = std::get<token_buf *>(r);
    std::cout << tbuf->to_string() << "\n";

    parser_drv drv;
    srte_parser::parser p(*tbuf, drv, "<input>");
    const auto status = p.parse();

    std::cout << status << "\n";
    if (status != 0) {
        for (std::vector<parse_error>::size_type i = 0; i < drv.get_errors().size(); i++) {
            std::cout << i << ": " << drv.get_errors()[i].message << "\n";
        }
    } else {
        drv.get_result()->print();
    }

    delete tbuf;
    return 0;
}
