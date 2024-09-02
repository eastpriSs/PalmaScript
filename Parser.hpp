#pragma once
#include <set>
#include "Scanner.hpp"
#include "AST.hpp"
#include "SymbolTable.hpp"

namespace Parser {

    class Parser
    {
    private:
        Token::Token currTkn = {};
    
    public:
        Parser() = delete;
        Parser(Scanner&);

        // Variables
        Int128AsgAST* parseIntVarDefinition();
        Int128AsgAST* parseIntVarAssigment();

        // Expression
        ExprAST* parsePrimary();
        ExprAST* parseTerm();

        OutOperAST* parseOutOper();
        ExprAST* parseExpr();
        StatementAST* parse();

    private: Scanner* _scn;
    };

    namespace ErrorMessage 
    {
        static constexpr void butfound() {}

        void expected(const Token::ttype&, void (*)(), const Token::Token&);
        void expectedOneOf(const std::set<Token::ttype>&, void (*)(), const Token::Token&);
        void expectedOneOf(std::set<Token::ttype>&&, void (*)(), const Token::Token&);
    };
    
    // warning! function with side-effect
    void checkLex(Token::ttype&&, const Token::Token&);

};

/*namespace ParserStuff
{

    bool equal(const Token::ttype& x, Token::ttype&&);
}*/