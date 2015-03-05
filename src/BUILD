root = True

compiler = 'g++'

cc_flags = [
  '-Wall', '-Werror',
  '-std=c++0x',
  '-I"{}"'.format(os.path.abspath('.')),
  '-D_WIN32_WINNT=0x600'
]

link_flags = [

]

if os.name == 'nt':
  cc_flags.append('-D_WIN32_WINNT=0x600')
  link_flags.append('-L"{}"'.format('C:\\Libraries\\bin'))

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
      'sfml-graphics-2',
      'sfml-window-2',
      'sfml-system-2',
      'sfml-audio-2',
      'thor',
      'pthread',
      'jsoncpp'
    ]
  },
}

# C:\Python34\python.exe ..\..\cc-build\src\cc_build.py --static :all
