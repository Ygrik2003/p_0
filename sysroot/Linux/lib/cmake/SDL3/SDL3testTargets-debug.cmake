#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SDL3::SDL3_test" for configuration "Debug"
set_property(TARGET SDL3::SDL3_test APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SDL3::SDL3_test PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libSDL3_testd.a"
  )

list(APPEND _cmake_import_check_targets SDL3::SDL3_test )
list(APPEND _cmake_import_check_files_for_SDL3::SDL3_test "${_IMPORT_PREFIX}/lib/libSDL3_testd.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
