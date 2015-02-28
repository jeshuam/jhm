targets = {
  'engine': {
    'type': 'library',
    'deps': [
      '//engine:components',
      '//engine:game',
    ]
  },

  'components': {
    'type': 'library',
    'srcs': [
      'component/*.cc',
    ],
  },

  'utility': {
    'type': 'library',
    'srcs': [
      'utility/*.cc',
    ],

    'deps': [
      '//engine:json',
    ],
  },

  'game': {
    'type': 'library',
    'srcs': [
      'game/*.cc',
    ],

    'deps': [
      '//engine:utility',
    ],
  },

  'json': {
    'type': 'library',
    'srcs': [
      'json/json_reader.cpp',
      'json/json_value.cpp',
      'json/json_writer.cpp',
    ],
  }
}
