// STL
//#include <iostream>

// Qt
//#include <QtCore/qchar.h>

// Self
#include "BioSenseGuiMain.h"
#include "CSVHelper.h"


int main(const int /*argc*/, char */*argv*/[])
{
    // 1. read CSV file
    Demo::CSVHelper csvHelper;
    csvHelper.ReadCSV(
        u8"C:/Users/52738/Documents/9_Tmp/20250116/20250116rcd84d7677220250116095027_p1.csv");

    // 2. return 0
    return 0;
}
