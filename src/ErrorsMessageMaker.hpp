#pragma once
#include "Token.hpp"
#include <set>
#include <unordered_map>
#include <algorithm>

namespace ErrorsMessagePrivate
{
    using Token::ttype;

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
    
    namespace Generate
    {
        using Token::ttype;

        class Error
        {
        public:
            virtual std::string what() const = 0;
        };
        
        class UnexpectedLex : public Error
        {
        private:
            std::string message;
        
        public:
            UnexpectedLex(const Token::ttype&, const ttype&);
            UnexpectedLex(const ttype&, const std::set<ttype>&);
            inline std::string what() const override;
        };

        class UndefinedVar : public Error
        {
        private:
            const std::string* idname;
                            
        public:
            UndefinedVar(const std::string&);
            std::string what() const override;
        };
    }
}

// Probably add class Warning for overload function log in LogMaker
namespace WarningMessage
{
    using namespace ErrorsMessagePrivate;

    namespace Generate
    {
        using Token::ttype;

        class Warning
        {
        public:
            virtual std::string what() const = 0;
        };

        class UnexpectedLex : public Warning
        {
        private:
            const ttype* foundlex;

        public:
            UnexpectedLex(const ttype&);
            inline std::string what() const override;
        };
    }
}