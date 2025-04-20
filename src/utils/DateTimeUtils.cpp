#include "utils/DateTimeUtils.h"
#include <chrono>
#include <iomanip>
#include <sstream>

std::string getCurrentDate()
{
    //Use chrono to access system clock and set t_now
    auto now = std::chrono::system_clock::now();
    std::time_t t_now = std::chrono::system_clock::to_time_t(now);

    // Convert time to year Y-M-D notation and return
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t_now), "%Y-%m-%d");
    return oss.str();
}