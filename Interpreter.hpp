#pragma once
#include "Parser.hpp"
#include "SymbolTable.hpp"
#include "Int128.hpp"
#include "AST.hpp"


namespace Interpreter {

    class StatementInterpreter : public Visitor
    {
    private:
        // class Array128
        Int128 _arrayInt128[64] = {};
        uint8_t amount = 0;

        Parser::Parser* pars = nullptr;
        bool doInterpret = false;

    public:

        StatementInterpreter(Parser::Parser& p) {
            pars = &p;
        }

        void visit(Int128AsgAST& ast) override
        {          
            SymbolTable::symtab[ast.id->strName].stackOffset = amount;
            _arrayInt128[amount] = ast.expr->accept(*this);
            ++amount;
        }
        void visit(StopInterpretAST& ast) override
        {
            doInterpret = false;
        }
        void visit(OutOperAST& ast) override
        {
            printInt128(ast.expr->accept(*this));
        }
        // EXPRESSIONS
        Int128 visitExpr(ExprInt128& ast) override
        {
            return ast.valNode->value;
        }
        Int128 visitExpr(ExprVariable& ast) override
        {
            return _arrayInt128[SymbolTable::symtab[ast.nameNode->strName].stackOffset];
        }
        Int128 visitExpr(ExprSum& ast) override
        {
            return ast.lhs->accept(*this) + ast.rhs->accept(*this);
        }

    public:

        void interpret() {
            doInterpret = true;
            while (doInterpret)
            {
                pars->parse()->accept(*this);
            }
        }
    };

}