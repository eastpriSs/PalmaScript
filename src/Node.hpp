// Node.hpp
#pragma once
#include <string>
#include "Int128.hpp"

class Node
{
public:
    virtual ~Node() = default;
};

class NodeInt128 : public Node
{
public:
    NodeInt128(const std::string& s) : value(s) {}
    Int128 value;
};

class NodeNameOfIdentificator : public Node
{
public:
    NodeNameOfIdentificator(const std::string& s) : strName(s) {}
    std::string strName;
};