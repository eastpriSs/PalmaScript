#pragma once
#include "Lexem.hpp"

namespace Token
{
    enum class ttype {
        lnone, lasg, lname, lnum, lfnum,
        lconst, lint, lif, lthen, lelse,
        ldot, lcomma, lcolon, lsemi,
        llpar, lrpar, lout_fun, loutln_fun, 
        leof, lunknown, lequal, lplus, lminus
    };

    class Token
    {
    public:
        Token() : type(ttype::lunknown) {}

        Token(char c, ttype t)
            : type(t)
        {
            lex.strview += c;
        }

        Token(std::string w, ttype t)
            : type(t)
        {
            lex.strview = w;
        }

        Token(std::string&& w, ttype t)
            : type(t)
        {
            lex.strview = w;
        }

        Lexem lex = {};
        ttype type = ttype::leof;
    };
}
