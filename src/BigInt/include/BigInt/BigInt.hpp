#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <algorithm>
namespace ACA
{

class BigInt
{
public:
    BigInt() = default;
    BigInt(std::string& s);
    BigInt(unsigned long long nr);
    BigInt(const BigInt& other);
    BigInt& operator=(const BigInt& other);
    bool operator==(const BigInt& rhs) const;
    bool operator!=(const BigInt& rhs) const;
    bool operator<(const BigInt& rhs) const;
    bool operator>(const BigInt& rhs) const;
    bool operator<=(const BigInt& rhs) const;
    bool operator>=(const BigInt& rhs) const;
    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);
    BigInt& operator+=(const BigInt& rhs);
    BigInt& operator-=(const BigInt& rhs);
    friend BigInt operator+(BigInt lhs, const BigInt& rhs);
    friend BigInt operator-(BigInt lhs, const BigInt& rhs);
    BigInt mul(char c) const;
    BigInt &operator*=(const BigInt &rhs);
    BigInt operator*(BigInt lhs, const BigInt &rhs);
    BigInt div(char c) const;
    BigInt &operator/=(const BigInt &rhs);
    BigInt operator/(BigInt lhs, const BigInt &rhs);
    BigInt &operator%=(const BigInt &rhs);
    BigInt operator%(BigInt lhs, const BigInt &rhs);
    BigInt &operator^=(const BigInt &rhs);
    BigInt operator^(BigInt lhs, const BigInt &rhs);

    friend std::istream &operator>>(std::istream &in, BigInt &a);
    friend std::ostream &operator<<(std::ostream &out, const BigInt &a);
private:
    std::string digits;
    std::size_t size = 0;
};
} // namespace ACA

#endif
