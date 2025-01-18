// This file contains AST related classes.
#pragma once
#include "parser/location.hh"
#include "type.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

// Points to a source file specific location (for error messages)
struct ast_location {
    std::string file_name;
    unsigned int line;
    unsigned int col;

  private:
    ast_location(const std::string &fn, unsigned int l, unsigned int c) : file_name(fn), line(l), col(c) {}

  public:
    ast_location() {}

    std::string to_string();
    static std::shared_ptr<ast_location> from_bison_location(srte_parser::location loc, const std::string &filename);
};

// The type of AST node
enum class ast_type {
    AssemblyUnit,
    VersionDeclaration,
    GlobalVariableDeclaration,
    TypeId,
    Value,
    FunctionDef,
    FunctionParameter,
    RegisterReference,
    InstructionInvocation,
    AssignInstructionInvocation,
    VoidInstructionInvocation,
};

// Base class for all AST nodes.
class ast_base {
  private:
    std::shared_ptr<ast_location> _location;

  protected:
    ast_base() {}
    virtual ~ast_base() {}
    ast_base(std::shared_ptr<ast_location> loc) : _location(loc) {}
    ast_base(const ast_base &o);

  public:
    std::shared_ptr<ast_location> get_location() { return _location; }

    // Should be a constant implementation in the base class
    virtual ast_type get_type() = 0;
    virtual std::vector<std::shared_ptr<ast_base>> get_children() = 0;
    virtual void print(int indent = 4, std::ostream &stream = std::cout) = 0;
};

class version_decl final : public ast_base {
  private:
    unsigned char _maj, _min, _patch;

  public:
    version_decl(std::shared_ptr<ast_location> loc, unsigned char maj, unsigned char min, unsigned char p)
        : ast_base(loc), _maj(maj), _min(min), _patch(p) {}
    ~version_decl() {}

    std::vector<std::shared_ptr<ast_base>> get_children() override { return {}; }
    ast_type get_type() override { return ast_type::VersionDeclaration; }
    void print(int indent = 4, std::ostream &stream = std::cout) override;

    inline unsigned char get_major_version() { return _maj; }
    inline unsigned char get_minor_version() { return _min; }
    inline unsigned char get_patch_version() { return _patch; }
};

class type_id : public ast_base {
  private:
    std::shared_ptr<rt_type_base> _type;

  public:
    type_id(std::shared_ptr<ast_location> loc, std::shared_ptr<rt_type_base> typ) : ast_base(loc), _type(typ) {}
    ~type_id() {}

    ast_type get_type() override { return ast_type::TypeId; }
    std::vector<std::shared_ptr<ast_base>> get_children() override { return {}; }
    void print(int indent = 4, std::ostream &stream = std::cout) override;

    inline std::shared_ptr<rt_type_base> get_rt_type() { return _type; }
};

class named_base : public ast_base {
  public:
    named_base(std::shared_ptr<ast_location> l) : ast_base(l) {}

    virtual std::string get_exported_symbol() = 0;
    virtual std::shared_ptr<rt_type_base> get_exported_type() = 0;
};

class value_base : public ast_base {
  private:
    std::string _vstr;

  public:
    value_base(std::shared_ptr<ast_location> l, const std::string &vstr) : ast_base(l), _vstr(vstr) {}

    inline std::string get_vstr() { return _vstr; }
    ast_type get_type() override final { return ast_type::Value; }
};

class int_value : public value_base {
  public:
    enum class format {
        Hex,
        Dec,
        Bin,
    };

  private:
    std::uint64_t _val;
    format _fmt;

  public:
    int_value(std::shared_ptr<ast_location> l, const std::string &vstr, std::uint64_t val, format fmt)
        : value_base(l, vstr), _val(val), _fmt(fmt) {}

    inline std::uint64_t get_val() { return _val; }
    inline format get_fmt() { return _fmt; }
    std::vector<std::shared_ptr<ast_base>> get_children() override { return {}; }
    void print(int indent = 4, std::ostream &ost = std::cout) override;
};

class str_value : public value_base {
  public:
    enum class format {
        Utf8,
        Utf16,
        Utf32,
    };

  private:
    format _fmt;
    std::vector<unsigned char> _data;

  public:
    str_value(std::shared_ptr<ast_location> l, const std::string &vstr, format fmt, std::vector<unsigned char> data)
        : value_base(l, vstr), _fmt(fmt), _data(data) {}

    inline format get_fmt() { return _fmt; }
    inline std::vector<unsigned char> get_data() { return _data; }
    std::vector<std::shared_ptr<ast_base>> get_children() override { return {}; }
    void print(int indent = 4, std::ostream &ost = std::cout) override;
};

class global_var : public named_base {
  private:
    std::uint32_t _flags;
    std::string _name;
    std::shared_ptr<type_id> _type;
    std::shared_ptr<value_base> _value;

