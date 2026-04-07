option(ENABLE_X86_64 "Compile x86_64-only sources" ON)

set(CPU_SRCS
  init.cc
  cpu.cc
  event.cc
  icache.cc
  decoder/fetchdecode32.cc
  decoder/fetchdecode_opmap_0f38.cc
  decoder/fetchdecode_opmap_0f3a.cc
  decoder/fetchdecode_opmap_avx.cc
  decoder/fetchdecode_opmap_xop.cc
  decoder/fetchdecode_opmap_evex.cc
  access.cc
  access2.cc
  shift16.cc
  logical16.cc
  ctrl_xfer32.cc
  ctrl_xfer16.cc
  mmx.cc
  3dnow.cc
  3dnow_rcp.cc
  fpu_emu.cc
  sse.cc
  sse_move.cc
  sse_pfp.cc
  sse_rcp.cc
  sse_string.cc
  xsave.cc
  aes.cc
  gf2.cc
  sha.cc
  sha512.cc
  sm3.cc
  sm4.cc
  svm.cc
  vmx.cc
  vmcs.cc
  vmexit.cc
  vmfunc.cc
  soft_int.cc
  apic.cc
  bcd.cc
  mult16.cc
  tasking.cc
  shift32.cc
  shift8.cc
  arith8.cc
  stack.cc
  stack16.cc
  protect_ctrl.cc
  mult8.cc
  load.cc
  data_xfer8.cc
  vm8086.cc
  logical8.cc
  logical32.cc
  arith16.cc
  segment_ctrl.cc
  data_xfer16.cc
  data_xfer32.cc
  exception.cc
  cpuid.cc
  proc_ctrl.cc
  mwait.cc
  crregs.cc
  cet.cc
  msr.cc
  smm.cc
  flag_ctrl_pro.cc
  stack32.cc
  debugstuff.cc
  flag_ctrl.cc
  mult32.cc
  arith32.cc
  jmp_far.cc
  call_far.cc
  ret_far.cc
  iret.cc
  ctrl_xfer_pro.cc
  segment_ctrl_pro.cc
  io.cc
  crc32.cc
  bit.cc
  bit16.cc
  bit32.cc
  bmi32.cc
  string.cc
  faststring.cc
  paging.cc
  rdrand.cc
  rao.cc
  wide_int.cc
  decoder/disasm.cc
)

# x86_64-only sources (converted from OBJS64)
set(CPU_SRCS_X86_64
  arith64.cc
  ctrl_xfer64.cc
  data_xfer64.cc
  decoder/fetchdecode64.cc
  logical64.cc
  mult64.cc
  shift64.cc
  bit64.cc
  stack64.cc
  bmi64.cc
  cmpccxadd32.cc
  cmpccxadd64.cc
  vapic.cc
  uintr.cc
)

if(ENABLE_X86_64)
  list(APPEND CPU_SRCS ${CPU_SRCS_X86_64})
endif()

add_library(cpu STATIC ${CPU_SRCS})

target_include_directories(cpu PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/..
${CMAKE_CURRENT_SOURCE_DIR}/../instrument/stubs)

target_compile_options(cpu PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)

add_subdirectory(cpudb)
add_subdirectory(fpu)
add_subdirectory(avx)
add_subdirectory(softfloat3e)