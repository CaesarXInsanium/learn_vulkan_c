project(
  'learn_vulkan',
  'c',
  version : '0.1',
  default_options: [
    'warning_level=3',
    'werror=true',
    'buildtype=debug',
    'debug=true',
    #'optimization=3',
    'c_std=c18'
  ]
)


DEPS = [
  dependency('glfw3'),
  dependency('cglm'),
  dependency('vulkan'),
]


vklearn = [
  'src/app.c',
  'src/constants.c',
  'src/main.c',
  'src/window.c',
]

vklearn_exe = executable(
          'vklearn',
          vklearn, 
          install : true,
          dependencies: DEPS,
          include_directories: include_directories('include')
)
