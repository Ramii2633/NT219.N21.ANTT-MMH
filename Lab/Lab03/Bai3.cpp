#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;
set<long long> prime; // tập hợp số nto để chọn p, q
long long public_key;
long long private_key;
long long n;
long long e;
long long d;

void primefiller() // tạo ra một tập hợp các số nguyên tố.
{
    //sử dụng phương pháp sàng Eratosthenes
    vector<bool> seive(100000, true);
    seive[0] = false;
    seive[1] = false;
    //đặt các vị trí là bội của số từ 2-99999 thành flase
    for (long long i = 2; i < 100000; i++)
    {
        for (long long j = i * 2; j < 100000; j += i)
        {
            seive[j] = false;
        }
    }
    //các vị trí true là snt
    for (long long i = 0; i < seive.size(); i++) {
        if (seive[i])
            prime.insert(i);
    }
}

// chọn 1 snt và xoá snt đó (để tránh p==q)
long long pickrandomprime()
{
    long long k = rand() % prime.size();
    auto it = prime.begin();
    while (k--)
        it++;
    long long ret = *it;
    prime.erase(it);
    return ret;
}


long long gcd(long long a, long long b)
{
    if (a < b)
        swap(a, b);
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

//Thuật toán euclid mở rộng để tìm d
long long extended_euclid(long long a, long long b, long long& x, long long& y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

//rand chọn 2 số snt p,q, tính n =p*q
void setkeysrand()
{
    long long prime1 = pickrandomprime();
    long long prime2 = pickrandomprime();
    cout << "p = " << prime1 << endl;
    cout << "q = " << prime2 << endl;
    n = prime1 * prime2;
    long long fi = (prime1 - 1) * (prime2 - 1);
    e = 2;
    //sd tìm kiếm nhị phân để tìm e lớn nhất có thể
    long long low = 2, high = fi - 1;
    while (low <= high)
    {
        long long mid = (low + high) / 2;
        if (gcd(mid, fi) == 1)
        {
            e = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    // tính d 
    long long y;
    extended_euclid(e, fi, d, y);
    d = (d % fi + fi) % fi; // d chắc chắn nhỏ hơn fi
    public_key = e;
    private_key = d;
    cout << "n = " << n << endl;
}

//nhập p,q,e, tính d,n
void setkeysin()
{
    long long prime1, prime2;
    cout << "Enter p: ";
    cin >> prime1;
    cout << "Enter q: ";
    cin >> prime2;
    n = prime1 * prime2;
    long long fi = (prime1 - 1) * (prime2 - 1);
    cout << "Enter the public key e: ";
    cin >> e;
    while (gcd(e, fi) != 1)
    {
        cout << "Invalid public key exponent. Please enter another value: ";
        cin >> e;
    }
    long long y;
    extended_euclid(e, fi, d, y);
    d = (d % fi + fi) % fi;
    public_key = e;
    private_key = d;
    cout << "n = " << n << endl;
}

long long encrypt(double message)
{
    long long e = public_key;
    long long encrpyted_text = 1;
    while (e--) {
        encrpyted_text *= message;
        encrpyted_text %= n;
    }
    return encrpyted_text;
}

long long decrypt(long long encrpyted_text)
{
    long long d = private_key;
    long long decrypted = 1;
    while (d--) {
        decrypted *= encrpyted_text;
        decrypted %= n;
    }
    return decrypted;
}

// chuyển từng kí tự sang mã ascii và mã hoá 
vector<long long> encoder(string message)
{
    //xoá khoảng trắng*
    message.erase(std::remove_if(message.begin(), message.end(), ::isspace), message.end());
    // Mã hoá từng kí tự trong chuỗi message
    vector<long long> form;
    for (auto& letter : message)
        form.push_back(encrypt((long long)letter));
    return form;
}

string decoder(vector<long long> encoded)
{
    string s;
    for (auto& num : encoded)
        s += decrypt(num);
    return s;
}


int main()
{
    string message;
    cout << "Enter the message: ";
    getline(cin, message);
    int choice;
    cout << "1. Enter p,q,e // 2.Random p,q,e" << endl;
    cin >> choice;
    if (choice == 1)
    {
        setkeysin();
    }
    else
    {
        srand(time(NULL)); // khởi tạo bộ sinh số ngẫu nhiên
        primefiller();
        setkeysrand();
    }
    // calling the encoding function
    vector<long long> coded = encoder(message);
    cout << "Public key: " << public_key << endl;
    cout << "Private key: " << private_key << endl;
    cout << "Initial message:\n" << message;
    cout << "\n\nThe encoded message(encrypted by public key)\n";
    for (auto& p : coded)
        cout << hex << p;
    cout << "\n\nThe decoded message(decrypted by private key)\n";
    cout << decoder(coded) << endl;
    return 0;
}