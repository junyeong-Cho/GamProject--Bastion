include(FetchContent)

include(cmake/dependencies/OpenGL.cmake)    #defines target GAM250_opengl
include(cmake/dependencies/GLEW.cmake)      # defines target GAM250_glew
include(cmake/dependencies/SDL2.cmake)      # defines target GAM250_sdl2
include(cmake/dependencies/DearImGUI.cmake) # defines target imgui   ;  note DearImGUI.cmake depends on SDL2.cmake
include(cmake/dependencies/STB.cmake)       # defines target stb
include(cmake/dependencies/GSL.cmake)       # defines target gsl
include(cmake/dependencies/GLM.cmake)       # defines target GAM250_glm
include(cmake/dependencies/freetype.cmake)  # defines target freetype
include(cmake/dependencies/SFML.cmake)      # defines target GAM250_sfml

add_library(dependencies INTERFACE)

target_link_libraries(dependencies INTERFACE 
    GAM250_opengl
    GAM250_glew
    GAM250_sdl2
    imgui
    stb
    gsl
    GAM250_glm
    freetype
)


if(NOT EMSCRIPTEN)
    target_link_libraries(dependencies INTERFACE GAM250_sfml)
endif()
