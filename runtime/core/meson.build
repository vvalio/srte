core_rt_sources = [
    'srte_string.c',
    'own.c',
]

core_rt_deps = [
    dependency('icu-uc'),
]

cflags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-Wno-unused-parameter',
    '-Wno-unused-function',
    '-Wno-unused-variable',
    '-Wpedantic',
    '-std=c11',
]

core_rt = static_library(
    'corert',
    sources: core_rt_sources,
    dependencies: core_rt_deps,
    c_args: cflags,
)
