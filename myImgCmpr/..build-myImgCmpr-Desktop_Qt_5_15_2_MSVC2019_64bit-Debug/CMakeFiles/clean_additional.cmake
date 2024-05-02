# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\myImgCmpr_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\myImgCmpr_autogen.dir\\ParseCache.txt"
  "myImgCmpr_autogen"
  )
endif()
