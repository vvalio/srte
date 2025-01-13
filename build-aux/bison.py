#!/usr/bin/python3
'''This script runs bison and preps the correct folders in the build directory, since Meson can't do that.'''
from os import mkdir
from os.path import join, isabs, isfile
from subprocess import Popen, PIPE
from typing import List
from sys import stderr, argv
from shutil import which

DIR = argv[1]
PARSER_DESC = f'{DIR}/../assembler/parser/srte-asm.y'
PARSER_OUTPUT_IMPL = f'{DIR}/../assembler/parser/srte-asm-parser.cpp'
PARSER_OUTPUT_HEADER = f'{DIR}/../assembler/parser/srte-asm-parser.hpp'


def _perr(*args, **kwargs) -> None:
    print(*args, **kwargs, file=stderr)


def _run_cmd(abs_command: str, args: List[str]) -> None:
    '''Assumes abs_command exists.'''
    if not isabs(abs_command):
        raise ValueError(f'{abs_command} is not an absolute path!')

    proc = Popen([abs_command] + args, stdout=PIPE, text=True)
    if proc.returncode is not None and proc.returncode != 0:
        _perr(f'Command {abs_command} failed: {proc.stderr}')
        quit(1)


def _prep_build_dir(abs_builddir: str) -> None:
    '''Prepares the build directory by creating a new folder in it for Bison outputs.'''
    if not isabs(abs_builddir):
        raise ValueError(f'{abs_builddir} is not an absolute path!')

    try:
        mkdir(join(abs_builddir, 'parser'))
    except FileExistsError:
        ...


def _check_cmd(cmd: str) -> None:
    if not which(cmd):
        raise ValueError(f'No command {cmd} installed!')
    else:
        print(f'Program: {cmd} found')


def _begin() -> None:
    _check_cmd('bison')
    if not isfile(join(DIR, 'build.ninja')):
        raise ValueError(f'Not a build directory: {DIR}: no file build.ninja')

    bison_cmd_path = which('bison')
    _prep_build_dir(DIR)
    _run_cmd(bison_cmd_path, [
        PARSER_DESC,
        '-o', PARSER_OUTPUT_IMPL,
        f'-H{PARSER_OUTPUT_HEADER}',
        '-L', 'C++', '-k', '-Wcounterexamples',
    ])


if __name__ == '__main__':
    _begin()
