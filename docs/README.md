# Genrerate the documentation of PyAF

Prerequisite:

	$ sudo apt install sphinx

Generate the documentation:

	$ cd docs
	$ mkdir build
	$ sphinx-build source build
	$ make html

Now the PyAF HTML documentation has been built in the `docs/build` folder.