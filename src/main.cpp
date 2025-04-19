#include <iostream>
#include "models/Routine.h"
#include "utils/RoutineSerializer.h"
#include "models/WorkoutLog.h"
#include "utils/WorkoutLogSerializer.h"
#include "utils/DateTimeUtils.h"
#include "cli/Menu.h"


int main ()
{
    CLI::run();
    return 0;
}