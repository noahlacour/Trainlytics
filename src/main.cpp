#include "cli/Menu.h"
#include "utils/RoutineSerializer.h"
#include "cli/Menu.h"
#include <iostream>


int main(int argc, char* argv[])
{
    if(argc == 3 && std::string(argv[1]) == "--log")
    {
        std::string routineFile = argv[2];
        try
        {
            Routine routine = RoutineSerializer::loadFromFile(routineFile);
            CLI::logRoutine(routine);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Fialed to load routine: " << e.what() << "\n";
            return 1;
        }

        return 0;
    }
}