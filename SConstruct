"""
Currently only supports MSVC++

Available parameters:
    `-c`            Cleaning
    `release=1`     Make release build
    `c-binding=1`   Build C wrapper library
"""

import fnmatch
import sys
import os
from subprocess import call



env = Environment(
    CPPPATH=['./src', './include'],
    CPPDEFINES=['WIN32', '__WINDOWS_MM__'],
    CCFLAGS='/nologo /EHsc /std:c++17 ',

    SHCXXCOMSTR = "Compiling $TARGET",
    SHLINKCOMSTR = "Linking $TARGET"
)
env.Append(LINKFLAGS='/SUBSYSTEM:CONSOLE')


# Debug and release target
release = ARGUMENTS.get('release', 0)
if int(release):
    env.Append(CCFLAGS = '/O2 ')
    env.Append(LINKFLAGS = '')
    build_dir = 'build/release'
else:
    env.Append(CCFLAGS = '/MTd ')
    env.Append(LINKFLAGS = '/DEBUG:FULL')
    env.Append(CPPDEFINES = 'DEBUG')
    build_dir = 'build/debug'



buildc = ARGUMENTS.get('c-binding', 0)
if int(buildc):
    #
    # Build C stuff
    #
    print('Building with C support')
    env_c_tests = env
    env.Append(CPPDEFINES = [ 'APCAPI_EXPORT_C' ]) # @TODO: Remove after building lib so C tests dont get messed up


# Gather list of sources
lib_sources = []
for root, dirnames, filenames in os.walk('src'):
    for filename in filenames:
        if fnmatch.fnmatch(filename, '*.cpp') or fnmatch.fnmatch(filename, '*.c'):
            lib_sources.append(str(os.path.join(root, filename)))

# Build APCAPI
VariantDir('build', 'src', duplicate=0)
lib_objects = []
for s in lib_sources:
    t = s.replace('src', build_dir, 1).replace('.cpp', '.obj').replace('.c', '.obj')
    lib_objects.append(env.Object(target=t, source=s))
env.StaticLibrary(build_dir+'/APC40MkII.lib', source=lib_objects, LIBS=['Winmm'])


# Build C++ tests
def defineTestProgram(environment, filename, srcext='.cpp'):
    test_objects = [ environment.Object(target=build_dir+'/'+filename+'.obj', source='tests/'+filename+srcext) ]
    test = environment.Program(build_dir+'/'+filename+'.exe', source=test_objects, LIBS=[build_dir+'/APC40MkII.lib', 'Winmm'])
    environment.AlwaysBuild(test)

defineTestProgram(env, 'test')
defineTestProgram(env, 'test-mode0')

# Build C Binding tests
if int(buildc):
    defineTestProgram(env_c_tests, 'test-c-binding', '.c')