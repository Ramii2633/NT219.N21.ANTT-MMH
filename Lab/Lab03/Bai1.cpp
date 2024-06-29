/*#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"
#include "integer.h"
#include "osrng.h"
#include "nbtheory.h"
#include "modarith.h"
#include <iostream>
#include <cstring>

using namespace CryptoPP;

// Sinh số nguyên tố ngẫu nhiên có n bit
Integer generateRandomPrime(int n)
{
    AutoSeededRandomPool rng;
    Integer p;
    do {
        p.Randomize(rng, n);
    } while (!IsPrime(p));
    return p;
}

// Kiểm tra số nguyên n có phải là số nguyên tố hay không
bool isPrime(const Integer& n)
{
    return IsPrime(n);
}

// Tính ước chung lớn nhất của a và b
Integer gcd(const Integer& a, const Integer& b)
{
    Integer c = GCD(a, b);
    return c;
}

// Tính a^x mod p
Integer modExp(const Integer& a, const Integer& x, const Integer& p)
{
    ModularArithmetic mod(p);
    return mod.Exponentiate(a, x);
}

int main()
{
    // Sinh số nguyên tố ngẫu nhiên có độ dài 2 byte, 8 byte và 32 byte
    Integer p16 = generateRandomPrime(16);
    Integer p64 = generateRandomPrime(64);
    Integer p256 = generateRandomPrime(256);

    std::cout << "--- RANDOM PRIME NUMBER ---\n";
    std::cout << "2 bytes: " << p16 << "\n";
    std::cout << "8 bytes: " << p64 << "\n";
    std::cout << "32 bytes: " << p256 << "\n\n";

    // Kiểm tra số nguyên n có phải là số nguyên tố hay không
    std::cout << "--- CHECK PRIME NUMBER ---\n";
    Integer n("618970019642690137449562111045832");
    std::cout << n << " is Prime Number? " << std::boolalpha << isPrime(n) << "\n";
    Integer n1("10649295715232701624149741045652844502195481997716135152553870009042198129939");
    std::cout << n1 << " is Prime Number? " << std::boolalpha << isPrime(n1) << "\n\n";

    // Tính ước chung lớn nhất của hai số nguyên "lớn"
    std::cout << "--- FIND GCD ---\n";
    Integer a("1234567890123456789012345678901234567890");
    Integer b("9876543210987654321098765432109876543210");
    Integer c = gcd(a, b);
    std::cout << "gcd(" << a << ", " << b << ") = " << c << "\n";

    Integer a1("29347589345792384759247593485729385");
    Integer b1("28934759035723857945725");
    Integer c1 = gcd(a1, b1);
    std::cout << "gcd(" << a1 << ", " << b1 << ") = " << c1 << "\n\n";

    // Tính a^x mod p
    std::cout << "--- CALCULATE a^x mod p ---\n";
    Integer a2("7");
    Integer x("40");
    Integer p("19");
    std::cout << a2 << "^" << x << " mod " << p << " = " << modExp(a2, x, p) << "\n";
    std::cout << "19^50 mod 32 = " << modExp(19, 50, 32) << "\n";
    return 0;
}*/