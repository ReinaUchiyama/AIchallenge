# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_bag_manager_py_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED bag_manager_py_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(bag_manager_py_FOUND FALSE)
  elseif(NOT bag_manager_py_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(bag_manager_py_FOUND FALSE)
  endif()
  return()
endif()
set(_bag_manager_py_CONFIG_INCLUDED TRUE)

# output package information
if(NOT bag_manager_py_FIND_QUIETLY)
  message(STATUS "Found bag_manager_py: 0.1.0 (${bag_manager_py_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'bag_manager_py' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${bag_manager_py_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(bag_manager_py_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${bag_manager_py_DIR}/${_extra}")
endforeach()
