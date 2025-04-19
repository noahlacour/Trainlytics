#include "utils/DateTimeUtils.h"
#include <chrono>
#include <iomanip>
#include <sstream>

std::string getCurrentDate()
{
    auto now = std::chrono::system_clock::now();
    std::time_t t_now = std::chrono::system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t_now), "%Y-%m-%d");
    return oss.str();
}