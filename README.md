# Metabolite inference

## Compiling the repo

```bash
git clone https://github.com/anticipated-lotus/metabolite_inference.git
mkdir build 
cd build
cmake ..
```

Once this is done, you can compile the files using :

```bash
make 
```

or with multiple cores by replacing `N` by the number of cores you want:

```bash
make -j N
```

## Running the test suite

In the build directory:

```bash
make -j8 acol_unitTests
./acol_unitTests
```