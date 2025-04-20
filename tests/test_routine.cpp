#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "models/Routine.h"
#include "utils/RoutineSerializer.h"
#include "models/WorkoutLog.h"
#include "cli/Menu.h"

#include <cstdio>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

TEST_CASE("Routine creation and exercise adding")
{
    Routine r("Push Day");
    Exercise bench("Bench Press", "Chest", "Barbell");

    r.addExercise(bench, 4, 10);
    auto ex = r.getExercises();

    CHECK(r.getName() == "Push Day");
    CHECK(ex.size() == 1);
    CHECK(ex[0].plannedReps == 10);
    CHECK(ex[0].plannedSets == 4);
    CHECK(ex[0].exercise.name == "Bench Press");
}

TEST_CASE("Workout log reps and weights match")
{
    WorkoutLog log;
    log.routineName = "Push Day";
    log.date = "2025-04-18";

    log.exercises.push_back({Exercise("Bench", "Chest", "Barbell"), {10 ,8, 6},{135.0f, 145.0f, 155.0f}, "Felt Heavy"});

    CHECK(log.exercises[0].repsPerSet.size() == log.exercises[0].weightPerSet.size());
}

TEST_CASE("Create test routine for CLI logging")
{
    const std::string testRoutineFile = "CLI_Test_Routine.json";

    Routine r("CLI Test Routine");
    r.addExercise(Exercise("Test Exercise", "Test Muscle", "Bodyweight"), 2, 10);

    bool saved = RoutineSerializer::saveToFile(r, testRoutineFile);
    CHECK(saved);
    CHECK(std::filesystem::exists(fs::path(PROJECT_SOURCE_DIR) / "data" / "routines" / testRoutineFile));
}

TEST_CASE("CLI logging into test routine")
{
    const std::string testRoutineFile = "CLI_Test_Routine.json";
    fs::path fullRoutinePath = fs::path(PROJECT_SOURCE_DIR) / "data" / "routines" / testRoutineFile; 
    CHECK(std::filesystem::exists(fullRoutinePath));

    const char* cmd = "./trainlytics --log CLI_Test_Routine.json";
    FILE* pipe = popen(cmd, "w");
    REQUIRE(pipe != nullptr);

    const char* input = "10\n100\n8\n95\nCLI test notes\n";
    fwrite(input, sizeof(char), strlen(input), pipe);
    pclose(pipe);

    // Find matching log file
    std::filesystem::path logsDir = std::filesystem::path(PROJECT_SOURCE_DIR) / "data" / "logs";
    bool logFound = false;

    for(const auto& entry : std::filesystem::directory_iterator(logsDir))
    {
        if(entry.path().filename().string().rfind("CLI Test Routine", 0) == 0)
        {
            logFound = true;
            std::filesystem::remove(entry.path());
        }
    }

    CHECK(logFound);

    // Clean up routine
    std::filesystem::remove(fullRoutinePath);
}