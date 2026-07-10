from setuptools import find_packages
from setuptools import setup

setup(
    name='bag_manager_py',
    version='0.1.0',
    packages=find_packages(
        include=('bag_manager_py', 'bag_manager_py.*')),
)
