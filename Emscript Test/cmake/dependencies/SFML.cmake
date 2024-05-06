include(FetchContent)

set(GAM250_SFML_VERSION "2.5.1")  # 필요한 SFML 버전 설정

if (NOT WIN32 AND NOT EMSCRIPTEN)
    find_package(SFML ${GAM250_SFML_VERSION} COMPONENTS graphics window system network audio REQUIRED)
    if(NOT SFML_FOUND)
        message(FATAL_ERROR "SFML not found")
    endif()
elseif(EMSCRIPTEN)
    message(FATAL_ERROR "SFML is not natively supported with Emscripten.")
else()  # Windows 경로
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
    endif()
endif()

# GAM250_sfml 인터페이스 라이브러리 정의
add_library(GAM250_sfml INTERFACE)
target_link_libraries(GAM250_sfml INTERFACE sfml-audio)
target_include_directories(GAM250_sfml INTERFACE ${sfml_SOURCE_DIR}/include)
