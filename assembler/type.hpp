// Type representation used by the AST & others
#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

enum class rt_type_kind {
    // Builtin basic types. Represented by rt_type_basic
    I8,
    U8,
    I16,
    U16,
    I32,
    U32,
    I64,
    U64,
    I128,
    U128,
    Bool,
    Void,
    String,

    // Function type, represented by rt_type_function
    Function,
    // Reference to a type, represented by rt_type_ref
    Reference,
};

// Any runtime type, base class. Subclasses implement concrete types.
class rt_type_base {
  private:
    rt_type_kind _kind;

  public:
    rt_type_base(rt_type_kind k) : _kind(k) {}

    // Is this type a basic builtin type?
    inline bool is_basic() { return (int)_kind <= (int)rt_type_kind::String; }
    rt_type_kind get_kind() { return _kind; }

    virtual std::string to_string() = 0;
};

// Represents basic types.
class rt_type_basic final : public rt_type_base {
  public:
    rt_type_basic(rt_type_kind k) : rt_type_base(k) {}

    std::string to_string() override {
        switch (get_kind()) {
            case rt_type_kind::I8: return "i8";
            case rt_type_kind::U8: return "u8";
            case rt_type_kind::I16: return "i16";
            case rt_type_kind::U16: return "u16";
            case rt_type_kind::I32: return "i32";
            case rt_type_kind::U32: return "u32";
            case rt_type_kind::I64: return "i64";
            case rt_type_kind::U64: return "u64";
            case rt_type_kind::I128: return "i128";
            case rt_type_kind::U128: return "u128";
            case rt_type_kind::Bool: return "bool";
            case rt_type_kind::Void: return "void";
            case rt_type_kind::String: return "str";
            default: std::cerr << "bad type_kind in rt_type_basic: " << (int)get_kind() << "\n"; std::abort();
        }
    }
};

class rt_type_function final : public rt_type_base {
  private:
    std::shared_ptr<rt_type_base> _return_type;
    std::vector<std::shared_ptr<rt_type_base>> _params;

  public:
    std::string to_string() override {
        std::stringstream sr;
        sr << "function(";
        for (size_t i = 0; i < _params.size(); i++) {
            auto pt = _params[i];
            sr << pt->to_string();

            if (i != _params.size() - 1) {
                sr << ", ";
            }
        }

        sr << ") -> " << _return_type->to_string();
        return sr.str();
    }
};

class rt_type_ref final : public rt_type_base {
  private:
    std::shared_ptr<rt_type_base> _inner;

  public:
    inline std::shared_ptr<rt_type_base> get_inner() { return _inner; }
    std::string to_string() override { return "&" + _inner->to_string(); }
};
