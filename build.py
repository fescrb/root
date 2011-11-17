import os
import sys

if not os.path.exists('obj'):
    os.mkdir('obj')
    
os.chdir('obj')

if not os.system('cmake .. -DROOT_USE_SIMD=1'):
    os.system('make')
else:
    sys.exit(1)