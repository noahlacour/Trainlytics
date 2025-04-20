#pragma once
#include "models/WorkoutLog.h"
#include <string>

/**
 * @class WorkoutLogSerializer.
 * @brief A utility class to deserialize/serialize WorkoutLog's to/from JSON files.
 */
class WorkoutLogSerializer
{
public:
    /**
     * @brief Serializes and saves a WorkoutLog to a JSON file.
     * @param log The log to serialize.
     */
    static bool saveToFile(const WorkoutLog& log);

      /**
     * @brief finds and converts a JSON file to a WorkoutLog.
     * @param filename The file path where the file to load is located.
     */
    static WorkoutLog loadFromFile(const std::string& filename);
};