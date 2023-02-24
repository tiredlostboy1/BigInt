#include <BigInt/BigInt.hpp>

#include <iostream>
#include <string>

using namespace ACA;

int main()
{
	BigInt first(std::string("12345"));
    BigInt second(12934);

    BigInt third(second);
    BigInt forth = third;

    second = first;

    if (first != second) 
    {
        // cout
    }

    BigInt fifth = (first + second);
    BigInt sixth = (1 + second);


	std::cout << "first = " << first << " second = " << second 
    << " third = " << third << " forth = " << forth 
    << " fifth = " << fifth << " sixth = " << sixth;

    return 0;
}

