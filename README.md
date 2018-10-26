To build and run from command line:

```
mkdir build
cd build
cmake ..
make
./vslab <args>
```

If CAF is not installed (or cannot be installed) on the computer, instead of `cmake ..`, use:

```bash
cmake -D CAF_ROOT_DIR=<path-to-caf>/build ..
```

Note: you need to build CAF first (in parent directory)
