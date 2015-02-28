root = True

compiler = 'clang++'

cc_flags = [
  '-Wall', '-Werror',
  '-std=c++11',
  '-I' + os.path.abspath('../dependencies/spdlog/include'),
  '-I' + os.path.abspath('engine'),
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
      'sfml-system',
      'thor',
      'pthread',
    ]
  },
}
