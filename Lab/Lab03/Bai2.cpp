#include "cryptlib.h"
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

// Kiểm tra số nguyên n có phải là số nguyên tố hay không
bool isPrime(const Integer& n)
{
    return IsPrime(n);
}


// Tính a^x mod p
Integer modExp(const Integer& a, const Integer& x, const Integer& p)
{
    ModularArithmetic mod(p);
    return mod.Exponentiate(a, x);
}

int main()
{
    //2.1
    Integer p("329520679814142392965336341297134588639"); //("11"); ("20079993872842322116151219");
    Integer q("308863399973593539130925275387286220623"); //("17"); //
    Integer e("886979");//("7");//("17");
    Integer p1 = p - 1;
    Integer q1 = q - 1;
    std::cout << p << " is Prime Number? " << std::boolalpha << isPrime(p) << "\n";
    std::cout << q << " is Prime Number? " << std::boolalpha << isPrime(q) << "\n";
    Integer n = p * q;
    Integer f = q1 * p1;
    std::cout << "p * q = " << n << std::endl;
    std::cout << "(p-1) * (q-1) = " << f << std::endl;
    //2.2
    std::cout << "\n5^7 mod 187 = " << modExp(5, 7, 187) << "\n"; 
    std::cout << "5^23 mod 187 = " << modExp(5, 23, 187) << "\n";
    return 0;
}
