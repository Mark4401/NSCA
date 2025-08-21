#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "NSCA::NSCA" for configuration "Release"
set_property(TARGET NSCA::NSCA APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(NSCA::NSCA PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/bin/NSCA.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/NSCA.dll"
  )

list(APPEND _cmake_import_check_targets NSCA::NSCA )
list(APPEND _cmake_import_check_files_for_NSCA::NSCA "${_IMPORT_PREFIX}/bin/NSCA.lib" "${_IMPORT_PREFIX}/bin/NSCA.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
