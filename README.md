# README for the Demo Project

# Demo Project

This project is a simple demonstration application built using C++. It serves as an example of how to structure a C++ project with a main application loop and basic initialization and cleanup procedures.

## Project Structure

```
00_QtBasicFeaturesDemo
├── src
│   ├── Demo
│   │   ├── DemoMain.cpp    # Contains the main function and application logic
│   │   └── DemoMain.h      # Header file for function and class declarations
├── CMakeLists.txt          # CMake configuration file for building the project
└── README.md               # Documentation for the project
```

## Building the Project

To build the project, you need to have CMake installed. Follow these steps:

1. Open a terminal and navigate to the root directory of the project.
2. Create a build directory:
   ```
   mkdir build
   cd build
   ```
3. Run CMake to configure the project:
   ```
   cmake ..
   ```
4. Build the project:
   ```
   cmake --build .
   ```

## Running the Application

After building the project, you can run the application by executing the generated executable located in the build directory.

## License

This project is open-source and available under the MIT License.