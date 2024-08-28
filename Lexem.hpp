#pragma once
#include <string>


struct Lexem
{
    std::string strview = {};
    size_t linepos = 0;
    size_t charpos = 0;
    size_t charPosInline = 0;
};