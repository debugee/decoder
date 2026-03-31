cmake_minimum_required(VERSION 3.30)

project(decoder)

add_executable(decoder
    main.cc
    bochs/cpu/decoder/disasm.cc 
    bochs/cpu/decoder/fetchdecode32.cc 
    bochs/cpu/decoder/fetchdecode64.cc
    bochs/cpu/decoder/fetchdecode_opmap_0f3a.cc
    bochs/cpu/decoder/fetchdecode_opmap_0f38.cc
    bochs/cpu/decoder/fetchdecode_opmap_avx.cc
    bochs/cpu/decoder/fetchdecode_opmap_evex.cc
    bochs/cpu/decoder/fetchdecode_opmap_xop.cc
)

target_compile_definitions(decoder PRIVATE -DBX_STANDALONE_DECODER -DBX_INSTR_STORE_OPCODE_BYTES)

target_compile_options(decoder PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)