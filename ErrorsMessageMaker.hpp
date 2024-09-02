#pragma once
#include "Token.hpp"
#include <set>
#include <unordered_map>
#include <algorithm>

namespace ErrorsMessagePrivate
{
    using namespace Token;

    static std::unordered_map<ttype, std::string> tempatesForErrors =
    {
        {ttype::lint, "variable identificator"},
        {ttype::lasg, "assigment symbol(=)"},
        {ttype::lnum, "number literal"},
        {ttype::lfnum, "float literal"},
        {ttype::lname, "name of identificator"},
        {ttype::lout_fun, "out operator"},
        {ttype::llpar, "start of expression" },
        {ttype::lrpar, "end of expression" },
        {ttype::lminus, "minus(-)"},
        {ttype::lplus, "plus(-)"}
    };

}

namespace ErrorsMessage
{
    using namespace ErrorsMessagePrivate;
    using namespace Token;
    
    namespace Generate
    {
        /*class Error
        {
        public:
            virtual std::string what() const;
        };
        class UnexpectedLex : Error
        {
        public:
            UnexpectedLex(const ttype&, const ttype&);
            UnexpectedLex(const ttype&, const std::set<ttype>&);
            std::string what
        };*/

        std::string unexpectedLex(const ttype&, const ttype&);
        std::string unexpectedLex(const ttype&, const std::set<ttype>&);
        std::string undefinedVar(const std::string&);
        std::string inconsistency_of_types();
    }
}

// Probably add class Warning for overload function log in LogMaker
namespace WarningMessage
{
    using namespace ErrorsMessagePrivate;
    using namespace Token;

    namespace Generate
    {
        std::string unexpectedLex(const ttype&);
    }
}