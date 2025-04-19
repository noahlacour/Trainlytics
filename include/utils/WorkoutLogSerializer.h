#pragma once
#include "models/WorkoutLog.h"
#include <string>

class WorkoutLogSerializer
{
public:
    static bool saveToFile(const WorkoutLog& log);
    static WorkoutLog loadFromFile(const std::string& filename);
};