set(IODEV_THAT_CANNOT_BE_PLUGINS
  devices.cc
  virt_timer.cc
  slowdown_timer.cc
  ${MCH_OBJS}
)

set(IODEV_THAT_CAN_BE_PLUGINS
  pic.cc
  pit.cc
  serial.cc
  parallel.cc
  floppy.cc
  keyboard.cc
  biosdev.cc
  cmos.cc
  harddrv.cc
  dma.cc
  unmapped.cc
  extfpuirq.cc
  speaker.cc
  ioapic.cc
  pci.cc
  pci2isa.cc
  pci_ide.cc
  acpi.cc
  hpet.cc
)

set(IODEV_THAT_SUPPORT_OTHER_PLUGINS
  pit82c54.cc
  scancodes.cc
  serial_raw.cc
)

set(IODEV_NONPLUGIN_CC 
    ${IODEV_THAT_CANNOT_BE_PLUGINS}
    ${IODEV_THAT_CAN_BE_PLUGINS}
    ${IODEV_THAT_SUPPORT_OTHER_PLUGINS}
)

set(IODEV_PLUGIN_CC
)


add_library(iodev STATIC ${IODEV_NONPLUGIN_CC})

target_include_directories(iodev PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/..
${CMAKE_CURRENT_SOURCE_DIR}/../instrument/stubs)

target_compile_options(iodev PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)

add_subdirectory(display)
add_subdirectory(hdimage)