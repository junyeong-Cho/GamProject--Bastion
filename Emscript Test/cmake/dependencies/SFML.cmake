# SFML.cmake
include(FetchContent)

set(GAM250_SFML_VERSION "2.5.1")  # Set required SFML version

if (NOT WIN32 AND NOT EMSCRIPTEN)
    find_package(SFML ${GAM250_SFML_VERSION} COMPONENTS graphics window system network audio REQUIRED)
    if(NOT SFML_FOUND)
        message(FATAL_ERROR "SFML not found")
    endif()
elseif(EMSCRIPTEN)
    message(FATAL_ERROR "SFML is not natively supported with Emscripten.")
else()  # Windows path
    FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.1
    )
    FetchContent_GetProperties(sfml)
    if(NOT sfml_POPULATED)
        FetchContent_Populate(sfml)
        set(SFML_BUILD_AUDIO ON CACHE BOOL "" FORCE)
        add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})

        # Define a custom target to copy openal32.dll to the build directory
        add_custom_target(copy_openal32_dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${sfml_SOURCE_DIR}/extlibs/bin/x64/openal32.dll
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/openal32.dll
            COMMENT "Copying openal32.dll to executable directory"
        )
    endif()
endif()

# Define GAM250_sfml interface library
add_library(GAM250_sfml INTERFACE)
target_link_libraries(GAM250_sfml INTERFACE sfml-graphics sfml-audio sfml-window sfml-system sfml-network)
target_include_directories(GAM250_sfml INTERFACE ${sfml_SOURCE_DIR}/include)
