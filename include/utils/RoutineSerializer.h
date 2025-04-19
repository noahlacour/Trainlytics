#pragma once
#include "models/Routine.h"
#include <string>

class RoutineSerializer
{
public:
    static bool saveToFile(const Routine& routine, const std::string& filePath);
    static Routine loadFromFile(const std::string& filePath);
};