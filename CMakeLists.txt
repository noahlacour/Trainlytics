cmake_minimum_required(VERSION 3.10)
project(trainlytics)

set(CMAKE_CXX_STANDARD 17)

# JSON library (assumes installed with pacman or vcpkg)
find_package(nlohmann_json REQUIRED)

# --------------------------------------------------------------------------------
# Main executable: trainlytics
# --------------------------------------------------------------------------------
add_executable(trainlytics
    src/main.cpp

    # Model sources
    src/models/Exercise.cpp
    src/models/Routine.cpp
    src/cli/Menu.cpp

    # Utils
    src/utils/RoutineSerializer.cpp
    src/utils/WorkoutLogSerializer.cpp
    src/utils/DateTimeUtils.cpp
)

target_include_directories(trainlytics PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(trainlytics PRIVATE
    nlohmann_json::nlohmann_json
)

# Pass project root as a macro
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# --------------------------------------------------------------------------------
# Test executable: trainlytics_tests
# --------------------------------------------------------------------------------
add_executable(trainlytics_tests
    tests/test_routine.cpp

    # Add sources needed for testing
    src/models/Exercise.cpp
    src/models/Routine.cpp
)

target_include_directories(trainlytics_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/doctest
)

target_link_libraries(trainlytics_tests PRIVATE
    nlohmann_json::nlohmann_json
)
