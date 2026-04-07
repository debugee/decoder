set(MEMORY_SRCS
    memory.cc
    memory_stub.cc
    misc_mem.cc
)

add_library(memory STATIC ${MEMORY_SRCS})

target_include_directories(memory PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/..

${CMAKE_CURRENT_SOURCE_DIR}/../instrument/stubs)

target_compile_options(memory PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)