'''Runs tests from this folder after build.'''
from os.path import dirname, join, realpath
from os import walk
from sys import argv
from subprocess import run, PIPE

TESTDIR = dirname(realpath(__file__))
BUILDDIR = join(TESTDIR, '..', argv[1], 'assembler')
execf = join(BUILDDIR, 'assrte')
test_output = open(join(TESTDIR, 'tests.log'), 'w+')


def log(msg: str, **print_kwargs: any):
    test_output.write(msg if msg.endswith(
        '\n') or print_kwargs.get('end') == '' else (msg + '\n'))
    print(msg, **print_kwargs)


def _parser_test(path: str, expect: int):
    log(f'Running parser test {path}... ', end='', flush=True)

    proc = run([execf, path], stderr=PIPE, stdout=PIPE)
    if proc.returncode != expect:
        log(f'FAILED: {path}: {execf} returned code {
            proc.returncode} when should be {expect}')
    else:
        log(f'Ok, return code {proc.returncode} as it should be')


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
test_output.close()
