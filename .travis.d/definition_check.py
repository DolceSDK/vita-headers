#!/usr/bin/env python3

import os
import sys
import re
import fnmatch

CURR_DIR = os.path.dirname(os.path.realpath(__file__))
DB_FILE = 'db.yml'
DB_FILE_PATH = os.path.join(CURR_DIR, '..', 'db.yml')
INCLUDE_DIR = os.path.join(CURR_DIR, '..', 'include')

FUNC_RULE_PATTERN = (
    # ret
    '^\w+\s+' +
    # func name
    '(_*k?sce\w+|__\w+)' +
    # args; if define with multiline, end with comma, if not end with `);`
    '\(.*(,|\);)' +
    # white spaces
    '\s*$'
)
FUNCTION_RULE = re.compile(FUNC_RULE_PATTERN)
IGNORE_FILES = [
    'dolcesdk/align.h',
    'dolcesdk/utils.h',
    'psp2/scream_top.h',
    'psp2/scream/sce_scream.h',
    'psp2/scream/sce_scream_ngs.h',
    'psp2/scream/sce_snd_data.h',
    'psp2/scream/sce_sndstream.h',
    'psp2/scream/sce_sndstream_io.h',
    'psp2/scream/scream_error.h',
]

# older python's glob not support `**`
def findfile(directory, filepattern):
    matches = []
    for root, dirnames, filenames in os.walk(directory):
        for filename in fnmatch.filter(filenames, filepattern):
            matches.append(os.path.join(root, filename))
    return matches

def readlines(f):
    if sys.version_info.major < 3:
        return f.xreadlines()
    return f

def dict_items(dic):
    if sys.version_info.major < 3:
        return dic.iteritems()
    return dic.items()

def read_nids():
    errors = []
    user_nids = dict()
    kernel_nids = dict()
    nids = None
    with open(DB_FILE_PATH, 'r') as d:
        SECTION = None
        for line_no, line in enumerate(readlines(d)):
            line = line.split('#')[0].strip()
            if line == '':
                continue
            k, v = line.split(':')[:2]
            if not v.strip():
                SECTION = k
                continue
            if k.strip() == 'kernel':
                if v.strip() == 'true':
                    nids = kernel_nids
                else:
                    nids = user_nids
            if SECTION != 'functions':
                continue
            nids[k] = 1
    return dict(user_nids, **kernel_nids), errors

def check_function_nids(nids):
    errors = []
    functions = dict()
    for header_path in findfile(INCLUDE_DIR, '*.h'):
        header_file = header_path.split('include/')[1]
        if header_file in IGNORE_FILES:
            continue
        with open(header_path, 'r') as h:
            have_group_define = False
            for line in readlines(h):
                m = FUNCTION_RULE.match(line)
                if not m:
                    continue
                fn = m.group(1)
                if functions.get(fn):
                    errors.append('%s: Already defined %s' %
                                  (header_file, fn))
                    continue
                if not nids.get(fn):
                    errors.append('%s: Could not find NID %s' %
                                  (header_file, fn))
                functions[fn] = 1
    return errors

if __name__ == '__main__':
    nids, errors = read_nids()
    errors += check_function_nids(nids)
    if len(errors):
        for e in errors:
            print(e)
        sys.exit(1)
