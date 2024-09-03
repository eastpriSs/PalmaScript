#include "Parser.hpp"

//#include <iostream>

// TODO replace all 'new' ->  'unique_ptr'

Parser::Parser::Parser(Scanner& s) 
{
    _scn = &s;
}

// TODO: exceptions
ExprAST* Parser::Parser::parsePrimary() 
{
    currTkn = _scn->scan();
    switch (currTkn.type)
    {
    case Token::ttype::lnum:
        return new ExprInt128(new NodeInt128(currTkn.lex.strview));

    case Token::ttype::lname:
        return new ExprVariable(new NodeNameOfIdentificator(currTkn.lex.strview));

    case Token::ttype::llpar:
        _scn->scan(); // eat '('
        ExprAST* expr = parseExpr();
        currTkn = _scn->scan(); // eat ')'
        checkLex(Token::ttype::llpar, currTkn);
        return expr;

    // default: throw warning

    }
}

// TODO: exceptions
ExprAST* Parser::Parser::parseTerm() 
{
    using namespace Token;

    ExprAST* lhs = parsePrimary();
    currTkn = _scn->scan();
    while (currTkn.type == ttype::lmult || currTkn.type == ttype::ldiv)
    {
        ttype oper = currTkn.type;        
        ExprAST* rhs = parsePrimary();
        
        switch (oper)
        {
        case ttype::lmult:
            lhs = new ExprMult(lhs, rhs);
            break;
        }
        currTkn = _scn->scan();
    }
    return lhs;
}

// TODO fix incorrect parsing (expr)
ExprAST* Parser::Parser::parseExpr()
{
    using namespace Token;
    using namespace ErrorMessage;

    ExprAST* lhs = parseTerm();
    bool currLexPlusOrMinus = (currTkn.type == ttype::lplus || currTkn.type == ttype::lminus);
    
    if (!currLexPlusOrMinus && !(currTkn.type == ttype::leof))
        expectedOneOf({ ttype::lplus, ttype::lminus }, butfound, currTkn); // throw warning to user
   
    while (currLexPlusOrMinus)
    {
        ttype oper = currTkn.type;
        ExprAST* rhs = parseTerm();
        printf("%s", currTkn.lex.strview.c_str());
        switch (oper)
        {
        case ttype::lplus:
            lhs = new ExprSum(lhs, rhs);
            break;
        case ttype::lminus:
            lhs = new ExprSub(lhs, rhs);
            break;
        default:
            expectedOneOf({ ttype::lplus, ttype::lminus }, butfound, currTkn);
        }
        currLexPlusOrMinus = (currTkn.type == ttype::lplus || currTkn.type == ttype::lminus);
    }
    return lhs;
}

// int128 x = 10
// int128 = x 10
// ! Expression start with char '(' and end with ')'
// ! in this case insted of '10' can stay expression
Int128AsgAST* Parser::Parser::parseIntVarDefinition()
{
    using namespace Token;
    using namespace ErrorMessage;

    static std::set<ttype> possibleTokens = { ttype::lname, ttype::lasg };

    NodeNameOfIdentificator* idnode = nullptr;
    ExprAST* expr;

    switch (currTkn.type)
    {
    // TODO
    case ttype::lname:
        idnode = new NodeNameOfIdentificator(currTkn.lex.strview);
        currTkn = _scn->scan();
        checkLex(ttype::lasg, currTkn); // TODO Message about declaration like 'int128 var' 
        break;
    
    case ttype::lasg:
        currTkn = _scn->scan();
        checkLex(ttype::lname, currTkn);
        idnode = new NodeNameOfIdentificator(currTkn.lex.strview);
        break;

    default:
        expectedOneOf(possibleTokens, butfound, currTkn);
        break;
    }

    currTkn = _scn->scan();
    expr = parseExpr();
    return new Int128AsgAST(idnode, expr);
}

Int128AsgAST* Parser::Parser::parseIntVarAssigment() 
{
    // hmm
    return parseIntVarDefinition();
}

OutOperAST* Parser::Parser::parseOutOper()
{
    return new OutOperAST(parseExpr());
}

StatementAST* Parser::Parser::parse()
{
    using namespace Token;

    while ((currTkn = _scn->scan()), currTkn.type != ttype::leof)
    {
        switch (currTkn.type)
        {

        case ttype::lint:
            currTkn = _scn->scan();
            return parseIntVarDefinition();
            break;

        case ttype::lout_fun:
            return parseOutOper();
            break;

        case ttype::lname: case ttype::lasg:
            return parseIntVarAssigment();
            break;

        default:
            break;
        }
    }
    return new StopInterpretAST(0); // add error code type
}