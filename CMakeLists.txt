cmake_minimum_required(VERSION 3.10)
project(trainlytics)

set(CMAKE_CXX_STANDARD 17)

# Add all source files here
add_executable(trainlytics
    src/main.cpp

    # Model sources
    src/models/Exercise.cpp
    src/models/Routine.cpp

    # Utils
    src/utils/RoutineSerializer.cpp
    src/utils/WorkoutLogSerializer.cpp
    src/utils/DateTimeUtils.cpp
)

# JSON library (assumes installed with pacman or vcpkg)
find_package(nlohmann_json REQUIRED)
target_link_libraries(trainlytics PRIVATE nlohmann_json::nlohmann_json)

# Include our header directory
target_include_directories(trainlytics PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Pass project root as a macro to source
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
