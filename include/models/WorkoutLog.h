#pragma once
#include "ExerciseEntry.h"
#include <string>
#include <vector>

/**
 * @struct WorkoutLog
 * @brief A log of how much weight and reps were completed per Exercise of a Routine with notes.
 */
struct WorkoutLog
{
    std::string routineName;
    std::string date;

    struct LoggedExercise
    {
        Exercise exercise;
        std::vector<int> repsPerSet;
        std::vector<float> weightPerSet;
        std::string notes;
    };

    std::vector<LoggedExercise> exercises;
};

#include <nlohmann/json.hpp>
using json = nlohmann::json;

/**
 * @brief Serialize a LoggedExercise to JSON.
 * @param j the JSON object to write to.
 * @param le the LoggedExercise to serialize.
 */
inline void to_json(json& j, const WorkoutLog::LoggedExercise& le)
{
    j = json{{"exercise", le.exercise}, {"repsPerSet", le.repsPerSet}, {"weightPerSet", le.weightPerSet}, {"notes", le.notes}};
}

/**
 * @brief Deserialize a LoggedExercise from JSON.
 * @param j the JSON object to read from.
 * @param le the LoggedExercise to populate.
 */
inline void from_json(const json& j, WorkoutLog::LoggedExercise& le)
{
    j.at("exercise").get_to(le.exercise);
    j.at("repsPerSet").get_to(le.repsPerSet);
    j.at("weightPerSet").get_to(le.weightPerSet);
    j.at("notes").get_to(le.notes);
}

/**
 * @brief Serialize a WorkoutLog to JSON.
 * @param j the JSON object to write to.
 * @param wl the WorkoutLog to serialize.
 */
inline void to_json(json& j, const WorkoutLog& wl)
{
    j = json{{"routineName", wl.routineName}, {"date", wl.date}, {"exercises", wl.exercises}};
}


/**
 * @brief Deserialize a WorkoutLog from JSON.
 * @param j the JSON object to read from.
 * @param wl the WorkoutLog  to populate.
 */
inline void from_json(const json& j, WorkoutLog& wl)
{
    j.at("routineName").get_to(wl.routineName);
    j.at("date").get_to(wl.date);
    j.at("exercises").get_to(wl.exercises);
}