#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cpptrace::cpptrace" for configuration "Debug"
set_property(TARGET cpptrace::cpptrace APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(cpptrace::cpptrace PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libcpptrace.a"
  )

list(APPEND _cmake_import_check_targets cpptrace::cpptrace )
list(APPEND _cmake_import_check_files_for_cpptrace::cpptrace "${_IMPORT_PREFIX}/lib/libcpptrace.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
