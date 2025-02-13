
from setuptools import setup,fin_packages
import pathlib

here = pathlib.Path(__file__).parent.resolve()

long_description = (hrere / "README.md").read_text(encoding="utf=8")

setup(
    name="pystreampu",
    
    version="0.0.1",
    
    description="A python API for streampu",
    
    long_description=long_description,
    
    url="https://github.com/aff3ct/pystreampu",
    
    author="Storm Team",
    
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Developpers",
    ],
    
    keywords="",
    
    #package_dir={"": "src","": "streampu"},
    
    #packages=find_packages(where="src"),
    packages=find_packages(include=['src','streampu','lib/streampu/src'])

    #python_requires=">=3.8 <4"

    install_requires["pybind11","streampu"]

    #entry_points={
    #   "console_scripts": [
    #       "sample=sample:main",
    #   ],
    #},

)
