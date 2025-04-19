#include "models/Routine.h"

Routine::Routine(const std::string& name) : name(name) {}

void Routine::addExercise(const Exercise& exercise, int sets, int reps)
{
    exercises.emplace_back(exercise, sets, reps);
}

std::string Routine::getName() const
{
    return name;
}

const std::vector<ExerciseEntry>& Routine::getExercises() const
{
    return(exercises);
}