#!/bin/python3

from sys import argv
import os

IGNORED_FILES = {'debug.hpp'}
expanded_files = set()

def is_local_include(line: str):
    if line.startswith('#include <mog/') and line.endswith('>\n'):
        return True
    if line.startswith('#include "mog/') and line.endswith('"\n'):
        return True
    return False

def get_local_include_file(line: str):
    filename = line[len('#include <mog/'):-2]
    if filename in IGNORED_FILES:
        return '\n'
    print(f'Expanding {filename}')
    filepath = os.path.join(os.getenv('MOG_CPP_PATH'), 'mo', filename)
    contents = open(filepath).readlines()
    return contents

def mapper(line: str):
    if not is_local_include(line):
        return line.rstrip()
    if line in expanded_files:
        return ''
    expanded_files.add(line)
    lines = get_local_include_file(line)
    lines = list(map(mapper, lines))
    return '\n'.join(lines)

def main(filename):
    lines = open(filename).readlines()
    lines = list(map(mapper, lines))
    print('Writing to sol.cpp')
    open('sol.cpp', 'w').write('\n'.join(lines))

if __name__ == '__main__':
    if len(argv) < 2:
        print("Usage: expand.py <filename>")
        exit(1)
    main(argv[1])
