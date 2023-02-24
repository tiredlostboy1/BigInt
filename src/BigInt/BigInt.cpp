#include <BigInt/BigInt.hpp>

#include <iostream>
#include <vector>

using namespace std;

namespace ACA
{

    BigInt::BigInt(const std::string &s)
    {
        digits.reserve(s.length());
        for (auto &i : s)
        {
            if (isdigit(s[i]))
            {
                digits.push_back(s[i]);
            }
        }
    }

    BigInt::BigInt(unsigned long long nr) : digits{std::to_string(nr)}
    {
    }

    BigInt::BigInt(const BigInt &other) : digits{other.digits}
    {
    }

    BigInt &BigInt::operator=(const BigInt &other)
    {
        // Guard self assignment
        if (this == &other)
        {
            return *this;
        }
        digits = other.digits;
        return *this;
    }

    /*
    BigInt& BigInt::operator=(BigInt other) noexcept
    {
        // exchange resources between *this and other
        std::swap(digits, other.digits);
        return *this;
    }
    */

    bool operator==(const BigInt &lhs, const BigInt &rhs)
    {
        return lhs.digits == rhs.digits;
    }

    bool operator!=(const BigInt &lhs, const BigInt &rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const BigInt &lhs, const BigInt &rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return lhs.size() < rhs.size();
        }
        for (std::size_t i = 0; i < lhs.size(); i++)
        {
            if (lhs.digits[i] != rhs.digits[i])
            {
                return lhs.digits[i] < rhs.digits[i];
            }
        }
        return false;
    }

    bool operator>(const BigInt &lhs, const BigInt &rhs)
    {
        return rhs < lhs;
    }

    bool operator>=(const BigInt &lhs, const BigInt &rhs)
    {
        return !(lhs < rhs);
    }

    bool operator<=(const BigInt &lhs, const BigInt &rhs)
    {
        return !(lhs > rhs);
    }

    BigInt &BigInt::operator++()
    {
        *this += 1;
        return *this;
    }

    BigInt BigInt::operator++(int /* tmp */)
    {
        BigInt old = *this;
        operator++(); // prefix increment
        return old;
    }

    BigInt &BigInt::operator--()
    {
        *this -= 1;
        return *this;
    }

    BigInt BigInt::operator--(int /* tmp */)
    {
        BigInt old = *this;
        operator--(); // prefix decrement
        return old;
    }

    BigInt &BigInt::operator+=(const BigInt &rhs)
    {
        std::reverse(digits.begin(), digits.end());

        std::size_t ll = digits.length(), rl = rhs.digits.length();

        if (ll < rl)
            digits.append(rl - ll, '0');

        std::size_t j = rl - 1;
        std::size_t sum;
        std::size_t tmp = 0;
        for (std::size_t i = 0; i < digits.length(); i++)
        {
            if (j >= 0)
            {
                sum = digits[i] - '0' + rhs.digits[j] - '0' + tmp;
                digits[i] = sum % 10 + '0';
                j--;
            }
            else
            {
                sum = digits[i] - '0' + tmp;
                digits[i] = sum % 10 + '0';
            }
            tmp = sum / 10;
        }
        if (tmp != 0)
        {
            digits.push_back(tmp + '0');
        }
        std::reverse(digits.begin(), digits.end());
        return *this;
    }

    BigInt operator+(BigInt lhs, const BigInt &rhs)
    {
        lhs += rhs;

        return lhs;
    }

    BigInt &BigInt::operator-=(const BigInt &rhs)
{
    if (*this < rhs)
    {
        throw("This will give a negative value");
    }
    if (*this == rhs)
    {
        digits = "0";
    }
    else
    {
        std::size_t j = rhs.digits.length() - 1;
        std::size_t tmp = 0;
        bool isPos;
        for (std::size_t i = digits.length() - 1; i >= 0; --i)
        {
            if (j >= 0)
            {
                if ((digits[i] - rhs.digits[j] - tmp) >= 0)
                {
                    isPos = true;
                    digits[i] = digits[i] - rhs.digits[j] - tmp + '0';
                }
                else
                {
                    isPos = false;
                    digits[i] = digits[i] - rhs.digits[j] - tmp + 10 + '0';
                }
                j--;
            }
            else if ((digits[i] - tmp) >= '0')
            {
                isPos = true;
                digits[i] = digits[i] - tmp;
            }
            else
            {
                isPos = false;
                digits[i] = digits[i] - tmp + 10;
            }
            tmp = isPos ? 0 : 1;
        }
        std::size_t i = 0;
        while (digits[i] == '0')
        {
            i++;
        }
        digits = digits.substr(i);
    }

    return *this;
}

    BigInt operator-(BigInt lhs, const BigInt &rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    BigInt BigInt::mul(char c) const
    {
        std::string str = digits;
        std::reverse(str.begin(), str.end());
        std::size_t tmp = 0;
        for (std::size_t i = 0; i < str.length(); i++)
        {
            std::size_t mul = (str[i] - '0') * (c - '0') + tmp;
            str[i] = (mul % 10) + '0';
            tmp = mul / 10;
        }
        if (tmp != 0)
        {
            str.push_back(tmp + '0');
        }
        std::reverse(str.begin(), str.end());
        return BigInt(str);
    }

    BigInt &BigInt::operator*=(const BigInt &rhs)
    {
        std::string res(this->digits.length() + rhs.digits.length(), '0');
        for (std::size_t i = rhs.digits.length() - 1; i >= 0; i--)
        {
            BigInt tmp = this->mul(rhs.digits[i]);
            std::string tmpStr = tmp.digits;
            tmpStr.append(rhs.digits.length() - i - 1, '0');
            for (std::size_t j = res.length() - 1, k = 0; k < tmpStr.length(); j--, k++)
            {
                std::size_t mul = (res[j] - '0') + (tmpStr[k] - '0');
                res[j] = (mul % 10) + '0';
                res[j - 1] += mul / 10;
            }
        }
        std::size_t i = 0;
        while (res[i] == '0')
        {
            i++;
        }
        this->digits = res.substr(i);
        return *this;
    }

    BigInt operator*(BigInt lhs, const BigInt &rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    BigInt BigInt::div(char c) const
    {
        std::string str = digits;
        std::string res = "";
        std::size_t tmp = 0;
        for (std::size_t i = 0; i < str.length(); i++)
        {
            std::size_t cur = (str[i] - '0') + tmp * 10;
            res.push_back(cur / (c - '0') + '0');
            tmp = cur % (c - '0');
        }
        if (res[0] == '0')
        {
            res.erase(res.begin());
        }
        return BigInt(res);
    }

    BigInt &BigInt::operator/=(const BigInt &rhs)
    {
        if ((*this) < rhs)
        {
            digits = "0";
            return *this;
        }
        if (rhs.digits == "0")
        {
            throw std::logic_error("Divide by Zero");
        }
        BigInt tmp;
        std::string result;
        std::size_t count = 0;
        for (std::size_t i = 0; i < digits.length(); ++i)
        {
            if (tmp < rhs)
            {
                tmp.digits += digits[i];
                result += '0';
            }
            else
            {
                count = 0;
                while (tmp >= rhs)
                {
                    tmp -= rhs;
                    count++;
                }
                result += to_string(count);
                tmp.digits += digits[i];
            }
        }

        count = 0;
        while (tmp >= rhs)
        {
            tmp -= rhs;
            count++;
        }
        result += to_string(count);

        *this = result;
        return *this;
    }

    BigInt operator/(BigInt lhs, const BigInt &rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    BigInt &BigInt::operator%=(const BigInt &rhs)
    {

        if ((*this) < rhs)
        {
            return *this;
        }
        if (rhs.digits == "0")
        {
            throw("Divide by Zero");
        }
        BigInt tmp;
        for (std::size_t i = 0; i < digits.length(); ++i)
        {
            if (tmp < rhs)
            {
                tmp.digits += digits[i];
            }
            else
            {
                while (tmp >= rhs)
                {
                    tmp -= rhs;
                }
                tmp.digits += digits[i];
            }
        }
        while (tmp >= rhs)
        {
            tmp -= rhs;
        }
        *this = tmp;
        return *this;
    }

    BigInt operator%(BigInt lhs, const BigInt &rhs)
    {
        lhs %= rhs;
        return lhs;
    }

    BigInt &BigInt::operator^=(const BigInt &rhs)
    {
        BigInt b = rhs;
        BigInt a = *this;
        digits = "1";
        BigInt two("2");
        while (b.digits != "0")
        {
            if ((b.digits[b.digits.length() - 1] - '0') & 1 == 1)
            {
                (*this) *= a;
            }
            a *= a;
            b /= two;
        }
        return *this;
    }

    BigInt operator^(BigInt lhs, const BigInt &rhs)
    {
        lhs ^= rhs;
        return lhs;
    }

    istream &operator>>(istream &in, BigInt &a)
    {
        std::string input;
        in >> input;
        a = BigInt(input);
        return in;
    }

    ostream &operator<<(ostream &out, const BigInt &a)
    {
        out << a.toString();
        return out;
    }

} // namespace ACA