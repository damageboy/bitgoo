cmake_minimum_required(VERSION 3.10)
project(bitgoo LANGUAGES CXX)
#set(CMAKE_CXX_STANDARD 11)

# Location of additional cmake modules
#
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${PROJECT_SOURCE_DIR}/cmake
    )

# Guard against in-source builds and bad build-type strings
#
include(ConfigSafeGuards)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# If you want to self-test benchmark lib too, turn me ON
#
set(BENCHMARK_ENABLE_TESTING OFF)

# Configure google micro benchmark
#

#set(SANITIZERS "-fsanitize=address,bounds,alignment,bool,enum,shift,shift-exponent")

# c++11 is required
#
if((CMAKE_CXX_COMPILER_ID MATCHES GNU) OR (CMAKE_CXX_COMPILER_ID MATCHES Clang))
   set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=c++11 -mbmi2 -march=native")
   set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3 ${SANITIZERS}")
   set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;IACA" CACHE STRING
        "Available build-types: Debug, Release and IACA")

set(CMAKE_CXX_FLAGS_IACA "${CMAKE_CXX_FLAGS_RELEASE} -DUSE_IACA")
set(CMAKE_C_FLAGS_IACA "${CMAKE_CXX_FLAGS_RELEASE} -DUSE_IACA")

include(ConfigGBench)
include(ConfigGTest)

add_subdirectory(${PROJECT_SOURCE_DIR}/bitgoo/)
add_subdirectory(${PROJECT_SOURCE_DIR}/bench/)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests/)

