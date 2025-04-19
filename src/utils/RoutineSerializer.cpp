#include "utils/RoutineSerializer.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

static fs::path getProjectRootPath()
{
    return fs::path(PROJECT_SOURCE_DIR);
}

static fs::path getDataPath(const std::string& filename)
{
    fs::path dataDir = getProjectRootPath() / "data";

    if (!fs::exists(dataDir))
    {
        fs::create_directory(dataDir);
    }

    return dataDir / filename;
}

bool RoutineSerializer::saveToFile(const Routine& routine, const std::string& filePath)
{
    fs::path fullPath = getDataPath(filePath);
    std::ofstream file(fullPath);
    if(!file.is_open())
    {
        std::cerr << "Error: Could not open file: " << fullPath << std::endl;
        return false;
    }

    nlohmann::json j = routine;
    file << j.dump(4);
    file.close();
    return true;
}

Routine RoutineSerializer::loadFromFile(const std::string& filePath)
{
    fs::path fullPath = getDataPath(filePath);
    std::ifstream file(fullPath);
    if(!file.is_open())
    {
        throw std::runtime_error("Error: Could not open file: " + fullPath.string());
    }

    nlohmann::json j;
    file >> j;
    file.close();
    return j.get<Routine>();
}