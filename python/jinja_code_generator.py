#!/usr/bin/python3

import argparse
from jinja2 import Environment, FileSystemLoader
import sys
import os.path
import yaml

parser = argparse.ArgumentParser(description='Generate code using jinja.')
parser.add_argument('-d', '--data', default='data.yml', help='Data in yaml (default: data.yml)')
parser.add_argument('-t', '--template', default='template.pre', help='Template file in jinja (default:template.pre)')
args = parser.parse_args()

if os.path.basename(args.data)[-4:] != '.yml':
    print('data file must be *.yml')
    sys.exit(1)

if os.path.basename(args.template)[-4:] != '.pre':
    print('template file must be *.pre')
    sys.exit(1)

# Load yaml data
data = yaml.load(open(args.data))

# Load jinja2 template
env = Environment(loader = FileSystemLoader(os.path.dirname(args.template)), trim_blocks=True, lstrip_blocks=True)
template = env.get_template(os.path.basename(args.template))

# Render and write the output
with open(args.template[:-4], 'w') as f:
    f.write(template.render(data))
