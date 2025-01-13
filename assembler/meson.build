sources = [
    'main.cpp',
    'ast.cpp',
    'numparse.cpp',
    'scanner/fastscanner.cpp',
    'parser/srte-asm-parser.cpp',
    'parser/drv/drv.cpp',
]

inc_dirs = [
    include_directories('.'),
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
    install: true,
)
