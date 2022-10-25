{
    "targets": [{
        "target_name": "fallocate",
        "cflags": ["-Wno-cast-function-type"],
        "include_dirs": ["<!(node -e \"require('nan')\")"],
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
