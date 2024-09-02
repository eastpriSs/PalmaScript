#include "Parser.hpp"
#include "LogMaker.hpp"
#include "ErrorsMessageMaker.hpp"

// warning! function with side-effect
void Parser::checkLex(Token::ttype&& explx,
    const Token::Token& currtk)
{
    using namespace ErrorMessage;
    if (currtk.type != explx)
        expected(explx, butfound, currtk);
}

void Parser::ErrorMessage::expected(const Token::ttype& ex, void (*)(),
    const Token::Token& currtk)
{
    iLogMaker::logMaker::instance(&currtk).log(ErrorsMessage::Generate::unexpectedLex(currtk.type, ex));
}

void Parser::ErrorMessage::expectedOneOf(const std::set<Token::ttype>& exlist, void (*)(),
    const Token::Token& currtk)
{
    iLogMaker::logMaker::instance(&currtk).log(ErrorsMessage::Generate::unexpectedLex(currtk.type, exlist));
}

void Parser::ErrorMessage::expectedOneOf(std::set<Token::ttype>&& exlist, void (*)(),
    const Token::Token& currtk)
{
    iLogMaker::logMaker::instance(&currtk).log(ErrorsMessage::Generate::unexpectedLex(currtk.type, exlist));
}