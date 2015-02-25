root = True

compiler = 'clang++'

cc_flags = [
  '-Wall', '-Werror',
  '-std=c++11'
]

link_flags = []

targets = {
  'jhm': {
    'type': 'binary',
    'srcs': [
      'main.cc',
      'jhm.cc',
    ],

    'deps': [
      '//engine:engine'
    ],

    'link_with': [
      'sfml-graphics',
      'sfml-window',
      'sfml-system'
    ]
  },
}
