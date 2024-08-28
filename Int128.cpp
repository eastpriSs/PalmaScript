#include "Int128.hpp"

Int128::Int128(std::string numStrView)
{
    len = numStrView.size();
    sign = numStrView[0] == '-';
    for (int i = len - 1; i >= static_cast<int>(sign); --i)
        digits[len - i - 1] = numStrView[i] - '0';
    if (sign) len -= 1;
}

Int128::Int128(size_t lenNum)
{
    len = lenNum;
    for (auto i = 0; i < len; ++i)
        digits[i] = 0;
}

void printInt128(const Int128& num)
{
    if (num.sign) printf("-");
    for (int i = num.len - 1; i >= 0; --i)
        printf("%d", num.digits[i]);
}

bool abslBigger(const Int128& lhs, const Int128& rhs)
{
    if (lhs.len != rhs.len)
        return lhs.len > rhs.len;

    for (int i = lhs.len - 1; i >= 0; --i)
        if (lhs.digits[i] > rhs.digits[i])      return true;
        else if (lhs.digits[i] < rhs.digits[i]) return false;

    return false;
}

bool operator>(const Int128& lhs, const Int128& rhs)
{
    if (lhs.sign ^ rhs.sign)
        return !(lhs.sign > rhs.sign);

    if (lhs.len != rhs.len)
        return (lhs.sign && rhs.sign) ? !(lhs.len > rhs.len) : (lhs.len > rhs.len);

    for (int i = lhs.len - 1; i >= 0; --i)
        if (lhs.digits[i] > rhs.digits[i])      return !(lhs.sign && rhs.sign);
        else if (lhs.digits[i] < rhs.digits[i]) return !(rhs.sign && lhs.sign);

    return false;
}

bool operator<=(const Int128& lhs, const Int128& rhs)
{
    return !(lhs > rhs);
}


bool operator==(const Int128& lhs, const Int128& rhs)
{
    if (lhs.len != rhs.len)
        return false;

    for (int i = 0; i <= lhs.len - 1; ++i)
        if (lhs.digits[i] != rhs.digits[i])
            return false;
    return true;

}

bool operator!=(const Int128& lhs, const Int128& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Int128& lhs, const Int128& rhs)
{
    return rhs < lhs;
}

Int128 operator+(const Int128& lhs, const Int128& rhs)
{
    Int128 res;
    unsigned short min_l;

    min_l = std::min(lhs.len, rhs.len);

    // when - and -
    if (lhs.sign && rhs.sign)
        res.sign = true;

    if (lhs.sign ^ rhs.sign) {
        res = difference(lhs, rhs, min_l);
        res.sign = (abslBigger(lhs, rhs)) ? lhs.sign : rhs.sign;
        return res;
    }

    if (lhs.len > rhs.len)
        res = lhs;
    else
        res = rhs;

    uint8_t sumDigits = 0;
    uint8_t base = 10;
    uint8_t carry = 0;

    for (size_t i = 0; i < min_l; ++i)
    {
        sumDigits = lhs.digits[i] + rhs.digits[i] + carry;
        res.digits[i] = sumDigits;
        carry = sumDigits / base;
        res.digits[i] %= base;
    }

    if (carry != 0) {
        res.overflow = 1;
    }

    return res;
}

Int128 difference(const Int128& lhs, const Int128& subtractedNumber, const unsigned short& min_l)
{
    Int128 res = lhs;
    res.sign = false;
    int8_t subtrDigits = 0;
    for (size_t i = 0; i < min_l; ++i)
    {
        subtrDigits = res.digits[i] - subtractedNumber.digits[i];
        if (subtrDigits < 0) {
            int iterNumber = i;
            while (res.digits[++iterNumber] == 0) { res.digits[iterNumber] = 9; }
            res.digits[iterNumber] -= 1;
            if (res.digits[iterNumber] == 0) res.len -= 1;
            subtrDigits += 10;
        }
        res.digits[i] = subtrDigits;
    }
    while (res.digits[res.len - 1] == 0) res.len -= 1;
    return res;
}

Int128 operator-(const Int128& lhs, const Int128& rhs)
{
    Int128 res;
    const Int128* subtractedNumber = nullptr;
    unsigned short min_l = 0;

    // when lhs is - and rhs is +
    if (lhs.sign && (rhs.sign == false))
    {
        res = lhs + rhs;
        res.sign = true;
        return res;
    }
    // when lhs is + and rhs is -
    else if ((lhs.sign == false) && rhs.sign)
    {
        res = lhs + rhs;
        res.sign = false;
        return res;
    }

    //when lhs is + and rhs is +
    //when lhs is - and rhs is -
    if (lhs.len > rhs.len) {
        res = lhs;
        subtractedNumber = &rhs;
        min_l = rhs.len;
        res.sign = lhs.sign;
    }
    else if (lhs.len == rhs.len)
    {
        // -lhs -(-rhs)
        if (lhs > rhs) {
            res = lhs;
            subtractedNumber = &rhs;
            res.sign = true;
        }
        else {
            res = rhs;
            subtractedNumber = &lhs;
            res.sign = false;
        }
        min_l = lhs.len;
    }
    else {
        res = rhs;
        subtractedNumber = &lhs;
        min_l = lhs.len;
    }

    uint8_t subtrDigits = 0;
    for (size_t i = 0; i < min_l; ++i)
    {
        subtrDigits = res.digits[i] - subtractedNumber->digits[i];
        if (subtrDigits < 0) {
            int iterNumber = i;
            while (res.digits[++iterNumber] == 0) { res.digits[iterNumber] = 9; }
            res.digits[iterNumber] -= 1;
            if (res.digits[iterNumber] == 0) res.len -= 1;
            subtrDigits += 10;
        }
        res.digits[i] = subtrDigits;
    }
    while (res.digits[res.len - 1] == 0) res.len -= 1;
    return res;
}