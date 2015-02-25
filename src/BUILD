root = True

compiler = 'clang++'

cc_flags = [
  '-std=c++11',
  '-I' + os.path.abspath('../dependencies/SFML-2/include')
]

link_flags = ['-L' + os.path.abspath('../dependencies/SFML-2/bin/lib')]

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
