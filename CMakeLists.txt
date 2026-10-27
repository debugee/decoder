cmake_minimum_required(VERSION 3.30)

project(bochs-cmake LANGUAGES CXX C)

set(CMAKE_ASM_NASM_OBJECT_FORMAT bin)
enable_language(ASM_NASM)

set(patch_check_and_apply 
    git apply ${CMAKE_CURRENT_SOURCE_DIR}/patches/basename+quicktime.diff || echo patch_failed_or_already_applied
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

include(FetchContent)
include(ExternalProject)

#--enable-gdb-stub 和--enable-debugger 互斥
#选择--enable-x86-64之后才能选择
#    --enable-vmx=2
#    --enable-svm
#    --enable-avx
#    --enable-evex
#    --enable-cet

ExternalProject_Add(Bochs
    GIT_REPOSITORY https://github.com/bochs-emu/Bochs.git
    GIT_TAG REL_3_0_FINAL
    GIT_SHALLOW 1#浅克隆
    UPDATE_DISCONNECTED 1
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E env "CFLAGS=-g -O0" "CXXFLAGS=-g -O0" ../Bochs/bochs/configure
    --prefix=${CMAKE_INSTALL_PREFIX}
    --with-sdl2
    --enable-sb16
	--enable-ne2000
	--enable-all-optimizations
    --enable-cpu-level=6
    --enable-3dnow
    --enable-x86-64
    --enable-vmx=2
    --enable-svm
    --enable-avx
    --enable-evex
    --enable-cet
    --enable-pci
    --enable-clgd54xx
    --enable-voodoo
    --enable-usb
    --enable-usb-ohci
    --enable-usb-ehci
    --enable-usb-xhci
    --enable-busmouse
    --enable-es1370
    --enable-e1000
    --enable-plugins
    --enable-x86-debugger
    --enable-debugger
#    --enable-gdb-stub
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

add_custom_command(OUTPUT boot.elf.o
    COMMAND nasm
            -f elf64
            -g 
            -F dwarf
            -o ${CMAKE_CURRENT_BINARY_DIR}/boot.elf.o
            ${CMAKE_CURRENT_SOURCE_DIR}/boot.asm
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/boot.asm
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/boot.elf
    COMMAND x86_64-elf-ld
            -T ${CMAKE_CURRENT_SOURCE_DIR}/boot.ld
            -o ${CMAKE_CURRENT_BINARY_DIR}/boot.elf
            ${CMAKE_CURRENT_BINARY_DIR}/boot.elf.o
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/boot.elf.o ${CMAKE_CURRENT_SOURCE_DIR}/boot.ld
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/boot.bin
    COMMAND x86_64-elf-objcopy
            -O binary
            ${CMAKE_CURRENT_BINARY_DIR}/boot.elf
            ${CMAKE_CURRENT_BINARY_DIR}/boot.bin
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/boot.elf
)

add_custom_command(OUTPUT floppy.img
    COMMAND dd if=/dev/zero of=floppy.img bs=512 count=2880 && dd if=${CMAKE_CURRENT_BINARY_DIR}/boot.bin of=floppy.img bs=512 count=1 conv=notrunc
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/boot.bin
)

add_custom_target(create_floppy_img ALL DEPENDS floppy.img)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/floppy.img DESTINATION .)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/boot.bin DESTINATION .)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/boot.elf DESTINATION .)

set(FILE_FLOPPY_IMG ${CMAKE_INSTALL_PREFIX}/floppy.img)
configure_file(bochsrc.txt.in bochsrc.txt @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bochsrc.txt DESTINATION .)