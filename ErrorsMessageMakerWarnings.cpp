#include "ErrorsMessageMaker.hpp"

std::string WarningMessage::Generate::unexpectedLex(const ttype& foundlex)
{
    std::string er_str = "Unexpected lexem ";
    er_str += tempatesForErrors[foundlex];
    er_str += " was replaced by zero value! Be careful total result can be changed.";
    return er_str;
}