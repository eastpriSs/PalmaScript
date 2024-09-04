#include "Parser.hpp"
#include "LogMaker.hpp"
#include "ErrorsMessageMaker.hpp"

// warning! function with side-effect
void Parser::checkLex(Token::ttype&& explx,
    const Token::Token& currtk)
{
    using namespace Error;
    if (currtk.type != explx)
        expected(explx, butfound, currtk);
}

void Parser::Error::expected(const Token::ttype& ex, void (*)(),
    const Token::Token& currtk)
{
    iLogMaker::logMaker::instance(&currtk).log(new ErrorsMessage::Generate::UnexpectedLex(currtk.type, ex));
}

void Parser::Error::expectedOneOf(const std::set<Token::ttype>& exlist, void (*)(),
    const Token::Token& currtk)
{
    iLogMaker::logMaker::instance(&currtk).log(new ErrorsMessage::Generate::UnexpectedLex(currtk.type, exlist));
}

void Parser::Error::expectedOneOf(std::set<Token::ttype>&& exlist, void (*)(),
    const Token::Token& currtk)
{
    iLogMaker::logMaker::instance(&currtk).log(new ErrorsMessage::Generate::UnexpectedLex(currtk.type, exlist));
}

void Parser::Warning::replacingToken(const Token::Token& currtk)
{
    iLogMaker::logMaker::instance(&currtk).log(new WarningMessage::Generate::UnexpectedLex(currtk.type));
}