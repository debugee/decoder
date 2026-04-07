set(HDIMAGE_CDROM_CC cdrom.cc cdrom_osx.cc)
set(HDIMAGE_EXTRA_CC vbox.cc vmware3.cc vmware4.cc vpc.cc vvfat.cc)

set(HDIMAGE_THAT_CANNOT_BE_PLUGINS
  hdimage.cc
  ${HDIMAGE_CDROM_CC}
)

set(HDIMAGE_THAT_CAN_BE_PLUGINS
  ${HDIMAGE_EXTRA_CC}
)

set(HDIMAGE_NONPLUGIN_CC
 ${HDIMAGE_THAT_CANNOT_BE_PLUGINS}
 ${HDIMAGE_THAT_CAN_BE_PLUGINS}
 ${HDIMAGE_THAT_SUPPORT_OTHER_PLUGINS}
)

set(HDIMAGE_PLUGIN_CC)

add_library(hdimage STATIC ${HDIMAGE_NONPLUGIN_CC})

target_include_directories(hdimage PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/..
${CMAKE_CURRENT_SOURCE_DIR}/../..
${CMAKE_CURRENT_SOURCE_DIR}/../../instrument/stubs)

target_compile_options(hdimage PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)