set(BOCHS_NONINLINE_CC
	logio.cc
	main.cc
	config.cc
	pc_system.cc
	osdep.cc
	plugin.cc
	crc.cc
	bxthread.cc
)

set(BOCHS_EXTERN_ENVIRONMENT_CC
	main.cc
	config.cc
	pc_system.cc
)

set(BOCHS_SIMX86_CC)

add_compile_options(-fno-common)
add_definitions(-Dmacintosh -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES)
add_subdirectory(cpu)
add_subdirectory(memory)
add_subdirectory(iodev)
add_subdirectory(gui)


set(GDBSTUB_CC gdbstub.cc)

set(BOCHS_CC ${BOCHS_NONINLINE_CC})

add_executable(bochs ${BOCHS_CC})

target_include_directories(bochs PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/instrument/stubs)

target_compile_options(bochs PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)

target_link_libraries(bochs PRIVATE
    iodev
    display
    hdimage
    "-Wl,-force_load,$<TARGET_FILE:cpu>"
    cpudb
    memory
    gui
    softfloat
    avx
    fpu
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL REQUIRED IMPORTED_TARGET sdl)

target_link_libraries(bochs PRIVATE PkgConfig::SDL)

find_library(COCOA_FRAMEWORK Cocoa)
find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
find_library(IOKIT_FRAMEWORK IOKit)
target_link_libraries(bochs PRIVATE ${COCOA_FRAMEWORK} ${COREFOUNDATION_FRAMEWORK} ${IOKIT_FRAMEWORK})

target_compile_definitions(bochs PRIVATE -DBX_SHARE_PATH="/Users/admin/Desktop/Bochs/install/share/bochs")