#pragma once
#include <string>
#include "Exercise.h"

/**
 * @struct ExerciseEntry
 * @brief Represents a single exercise entry in a Routine.
 */
struct ExerciseEntry
{
    Exercise exercise;
    int plannedSets;
    int plannedReps;

    /** Default constructor */
    ExerciseEntry() = default;

    /**
     * @brief Construct an ExerciseEntry
     * @param ex the exercise to add
     * @param sets the amount of planned sets for this exercise
     * @param reps the amount of planned reps per set for this exercise
     */
    ExerciseEntry(const Exercise& ex, int sets, int reps)
        : exercise(ex), plannedSets(sets), plannedReps(reps) {}

};

/**
 * @brief Serialize a Routine to JSON.
 * @param j the JSON object to write to.
 * @param r the Routine to serialize.
 */
inline void to_json(json& j, const ExerciseEntry& e)
{
    j = json{{"exercise", e.exercise}, {"plannedSets", e.plannedSets}, {"plannedReps", e.plannedReps}};
}

/**
 * @brief Deserialize a Routine from JSON.
 * @param j the JSON object to read from.
 * @param r the Routine to populate.
 */
inline void from_json(const json& j, ExerciseEntry& e)
{
    j.at("exercise").get_to(e.exercise);
    j.at("plannedSets").get_to(e.plannedSets);
    j.at("plannedReps").get_to(e.plannedReps);
}