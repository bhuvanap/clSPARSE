# clSPARSE
clSPARSE is an OpenCL© library implementing Sparse linear algebra. This project is a result of
a collaboration between [AMD Inc.](http://www.amd.com/) and [Vratis Ltd.](http://www.vratis.com/).

## Introduction to clSPARSE

For the beta release, the clSPARSE library provides the following fundamental operations:

-  Sparse Matrix - dense Vector multiplication (SpM-dV)
-  Sparse Matrix - dense Matrix multiplication (SpM-dM)
-  Iterative conjugate gradient solver (CG)
-  Iterative biconjugate gradient stabilized solver (BiCGStab)
-  Dense to CSR conversions (and converse)
-  COO to CSR conversions (and converse)
-  Functions to read matrix market files in COO or CSR format

Similar to the other clMath libraries, the clSPARSE library exports a “C” interface to allow
projects to build wrappers around clSPARSE in any programming language.  The API for the 
clSPARSE library is well organized compared to the APIs for the older clMath libraries. 
The  OpenCL state is not explicitly passed through the API, enabling the library to be 
forward compatible when users switch from OpenCL 1.2 to OpenCL 2.0. 

The APIs are designed such that users are in control of where input and output
buffers live, and they maintain control of when data transfers to/from device
memory happen, so that there are no performance surprises.

The APIs for the clSPARSE library are designed such that the users are in control of the location
of input and output buffers, and maintain control of when data transfers to/from device
memory occur, so that to some degree the user can anticipate the performance of the library.

### API semantic versioning

The clSPARSE API includes the key aspects of good software: the feedback loop, iterations, 
and the software interfaces. clSPARSE follows the [semantic versioning](http://semver.org/) 
guidelines. The major version number remains '0' -- but the public API must not be considered 
stable.  clSPARSE is released as beta software (0.y.z) early to the community to elicit feedback 
and comment so that breaking changes to the API that might require early users to recompile or 
rewrite portions of their code can be incoorporated early in the design cycle.


The pre-built binaries are available on our 
[releases page](https://github.com/clMathLibraries/clSPARSE/releases).

### Google Groups
Two mailing lists have been created for the clMath projects:

-   clmath@googlegroups.com - group whose focus is to answer
    questions on using the library or reporting issues

-   clmath-developers@googlegroups.com - group whose focus is for
    developers interested in contributing to the library code itself

## Samples
clSPARSE contains a directory of simple [OpenCL samples](./samples) that demonstrate the use
of the API in both C and C++.  The [superbuild](http://www.kitware.com/media/html/BuildingExternalProjectsWithCMake2.8.html)
script for clSPARSE builds the samples as an external project, to demonstrate
how an application finds and links to clSPARSE using cMake.

### clSPARSE library documentation
The**API documentation** relevant to this library is not yet available, but the examples in the samples 
directory provide an excellent starting point to basic library operations.

### Contributing code
Please refer to and read the [Contributing](CONTRIBUTING.md) document for guidelines on
how to contribute code to this open source project. Code in the
/master branch is considered to be stable and new library releases are made
when commits are merged into /master.  Active development and pull-requests should
be made to the **/develop** branch.

## Build
clSPARSE is primarily written in C++ using C++11 core features. It exports
a 'C' interface for compatibility with other languages. This section lists 
the packages required to develop the library code and guides you to the
information about how to build your programs and test and measure the 
performance of the developed code.


### Compiling for Windows

To develop the clSPARSE library code on a Windows operating system, 
ensure that the following packages are installed on your system:
-  Windows&reg; 7/8
-  Visual Studio 2013 and above
-  CMake 2.8.12 (download from [Kitware](http://www.cmake.org/download/))
  -  Solution (.sln) or
  -  Nmake makefiles
-  An OpenCL SDK, such as [APP SDK 3.0](http://developer.amd.com/tools-and-sdks/opencl-zone/amd-accelerated-parallel-processing-app-sdk/)

### Compiling for Linux

To develop the clSPARSE library code on a Linux operating system, 
ensure that the following packages are installed on your system:
-  GCC 4.8 and above
-  CMake 2.8.12 (install with distro package manager )
   -  Unix makefiles or
   -  KDevelop or
   -  QT Creator
-  An OpenCL SDK, such as [APP SDK 3.0](http://developer.amd.com/tools-and-sdks/opencl-zone/amd-accelerated-parallel-processing-app-sdk/)

### Compiling for Mac OSX

To develop the clSPARSE library code on a MAC OS X, 
ensure that the following packages are installed on your system:
-   CMake 2.8.12 (install via [brew](http://brew.sh/))
   -  Unix makefiles or
   -  XCode
- An OpenCL SDK (installed via `xcode-select --install`)


### How to build clSPARSE for your platform
For details on using CMake to generate platform specific build files, 
see the [Build primer](https://github.com/clMathLibraries/clSPARSE/wiki/Build) 
available on the wiki page.


### Bench and test infrastructure dependencies
To test and benchmark the developed clSPARSE library code, 
ensure that the following packages are installed on your system:
-   Googletest v1.7
-   Boost v1.58



