# This acts as a python makefile for ca_cython
# To build the cython extension to import in your python script, run 'python setup.py build_ext --inplace'
# annotate=True will generate a html file with the cython code and the c code side by side for comparison to profile for optimization in runtime

from setuptools import setup, Extension
from Cython.Build import cythonize

extensions = [
    Extension("ca_cython", ["ca_cython.pyx"])
]

setup(name="ca_cython", ext_modules = cythonize(extensions, annotate=True))