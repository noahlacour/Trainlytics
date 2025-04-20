#pragma once
#include "models/Routine.h"
#include <string>

/**
 * @class RoutineSerializer.
 * @brief A utility class to deserialize/serialize routines to/from JSON files.
 */
class RoutineSerializer
{
public:

    /**
     * @brief Serializes and saves a routine to a JSON file.
     * @param routine The routine to save.
     * @param filepath The file path to store the saved file.
     */
    static bool saveToFile(const Routine& routine, const std::string& filePath);

    /**
     * @brief finds and converts a JSON file to a Routine.
     * @param filepath The file path where the file to load is located.
     */
    static Routine loadFromFile(const std::string& filePath);
};