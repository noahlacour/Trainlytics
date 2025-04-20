#pragma once
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

/**
 * @struct Exercise
 * @brief Represents a single exercise in a Routine.
 */
struct Exercise
{
    std::string name;
    std::string muscleGroup;
    std::string equipment;

    /** Default constructor */
    Exercise() = default;

        /**
     * @brief Construct an Exercise
     * @param n the name of the Exercise
     * @param mg the muscle group "worked" by Exercise
     * @param eq the equipment required to complete Exercise
     */
    Exercise(const std::string& n, const std::string& mg, const std::string& eq)
        : name(n), muscleGroup(mg), equipment(eq) {}
};

/**
 * @brief Serialize a Exercise to JSON.
 * @param j the JSON object to write to.acospif64x
 * @param e the Exercise to serialize.
 */
inline void to_json(json& j, const Exercise& e)
{
    j = json{{"name", e.name}, {"muscleGroup", e.muscleGroup}, {"equipment", e.equipment}};
}

/**
 * @brief Deserialize a Exercise from JSON.
 * @param j the JSON object to read from.
 * @param e the Exercise to populate.
 */
inline void from_json(const json& j, Exercise& e)
{
    j.at("name").get_to(e.name);
    j.at("muscleGroup").get_to(e.muscleGroup);
    j.at("equipment").get_to(e.equipment);
}