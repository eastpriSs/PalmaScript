#include "Compiler.hpp"
#include "Scanner.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"

void Compiler::Compile(const CharDriver::CharStream& chs)
{
    Scanner scnr(chs);
    Parser::Parser pars(scnr);
    Interpreter::StatementInterpreter Interpreter(pars);
    Interpreter.interpret();
}