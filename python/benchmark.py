#!/usr/bin/python3

import argparse
from blasbooster import *
import numpy as np
import sys
import yaml

parser = argparse.ArgumentParser(description='Generate code using jinja.')
parser.add_argument('-d', '--data', default='data.yml', help='Data in yaml (default: data.yml)')
args = parser.parse_args()

#if os.path.basename(args.data)[-4:] != '.yml':
#    print('data file must be *.yml')
#    sys.exit(1)

# Load yaml data
#data = yaml.load(open(args.data))

print('BlasBooster Benchmarks\n----------------------\n')

np.random.seed(1234)
an = bm = 2
am = bn = 3

A = np.random.rand(an, am)
B = np.random.rand(bn, bm)

C = np.matmul(A, B)

print(C)

A2 = Matrix(an, am)
B2 = Matrix(bn, bm)

#C2 = matmul(A2, B2)
