// ----------------------------------------------------------------------------
//  OgmaNeo
//  Copyright(c) 2016 Ogma Intelligent Systems Corp. All rights reserved.
//
//  This copy of OgmaNeo is licensed to you under the terms described
//  in the OGMANEO_LICENSE.md file included in this distribution.
// ----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input> <output> <tag>\n", argv[0]);
        return 1;
    }

    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2]);

    std::string stringTag(argv[3]);
    std::transform(stringTag.begin(), stringTag.end(), stringTag.begin(), ::toupper);

    if (inFile.is_open() && outFile.is_open())
    {
        // Copyright and header file preamble
        outFile << "// ----------------------------------------------------------------------------" << std::endl;
        outFile << "//  OgmaNeo" << std::endl;
        outFile << "//  Copyright(c) 2016 Ogma Intelligent Systems Corp. All rights reserved." << std::endl;
        outFile << "//" << std::endl;
        outFile << "//  This copy of OgmaNeo is licensed to you under the terms described" << std::endl;
        outFile << "//  in the OGMANEO_LICENSE.md file included in this distribution." << std::endl;
        outFile << "// ----------------------------------------------------------------------------" << std::endl;
        outFile << std::endl;
        outFile << "#pragma once" << std::endl;
        outFile << std::endl;
        outFile << "#if !defined(_" << stringTag.c_str() << "_OCL_HEADER)" << std::endl;
        outFile << "#define _" << stringTag.c_str() << "_OCL_HEADER" << std::endl;
        outFile << std::endl;
        outFile << "#include <string>" << std::endl;
        outFile << std::endl;

        outFile << "const std::string " << argv[3] << "_ocl[] = {" << std::endl;

        const char* ws = " \t\n\r\f\v";
        std::string line;
        while (std::getline(inFile, line))
        {
            // Strip certain trailing characters from the line
            line.erase(line.find_last_not_of(ws) + 1);

            // Output a string form of the line, including a trailing new-line and comma
            outFile << "\"" << line << "\\n\"," << std::endl;
        }

        outFile << "};" << std::endl;
        outFile << std::endl;
        outFile << "#endif" << std::endl;
    }
    else
    {
        if (!inFile.is_open())
            std::cerr << "Unable to open file - " << argv[1] << std::endl;
        if (!outFile.is_open())
            std::cerr << "Unable to open file - " << argv[2] << std::endl;

        return 1;
    }

    return 0;
}
