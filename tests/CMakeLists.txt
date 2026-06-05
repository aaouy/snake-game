enable_testing()

add_executable(Tests)

target_sources(Tests
    PRIVATE
        unit/AudioManagerTests.cpp
        unit/FontManagerTests.cpp
        unit/FoodTests.cpp
        unit/SnakeTests.cpp
        unit/SpriteManagerTests.cpp
        integration/CollisionTests.cpp
        integration/SnakeEatingTests.cpp
    )

target_link_libraries(Tests PRIVATE 
    GTest::gtest_main
    SDL3::SDL3
    SDL3_mixer::SDL3_mixer
    SnakeLib
)

target_include_directories(Tests PRIVATE ../src/)

include(GoogleTest)
gtest_discover_tests(Tests)