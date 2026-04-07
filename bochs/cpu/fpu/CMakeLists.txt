set(FPU_SRCS
    ferr.cc
    fpu.cc
    fpu_arith.cc
    fpu_compare.cc
    fpu_const.cc
    fpu_cmov.cc
    fpu_load_store.cc
    fpu_misc.cc
    fpu_trans.cc
    fprem.cc
    fsincos.cc
    f2xm1.cc
    fyl2x.cc
    fpatan.cc
    poly.cc
)

add_library(fpu STATIC ${FPU_SRCS})

target_include_directories(fpu PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/..
${CMAKE_CURRENT_SOURCE_DIR}/../..
${CMAKE_CURRENT_SOURCE_DIR}/../../instrument/stubs)

target_compile_options(fpu PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)