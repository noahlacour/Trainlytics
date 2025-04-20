#include "utils/RoutineSerializer.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

static fs::path getProjectRootPath()
{
    // Returns the root directory of the project as defined by CMake
    return fs::path(PROJECT_SOURCE_DIR);
}

/**
 * @brief Returns the full path to a file inside the data directory (creates it if needed) 
 * @param filename Name of file to add to data sub-directory
*/
static fs::path getDataPath(const std::string& filename)
{
    fs::path dataDir = getProjectRootPath() / "data";

    // Confirm the path created exists
    if (!fs::exists(dataDir))
    {
        // If not create it
        fs::create_directory(dataDir);
    }

    // return the directory with the inputted file name appended
    return dataDir / filename;
}

bool RoutineSerializer::saveToFile(const Routine& routine, const std::string& filePath)
{
    // Check if filepath is valid
    fs::path fullPath = getDataPath(filePath);
    std::ofstream file(fullPath);
    if(!file.is_open())
    {
        // Flag error and return false
        std::cerr << "Error: Could not open file: " << fullPath << std::endl;
        return false;
    }

    // create a json file containing routine and write to file
    nlohmann::json j = routine;
    file << j.dump(4);
    file.close();
    return true;
}

Routine RoutineSerializer::loadFromFile(const std::string& filePath)
{
    // Check if filepath is valid
    fs::path fullPath = getDataPath(filePath);
    std::ifstream file(fullPath);
    if(!file.is_open())
    {
        // Flag error
        throw std::runtime_error("Error: Could not open file: " + fullPath.string());
    }

    // Create a routine from the file contents
    nlohmann::json j;
    file >> j;
    file.close();
    return j.get<Routine>();
}