cmake_minimum_required(VERSION 3.30)

project(bochs-cmake)

set(patch_check_and_apply 
    git apply ${CMAKE_CURRENT_SOURCE_DIR}/patches/basename.diff || echo patch_failed_or_already_applied
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

include(FetchContent)
include(ExternalProject)

ExternalProject_Add(Bochs
    GIT_REPOSITORY https://github.com/bochs-emu/Bochs.git
    GIT_TAG REL_3_0_FINAL
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E env "CFLAGS=-g -O0" "CXXFLAGS=-g -O0" ../Bochs/bochs/configure --prefix=${CMAKE_INSTALL_PREFIX} --with-sdl --enable-debugger
    PATCH_COMMAND ${patch_check_and_apply}
    BUILD_COMMAND make
    INSTALL_COMMAND make install
)
ExternalProject_Get_Property(Bochs SOURCE_DIR)
ExternalProject_Get_Property(Bochs BINARY_DIR)

install(DIRECTORY ${SOURCE_DIR}/bochs/cpu/decoder DESTINATION bochs/cpu)
install(FILES ${SOURCE_DIR}/bochs/misc/bswap.h DESTINATION bochs/misc/)
install(FILES ${SOURCE_DIR}/bochs/instrument/stubs/instrument.h DESTINATION bochs/instrument/stubs/)
install(FILES ${SOURCE_DIR}/bochs/logio.h DESTINATION bochs/)
install(FILES ${BINARY_DIR}/config.h DESTINATION bochs/)
install(FILES ${SOURCE_DIR}/bochs/osdep.h DESTINATION bochs/)
install(FILES ${SOURCE_DIR}/bochs/bochs.h DESTINATION bochs/)

install(FILES CMakeLists.txt.in DESTINATION . RENAME CMakeLists.txt)
install(FILES main.cc DESTINATION .)
