set(DISPLAY_CC)
set(DISPLAY_EXTRA_CC) 

set(DISPLAY_THAT_CAN_BE_PLUGINS
  vga.cc
  ${DISPLAY_CC}
)

set(DISPLAY_THAT_SUPPORT_OTHER_PLUGINS
  vgacore.cc
  ddc.cc
  ${DISPLAY_EXTRA_CC}
)

set(DISPLAY_NONPLUGIN_CC
 ${DISPLAY_THAT_CANNOT_BE_PLUGINS}
 ${DISPLAY_THAT_CAN_BE_PLUGINS}
 ${DISPLAY_THAT_SUPPORT_OTHER_PLUGINS}
)

set(DISPLAY_PLUGIN_CC)

add_library(display STATIC ${DISPLAY_NONPLUGIN_CC})

target_include_directories(display PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/..
${CMAKE_CURRENT_SOURCE_DIR}/../..
${CMAKE_CURRENT_SOURCE_DIR}/../../instrument/stubs)

target_compile_options(display PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)