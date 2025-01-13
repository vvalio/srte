// This file contains AST related classes.
#pragma once
#include "parser/location.hh"
#include "type.hpp"

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
};

class named_base : public ast_base {
  public:
    named_base(std::shared_ptr<ast_location> l) : ast_base(l) {}

    virtual std::string get_exported_symbol() = 0;
    virtual std::shared_ptr<type_id> get_type_id() = 0;
};

class value_base : public ast_base {
  public:
    value_base(std::shared_ptr<ast_location> l) : ast_base(l) {}

    virtual std::shared_ptr<rt_type_base> get_value_type() = 0;
};

class global_var : public named_base {
  private:
    int _flags;
    std::string _name;
    std::shared_ptr<type_id> _type;
    std::shared_ptr<value_base> _value;

  public:
    global_var(std::shared_ptr<ast_location> l, int f, const std::string &n, std::shared_ptr<type_id> t,
               std::shared_ptr<value_base> v)
        : named_base(l), _flags(f), _name(n), _type(t), _value(v) {}
    ~global_var() {}

    int get_flags() { return _flags; }
    std::string get_exported_symbol() override { return _name; }
    std::shared_ptr<type_id> get_constant_type() { return _type; }
    std::shared_ptr<value_base> get_value() { return _value; }
    std::shared_ptr<type_id> get_type_id() override { return _type; }
    ast_type get_type() override { return ast_type::GlobalVariableDeclaration; }
    std::vector<std::shared_ptr<ast_base>> get_children() override { return {_type, _value}; }
    void print(int indent = 4, std::ostream &ostream = std::cout) override;
};

class assembly_unit final : public ast_base {
  private:
    std::string _filename;
    std::shared_ptr<version_decl> _version;
    std::vector<std::shared_ptr<global_var>> _consts;

  public:
    assembly_unit(std::string fname) : _filename(fname) {}
    ~assembly_unit() {}

    void set_version(std::shared_ptr<version_decl> vd);
    void push_constant(std::shared_ptr<global_var> cd);

    ast_type get_type() override { return ast_type::AssemblyUnit; }
    std::vector<std::shared_ptr<ast_base>> get_children() override;
    void print(int indent = 4, std::ostream &stream = std::cout) override;
};
