# init @ variables before doing anything else


# Dependencies
include(CMakeFindDependencyMacro)
find_dependency(cpptrace REQUIRED)
if(OFF)
  find_dependency(magic_enum REQUIRED)
endif()

# We cannot modify an existing IMPORT target
if(NOT TARGET libassert::assert)

  # import targets
  include("${CMAKE_CURRENT_LIST_DIR}/libassert-targets.cmake")

endif()

if(TRUE)
    target_compile_definitions(libassert::assert INTERFACE LIBASSERT_STATIC_DEFINE)
endif()
