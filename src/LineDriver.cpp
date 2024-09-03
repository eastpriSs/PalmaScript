#include "LineDriver.hpp"

std::string lineDriver::LineDriver::getlineByIndx(const size_t& indx)
{
    using std::ifstream;
    ifstream f(path); // TODO can't open

    std::string line;
    size_t i = 0;

    while (getline(f, line)) if (i++ == indx) break;
    f.close();
    return line;
}

void lineDriver::LineDriver::setPath(const std::string& p)
{
    path = p;
}