# Numerical solution to Schrödinger equation

This repo will solve the Schrödinger equation numerically using `C++` and then visualize it using `Python`. 

Dependencies
============
- `c++`
  - [`armadillo`](https://arma.sourceforge.net/)
- `Python`
  - [`numpy`](https://numpy.org/)
  - [`matplotlib`](https://matplotlib.org/)
  - [`pyarma`](https://pyarma.sourceforge.io/)

### Build
All of the following assumes you are in the [`code`](code/) repository.


This project can either be built with running

```Shell
make
```
This will run all of the simulations for all of the subproblems. If this is not wanted

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
