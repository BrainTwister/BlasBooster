from jinja2 import Environment, FileSystemLoader
import yaml

# Load yaml data
data = yaml.load(open('../../include/BlasBooster/BlasInterface/BlasFunctionList.yml'))

# Load jinja2 template
env = Environment(loader = FileSystemLoader('./OpenBLAS'), trim_blocks=True, lstrip_blocks=True)
template = env.get_template('BlasInterface_OpenBLAS.cpp.pre')

# Render and print the output
print(template.render(data))
