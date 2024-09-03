#pragma once
#include "Int128.hpp"
#include "Node.hpp"

class Int128AsgAST;
class StopInterpretAST;
class OutOperAST;
class ExprAST;
class ExprInt128;
class ExprVariable;
class ExprSum;
class ExprSub;
class ExprMult;

class Visitor 
{
public:
    virtual void visit(Int128AsgAST&) = 0;
    virtual void visit(StopInterpretAST&) = 0;
    virtual void visit(OutOperAST&) = 0;
    virtual Int128 visitExpr(ExprInt128&) = 0;
    virtual Int128 visitExpr(ExprVariable&) = 0;
    virtual Int128 visitExpr(ExprSum&) = 0;
    virtual Int128 visitExpr(ExprMult&) = 0;
    virtual Int128 visitExpr(ExprSub&) = 0;
};

// StatementAST
class StatementAST
{
public:
    virtual ~StatementAST() = default;
    virtual void accept(Visitor& visitor) = 0;
};


class Int128AsgAST : public StatementAST
{
public:
    NodeNameOfIdentificator* id;
    ExprAST* expr;
    
    Int128AsgAST(NodeNameOfIdentificator* idnode, ExprAST* exast)
    {
        id = idnode;
        expr = exast;
    }
    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
};

class OutOperAST : public StatementAST
{
public:
    ExprAST* expr;
    OutOperAST(ExprAST* ex) { expr = ex; }
    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
};

class StopInterpretAST : public StatementAST
{
public:
    int code;
    StopInterpretAST(int&& c) : code(c) {}
    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
};


class ExprAST {
public:
    virtual ~ExprAST() = default;
    virtual Int128 accept(Visitor& visitor) = 0;
};

// Expr
class ExprInt128 : public ExprAST
{
public:
    NodeInt128* valNode;
    ExprInt128(NodeInt128* vn) { valNode = vn; }
    Int128 accept(Visitor& visitor) override {
        return visitor.visitExpr(*this);
    };
};

class ExprVariable : public ExprAST
{
public:
    NodeNameOfIdentificator* nameNode;
    ExprVariable(NodeNameOfIdentificator* nni) { nameNode = nni; }
    Int128 accept(Visitor& visitor) override {
        return visitor.visitExpr(*this);
    };
};

class ExprSum : public ExprAST 
{
public:
    ExprAST* lhs;
    ExprAST* rhs;
    ExprSum(ExprAST* l, ExprAST* r) { lhs = l; rhs = r; }
    Int128 accept(Visitor& visitor) override {
        return visitor.visitExpr(*this);
    };
};

class ExprSub : public ExprAST
{
public:
    ExprAST* lhs;
    ExprAST* rhs;
    ExprSub(ExprAST* l, ExprAST* r) { lhs = l; rhs = r; }
    Int128 accept(Visitor& visitor) override {
        return visitor.visitExpr(*this);
    };
};

class ExprMult : public ExprAST
{
public:
    ExprAST* lhs;
    ExprAST* rhs;
    ExprMult(ExprAST* l, ExprAST* r) { lhs = l; rhs = r; }
    Int128 accept(Visitor& visitor) override {
        return visitor.visitExpr(*this);
    };
};
