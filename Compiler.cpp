#include "Compiler.hpp"
#include "Scanner.hpp"
#include "Parser.hpp"
#include "Interpretator.hpp"

void Compiler::Compile(const CharDriver::CharStream& chs)
{
    Scanner scnr(chs);
    Parser::Parser pars(scnr);
    Interpretator::StatementInterpretator interpretator(pars);
    interpretator.interpret();
}