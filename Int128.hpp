#pragma once
#include <iostream>
#include <cstdint>

struct Int128
{
    uint8_t digits[39];
    bool sign : 1;
    bool overflow : 1;
    unsigned short len : 6;

    Int128() = default;
    explicit Int128(std::string numStrView);
    explicit Int128(size_t lenNum);
};

bool operator<(const Int128& lhs, const Int128& rhs);
bool operator!=(const Int128& lhs, const Int128& rhs);
bool operator==(const Int128& lhs, const Int128& rhs);
bool operator<=(const Int128& lhs, const Int128& rhs);
bool operator>(const Int128& lhs, const Int128& rhs);
Int128 operator+(const Int128& lhs, const Int128& rhs);
Int128 operator-(const Int128& lhs, const Int128& rhs);
Int128 difference(const Int128& lhs, const Int128& subtractedNumber, const unsigned short& min_l);
bool abslBigger(const Int128& lhs, const Int128& rhs);
void printInt128(const Int128& num);
