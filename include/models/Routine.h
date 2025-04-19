#pragma once
#include <string>
#include <vector>
#include "ExerciseEntry.h"
#include <nlohmann/json.hpp>

class Routine
{
public:
    Routine() = default;
    Routine(const std::string& name);

    void addExercise(const Exercise& exercise, int sets, int reps);
    std::string getName() const;
    const std::vector<ExerciseEntry>& getExercises() const;

private:
    std::string name;
    std::vector<ExerciseEntry> exercises;

    friend void to_json(json& j, const Routine& r);
    friend void from_json(const json& j, Routine& r);
};

inline void to_json(json& j, const Routine& r)
{
    j = json{{"name", r.name}, {"exercises", r.exercises}};
}

inline void from_json(const json& j, Routine& r)
{
    j.at("name").get_to(r.name);
    j.at("exercises").get_to(r.exercises);
}