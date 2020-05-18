{
    'targets' : [
        {
            'target_name': 'memory',
            'type' : 'static_library',
            'includes' : [
                '../root_common.gypi'
            ],
            'sources' : [
                'allocator.cpp',
                'system_allocator.cpp'
            ]
        }
    ]
}