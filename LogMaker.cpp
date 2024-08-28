#include "LogMaker.hpp"
#include "LineDriver.hpp"
#include <stdio.h>

void iLogMaker::logMaker::log(std::string error_info) const
{
    static constexpr char head[] = "\nOh no.. ";
    static constexpr char codepos_info_head[] = "\nCode position: ";
    static constexpr unsigned char c = '~';
    unsigned char ptr_head[128];

    //printf("%d", currTkn->lex.charPosInline);

    __stosb((unsigned char*)ptr_head, c, currTkn->lex.charPosInline);
    ptr_head[currTkn->lex.charPosInline] = '^';
    ptr_head[currTkn->lex.charPosInline + 1] = '\0';

    printf("%s", head);
    printf("%s", codepos_info_head);
    printf("(%d, %d)\n", currTkn->lex.linepos + 1, currTkn->lex.charPosInline);
    printf("%s\n", lineDriver::LineDriver::instance().getlineByIndx(currTkn->lex.linepos).c_str());
    printf("%s\n", ptr_head);
    printf("%s\n", error_info.c_str());
}