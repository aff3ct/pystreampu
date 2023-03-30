# pyaf-core



## Getting started
Once you have clone this repository just run the following command:
```
pip3 install pyaf-core
```
If you want more information during compilation, use `-v` option.

To build using `debug` configuration set `DEBUG=1`.
To build using multiple cores set the variable `CMAKE_BUILD_PARALLEL_LEVEL` to the number of core.

For example the following command will compile `pyaf` in `Debug` and `editable` mode, using 8 cores and shows the compilation output.
```
DEBUG=1 CMAKE_BUILD_PARALLEL_LEVEL=8 pip3 install -e pyaf-core -v
```

## Run tests
Tests for `pyaf` require `pytest`, run the following command:
```
pytest --pyargs pyaf
```

## A simple `pyaf` program

```python
import pyaf

x = pyaf.array([1,2,3], dtype = pyaf.uint8)
y = pyaf.array([4,5,6], dtype = pyaf.uint8)

z = x+y
print(z)
```
This should return `[5 7 9]`.
