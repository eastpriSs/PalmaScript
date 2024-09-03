#pragma once 
#include "Token.hpp"

namespace iLogMaker
{

    class logMaker
    {
    private:    
        logMaker() = default;
        const Token::Token* currTkn = nullptr;

    public:

        void log(std::string) const;
        
        static logMaker& instance(const Token::Token* crtkn)
        {
            static logMaker singelton = {};
            singelton.currTkn = crtkn;
            return singelton;
        }
    };

}