# VSLAB CAF

## Build

Build the project as follows. This will build CAF as part of this project. 

```bash
mkdir build
cd build
cmake ..
make
```

### Choose your own CAF build

You can alternatively point CMake to an existing CAF build by passing the path to the build via `CAF_ROOT`. Replace the `cmake ..` call above with the following:

```bash
cmake -D CAF_ROOT=<path-to-caf>/build ..
```

## Run

You can then run the binary (located inside the build directory):

```bash
./vslab <args>
````

The default project offers these CLI options:

```bash
vslab-caf> ./build/vslab --help
global options:
  (-h|-?|--help)                  : print help text to STDERR and exit
  --long-help                     : print long help text to STDERR and exit
  --dump-config                   : print configuration to STDERR and exit
  --config-file=<std::string>     : sets a path to a configuration file
  (-H|--host) <std::string>       : server host (ignored in server mode)
  (-p|--port) <uint16_t>          : port
  (-w|--num-workers) <dictionary> : number of workers (in worker mode)
  (-m|--mode) <std::string>       : one of 'server', 'worker' or 'client'
```
