Staticlibs common utilities library
===================================

[![travis](https://travis-ci.org/staticlibs/staticlib_utils.svg?branch=master)](https://travis-ci.org/staticlibs/staticlib_utils)
[![appveyor](https://ci.appveyor.com/api/projects/status/github/staticlibs/staticlib_utils?svg=true)](https://ci.appveyor.com/project/staticlibs/staticlib-utils)

This project is a part of [Staticlibs](http://staticlibs.net/).

This project contains common utilities for strings, process spawning etc.

Link to the [API documentation](http://staticlibs.github.io/staticlib_utils/docs/html/namespacestaticlib_1_1utils.html).

How to build
------------

[CMake](http://cmake.org/) is required for building.

[pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config/) utility is used for dependency management.
For Windows users ready-to-use binary version of `pkg-config` can be obtained from [tools_windows_pkgconfig](https://github.com/staticlibs/tools_windows_pkgconfig) repository.
See [StaticlibsPkgConfig](https://github.com/staticlibs/wiki/wiki/StaticlibsPkgConfig) for Staticlibs-specific details about `pkg-config` usage.

To build the library on Windows using Visual Studio 2013 Express run the following commands using
Visual Studio development command prompt 
(`C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\Shortcuts\VS2013 x86 Native Tools Command Prompt`):

    git clone https://github.com/staticlibs/staticlib_config.git
    git clone https://github.com/staticlibs/staticlib_support.git
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
more information about the CMake toolchains setup and cross-compilation.

License information
-------------------

This project is released under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

Changelog
---------

**2021-01-07**

 * version 1.7.11
 * make `signal_utils` thread-safe

**2020-11-01**

 * version 1.7.10
 * `process_utils` with no output file

**2020-10-04**

 * version 1.7.9
 * `process_utils` empty argument fix

**2020-03-29**

 * version 1.7.8
 * `process_utils` error reporting fix

**2020-03-29**

 * version 1.7.7
 * `process_utils` enhancements

**2019-08-30**

 * version 1.7.6
 * `process_utils` enhancements

**2019-04-04**

 * version 1.7.5
 * `user_utils` added

**2018-09-05**

 * version 1.7.3
 * use `644` permissions for spawned process output file

**2018-02-18**

 * version 1.7.2
 * `current_time_millis` added

**2017-12-23**

 * version 1.7.1
 * vs2017 support

**2017-05-22**
 * version 1.7.0
 * windows utilities added

**2017-04-10**

 * version 1.6.0
 * minor cmake fixes

**2016-06-29**

 * version 1.5.0
 * ICU API removed

**2016-01-16**

 * version 1.4.2
 * minor CMake changes

**2015-12-07**

 * version 1.4.1
 * `current_executable_path` fix for linux and mac

**2015-12-03**

 * version 1.4.0
 * basic utils moved to `staticlib_config`
 * ICU support for `FileDescriptor` and `process_utils`

**2015-11-17**

 * version 1.3.4
 * deplibs cache support

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
