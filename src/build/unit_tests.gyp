{
    'targets' : [
        {
            'target_name': 'unit_tests',
            'type' : 'executable',
            'cflags' : [
                '-g -fPIC'
            ],
            'includes' : [
                '../root/root_common.gypi',
                '../root/core/test/core_tests.gypi',
                '../root/math/test/math_tests.gypi',
                '../root/memory/test/memory_tests.gypi',
                '../root/io/test/io_tests.gypi'
            ],
            'dependencies' : [
                'root_library.gyp:root'
            ],
            'link_settings': {
                'libraries': [
                    '-lgtest_maind',
                    '-lgtestd',
                    '-lgmockd',
                    '-pthread'
                ],
                'library_dirs': [
                    '../../lib'
                ]
            }
        }
    ]
}