# (Unofficial) APC40 mkII C/C++ API

## Installation
I have chosen [SCons](https://scons.org/) as build tool because I find it to be quite easy to use.
To build the library, type `scons release=1`, to clean, type `scons -c`.

In order to build the C binding, type `scons c-binding=1 release=1 && build\release\test-c-binding`.


## Todo
- Testing it on OSX, but I don\'t own a Mac sorry :X

*By Maxim van Dijk (https://github.com/vananasun/)*