project('srte', ['c', 'cpp'])

python_exe = find_program('python3', 'python')
params = ['build-aux/bison.py', meson.project_build_root()]

find_program('bison', required: true)

message('Generating Bison parser...')
r = run_command(python_exe, params, check: true)
if r.returncode() != 0
    error(r.stderr())
endif

subdir('assembler')
