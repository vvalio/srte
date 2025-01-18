'''Runs tests from this folder after build.'''
from shutil import copyfile
from os.path import dirname, join, realpath
from os import walk
from sys import argv
from subprocess import run

TESTDIR = dirname(realpath(__file__))
BUILDDIR = join(TESTDIR, '..', argv[1], 'assembler')
execf = join(BUILDDIR, 'assrte')

def _parser_test(path: str, expect: int):
    print(f'Running parser test {path}... ', end='')

    proc = run([execf, path])
    if proc.returncode != expect:
        print(f'FAILED: {path}: {execf} returned code {proc.returncode} when should be {expect}')
        quit(1)
    else:
        print(f'Ok')

def _run_parser_tests():
    for root, _, files in walk(TESTDIR):
        for file in files:
            if not file.endswith('.srte'):
                continue

            fullpath = join(root, file)
            expected_retc = 0 if fullpath.endswith('_ok.srte') else 1
            _parser_test(fullpath, expected_retc)
    
    print('All parser tests passed!')

_run_parser_tests()
