project(
  'RaxtorC',
  'c',
  version : '0.1',
  default_options: [
    'warning_level=3',
    'werror=true',
    'buildtype=debug',
    'debug=true',
    'c_std=gnu18'
  ]
)

DEPS = [
  dependency('glfw3'),
  dependency('vulkan'),
  dependency('cglm'),
]

libraxtor_src = [
  'raxtor-c/utils.c',
   'raxtor-c/extensions.c',
   'raxtor-c/validation.c',
   'raxtor-c/debug.c',
   'raxtor-c/instance.c',
   'raxtor-c/renderer.c',
  # 'raxtor-c/physical_device.c',
  # 'raxtor-c/logical_device.c',
  # 'raxtor-c/renderer.c',
]

libraxtorc = shared_library(
  'raxtorc',
  libraxtor_src,
  dependencies: DEPS,
  include_directories: include_directories('raxtor-c/include'),
)

app_src = [
  'learnvulkan/main.c',
  'learnvulkan/app.c',
  'learnvulkan/window.c',
]

# example executable
learnvulkan =  executable(
          'learnvulkan',
          app_src, 
          install : true,
          dependencies: DEPS,
          link_with: [libraxtorc],
          include_directories: include_directories('raxtor-c/include')
)
