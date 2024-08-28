#include "ErrorsMessageMaker.hpp"

std::string ErrorsMessage::Generate::unexpectedLex(const ttype& foundlex, const ttype& ex)
{
    // TODO
    std::string er_str = "expected ";
    er_str += tempatesForErrors[ex];
    er_str += " but found ";
    er_str += tempatesForErrors[foundlex];
    return er_str;
}

std::string ErrorsMessage::Generate::unexpectedLex(const ttype& foundlex, const std::set<ttype>& exlist)
{
    static constexpr char enter[] = "\n";
    std::string er_str = "Probably, expected one of this lexems: ";

    std::for_each(exlist.begin(), exlist.end(),
        [&](const ttype& i)
        {
            er_str += enter;
            er_str += tempatesForErrors[i];
        });
    er_str += "\nbut found ";
    er_str += tempatesForErrors[foundlex];

    return er_str;
}

std::string ErrorsMessage::Generate::inconsistency_of_types()
{
    return "inconsistency_of_types";
}