#pragma once

#include <cassert>
#include <fstream>
#include <sstream>
#include <string>


namespace Utils
{

[[nodiscard]] inline bool isFileExists(const std::string &filename)
{
    // stupid but idc
    std::ifstream fs(filename);
    return fs.is_open();
}

[[nodiscard]] inline std::string getFileContent(const std::string &filename)
{
    std::ifstream fs(filename);
    assert(fs.is_open());
    std::ostringstream sstr;
    sstr << fs.rdbuf();
    return sstr.str();
}


}
