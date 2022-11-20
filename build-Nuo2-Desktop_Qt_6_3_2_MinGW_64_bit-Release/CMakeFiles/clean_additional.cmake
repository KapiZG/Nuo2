# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Nuo2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Nuo2_autogen.dir\\ParseCache.txt"
  "Nuo2_autogen"
  )
endif()
