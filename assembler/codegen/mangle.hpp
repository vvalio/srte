// Name mangling routines.
#pragma once
#include "type.hpp"
#include <string>

// Mangles the passed name according to the type and visibility flags.
std::string mangle(std::string name, std::shared_ptr<rt_type_base> type, int vflags);
