# Numerical solution to Schrödinger equation

This repo will solve the Schrödinger equation numerically using `C++` and then visualize it using `Python`. 

### Table of contents
- [Dependencies](#dependencies)
- [Code structure](#code-structure)
  - [PDESolver](#pdesolver)
  - [Box](#box)
  - [Utils](#utils)
- [Build](#build)
- [Visuailze](#visuailze)
- [Report](#report)

### Dependencies

- `C++`
  - [`armadillo`](https://arma.sourceforge.net/)
- `Python`
  - [`numpy`](https://numpy.org/)
  - [`matplotlib`](https://matplotlib.org/)
  - [`pyarma`](https://pyarma.sourceforge.io/)

### Code structure
The code is built up from two classes in `C++`. Where all the header files can be found in the [`include`](code/include/) directory, and the source files in [`src`](code/src/).

#### PDESolver
The [`PDESolver`](code/PDESolver.cpp) takes care setting up the system and doing the time evolution with the [Crank–Nicolson method](https://en.wikipedia.org/wiki/Crank%E2%80%93Nicolson_method). 

#### Box
The [`box`](code/box.cpp) only takes care setting up the slits. Where we have for simplified getting the slits by having a potential equal to infinity, numerically speaking. 

#### Utils
A collection of functions used over the different files.

### Build
All of the following assumes you are in the [`code`](code/) repository.


This project can either be built with running

```Shell
make
```
This will run all of the simulations for all of the subproblems, and create the `data` directory for all the binaries. 
If this is not wanted

```Shell
g++ -I include src/* main.cpp -o main -larmadillo -O2
```

Then running it with

```Shell
./main input_parameters.csv
```

Where the `input_parameters.csv` have the structure

h      |       dt  |       T  |       xc  |     sigma_x  |   px      |    yc  |     sigma_y  |   py    |    v0     |     slit  |
-------|-----------|----------|-----------|--------------|-----------|--------|--------------|---------|-----------|-----------|
0.005  |   2.5e-5  |   0.008  |   0.25    |   0.05       |      200  |   0.5  |    0.05      |      0  |     1e10  |   2       |

But seperated by commas( , ). The file [`input_test.csv`](code/input_test.csv), can be viewed as an example. All of the input parameter files are found in [`input_files`](code/input_files/). 

The binary files will be saved in a `data` directory that is not in this repo, since all of the binary files are large.


### Visuailze
After simulation is done it will generate a binary file. This can be used in `Python` as follows

```Python
python anim.py foo.bin savefile
```

Where `foo.bin` is the binary file that is to be visualized, and `savefile` is the suffix to the `anim.mp4`. Or if you want to generate all of the animations

```Shell
make animate
```

Which will create a new `animation` directory with all of the `.mp4

### Report
The report can be found in the [`report/`](report/) sub directory. Where all the figures can be found in the [`report/figures`](report/figures/)
