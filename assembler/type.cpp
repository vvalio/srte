#include "type.hpp"

bool rt_type_basic::is_assignable_to(const rt_type_base &other) const { return equals(other); }

bool rt_type_basic::equals(const rt_type_base &other) const {
    if (!other.is_basic()) {
        return false;
    }

    const auto &typ = static_cast<const rt_type_basic &>(other);
    return typ.get_kind() == get_kind();
}

bool rt_type_function::is_assignable_to(const rt_type_base &other) const { return equals(other); }

bool rt_type_function::equals(const rt_type_base &other) const {
    if (other.get_kind() != rt_type_kind::Function) {
        return false;
    }

    const auto &typ = static_cast<const rt_type_function &>(other);
    if (!_return_type->equals(*typ._return_type)) {
        return false;
    } else if (_params.size() != typ._params.size()) {
        return false;
    }

    for (decltype(_params)::size_type i = 0; i < _params.size(); i++) {
        if (!_params[i]->equals(*typ._params[i])) {
            return false;
        }
    }

    return true;
}

bool rt_type_ref::is_assignable_to(const rt_type_base &other) const { return equals(other); }

bool rt_type_ref::equals(const rt_type_base &other) const {
    if (other.get_kind() != rt_type_kind::Reference) {
        return false;
    }

    const auto &typ = static_cast<const rt_type_ref &>(other);
    return typ._inner->equals(*_inner);
}

bool rt_type_array::is_assignable_to(const rt_type_base &other) const { return equals(other); }

bool rt_type_array::equals(const rt_type_base &other) const {
    if (other.get_kind() != rt_type_kind::Array) {
        return false;
    }

    const auto &typ = static_cast<const rt_type_array &>(other);
    return typ._capacity == _capacity && typ._inner->equals(*_inner);
}
