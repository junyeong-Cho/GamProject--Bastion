set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SOURCE_CODE

    assets/Path.hpp assets/Path.cpp
    assets/Reloader.hpp assets/Reloader.cpp

    Component/Diamond.h
    Component/GameSpeed.h
    Component/Gold.h
    Component/Map.h
    Component/Time.h
    Component/Wave.h   Component/Wave.cpp
    

    opengl/GL.hpp opengl/GL.cpp
    opengl/GLHandle.hpp
    opengl/GLIndexBuffer.hpp opengl/GLIndexBuffer.cpp
    opengl/GLShader.hpp opengl/GLShader.cpp
    opengl/GLTexture.hpp opengl/GLTexture.cpp
    opengl/GLVertexArray.hpp opengl/GLVertexArray.cpp
    opengl/GLVertexBuffer.hpp opengl/GLVertexBuffer.cpp
    opengl/GLFrameBuffer.hpp opengl/GLFrameBuffer.cpp

    environment/Environment.hpp
    environment/Input.hpp
    environment/OpenGL.hpp

    util/FPS.hpp
    util/Timer.hpp
    util/WatchFiles.hpp util/WatchFiles.cpp
    util/Random.hpp util/Random.cpp


    Engine/Animation.h          Engine/Animation.cpp
    Engine/Audio.h              Engine/Audio.cpp
    Engine/Camera.h	      Engine/Camer.cpp
    Engine/Collision.h          Engine/Collision.cpp
    Engine/Component.h
    Engine/ComponentManager.h
    Engine/Constants.h
    Engine/Drawing.h            Engine/Drawing.cpp
    Engine/DrawShape.h          Engine/DrawShape.cpp
    Engine/Engine.h             Engine/Engine.cpp
    Engine/Font.h               Engine/Font.cpp
    Engine/GameObject.h         Engine/GameObject.cpp
    Engine/GameObjectManager.h  Engine/GameObjectManager.cpp
    Engine/Image2D.h            Engine/Image2D.cpp
    Engine/GameState.h
    Engine/GameStateManager.h   Engine/GameStateManager.cpp
    Engine/IfWantShader.h
    Engine/ImGuiHelper.h        Engine/ImGuiHelper.cpp
    Engine/Input.h              Engine/Input.cpp
    Engine/IProgram.h
    Engine/Logger.h             Engine/Logger.cpp
    Engine/Matrix.h             Engine/Matrix.cpp
    Engine/MergeCollision.h     Engine/MergeCollision.cpp
    Engine/Mouse.h              Engine/Mouse.cpp
    Engine/Normalization.h      Engine/Normalization.cpp
    Engine/not_null.h
    Engine/OriginPosition.h
    Engine/owner.h
    Engine/Particle.h           Engine/Particle.cpp
    Engine/Rect.h
    Engine/ShowCollision.h      Engine/ShowCollision.cpp
    Engine/Sprite.h             Engine/Sprite.cpp
    Engine/Texture.h            Engine/Texture.cpp
    Engine/TextureManager.h     Engine/TextureManager.cpp
    Engine/Vec2.h               Engine/Vec2.cpp
    Engine/Window.h             Engine/Window.cpp


    Game/Components/Gold.h             Game/Components/Gold.cpp
    Game/Components/Life.h             Game/Components/Life.cpp


    Game/Modes/Game.h                  Game/Modes/Game.cpp
    Game/Modes/HowToPlay.h             Game/Modes/HowToPlay.cpp
    Game/Modes/Lose.h                  Game/Modes/Lose.cpp
    Game/Modes/MainMenu.h              Game/Modes/MainMenu.cpp
    Game/Modes/Store.h                 Game/Modes/Store.cpp
    Game/Modes/Tutorial.h              Game/Modes/Tutorial.cpp
    Game/Modes/Win.h                   Game/Modes/Win.cpp


    Game/Objects/Button.h               Game/Objects/Button.cpp

    Game/Objects/Monsters/Monster.h     Game/Objects/Monsters/Monster.cpp

    Game/Objects/Units/MagicUnit.h      Game/Objects/Units/MagicUnit.cpp
    Game/Objects/Units/MeleeUnit.h      Game/Objects/Units/MeleeUnit.cpp
    Game/Objects/Units/RangedUnit.h     Game/Objects/Units/RangedUnit.cpp
    Game/Objects/Units/Sniper.h         Game/Objects/Units/Sniper.cpp
    Game/Objects/Units/Spear.h          Game/Objects/Units/Spear.cpp
    Game/Objects/Units/Transform.h      Game/Objects/Units/Transform.cpp
    Game/Objects/Units/Unit.h           Game/Objects/Units/Unit.cpp


    Game/Fonts.h
    Game/GameObjectTypes.h
    Game/Mode1.h                       Game/Mode1.cpp
    Game/Mode2.h                       Game/Mode2.cpp
    Game/Particles.h  
    Game/Splash.h                      Game/Splash.cpp
    Game/States.h


    
    


    main.cpp
)

set(GAM250_EXODIA_LINK_OPTIONS "")

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    # https://emscripten.org/docs/tools_reference/settings_reference.html
    # ASSERTIONS=1                  - we want asserts to work
    # WASM=1                        - we want web assembly generated rather than just javascript
    # DISABLE_EXCEPTION_CATCHING=0  - we are using exceptions so let's not disable them
    # ALLOW_MEMORY_GROWTH=1         - we don't know exactly how much heap space we'll need so allow it to grow
    # EXIT_RUNTIME=1                - have exiting actually stop the program
    # SINGLE_FILE=1                 - generate everything into one html file
    # --embed-file                  - we need to tell it what files we will be reading at runtime. We are mapping the assets folder to the root folder
    # --use-preload-cache           - help with faster reloads : https://emscripten.org/docs/compiling/Deploying-Pages.html#providing-a-quick-second-time-load
    # -lembind                      - to call c++ from javascript https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
    # --shell-file                  - to customize the webpage https://emscripten.org/docs/compiling/Deploying-Pages.html#build-files-and-custom-shell
    set(GAM250_EXODIA_LINK_OPTIONS 
        -sASSERTIONS=1 
        -sWASM=1 
        -sNO_DISABLE_EXCEPTION_CATCHING 
        -sALLOW_MEMORY_GROWTH=1 
        -sEXIT_RUNTIME=1 
        -sSINGLE_FILE=1 
        --embed-file ${CMAKE_SOURCE_DIR}/assets@/assets
        --use-preload-cache
        -lembind
        $<$<CONFIG:Release>:--shell-file ${CMAKE_SOURCE_DIR}/app_resources/web/index_shell.html>
    )
endif()

add_executable(GAM250_Exodia ${SOURCE_CODE})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_CODE})

target_link_libraries(GAM250_Exodia PRIVATE project_options dependencies)
target_include_directories(GAM250_Exodia PRIVATE .)
target_compile_definitions(GAM250_Exodia PRIVATE $<$<NOT:$<CONFIG:Release>>:DEVELOPER_VERSION>)
target_link_options(GAM250_Exodia PRIVATE ${GAM250_EXODIA_LINK_OPTIONS})

add_custom_command(
    TARGET GAM250_Exodia POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:GAM250_Exodia>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/external $<TARGET_FILE_DIR:GAM250_Exodia>/
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets ${CMAKE_SOURCE_DIR}/build/source/assets
    
)


install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} DESTINATION ${CMAKE_BINARY_DIR}/install)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/install)

