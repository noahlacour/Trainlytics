#pragma once
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Exercise
{
    std::string name;
    std::string muscleGroup;
    std::string equipment;

    Exercise() = default;
    Exercise(const std::string& n, const std::string& mg, const std::string& eq)
        : name(n), muscleGroup(mg), equipment(eq) {}
};

inline void to_json(json& j, const Exercise& e)
{
    j = json{{"name", e.name}, {"muscleGroup", e.muscleGroup}, {"equipment", e.equipment}};
}

inline void from_json(const json& j, Exercise& e)
{
    j.at("name").get_to(e.name);
    j.at("muscleGroup").get_to(e.muscleGroup);
    j.at("equipment").get_to(e.equipment);
}