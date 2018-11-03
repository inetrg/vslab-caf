To build and run from command line (you need to build or install CAF first):

```bash
mkdir build
cd build
cmake ..
make
./vslab <args>
```

CMake will find CAF as long as it is installed or located in the parent
directory, i.e., `../actor-framework/build` contains a valid CAF build.

You can also point CMake to other CAF bulid directories:

```bash
cmake -D CAF_ROOT_DIR=<path-to-caf>/build ..
```
