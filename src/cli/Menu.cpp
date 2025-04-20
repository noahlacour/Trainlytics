#include "cli/Menu.h"
#include "models/Routine.h"
#include "models/WorkoutLog.h"
#include "utils/RoutineSerializer.h"
#include "utils/WorkoutLogSerializer.h"
#include "utils/DateTimeUtils.h"

#include <iostream>
#include <filesystem>
#include <limits>

namespace fs = std::filesystem;

namespace CLI
{
    /**
     * @brief Lists all saved Routines to command line.
     * @param directory The directory to search for valid JSON files.
     */
    void listRoutines(const std::string& directory)
    {
        std::cout << "\nAvailable Routines:\n";
        int index = 1;
        // Index through all valid sub-directories & files of directory.
        for(const auto& entry : fs::directory_iterator(directory))
        {
            // Only display if file found is of JSON type.
            if (entry.path().extension() == ".json")
            {
                std::cout << " [" << index++ << "] " << entry.path().stem().string() << "\n";
            }
        }
    }

    /**
     * @brief Allows user to select a routine to load.
     * @param directory The directory where the Routine JSON file is located.
     */
    std::string selectRoutine(const std::string& directory)
    {
        // Index through all valid sub-directories & files of directory.
        std::vector<std::string> files;
        for(const auto& entry : fs::directory_iterator(directory))
        {
            // Only add to list for potential selection if found file is of JSON type.
            if(entry.path().extension() == ".json")
            {
                files.push_back(entry.path().filename().string());
            }
        }


        if (files.empty())
        {
            // if not files are found alert user and return.
            std::cout << "No routines found.\n";
            return "";
        }

        // Allow user to select a Routine by inputing the number corresponding to wanted listed Routine.
        int choice = -1;
        while (choice < 1 || choice > static_cast<int>(files.size()))
        {
            std::cout << "\nSelect a routine (1-" << files.size() << "): ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        return files[choice - 1];
    }

    /**
     * @brief Allows user to log: reps, sets, and notes for Exercises in a given Routine.
     * @param routine The Routine in which the logs belong.
     */
    void logRoutine(const Routine& routine)
    {
        WorkoutLog log;
        log.routineName = routine.getName();
        log.date = getCurrentDate();

        // Alert user that the Routine is being logged, and parse Exercises in Routine
        std::cout << "\nLogging for routine: " << routine.getName() << "\n";
        for(const auto& entry : routine.getExercises())
        {
            std::vector<int> reps;
            std::vector<float> weights;
            std::cout << "\n" << entry.exercise.name << " (" << entry.plannedSets << " sets:\n";

            // Let user input from CLI their specific reps and weights for each set.
            for(int i = 0; i < entry.plannedSets; ++i)
            {
                int rep;
                float weight;
                std::cout << " Set " << (i + 1) << " - Reps: ";
                std::cin >> rep;
                std::cout << " Set " << (i + 1) << " - Weight (lbs): ";
                std::cin >> weight;

                reps.push_back(rep);
                weights.push_back(weight);
            }

            // Allow user to input notes for Exercises completed during this log. 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std:: string notes;
            std::cout << "Notes: ";
            std::getline(std::cin, notes);

            log.exercises.push_back({entry.exercise, reps, weights, notes});
        }

        // Now serialize and save log to a JSON file.
        WorkoutLogSerializer::saveToFile(log);
        std::cout << "\n Workout saved for " << log.date << "\n";
    }

    /**
     * @brief Allows a user to create a new Routine from the CLI.
     */
    void createRoutine()
    {
        // Create the Routines directory location and prompt user for Routine name.
        std::string routineDir = std::string(PROJECT_SOURCE_DIR) + "/data/routines";
        std::string name;
        std::cout << "\nEnter a name for the new routine: ";
        std::getline(std::cin, name);

        Routine routine(name);
        bool adding = true;

        // Allow the user to add Exercises, sets, and reps to Routine while adding is true.
        while (adding)
        {
            std::string exName, muscleGroup, equipment;
            int sets, reps;

            std::cout << "\nExercise name: ";
            std::getline(std::cin, exName);
            std::cout << "Muscle group: ";
            std::getline(std::cin, muscleGroup);
            std::cout << "Equipment: ";
            std::getline(std::cin, equipment);

            std::cout << "Planned sets: ";
            std::cin >> sets;
            std::cout << "Planed Reps per set: ";
            std::cin >> reps;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            routine.addExercise(Exercise(exName, muscleGroup, equipment), sets, reps);

            std::string cont;
            std::cout << "\nAdd another exercie? (y/n): ";
            std::getline(std::cin, cont);
            adding = (cont == "y" || cont == "Y");
        }

        // Initalize JSON file.
        std::string filename = name;
        std::replace(filename.begin(), filename.end(), ' ', '_');
        filename += ".json";

        // Save new Routine to JSON file.
        RoutineSerializer::saveToFile(routine, routineDir + "/" + filename);
        std::cout << "\n Routine '" << name << "' saved as " << filename << '\n';
    }

    void run()
    {
        // Load saved Routines.
        std::string routineDir = std::string(PROJECT_SOURCE_DIR) + "/data/routines";

        // if no Routines sub-directory exists, create it.
        if(!fs::exists(routineDir))
        {
            fs::create_directories(routineDir);
        }

        // Create inital CLI startup graphics.
        std::cout << R"(
            _______  ______    _______  ___   __    _  ___      __   __  _______  ___   _______  _______    
           |       ||    _ |  |   _   ||   | |  |  | ||   |    |  | |  ||       ||   | |       ||       |   
           |_     _||   | ||  |  |_|  ||   | |   |_| ||   |    |  |_|  ||_     _||   | |       ||  _____|   
             |   |  |   |_||_ |       ||   | |       ||   |    |       |  |   |  |   | |       || |_____    
             |   |  |    __  ||       ||   | |  _    ||   |___ |_     _|  |   |  |   | |      _||_____  |   
             |   |  |   |  | ||   _   ||   | | | |   ||       |  |   |    |   |  |   | |     |_  _____| |   
             |___|  |___|  |_||__| |__||___| |_|  |__||_______|  |___|    |___|  |___| |_______||_______|   

            
            1. Create new routine
            2. Log a workout
            3. Exit
              )" << "\n\n";

        std::cout << "\nSelect an option: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Handle User CLI traversal.
        switch(choice)
        {
            case 1:
            {
                createRoutine();
                break;
            }
            case 2:
            {
                listRoutines(routineDir);
                std::string filename = selectRoutine(routineDir);
                if(!filename.empty())
                {
                    Routine routine = RoutineSerializer::loadFromFile(filename);
                    logRoutine(routine);
                }
                break;
            }
            case 3:
            {
                std::cout << "Goodbye!\n";
                return;
            }
            default:
            {
                std::cout << "Invalid option.\n";
            }
        }
    }
}

void logRoutine(const Routine& routine)
{
    
}