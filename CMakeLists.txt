cmake_minimum_required(VERSION 3.12)
project(tiny-httpd C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_COMPILER_IS_GNUCC TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE DEBUG CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

message(STATUS "C flags, Debug configuration: ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "C flags, Release configuration: ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "C flags, Release configuration with Debug info: ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message(STATUS "C flags, minimal Release configuration: ${CMAKE_C_FLAGS_MINSIZEREL}")

#add_executable(client clients/simpleclient.c)
add_executable(httpd httpd.c)
add_executable(httpd-select httpd-select.c)
add_executable(httpd-fork httpd-fork.c)

find_library(LIBEVENT2_CORE event_core)
add_executable(httpd-libevent httpd-libevent.c)
target_link_libraries(httpd-libevent ${LIBEVENT2_CORE})

add_subdirectory(clients)
add_subdirectory(samples)