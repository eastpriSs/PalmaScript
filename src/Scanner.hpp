#pragma once
#include <unordered_map>
#include "CharDriver.hpp"
#include "Token.hpp"
#include "Lexem.hpp"

namespace KeyWords
{

    static std::unordered_map<std::string, Token::ttype> table =
    {
        {"const", Token::ttype::lconst},
        {"else",  Token::ttype::lelse},
        {"if",    Token::ttype::lif},
        {"out",   Token::ttype::lout_fun},
        {"outln",   Token::ttype::loutln_fun},
        {"then",  Token::ttype::lthen},
        {"int128",   Token::ttype::lint}
    };

}

class Scanner
{

    static constexpr char space = ' ';
    static constexpr char tab = '\t';
    static constexpr char enter = '\n';
    static constexpr char null_s = '\0';


private: Token::Token scanOneCharToken(char);
private: Token::Token scanTwoCharsToken(char, char);
//private: Token::Token scanWord(const std::string&);

public:
    Scanner() = delete;
    Scanner(const CharDriver::CharStream&);

    Token::Token scan();

private: const CharDriver::CharStream* chst;
};