  public:
    global_var(std::shared_ptr<ast_location> l, int f, const std::string &n, std::shared_ptr<type_id> t,
               std::shared_ptr<value_base> v)
        : named_base(l), _flags(f), _name(n), _type(t), _value(v) {}
    ~global_var() {}

    std::uint32_t get_flags() { return _flags; }
    std::string get_exported_symbol() override { return _name; }
    std::shared_ptr<type_id> get_constant_type() { return _type; }
    std::shared_ptr<value_base> get_value() { return _value; }
    std::shared_ptr<rt_type_base> get_exported_type() override { return _type->get_rt_type(); }
    ast_type get_type() override { return ast_type::GlobalVariableDeclaration; }
    std::vector<std::shared_ptr<ast_base>> get_children() override { return {_type, _value}; }
    void print(int indent = 4, std::ostream &ostream = std::cout) override;

    static inline constexpr const std::uint32_t MOD_CONST = 1 << 0;
    static inline constexpr const std::uint32_t MOD_STATIC = 1 << 1;
};

class function_param final : public ast_base {
  private:
    std::shared_ptr<type_id> _type;
    std::uint32_t _param_index;
    std::uint32_t _flags;

  public:
    function_param(std::shared_ptr<ast_location> loc, std::shared_ptr<type_id> type, std::uint32_t param_index,
                   std::uint32_t flags)
        : ast_base(loc), _type(type), _param_index(param_index), _flags(flags) {}

    ast_type get_type() override { return ast_type::FunctionParameter; }
    std::vector<std::shared_ptr<ast_base>> get_children() override { return {}; }
    void print(int indent = 4, std::ostream &stream = std::cout) override;

    inline std::shared_ptr<type_id> get_param_type() { return _type; }
    inline std::uint32_t get_param_index() { return _param_index; }
    inline std::uint32_t get_flags() { return _flags; }
};

class function_def final : public named_base {
  private:
    std::uint32_t _flags;
    std::string _name;
    std::shared_ptr<type_id> _return_type;
    std::vector<std::shared_ptr<function_param>> _params;

  public:
    function_def(std::shared_ptr<ast_location> loc, std::uint32_t flags, const std::string &name,
                 std::shared_ptr<type_id> return_type, std::vector<std::shared_ptr<function_param>> params)
        : named_base(loc), _flags(flags), _name(name), _return_type(return_type), _params(params) {}

    std::shared_ptr<rt_type_base> get_exported_type() override;
    std::vector<std::shared_ptr<ast_base>> get_children() override;
    void print(int indent = 4, std::ostream &ost = std::cout) override;

    std::string get_exported_symbol() override { return _name; }
    ast_type get_type() override { return ast_type::FunctionDef; }

    inline std::uint32_t get_flags() { return _flags; }
    inline std::string get_name() { return _name; }
    inline std::shared_ptr<type_id> get_return_type() { return _return_type; }
    inline std::vector<std::shared_ptr<function_param>> get_params() { return _params; }

    static inline constexpr const std::uint32_t MOD_STATIC = 1 << 0;
    static inline constexpr const std::uint32_t MOD_EXPORT = 1 << 1;
    static inline constexpr const std::uint32_t MOD_PURE = 1 << 2;
};

// A reference to a register, spelled out as #XXX where XXX is any number.
// May be in the assignment side of an instruction:
//  #0 = addi $0, 2
// or used as a value to one:
//  ret #0
class register_reference final : public ast_base {
  private:
    std::uint32_t _reg_idx; // the index to the register, e.g. the XXX in #XXX

  public:
    register_reference(std::shared_ptr<ast_location> loc, std::uint32_t reg_idx) : ast_base(loc), _reg_idx(reg_idx) {}

    inline std::uint32_t get_reg_idx() { return _reg_idx; }
    ast_type get_type() override { return ast_type::RegisterReference; }
    std::vector<std::shared_ptr<ast_base>> get_children() override { return {}; }
    void print(int indent = 4, std::ostream &stream = std::cout) override;
};

// An invocation of an instruction. This is an abstract class, see
// `assign_instruction_invocation` and `void_instruction_invocation`.
class instruction_invocation : public ast_base {
  private:
    // whether the instruction returns a value
    // NOTE: does not take a stance on what kind of instruction invocation this is, since
    // a returned value can also be ignored.
    bool _produces_value;
};

class assembly_unit final : public ast_base {
  private:
    std::string _filename;
    std::shared_ptr<version_decl> _version;
    std::vector<std::shared_ptr<global_var>> _globals;
    std::vector<std::shared_ptr<function_def>> _funcs;

  public:
    assembly_unit(std::string fname) : _filename(fname) {}
    ~assembly_unit() {}

    void set_version(std::shared_ptr<version_decl> vd);
    void add_globals(std::vector<std::shared_ptr<global_var>> globals);
    void add_functions(std::vector<std::shared_ptr<function_def>> funcs);

    ast_type get_type() override { return ast_type::AssemblyUnit; }
    std::vector<std::shared_ptr<ast_base>> get_children() override;
    void print(int indent = 4, std::ostream &stream = std::cout) override;
};
