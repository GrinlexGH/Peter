cmake_minimum_required(VERSION 3.22)

project("Peter" VERSION 0.0.0.0 LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
message(STATUS "Using C standard: c${CMAKE_C_STANDARD}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Using C++ standard: c++${CMAKE_CXX_STANDARD}")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(
        "-Wall" "-Wextra" "-Wpedantic"
        "$<$<CONFIG:Release>:-Werror>"
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(
        "/W4" "/utf-8" "/Zc:__cplusplus"
        "$<$<CONFIG:Release>:/WX;/Ox>"
    )
endif()

add_compile_definitions(UNICODE _UNICODE)

add_subdirectory(src)
