#include "mangle.hpp"
#include "type.hpp"
#include <bitset>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <string>

// Prefix for all name mangles
const std::string mangle_prefix = "SRTE_";

static std::string mangle_type(std::shared_ptr<rt_type_base> type) {
    if (type->is_basic()) {
        return type->to_string();
    }

    if (type->get_kind() == rt_type_kind::Reference) {
        const auto &ref = static_cast<const rt_type_ref &>(*type);
        return "r-" + ref.get_inner()->to_string();
    } else if (type->get_kind() == rt_type_kind::Array) {
        const auto &arr = static_cast<const rt_type_array &>(*type);
        return "a-" + std::to_string(arr.get_capacity()) + "-" + arr.get_inner()->to_string();
    } else if (type->get_kind() == rt_type_kind::Function) {
        const auto &fn = static_cast<const rt_type_function &>(*type);
        std::stringstream buf;

        buf << "f" << fn.get_params().size() << "(";
        for (const auto &p : fn.get_params()) {
            const auto pm = mangle_type(p);
            buf << std::to_string(pm.size()) << pm;
        }

        const auto &rt = fn.get_return_type()->to_string();
        buf << std::to_string(rt.size()) << rt;

        return buf.str();
    } else {
        std::cerr << "Unimplemented mangle: " << (int)type->get_kind() << "\n";
        std::abort();
        return "";
    }
}

std::string mangle(std::string name, std::shared_ptr<rt_type_base> type, int vflags) {
    const auto mangled_type = mangle_type(type);
    return mangle_prefix + mangled_type + "-" + std::bitset<32>(vflags).to_string();
}
