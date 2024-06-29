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

std::vector<Integer> modExpArray(const std::vector<Integer>& arr, const Integer& x, const Integer& p)
{
    std::vector<Integer> result;
    ModularArithmetic mod(p);
    for (const auto& a : arr) {
        result.push_back(mod.Exponentiate(a, x));
    }
    return result;
}

int main()
{
    // Khởi tạo một mảng số nguyên
    std::vector<Integer> arr = { Integer("84"), Integer("104"), Integer("101"), Integer("32"),Integer("70"),
        Integer("97"), Integer("99"), Integer("117"), Integer("108"), Integer("116"), Integer("121"), 
        Integer("32"), Integer("111"), Integer("102"), Integer("32"), Integer("67"), Integer("111"), Integer("109"),
        Integer("112"), Integer("117"), Integer("116"), Integer("101"), Integer("114"), Integer("32"), Integer("78"),
        Integer("101"), Integer("116"), Integer("119"), Integer("111"), Integer("114"), Integer("107"), Integer("115"),
        Integer("32"), Integer("97"), Integer("110"), Integer("100"), Integer("32"), Integer("67"), Integer("111"),
        Integer("109"), Integer("109"), Integer("117"), Integer("110"), Integer("105"), Integer("99"), Integer("97"),
        Integer("116"), Integer("105"), Integer("111"), Integer("110"), Integer("115") };

    // Tính toán modExp của mảng số nguyên
    Integer x("23");//thay thế các số x, p theo từng câu
    Integer p("187");
    std::vector<Integer> result = modExpArray(arr, x, p);

    // In ra kết quả
    for (const auto& r : result) {
        std::cout << std::hex << r << " ";
    }
    std::cout << std::endl;

    return 0;
}
