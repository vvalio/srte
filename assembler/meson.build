sources = [
    'main.cpp',
    'ast.cpp',
    'astprint.cpp',
    'numparse.cpp',
    'opcode.cpp',
    'type.cpp',
    'codegen/codegen.cpp',
    'codegen/codegencontext.cpp',
    'codegen/llvmtype.cpp',
    'codegen/mangle.cpp',
    'scanner/fastscanner.cpp',
    'parser/srte-asm-parser.cpp',
    'parser/drv/drv.cpp',
]

inc_dirs = [
    include_directories('.'),
]

dependencies = [
    dependency('llvm'),
]

cpp_args = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-Wno-unused-parameter',
    '-Wno-unused-function',
    '-Wno-unused-variable',
    '-Wno-unused-private-field',
    '-Wno-unused-but-set-variable', # bison
    '-Wpedantic',
    '-std=c++17',
]

executable(
    'assrte',
    sources: sources,
    cpp_args: cpp_args,
    include_directories: inc_dirs,
    dependencies: dependencies,
    install: true,
)
