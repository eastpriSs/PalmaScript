#include "Scanner.hpp"

Scanner::Scanner(const CharDriver::CharStream& cs)
{
    chst = &cs;
}


Token::Token Scanner::scanOneCharToken(char c)
{
    // ?? hashmap
    switch (c)
    {
    case '=': return Token::Token('=', Token::ttype::lasg);
    case '.': return Token::Token('.', Token::ttype::ldot);
    case ':': return Token::Token(':', Token::ttype::lcolon);
    case ',': return Token::Token(',', Token::ttype::lcomma);
    case '(': return Token::Token('(', Token::ttype::llpar);
    case ')': return Token::Token(')', Token::ttype::lrpar);
    case '+': return Token::Token('+', Token::ttype::lplus);
    case '-': return Token::Token('-', Token::ttype::lminus);
    case '*': return Token::Token('*', Token::ttype::lmult);
    case '/': return Token::Token('/', Token::ttype::ldiv);
    }
    return Token::Token();
}

Token::Token Scanner::scanTwoCharsToken(char c1, char c2)
{
    switch (c1)
    {
    case '=':
        switch (c2)
        {
        case '=': return Token::Token(c1 + c2, Token::ttype::lequal);
        }
    }
    return Token::Token();
}


Token::Token Scanner::scan()
{
    using namespace KeyWords;
    using namespace std;

    static size_t lineindx = 0;
    static size_t charindx = 0;
    static size_t charPosInline = 0;

    Token::Token tkn;
    // whitespaces
    while (std::isspace(*chst->startChar)
        || *chst->startChar == '\n')
    {
        if (*chst->startChar == '\n') {
            lineindx += 1;
            charPosInline = 0;
        }
        else {
            ++charPosInline;
        }
        *chst->startChar++; // old code throw warning!
        ++charindx;
    }

    // eof
    if (*chst->startChar == '\0') return Token::Token('\0', Token::ttype::leof);

    Lexem lexem;
    vector<char>::iterator beginLex = chst->startChar;
    vector<char>::iterator forward = chst->startChar + 1;

    tkn = scanTwoCharsToken(*beginLex, *forward);
    if (tkn.type == Token::ttype::lunknown)
    {
        tkn = scanOneCharToken(*beginLex);
    }

    if (tkn.type == Token::ttype::lminus) 
    {
        if (std::isdigit(*forward))
        {
            while (std::isdigit(*forward)) ++forward;
            tkn.type = Token::ttype::lnum;
        }
    }

    if (tkn.type == Token::ttype::lunknown)
    {
        // scan id/kw
        if (std::isalpha(*beginLex))
        {
            while (std::isalpha(*forward)
                || std::isdigit(*forward))
                forward++;

            lexem.strview = std::string(beginLex, forward);

            if (table.find(lexem.strview) != table.end())
                tkn.type = table.at(lexem.strview);
            else
                tkn.type = Token::ttype::lname;
        }
        // scan num
        else if (std::isdigit(*beginLex))
        {
            while (std::isdigit(*forward)) ++forward;
            tkn.type = Token::ttype::lnum;
        }
    }

    lexem.charPosInline = charPosInline;
    lexem.linepos = lineindx;
    lexem.charpos = charindx;
    lexem.strview = std::string(beginLex, forward);
    tkn.lex = lexem;

    //std::cout << '\n' << lexem.strview << '_' << static_cast<int>(tkn.type);

    chst->startChar = forward;
    charPosInline += forward - beginLex;
    return tkn;
}