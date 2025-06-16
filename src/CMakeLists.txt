set(CURRENT_TARGET_NAME "Peter")

set(SOURCES
    main.cpp
    resource.h
    resource.rc
)

add_executable(${CURRENT_TARGET_NAME} WIN32 ${SOURCES})

foreach(FILE IN LISTS SOURCES)
    get_filename_component(SOURCE_PATH "${FILE}" PATH)
    get_filename_component(EXT "${FILE}" EXT)
    string(REPLACE "/" "\\" SOURCE_PATH_GROUP "${SOURCE_PATH}")

    if(EXT STREQUAL ".cpp")
        source_group("Source Files\\${SOURCE_PATH_GROUP}" FILES "${FILE}")
    elseif(EXT STREQUAL ".h" OR EXT STREQUAL ".hpp")
        source_group("Header Files\\${SOURCE_PATH_GROUP}" FILES "${FILE}")
    elseif(EXT STREQUAL ".rc")
        source_group("Resource Files\\${SOURCE_PATH_GROUP}" FILES "${FILE}")
    else()
        source_group("Other\\${SOURCE_PATH_GROUP}" FILES "${FILE}")
    endif()
endforeach()

set_target_properties(${CURRENT_TARGET_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.output/$<CONFIG>/"
)

set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CURRENT_TARGET_NAME})
set_property(TARGET ${CURRENT_TARGET_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
