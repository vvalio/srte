'''Small and portable-ish resource compiler.'''
import json  # wee i want yaml but it ain't part of the standard
from typing import NamedTuple, List, Dict, Tuple
from sys import argv
from os.path import join, dirname

HEADER_BEGIN = '''
// Auto-generated. DO NOT EDIT!
#pragma once

extern "C" {
'''

HEADER_END = '''
}
'''


class RcFileDesc(NamedTuple):
    # path to the file
    path: str
    # the data name in source, generated as
    # const unsigned char {data_name}[] = { ... } and
    # const unsigned long {data_name}_len = ...
    data_name: str


class RcDesc(NamedTuple):
    # output filename
    output_file: str
    # list of input files to include
    resources: List[RcFileDesc]


def _read_json(data: str) -> RcDesc:
    j_data = json.loads(data)
    res_object = j_data['resources']
    if not isinstance(res_object, list):
        raise ValueError

    resources = []
    for entry in res_object:
        resources.append(RcFileDesc(entry['path'], entry['data_name']))

    return RcDesc(j_data['output_file'], resources)


def _write_header(desc: RcDesc):
    out = open(desc.output_file, 'w+')
    out.write(HEADER_BEGIN)
    for entry in desc.resources:
        rc_f = open(join(dirname(argv[0]), entry.path), 'rb')
        bc = 0
        out.write(f'\nconst unsigned char {entry.data_name}[] = {{\n')
        while (d := rc_f.read(1)):
            for b in d:
                bc += 1
                out.write(f'{hex(b)}, ')

        out.write('\n};\n')
        out.write(f'\nconst unsigned long int {
                  entry.data_name}_len = {bc};\n')

        rc_f.close()

    out.write(HEADER_END)
    out.close()


def main():
    input_files = argv[1:]
    for f in input_files:
        with open(f, 'r') as input_file:
            desc = _read_json(input_file.read())
            _write_header(desc)


if __name__ == '__main__':
    main()
