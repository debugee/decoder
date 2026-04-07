set(CPUDB_SRCS
intel/i486dx4.cc 
intel/pentium.cc 
intel/pentium_mmx.cc 
intel/p2_klamath.cc 
intel/p3_katmai.cc 
intel/p4_willamette.cc 
intel/p4_prescott_celeron_336.cc 
intel/atom_n270.cc 
intel/core_duo_t2400_yonah.cc 
intel/core2_penryn_t9600.cc 
intel/corei5_lynnfield_750.cc 
intel/corei5_arrandale_m520.cc 
intel/corei7_sandy_bridge_2600K.cc 
intel/corei7_ivy_bridge_3770K.cc 
intel/corei7_haswell_4770.cc 
intel/broadwell_ult.cc 
intel/corei7_skylake-x.cc 
intel/corei3_cnl.cc 
intel/corei7_icelake-u.cc 
intel/tigerlake.cc 
intel/sapphire_rapids.cc 
intel/arrow_lake.cc 
amd/amd_k6_2_chomper.cc  
amd/athlon_xp.cc 
amd/athlon64_clawhammer.cc 
amd/athlon64_venice.cc 
amd/turion64_tyler.cc 
amd/phenomx3_8650_toliman.cc 
amd/trinity_apu.cc 
amd/zambezi.cc 
amd/ryzen.cc
)

add_library(cpudb STATIC ${CPUDB_SRCS} ../../bochs.h ../../config.h)

target_include_directories(cpudb PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/..
${CMAKE_CURRENT_SOURCE_DIR}/../..
${CMAKE_CURRENT_SOURCE_DIR}/../../instrument/stubs)

target_compile_options(cpudb PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)