{
    'targets' : [
        {
            'target_name': 'io',
            'type' : 'static_library',
            'includes' : [
                '../root_common.gypi'
            ],
            'sources' : [
                'buffer_stream.cpp',
                'format.cpp',
                'log.cpp'
            ]
        }
    ]
}