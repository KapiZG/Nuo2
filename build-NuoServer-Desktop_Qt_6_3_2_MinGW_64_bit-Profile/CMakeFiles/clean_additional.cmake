# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "CMakeFiles\\NuoServer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NuoServer_autogen.dir\\ParseCache.txt"
  "NuoServer_autogen"
  )
endif()
