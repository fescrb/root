{
    'targets' : [
        {
            'target_name': 'unit_tests',
            'type' : 'executable',
            'includes' : [
                '../root/root_common.gypi',
                '../root/memory/test/memory_tests.gypi'
            ],
            'dependencies' : [
                'root_library.gyp:root'
            ],
            'link_settings': {
                'libraries': [
                    '-lgtest_main',
                    '-lgtest',
                    '-lgmock',
                    '-pthread'
                ],
                'library_dirs': [
                    '../../lib'
                ]
            }
        }
    ]
}