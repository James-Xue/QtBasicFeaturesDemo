#pragma once

#include <iostream>
#include <vector>

namespace Demo
{
    // This class is responsible for reading and writing CSV files.
    class CSVHelper
    {
    // constructors and destructor
    public:
        CSVHelper();
        ~CSVHelper();


    // Core functionality
    public:
        // Reads a CSV file and returns a vector of strings.
        bool ReadCSV(const std::string &sFileFullPath);

        // Writes a vector of strings to a CSV file.
        //void WriteCSV(const std::string &sFileFullPath, const std::vector<std::string> &data);


    // Member variables that are not exposed to subclasses
    private:
        std::vector<std::string> m_vctString;
    };
}
