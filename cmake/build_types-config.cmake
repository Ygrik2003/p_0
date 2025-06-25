set(CMAKE_CONFIGURATION_TYPES
    Debug
    Release
    RelWithDebInfo
    MinSizeRel
    Coverage)

set(coverage_compiler_flags
    $<$<CXX_COMPILER_ID:Clang>:
    -fprofile-instr-generate
    -fcoverage-mapping
    -fcoverage-mcdc
    >
    -coverage)
set(coverage_linker_flags -coverage)

set(CMAKE_C_FLAGS_COVERAGE ${CMAKE_C_FLAGS_RELWITHDEBINFO}
                           ${coverage_compiler_flags})
set(CMAKE_CXX_FLAGS_COVERAGE ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}
                             ${coverage_compiler_flags})
set(CMAKE_EXE_LINKER_FLAGS_COVERAGE ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}
                                    ${coverage_linker_flags})
set(CMAKE_STATIC_LINKER_FLAGS_COVERAGE
    ${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO} ${coverage_linker_flags})
set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    ${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} ${coverage_linker_flags})
