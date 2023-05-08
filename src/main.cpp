#include "FileUtils.h"
#include "Parser.h"

#include <fstream>
#include <iostream>

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cout << "The source file is not provided\n";
        return 1;
    }

    std::string filename(argv[1]);

    if (!Utils::isFileExists(filename))
    {
        std::cout << "File '" << argv[1] << "' not found\n";
        return 1;
    }

    std::string file_content = Utils::getFileContent(filename);
    Parser parser(file_content);



    return 0;
}
