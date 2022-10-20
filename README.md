# VSLAB CAF

To build and run from command line:

```bash
mkdir build
cd build
cmake ..
make
./vslab <args>
```

This will build CAF before building your project.

## Outside CAF Build

You can also point CMake to other CAF bulid directories. Replace the cmake call above with the following:

```bash
cmake -D CAF_ROOT=<path-to-caf>/build ..
```
