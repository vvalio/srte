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
    'runtime-support/corelib.cpp',
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

ir_res_files = [
]

python_exe = find_program('python3', 'python')
params = [meson.project_source_root() / 'build-aux/rc-comp.py'] + ir_res_files

message('Generating assembler resource header...')
r = run_command(python_exe, params, check: true)
if r.returncode() != 0
    error(r.stderr())
endif

executable(
    'assrte',
    sources: sources,
    cpp_args: cpp_args,
    include_directories: inc_dirs,
    dependencies: dependencies,
    install: true,
)
