cmake_minimum_required(VERSION 3.30)

project(decoder)

add_executable(decoder main.cc disasm.cc fetchdecode32.cc fetchdecode64.cc)

target_compile_definitions(decoder PRIVATE -DBX_STANDALONE_DECODER -DBX_INSTR_STORE_OPCODE_BYTES)

target_compile_options(decoder PRIVATE -Wno-deprecated-declarations)