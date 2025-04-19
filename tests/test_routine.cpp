#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "models/Routine.h"
#include "models/WorkoutLog.h"

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