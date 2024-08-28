
#pragma once
#include <string>
#include <fstream>

#include <iostream>

namespace lineDriver
{
    class LineDriver
    {    
    private:
        LineDriver() = default;
        std::string path;
    
    public:
        
        std::string getlineByIndx(const size_t&);            
        void setPath(const std::string&);

        static LineDriver& instance()
        {
            static LineDriver singelton = {};            
            return singelton;
        }

    };
}