{
    'targets' : [
        {
            'target_name': 'graphics',
            'type' : 'static_library',
            'includes' : [
                '../root_common.gypi'
            ],
            'sources' : [
                'instance.cpp',
                'physical_device.cpp',
                'window.cpp',
                'device.cpp',
                'vk_format.cpp'
            ],
            'link_settings': {
                'libraries': [
                    '-lvulkan'
                ],
            }
        }
    ]
}