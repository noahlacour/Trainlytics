#include "utils/WorkoutLogSerializer.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

static fs::path getDataPath(const std::string& filename, const std::string& subdir = "logs")
{
    fs::path basePath = fs::path(PROJECT_SOURCE_DIR);
    fs::path dataDir = basePath / "data" / subdir;

    if (!fs::exists(dataDir))
    {
        fs::create_directories(dataDir);
    }

    return dataDir / filename;

}

bool WorkoutLogSerializer::saveToFile(const WorkoutLog& log)
{
    std::string fileName = log.routineName + "_" + log.date + ".json";
    fs::path path = getDataPath(fileName, "logs");

    std::ofstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not save workout log: " << path << "\n";
        return false;
    }

    nlohmann::json j = log;
    file << j.dump(4);
    return true;
}

WorkoutLog WorkoutLogSerializer::loadFromFile(const std::string& filename)
{
    fs::path path = getDataPath(filename, "logs");

    std::ifstream file(path);
    if(!file.is_open())
    {
        throw std::runtime_error("Error: Cloud not open workout log: " + path.string());
    }

    nlohmann::json j;
    file >> j;
    return j.get<WorkoutLog>();
}