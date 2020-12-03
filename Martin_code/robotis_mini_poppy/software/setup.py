#!/usr/bin/env python

from setuptools import setup, find_packages


setup(name='robotis_mini_poppy',
      version='0.1',
      packages=find_packages(),

      install_requires=['pypot >= 3.0'],

      package_data={'robotis_mini_poppy': ['robotis_mini_poppy/configuration/robotis_mini_poppy.json']},
      include_package_data=True,

      zip_safe = False,
      
      author='Roberto Martin-Martin',
      author_email='rmartinmar@gmail.com',
      description='Pypot model for Robotis Mini robot',
      url='TO BE COMPLETED',
      license='TO BE COMPLETED',
      )
