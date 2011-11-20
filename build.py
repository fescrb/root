import os
import sys

# Declare variables
extra_flags= ""
verbose = ""
demos = ""
use_simd = " -DROOT_USE_SIMD=1 "

if len(sys.argv) > 1 :
	argc = 1
	while argc < len(sys.argv) :
		command = sys.argv[argc]
		if command == "extraflags":
			argc+=1
			extra_flags = sys.argv[argc]
		argc+=1
		if command == "verbose":
			verbose = " VERBOSE=1 "
		if command == "withdemos":
			demos = " -DROOT_COMPILE_DEMOS=1 "
		if command == "nosimd":
			use_simd = " "
	

if not os.path.exists('obj'):
    os.mkdir('obj')
    
os.chdir('obj')

cmake_command = 'cmake .. ' + use_simd + demos + ' -DEXTRA_FLAGS="' + extra_flags + '" '
make_command = 'make ' + verbose

if not os.system(cmake_command):
    os.system(make_command)
else:
    sys.exit(1)