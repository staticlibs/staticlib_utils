Staticlibs common utilities library
===================================

This project is a part of [Staticlibs](http://staticlibs.net/).

This project contains common utilities for exceptions, IO, strings etc.

Link to [API documentation](http://staticlibs.github.io/staticlib_utils/docs/html/namespacestaticlib_1_1utils.html).

How to build
------------

[CMake](http://cmake.org/) is required for building.

To build the library on Windows using Visual Studio 2013 Express run the following commands using
Visual Studio development command prompt 
(`C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\Shortcuts\VS2013 x86 Native Tools Command Prompt`):

    git clone https://github.com/staticlibs/staticlib_utils.git
    cd staticlib_utils
    mkdir build
    cd build
    cmake ..
    msbuild staticlib_utils.sln

To build on other platforms using GCC or Clang with GNU Make:

    cmake .. -DCMAKE_CXX_FLAGS="--std=c++11"
    make

See [StaticlibsToolchains](https://github.com/staticlibs/wiki/wiki/StaticlibsToolchains) for 
more information about the toolchain setup and cross-compilation.

License information
-------------------

This project is released under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

Changelog
---------

**2015-11-14**

 * version 1.3.3
 * use `slassert` in tests
 * fix bad cast in `FileDescriptor#read` on windows
 * `split` added to string utils


**2015-11-13**

 * version 1.3.2
 * getters added to `FileDescriptor`

**2015-10-20**

 * version 1.3.1
 * `WIN32_LEAN_AND_MEAN` enabled for all windows-specific bits
 * process async test disabled for stable test runs

**2015-10-19**

 * version 1.3.0
 * io utils moved to separate project 
 * file descriptor implementation

**2015-09-09**

 * git modules removed
 * pkg-config support
 * separate test project from main one

**2015-07-05**

 * version 1.2.0
 * toolchains update
 * `ProducerConsumerQueue` moved to separate project
 * `RandomStringGenerator` added

**2015-06-30**

 * version 1.1.0
 * `ProducerConsumerQueue` added
 * cmake toolchains update

**2015-05-17**

 * 1.0.0, initial public version
