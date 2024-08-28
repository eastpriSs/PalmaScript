#include "Parser.hpp"

// TODO replace all 'new' ->  'unique_ptr'

Parser::Parser::Parser(Scanner& s) 
{
    _scn = &s;
}

ExprAST* Parser::Parser::parseExpr()
{
    using namespace ErrorMessage;

    switch (currTkn.type)
    {
    case Token::ttype::lnum:        
        return new ExprInt128(new NodeInt128(currTkn.lex.strview));
        break;

    case Token::ttype::lname:
        return new ExprVariable(new NodeNameOfIdentificator(currTkn.lex.strview));
        break;
    
    case Token::ttype::llpar: 
    {
        // BIG TODO 
        //---------- * temprory
        currTkn = _scn->scan();
        ExprAST* operand1 = parseExpr();
        ExprAST* operand2 = nullptr;
        currTkn = _scn->scan();
        switch (currTkn.type)
        {
        case Token::ttype::lplus:
            currTkn = _scn->scan();
            operand2 = parseExpr();
            currTkn = _scn->scan(); // eat ')'
            return new ExprSum(operand1, operand2);
        }
        //------------
    }
    break;

    default:
        expectedOneOf({Token::ttype::lname, Token::ttype::lnum, Token::ttype::llpar}, butfound, currTkn);
        break;
    }
}

// int128 x = 10
// int128 = x 10
// ! Expression start with char '(' and end with ')'
// ! in this case insted of '10' can stay expression
Int128AsgAST* Parser::Parser::parseIntVarDeclaration()
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
        checkLex(ttype::lasg, currTkn); // TODO Message about definition like 'int128 var' 
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
    return parseIntVarDeclaration();
}

OutOperAST* Parser::Parser::parseOutOper()
{
    currTkn = _scn->scan();
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
            return parseIntVarDeclaration();
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
    return new StopInterpretAST(0);
}