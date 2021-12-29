"""
Currently only supports MSVC++
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
    env.Append(CCFLAGS = '/O2')
    env.Append(LINKFLAGS = '')
    build_dir = 'build/release'
else:
    env.Append(CCFLAGS = '/MTd')
    env.Append(LINKFLAGS = '/DEBUG:FULL')
    env.Append(CPPDEFINES = 'DEBUG')
    build_dir = 'build/debug'



# Gather list of sources
lib_sources = []
for root, dirnames, filenames in os.walk('src'):
    for filename in filenames:
        if fnmatch.fnmatch(filename, '*.cpp'):
            lib_sources.append(str(os.path.join(root, filename)))

# Build APCAPI
VariantDir('build', 'src', duplicate=0)
lib_objects = []
for s in lib_sources:
    t = s.replace('src', build_dir, 1).replace('.cpp', '.obj')
    lib_objects.append(env.Object(target=t, source=s))
env.StaticLibrary(build_dir+'/APC40MkII.lib', source=lib_objects, LIBS=['Winmm'])

# Build tests
def defineTestProgram(filename):
    test_objects = [ env.Object(target=build_dir+'/'+filename+'.obj', source='tests/'+filename+'.cpp') ]
    test = env.Program(build_dir+'/'+filename+'.exe', source=test_objects, LIBS=[build_dir+'/APC40MkII.lib', 'Winmm'])
    env.AlwaysBuild(test)

defineTestProgram('test')
defineTestProgram('test-mode0')

#test_objects = [ env.Object(target=build_dir+'/test-mode0.obj', source='tests/test-mode0.cpp') ]
#test = env.Program(build_dir+'/test-mode0.exe', source=test_objects, LIBS=[build_dir+'/APC40MkII.lib', 'Winmm'])
#env.AlwaysBuild(test)