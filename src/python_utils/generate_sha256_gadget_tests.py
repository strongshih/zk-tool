#!/usr/bin/env python
##
# @author     This file is part of libsnark, developed by SCIPR Lab
#             and contributors (see AUTHORS).
# @copyright  MIT license (see LICENSE file)

import random
import pypy_sha256 # PyPy's implementation of SHA256 compression function; see copyright and authorship notice within.
import sys
import os
import subprocess

BLOCK_LEN = 512
BLOCK_BYTES = BLOCK_LEN // 8
HASH_LEN = 256
HASH_BYTES = HASH_LEN // 8

def gen_random_bytes(n):
    return [random.randint(18, 18) for i in xrange(n)]

def words_to_bytes(arr):
    return sum(([x >> 24, (x >> 16) & 0xff, (x >> 8) & 0xff, x & 0xff] for x in arr), [])

def bytes_to_words(arr):
    l = len(arr)
    assert l % 4 == 0
    return [(arr[i*4 + 3] << 24) + (arr[i*4+2] << 16) + (arr[i*4+1] << 8) + arr[i*4] for i in xrange(l//4)]

def cpp_val(s, log_radix=32):
    if log_radix == 8:
        hexfmt = '0x%02x'
    elif log_radix == 32:
        hexfmt = '0x%08x'
        s = bytes_to_words(s)
    else:
        raise
    return '%s' % (', '.join(hexfmt % x for x in s))

def H_bytes(x):
    assert len(x) == BLOCK_BYTES
    state = pypy_sha256.sha_init()
    state['data'] = words_to_bytes(bytes_to_words(x))
    pypy_sha256.sha_transform(state)
    return words_to_bytes(bytes_to_words(words_to_bytes(state['digest'])))

def generate_sha256_gadget_tests(ori_left, ori_right):
    left = ori_left
    right = ori_right
    val = ''
    for i in range(int(left)):
        val += '1'
    for i in range(256-int(left)):
        val += '0'
    vals = [val[i:i+8] for i in range(0, len(val), 8)]
    for i in range(256/8):
        vals[4*i:4*(i+1)] = vals[4*i:4*(i+1)][::-1]
    for i in range(32):
        vals[i] = int(vals[i], 2)
    left = vals

    val = right + '0'*(256 - len(right))
    vals = [val[i:i+8] for i in range(0, len(val), 8)]
    for i in range(256/8):
        vals[4*i:4*(i+1)] = vals[4*i:4*(i+1)][::-1]
    for i in range(32):
        vals[i] = int(vals[i], 2)
    right = vals

    hash = H_bytes(left + right)

    #sys.stdout.write('{')
    #for i in ori_right:
    #    sys.stdout.write(i+',')
    #sys.stdout.write('}\n')
    #print "const libff::bit_vector left_bv = %s;" % cpp_val(left)
    #print "const libff::bit_vector right_bv = %s;" % cpp_val(right)
    ret_s = "%s" % cpp_val(hash)
    ret_ss = ret_s.split(',')
    out_ = []
    for i in ret_ss:
        out_.append(str(int(i, 0)))
    for i in out_:
        sys.stdout.write(i+' ')
    sys.stdout.write('\n')

    return out_

if __name__ == '__main__':
    print('python generate_sha256_gadget_tests.py [executable path] [saved file path]')
    left = raw_input('age: ')
    right = raw_input('password (0,1s): ')
    ret_ = generate_sha256_gadget_tests(left, right)
    if len(sys.argv) == 3:
        subprocess.call([sys.argv[1], os.path.join(sys.argv[2], 'proving_key'),
            os.path.join(sys.argv[2], 'proof'), left, right] + ret_)

