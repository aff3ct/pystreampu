# pyStreamPU

## Getting started
### Install from the sources
Clone the repository
```
git clone --recursive https://github.com/aff3ct/pystreampu.git
```
then install the python interface of `StreamPU` using `pip3`
```
pip3 install ./pystreampu
```
If you want more information during compilation, use `-v` option of the `pip3` command.

### Install with fine-tuning of C++ flags
To install `streampu`compiled with custom flags, use the following syntax:
```
pip3 install -v -Ccmake.define.YOUR_CMAKE_FLAG1=CONTENT1 -Ccmake.define.YOUR_CMAKE_FLAG2=CONTENT2 .
```
where you can replace `YOUR_CMAKE_FLAG1`and `YOUR_CMAKE_FLAG2` by the flags you want
and set `CONTENT1` and `CONTENT2` values.

## Run tests
Testing the `streampu` package requires `pytest`, run the following command:
```
pytest --pyargs streampu
```

## A simple `streampu` program

```python
import streampu as spu

x = spu.array([1,2,3], dtype = spu.uint8)
y = spu.array([4,5,6], dtype = spu.uint8)

z = x+y
print(z)
```
This should return `[5 7 9]`.
