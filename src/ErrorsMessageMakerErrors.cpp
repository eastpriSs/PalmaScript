#include "ErrorsMessageMaker.hpp"

ErrorsMessage::Generate::UnexpectedLex::UnexpectedLex(const ttype& foundlex, const ttype& ex)
{
    // TODO
    message = "expected ";
    message += tempatesForErrors[ex];
    message += " but found ";
    message += tempatesForErrors[foundlex];
}

ErrorsMessage::Generate::UnexpectedLex::UnexpectedLex(const ttype& foundlex, const std::set<ttype>& exlist)
{
    static constexpr char enter[] = "\n";
    message = "Probably, expected one of this lexems: ";

    std::for_each(exlist.begin(), exlist.end(),
        [&](const ttype& i)
        {
            message += enter;
            message += tempatesForErrors[i];
        });
    message += "\nbut found ";
    message += tempatesForErrors[foundlex];
}

inline std::string ErrorsMessage::Generate::UnexpectedLex::what() const { return message; }

ErrorsMessage::Generate::UndefinedVar::UndefinedVar(const std::string& id)
{
    idname = &id;
}

std::string ErrorsMessage::Generate::UndefinedVar::what() const
{
    std::string mes = "did not find ";
    mes += *idname;
    return mes;
}
