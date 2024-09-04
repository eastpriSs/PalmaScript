#pragma once 
#include "Token.hpp"
#include "ErrorsMessageMaker.hpp"

namespace iLogMaker
{

    class logMaker
    {
    private:    
        logMaker() = default;
        const Token::Token* currTkn = nullptr;

    public:

        void log(ErrorsMessage::Generate::Error*) const;
        void log(WarningMessage::Generate::Warning*) const;
        
        static logMaker& instance(const Token::Token* crtkn)
        {
            static logMaker singelton = {};
            singelton.currTkn = crtkn;
            return singelton;
        }
    };

}