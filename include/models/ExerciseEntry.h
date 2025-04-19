#pragma once
#include <string>
#include "Exercise.h"

struct ExerciseEntry
{
    Exercise exercise;
    int plannedSets;
    int plannedReps;

    ExerciseEntry() = default;
    ExerciseEntry(const Exercise& ex, int sets, int reps)
        : exercise(ex), plannedSets(sets), plannedReps(reps) {}

};

inline void to_json(json& j, const ExerciseEntry& e)
{
    j = json{{"exercise", e.exercise}, {"plannedSets", e.plannedSets}, {"plannedReps", e.plannedReps}};
}

inline void from_json(const json& j, ExerciseEntry& e)
{
    j.at("exercise").get_to(e.exercise);
    j.at("plannedSets").get_to(e.plannedSets);
    j.at("plannedReps").get_to(e.plannedReps);
}