{
    'targets' : [
        {
            'target_name': 'root',
            'type' : 'static_library',
            'includes' : [
                '../root/root_common.gypi'
            ],
            'dependencies' : [
                '../root/memory/memory.gyp:memory'
            ]
        }
    ]
}