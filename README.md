# Apparator

Game engine hobby project written in C++

## Building

### Install submodules

Some dependencies are included as git submodules, and need to be fetched before compiling.

```
$ git submodule init
$ git submodule update
```

### Build engine

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Libraries and executables are compiled into /output directory
