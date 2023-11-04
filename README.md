# pyaf-core

## Getting started
### Install from the sources
Clone the repository
```
git clone --recursive git@gitlab.inria.fr:fec/pyaf-core.git
```
then install `pyaf-core` using `pip3`
```
pip3 install ./pyaf-core
```
If you want more information during compilation, use `-v` option of the `pip3` command.

### Install with debug mode
To build using `debug` configuration, set an environment variable `DEBUG=1` prior to install the library.

For example the following command will compile the package `aff3ct` in `Debug` and `editable` mode, and shows the compilation output.
```
DEBUG=1  pip3 install -e pyaf-core -v
```

### Install with fine-tuning of C++ flags
When running the `pip3 install` command, CMake is used with some pre-defined flags, for example by default
```
CMAKE_CXX_FLAGS = -Wall -funroll-loops -fvisibility=hidden -fvisibility-inlines-hidden -faligned-new -Wno-overloaded-virtual
```
You can pass your own values using two environment variables.
 - Setting the environment variable `CMAKE_CXX_FLAGS = -fsome_options` will append `-fsome_options` to the default flag
 - Setting the environment variable `CMAKE_ARGS = -DCMAKE_CXX_FLAGS= -fsome_options` will erase the default behavior and use only your options. Using `CMAKE_ARGS` you can pass any arguments to `cmake`.

## Run tests
Testing `aff3ct` requires `pytest`, run the following command:
```
pytest --pyargs aff3ct
```

## A simple `aff3ct` program

```python
import aff3ct

x = aff3ct.array([1,2,3], dtype = aff3ct.uint8)
y = aff3ct.array([4,5,6], dtype = aff3ct.uint8)

z = x+y
print(z)
```
This should return `[5 7 9]`.
