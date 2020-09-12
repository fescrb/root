{
    'targets' : [
        {
            'target_name': 'universal_test',
            'type' : 'executable',
            'cflags' : [
                '-g -fPIC'
            ],
            'include_dirs' : [
                '../../include/'
            ],
            'sources' : [
                'universal_test.cpp',
            ],
            'dependencies' : [
                '../build/root_library.gyp:root'
            ],
            'link_settings': {
                'libraries': [
                    '-pthread'
                ],
                'library_dirs': [
                    '../../lib'
                ]
            }
        }
    ]
}