{
    "targets": [{
        "target_name": "fallocate",
        "defines": ['NAPI_DISABLE_CPP_EXCEPTIONS'],
        "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
        "conditions": [
            ['OS=="mac"', {
                "sources": [
                    "src/mac/fallocate.cc"
                ],
            }],
            ['OS=="linux"', {
                "sources": [
                    'src/linux/fallocate.cc'
                ],
            }],
        ]
    }],
}
