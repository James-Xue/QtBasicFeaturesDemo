#include "DemoMain.h"
#include <iostream>

bool InitApplication(int argc, char* argv[]);
void RunApplicationLoop();
void CleanupApplication();

int main(int argc, char* argv[])
{
    // Initialize the application
    if (false == InitApplication(argc, argv))
    {
        std::cerr << "Failed to initialize application."
                  << std::endl;
        return -1;
    }

    // Run the main application loop
    RunApplicationLoop();

    // Clean up and exit
    CleanupApplication();
    return 0;
}
