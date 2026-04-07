set(AVX_SRCS
	amx.cc 
	avx.cc 
	avx_pfp.cc 
	avx_cvt.cc 
	avx_fma.cc 
	avx_ifma52.cc 
	avx_ne_convert.cc 
	avx2.cc 
	avx512.cc 
	avx512_broadcast.cc 
	avx512_move.cc 
	avx512_pfp.cc 
	avx512_pfp16.cc 
	avx512_rcp14.cc 
	avx512_rsqrt14.cc 
	avx512_cvt.cc 
	avx512_cvt16.cc 
	avx512_fma.cc 
	avx512_mask8.cc 
	avx512_mask16.cc 
	avx512_mask32.cc 
	avx512_mask64.cc 
	avx512_bitalg.cc 
	avx512_bf16.cc 
	avx512_helpers.cc 
	gather.cc 
	tbm32.cc 
	tbm64.cc 
	xop.cc 
	bf16_arith.cc 
	avx10_2_cvt.cc 
	avx10_2_cvt_fp8.cc 
	avx10_2_minmax.cc 
	avx10_2_bf16.cc 
	avx10_2_misc.cc
)

add_library(avx STATIC ${AVX_SRCS})

target_include_directories(avx PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/..
${CMAKE_CURRENT_SOURCE_DIR}/../..
${CMAKE_CURRENT_SOURCE_DIR}/../../instrument/stubs)

target_compile_options(avx PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)