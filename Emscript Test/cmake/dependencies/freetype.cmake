# freetype.cmake
include(FetchContent)

# Specify the version and source repository of FreeType
FetchContent_Declare(
  freetype
  GIT_REPOSITORY https://github.com/freetype/freetype.git
  GIT_TAG        VER-2-13-2  # Adjust the tag based on your needs
)

# Make sure FreeType is available
FetchContent_GetProperties(freetype)
if(NOT freetype_POPULATED)
  FetchContent_Populate(freetype)
  add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})

  # Adjust include directories
  target_include_directories(freetype INTERFACE
    $<BUILD_INTERFACE:${freetype_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
endif()

# Alias for compatibility with find_package
add_library(Freetype::Freetype ALIAS freetype)
