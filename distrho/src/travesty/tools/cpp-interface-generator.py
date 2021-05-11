#!/usr/bin/env python

import sys
import os
import glob
import re

OUTPUT_DIR = 'gen'
IIDS_FILE = os.path.join(OUTPUT_DIR, 'iids.cpp')

EXPR_INTERFACE_AND_BODY = re.compile(
    r'struct\s+V3_INTERFACE' +
    r'\s*\(\s*([a-zA-Z0-9_]+)\s*\)' +
    r'\s*\{([^}]*)\}\s*;')

def process_c_hdr(input, output):
    out = None
    iids_out = None
    input_text = open(input).read()

    nth = 0
    for match in re.finditer(EXPR_INTERFACE_AND_BODY, input_text):
        name = match[1]
        body = parse_c_body(match[2])
        interfaces, methods = body['interfaces'], body['methods']

        if not out:
            out = open(output, 'w')

        if nth == 0:
            out.write('// This file is generated\n')
            out.write('#pragma once\n')
            #out.write('#include "%s"\n' % (os.path.basename(input)))
            out.write('#include "../align_push.h"\n')
            out.write('\nnamespace v3\n{\n')

        out.write('\nclass %s\n' % rename_class(name))
        for i in range(len(interfaces)):
            out.write((i == 0) and '	: ' or '	, ')
            out.write('public %s\n' % (rename_class(interfaces[i])))
        out.write('{\n')
        out.write('public:\n')
        for m_name, m_ret, m_args in methods:
            out.write('	virtual V3_API %s %s(%s) = 0;\n' % (m_ret, camelize(m_name), m_args))

        out.write('	static const fuid iid;\n')

        #out.write('	operator %s *() noexcept { return reinterpret_cast<%s *>(this); }\n' % (name, name))
        #out.write('	operator %s const *() const noexcept { return reinterpret_cast<%s const *>(this); }\n' % (name, name))

        out.write('};\n')

        if not iids_out:
            iids_out = open(IIDS_FILE, 'a')
            iids_out.write('#include "../%s"\n' % (os.path.basename(input)))

        iids_out.write('namespace v3 { const fuid %s::iid(%s_iid); }\n' % (rename_class(name), name))

        nth += 1

    if out:
        out.write('\n}\n// namespace v3\n')
        out.write('#include "../align_pop.h"\n')
    if iids_out:
        iids_out.write('\n')

EXPR_STRUCT = re.compile(
    r'\s*struct\s+([a-zA-Z0-9_]+)\s*;')
EXPR_METHOD = re.compile(
    r'\s*V3_API\s+' +
    r'([^(]+)' +
    r'\s*\(\s*\*\s*([a-zA-Z0-9_]+)\s*\)\s*' +
    r'\(' +
    r'\s*void\s*\*\s*[a-zA-Z0-9_]+\s*' +
    r'\s*(?:,\s*([^)]+))?' +
    r'\)\s*;')

def parse_c_body(text):
    interfaces = []
    methods = []

    while True:
        match = re.match(EXPR_STRUCT, text)
        if not match:
            break
        interfaces.append(match[1])
        text = text[len(match[0]):]

    while True:
        match = re.match(EXPR_METHOD, text)
        if not match:
            break
        name, ret, args = match[2], match[1], match[3] or ''
        methods.append((name.strip(), ret.strip(), args.strip()))
        text = text[len(match[0]):]

    text = text.strip()
    if len(text) > 0:
        raise ValueError('could not parse the interface')

    return {'interfaces': interfaces, 'methods': methods }

def rename_class(name):
    if not name.startswith('v3_'):
        raise ValueError('A class name should start with `v3_` (have `%s`)' % (name))
    name = name[3:]
    # name = camelize(name)
    # name = name[0].upper() + name[1:]
    return name

EXPR_CAMEL = re.compile(r'_([a-z])')
def camelize(name):
    return EXPR_CAMEL.sub(lambda x: x.group(1).upper(), name)

if __name__ == '__main__':
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    iids_out = open(IIDS_FILE, 'w')
    iids_out.write('// This file is generated\n')
    del iids_out

    if not os.path.exists('base.h'):
        sys.stderr.write('Run this in the travesty directory.\n')
        sys.exit(1)

    for file in glob.glob('*.h'):
        process_c_hdr(input=file, output=os.path.join(OUTPUT_DIR, file+'pp'))
