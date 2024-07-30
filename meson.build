# SPDX-License-Identifier: Apache-2.0
#
# Copyright 2023 Ledger SAS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# XXX:
#   There is no `C` sources to build in this project but as we use `C` pre processor
#   to digest input dts file (using `#include` directive for dtsi and defines).
#   We must define the project as a `C` project to get a working `C` compiler.
project(
    'devicetree', 'c',
    meson_version: '>=1.3.0',
    version: run_command('dunamai', 'from', 'git', '--style', 'semver', '--dirty', check: true)
             .stdout().strip(),
    license: 'Apache-2.0',
    license_files: ['LICENSES/Apache-2.0.txt'],
)

fs = import('fs')
pymod =  import('python')
py3 = pymod.find_installation('python3', modules: ['dts_utils'])

dtc = find_program('dtc')

# XXX: dtscheme is not compatible w/ our usage of jsonschema
#      i.e. stuck in <= 4.17 but we need >= 4.18 for json `$ref` features
#      This is disabled until dtschema bump
# dt_validate = find_program('dt-validate')

dts2src = find_program('dts2src')

# dts input file search path order:
# - Path is absolute
# - If relative:
#   - from global source root (i.e. top level meson project)
#   - from (this) project source root
devicetree_in = fs.expanduser(get_option('dts'))
if not fs.is_absolute(devicetree_in)
    # check if file exists in parent project
    dts_filename = join_paths(meson.global_source_root(), devicetree_in)
    if not fs.exists(dts_filename)
        dts_filename = join_paths(meson.project_source_root(), devicetree_in)
    endif
    devicetree_in = dts_filename
endif

if not fs.exists(devicetree_in)
    error('Cannot find DTS file', devicetree_in)
endif

devicetree_include_dirs = get_option('dts-include-dirs')
devicetree_bindings_dir = fs.expanduser(get_option('dts-bindings-dir'))

devicetree_cppflags = [
    '-E',
    '-P',
    '-nostdinc',
    '-undef',
    '-x', 'assembler-with-cpp'
]

# local dts include dir always added
devicetree_cppflags += [
    '-I', meson.current_source_dir() / 'include',
    '-I', meson.current_source_dir() / 'dts' / 'arch',
    '-I', meson.current_source_dir() / 'dts' / 'manufacturer',
    '-I', meson.current_source_dir() / 'dts' / 'common'
]

# There is no substitution while executing custom target commands
# so we need to exand user home (`~`) here.
# Relpath are always expands from global source root (i.e. rop level project).
# Prefer abspath here.
foreach d: devicetree_include_dirs
    d = fs.expanduser(d)
    if not fs.is_absolute(d)
        d = meson.global_source_root() / d
    endif
    devicetree_cppflags += [ '-I', d ]
endforeach

devicetree_dep = declare_dependency(
    include_directories: [ 'include' ]
)

# XXX:
# Do the same as include dir once bindings and dt-validate are up.
devicetree_bindings_dir = join_paths(meson.global_source_root(), 'include')

# Copy script at configure time
# The DTS file is copied in build tree and a depfile is created.
# This is required by meson, which can work only w/ file inside the project sandbox.
# In project integration mode, dts file is likely in outpost project top level directory
devicetree_copy = '''
import shutil
import sys
shutil.copyfile(sys.argv[1], sys.argv[2])
with open(sys.argv[3], "wt") as f:
    f.write(sys.argv[1])
'''

devicetree_dts_in = configure_file(
    output: fs.name(devicetree_in),
    depfile: fs.name(devicetree_in) + '.deps',
    command: [py3, '-c', devicetree_copy, devicetree_in, '@OUTPUT@', '@DEPFILE@']
)

devicetree_dtsd = custom_target('devicetree-dtsd',
    input: devicetree_dts_in,
    output: '@PLAINNAME@.pp',
    depfile: '@PLAINNAME@.d',
    command: meson.get_compiler('c', native: false).cmd_array() +
        devicetree_cppflags + [
        '@INPUT@',
        '-MT', '@INPUT@',
        '-MMD',  '-MF', '@DEPFILE@',
        '-o', '@OUTPUT@'],
)

devicetree_dts = custom_target('devicetree-dts',
    input: devicetree_dtsd,
    output: '@BASENAME@.dts',
    command: [ dtc, '-I', 'dts', '-O', 'dts', '-o', '@OUTPUT@', '@INPUT@' ],
    install: false
)

devicetree_dtb = custom_target('devicetree-dtb',
    input: devicetree_dtsd,
    output: '@BASENAME@.dtb',
    command: [ dtc, '-I', 'dts', '-O', 'dtb', '-o', '@OUTPUT@', '@INPUT@' ],
    install: false
)

# XXX:
#  To be removed ?
#  This might be unused, was necessary with old dtschema for validation
#  But newer version use dt blob instead.
devicetree_yaml = custom_target('devicetree-yaml',
    input: devicetree_dtsd,
    output: '@BASENAME@.yaml',
    command: [dtc, '-I', 'dts', '-O', 'yaml', '-o', '@OUTPUT@', '@INPUT@'],
    install: false
)

# pretty named targets
alias_target('dts',
    devicetree_dtb,
)

# XXX: cf above comment next to find_program
# run_target('dts-validate',
#     depends: devicetree_dtb,
#     command: [dt_validate, '-s', devicetree_bindings_dir, '-m', '-n', devicetree_dtb]
# )

summary(
    {
        'dts': devicetree_in,
        'extra include dirs': devicetree_include_dirs,
    },
    section: 'Device tree'
)
