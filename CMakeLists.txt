cmake_minimum_required(VERSION 3.22)

project("Peter" LANGUAGES CXX C)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(
        "/utf-8" "/Zc:__cplusplus"
        "$<$<CONFIG:Release>:/Ox>"
    )
endif()

add_compile_definitions(UNICODE _UNICODE)

add_subdirectory(src)
