#include <iostream>
#include "models/Routine.h"
#include "utils/RoutineSerializer.h"
#include "models/WorkoutLog.h"
#include "utils/WorkoutLogSerializer.h"
#include "utils/DateTimeUtils.h"


int main ()
{
    Routine r("Push Day");
    Exercise bench("Bench Press", "Chest", "Barbell");
    Exercise incline("Incline DB Press", "Chest", "Dumbbell");

    r.addExercise(bench, 4, 10);
    r.addExercise(incline, 3, 12);

    RoutineSerializer::saveToFile(r, "push_day.json");

    Routine loaded = RoutineSerializer::loadFromFile("push_day.json");
    std::cout << "=== " << loaded.getName() << " ===\n";
    for (const auto& e : loaded.getExercises()) 
    {
        std::cout << "- " << e.exercise.name << " | Planned: " << e.plannedSets << " sets of " << e.plannedReps << " reps\n";
    }

    WorkoutLog log;
    log.routineName = loaded.getName();
    log.date = getCurrentDate();

    log.exercises.push_back({bench, {12, 10, 9, 8}, "Felt strong, added pause at bottom"});
    log.exercises.push_back({incline, {12, 10, 10}, "Good chest activation"});

    WorkoutLogSerializer::saveToFile(log);

    std::cout << "\n Workout log saved for " << log.date << "\n";

    for (const auto& ex : log.exercises) 
    {
        std::cout << ex.exercise.name << ":\n";
        for (size_t i = 0; i < ex.repsPerSet.size(); ++i) 
        {
            std::cout << "  Set " << (i + 1) << ": " << ex.repsPerSet[i] << " reps\n";
        }
        std::cout << "  Notes: " << ex.notes << "\n";
    }

    return 0;
}