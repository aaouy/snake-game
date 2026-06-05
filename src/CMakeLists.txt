add_library(SnakeLib)

target_sources(SnakeLib
    PUBLIC
        AudioManager.cpp
        FontManager.cpp
        Food.cpp
        Game.cpp
        GameOverState.cpp
        Grid.cpp
        MenuState.cpp
        MenuState.hpp
        PausedState.cpp
        PlayingState.cpp
        Snake.cpp
        Specs.cpp
        SpriteManager.cpp
)   

add_executable(Snake)

target_sources(Snake
    PRIVATE
        main.cpp
)

target_link_libraries(SnakeLib PUBLIC
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
)

target_link_libraries(Snake PRIVATE SnakeLib)

target_compile_features(Snake PRIVATE cxx_std_17)

add_custom_command(TARGET Snake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Snake>/assets)