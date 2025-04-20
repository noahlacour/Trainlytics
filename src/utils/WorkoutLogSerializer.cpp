#include "utils/WorkoutLogSerializer.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

/**
 * @brief Returns the full path to a file inside the data directory (creates it if needed).
 * @param filename Name of file to add to data sub-directory.
 * @param subdir Name of directory containing logs.
*/
static fs::path getDataPath(const std::string& filename, const std::string& subdir = "logs")
{
    fs::path basePath = fs::path(PROJECT_SOURCE_DIR);
    fs::path dataDir = basePath / "data" / subdir;

    // Confirm the path created exists
    if (!fs::exists(dataDir))
    {
        // If not create it
        fs::create_directories(dataDir);
    }

    // return the directory with the inputted file name appended
    return dataDir / filename;

}

bool WorkoutLogSerializer::saveToFile(const WorkoutLog& log)
{
    std::string fileName = log.routineName + "_" + log.date + ".json";
    fs::path path = getDataPath(fileName, "logs");

    // Check if filepath is valid
    std::ofstream file(path);
    if (!file.is_open())
    {
        // Flag error and return false
        std::cerr << "Error: Could not save workout log: " << path << "\n";
        return false;
    }

    // create a json file containing log and write to file
    nlohmann::json j = log;
    file << j.dump(4);
    return true;
}

WorkoutLog WorkoutLogSerializer::loadFromFile(const std::string& filename)
{
    fs::path path = getDataPath(filename, "logs");

    // Check if filepath is valid
    std::ifstream file(path);
    if(!file.is_open())
    {
        // Flag error
        throw std::runtime_error("Error: Cloud not open workout log: " + path.string());
    }

    // Create a log from the file contents
    nlohmann::json j;
    file >> j;
    return j.get<WorkoutLog>();
}