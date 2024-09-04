#include "ErrorsMessageMaker.hpp"

WarningMessage::Generate::UnexpectedLex::UnexpectedLex(const ttype& foundlex)
{
    this->foundlex = &foundlex;
}

std::string WarningMessage::Generate::UnexpectedLex::what() const 
{
    std::string er_str = "Unexpected lexem ";
    er_str += tempatesForErrors[*foundlex];
    er_str += " was replaced by zero value! Be careful total result can be changed.";
    return er_str;
}
