cmake_minimum_required(VERSION 3.1)
project (OORA)
enable_language (C)


# Default to Release build
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()



# FFLAGS depend on the compiler
get_filename_component (C_COMPILER_NAME ${CMAKE_C_COMPILER} NAME)

if (C_COMPILER_NAME MATCHES "gcc.*")
  # gcc
  set (CMAKE_C_FLAGS_RELEASE "-O")
  set (CMAKE_C_FLAGS_DEBUG   "-O0 -g")
elseif (C_COMPILER_NAME MATCHES "cc.*")
  # cc
  set (CMAKE_C_FLAGS_RELEASE "-O")
  set (CMAKE_C_FLAGS_DEBUG   "-O0 -g")
elseif (C_COMPILER_NAME MATCHES "icc.*")
  # icc
  set (CMAKE_C_FLAGS_RELEASE "-O")
  set (CMAKE_C_FLAGS_DEBUG   "-O0 -g")
else (C_COMPILER_NAME MATCHES "gcc.*")
  message ("CMAKE_C_COMPILER full path: " ${CMAKE_C_COMPILER})
  message ("C compiler: " ${C_COMPILER_NAME})
  message ("No optimized C compiler flags are known, we just try -O2...")
  set (CMAKE_C_FLAGS_RELEASE "-O2")
  set (CMAKE_C_FLAGS_DEBUG   "-O0 -g")
endif (C_COMPILER_NAME MATCHES "gcc.*")

include_directories("${PROJECT_SOURCE_DIR}/src")

set(SRC src)
set(OORA_SRC
  ${SRC}/mm1.c
  )
  
# --------------------------------------------------------------------
# Libraries
# --------------------------------------------------------------------
set(OORA_LIBS)

# Searching PAPI libs

find_path(PAPI_PREFIX
    NAMES include/papi.h
)

find_library(PAPI_LIBRARIES
    # Pick the static library first for easier run-time linking.
    NAMES libpapi.so libpapi.a papi
    HINTS ${PAPI_PREFIX}/lib
)

find_path(PAPI_INCLUDE_DIRS
    NAMES papi.h
    HINTS ${PAPI_PREFIX}/include
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PAPI DEFAULT_MSG
    PAPI_LIBRARIES
    PAPI_INCLUDE_DIRS
)

mark_as_advanced(
    PAPI_PREFIX_DIRS
    PAPI_LIBRARIES
    PAPI_INCLUDE_DIRS
)

# Linking PAPI libs

include_directories(${PAPI_INCLUDE_DIRS})
link_directories(${PAPI_LIBRARIES})
list(APPEND OORA_LIBS ${PAPI_LIBRARIES})

# --------------------------------------------------------------------
# Exec
# --------------------------------------------------------------------

add_executable(OORA ${OORA_SRC})
target_link_libraries(OORA ${OORA_LIBS})

