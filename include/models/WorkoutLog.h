#pragma once
#include "ExerciseEntry.h"
#include <string>
#include <vector>

struct WorkoutLog
{
    std::string routineName;
    std::string date;

    struct LoggedExercise
    {
        Exercise exercise;
        std::vector<int> repsPerSet;
        std::string notes;
    };

    std::vector<LoggedExercise> exercises;
};

#include <nlohmann/json.hpp>
using json = nlohmann::json;

inline void to_json(json& j, const WorkoutLog::LoggedExercise& le)
{
    j = json{{"exercise", le.exercise}, {"repsPerSet", le.repsPerSet}, {"notes", le.notes}};
}

inline void from_json(const json& j, WorkoutLog::LoggedExercise& le)
{
    j.at("exercise").get_to(le.exercise);
    j.at("repsPerSet").get_to(le.repsPerSet);
    j.at("notes").get_to(le.notes);
}

inline void to_json(json& j, const WorkoutLog& wl)
{
    j = json{{"routineName", wl.routineName}, {"date", wl.date}, {"exercises", wl.exercises}};
}

inline void from_json(const json& j, WorkoutLog& wl)
{
    j.at("routineName").get_to(wl.routineName);
    j.at("date").get_to(wl.date);
    j.at("exercises").get_to(wl.exercises);
}