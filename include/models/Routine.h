#pragma once

#include <string>
#include <vector>
#include "ExerciseEntry.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;


/**
 * @class Routine.
 * @brief Represents a workout routine containing multiple exercises with planned sets and reps.
 */
class Routine
{
public:
    /** Default constructor */
    Routine() = default;

    /** 
     * @brief Construct a Routine with a given name.
     * @param name The name of the routine.
    */
    Routine(const std::string& name);

    /**
     * @brief Add an exercise to the routine.
     * @param exercise The exercise to add
     * @param sets The planned number of sets.
     * @param reps the planned number of reps per set.
     */
    void addExercise(const Exercise& exercise, int sets, int reps);

    /**
     * @brief Get the name of the routine.
     * @return The routine name.
     */
    std::string getName() const;

    /**
     * @brief Get the list of exercises in the routine.
     * @return A const reference to the list of exercises.
     */
    const std::vector<ExerciseEntry>& getExercises() const;

private:

    std::string name;
    std::vector<ExerciseEntry> exercises;

    // Allow JSON (de)serialization access to private members.
    friend void to_json(json& j, const Routine& r);
    friend void from_json(const json& j, Routine& r);
};

/**
 * @brief Serialize a Routine to JSON.
 * @param j the JSON object to write to.
 * @param r the Routine to serialize.
 */
inline void to_json(json& j, const Routine& r)
{
    j = json{{"name", r.name}, {"exercises", r.exercises}};
}

/**
 * @brief Deserialize a Routine from JSON.
 * @param j the JSON object to read from.
 * @param r the Routine to populate.
 */
inline void from_json(const json& j, Routine& r)
{
    j.at("name").get_to(r.name);
    j.at("exercises").get_to(r.exercises);
}