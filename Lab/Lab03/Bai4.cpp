﻿#include <iomanip>
#include "modes.h"
#include <assert.h>
#include <iostream>
using std::endl;
using std::wcin;
using std::wcout;
#include <io.h>
#pragma comment(lib, "libcmt.lib")

#include <string>
using std::string;
using std::wstring;
using namespace std;

#include <sstream>
using std::ostringstream;

#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "aes.h"
using CryptoPP::AES;

#include "integer.h"
#include "nbtheory.h"
using CryptoPP::Integer;

// Hash function
#include "sha.h"
#include "sha3.h"
using CryptoPP::SHA256;
using CryptoPP::SHA512;

// String filter
#include "filters.h"
using CryptoPP::ArraySink;
using CryptoPP::SignatureVerificationFilter;
using CryptoPP::SignerFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include "files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include <ctime>

// Sinh khoá
#include "cryptlib.h"
using CryptoPP::DecodingResult;
using CryptoPP::Exception;
using CryptoPP::PrivateKey;
using CryptoPP::PublicKey;

// "Đọc" khoá từ file
#include <queue.h>
using CryptoPP::ByteQueue;

#include <sstream>
using std::ostringstream;

// ECC
#include "eccrypto.h"
using CryptoPP::DL_GroupParameters_EC;
using CryptoPP::ECDSA;
using CryptoPP::ECP;

#include <oids.h> 
namespace ASN1 = CryptoPP::ASN1;
using CryptoPP::OID;

#include "hex.h"
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include "base64.h"
using CryptoPP::Base64Decoder;
using CryptoPP::Base64Encoder;

#include <asn.h>*/


// hỗ trợ TViet 
#include <fcntl.h>
#include <locale>
using std::wstring_convert;
#include <codecvt>
using std::codecvt_utf8;

wstring string_to_wstring(const std::string& str);
string wstring_to_string(const std::wstring& str);
wstring integer_to_wstring(const CryptoPP::Integer& t);
string integer_to_string(const CryptoPP::Integer& t);
string integer_to_hex(const CryptoPP::Integer& t);

#include "oids.h"
using CryptoPP::OID;

bool GeneratePrivateKey(const OID& oid, ECDSA<ECP, SHA256>::PrivateKey& key);
bool GeneratePublicKey(const ECDSA<ECP, SHA256>::PrivateKey& privateKey, ECDSA<ECP, SHA256>::PublicKey& publicKey);

void SavePrivateKey(const string& filename, const ECDSA<ECP, SHA256>::PrivateKey& key);
void SavePublicKey(const string& filename, const ECDSA<ECP, SHA256>::PublicKey& key);
void LoadPrivateKey(const string& filename, ECDSA<ECP, SHA256>::PrivateKey& key);
void LoadPublicKey(const string& filename, ECDSA<ECP, SHA256>::PublicKey& key);

void PrintDomainParameters(const ECDSA<ECP, SHA256>::PrivateKey& key);
void PrintDomainParameters(const ECDSA<ECP, SHA256>::PublicKey& key);
void PrintDomainParameters(const DL_GroupParameters_EC<ECP>& params);
void PrintPrivateKey(const ECDSA<ECP, SHA256>::PrivateKey& key);
void PrintPublicKey(const ECDSA<ECP, SHA256>::PublicKey& key);

bool SignMessage(const ECDSA<ECP, SHA256>::PrivateKey& key, const string& message, string& signature);
bool VerifyMessage(const ECDSA<ECP, SHA256>::PublicKey& key, const string& message, const string& signature);

void SignFunction();
void VerifyFunction();

int main(int argc, char* argv[])
{
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    int choice;
    wcout << L"Nhấn: 1.Tạo key / 2.Tạo chữ kí số / 3.Kiểm tra chữ kí số \n";
    fflush(stdin);
    wcin >> choice;

    switch (choice)
    {
    case 1:
    {
        //Tạo khóa ECDSA.
        wcout << L"---- Tạo key ----" << endl;
        AutoSeededRandomPool prng;

        ECDSA<ECP, SHA256>::PrivateKey privateKey;
        ECDSA<ECP, SHA256>::PublicKey publicKey;

        GeneratePrivateKey(CryptoPP::ASN1::secp256r1(), privateKey);
        GeneratePublicKey(privateKey, publicKey);

        PrintDomainParameters(publicKey);
        PrintPrivateKey(privateKey);
        PrintPublicKey(publicKey);
        SavePrivateKey("ecc.private.der", privateKey);
        SavePublicKey("ecc.public.der", publicKey);
        break;
    }
    case 2:
    {
        wcout << L"---- Tạo chữ kí số ----" << endl;
        SignFunction();
        break;
    }
    case 3:
    {
        wcout << L"---- Kiểm tra văn bản ----" << endl;
        VerifyFunction();
        break;
    }
    default:
        break;
    }
    return 0;
}

bool GeneratePrivateKey(const OID& oid, ECDSA<ECP, SHA256>::PrivateKey& key)
{
    AutoSeededRandomPool prng;

    key.Initialize(prng, oid);
    assert(key.Validate(prng, 3));

    return key.Validate(prng, 3);
}

bool GeneratePublicKey(const ECDSA<ECP, SHA256>::PrivateKey& privateKey, ECDSA<ECP, SHA256>::PublicKey& publicKey)
{
    AutoSeededRandomPool prng;

    // Validate key
    assert(privateKey.Validate(prng, 3));

    privateKey.MakePublicKey(publicKey);
    assert(publicKey.Validate(prng, 3));

    return publicKey.Validate(prng, 3);
}

void PrintDomainParameters(const ECDSA<ECP, SHA256>::PrivateKey& key)
{
    PrintDomainParameters(key.GetGroupParameters());
}

void PrintDomainParameters(const ECDSA<ECP, SHA256>::PublicKey& key)
{
    PrintDomainParameters(key.GetGroupParameters());
}

void PrintDomainParameters(const DL_GroupParameters_EC<ECP>& params)
{
    wcout << endl;

    wcout << "Modulus:" << endl;
    wcout << " " << integer_to_wstring(params.GetCurve().GetField().GetModulus()) << endl;

    wcout << "Coefficient A:" << endl;
    wcout << " " << integer_to_wstring(params.GetCurve().GetA()) << endl;

    wcout << "Coefficient B:" << endl;
    wcout << " " << integer_to_wstring(params.GetCurve().GetB()) << endl;

    wcout << "Base Point:" << endl;
    wcout << " X: " << integer_to_wstring(params.GetSubgroupGenerator().x) << endl;
    wcout << " Y: " << integer_to_wstring(params.GetSubgroupGenerator().y) << endl;

    wcout << "Subgroup Order:" << endl;
    wcout << " " << integer_to_wstring(params.GetSubgroupOrder()) << endl;

    wcout << "Cofactor:" << endl;
    wcout << " " << integer_to_wstring(params.GetCofactor()) << endl;
}

void PrintPrivateKey(const ECDSA<ECP, SHA256>::PrivateKey& key)
{
    wcout << endl;
    wcout << "Private Exponent:" << endl;
    wcout << " " << integer_to_wstring(key.GetPrivateExponent()) << endl;
}

void PrintPublicKey(const ECDSA<ECP, SHA256>::PublicKey& key)
{
    wcout << endl;
    wcout << "Public Element:" << endl;
    wcout << " X: " << integer_to_wstring(key.GetPublicElement().x) << endl;
    wcout << " Y: " << integer_to_wstring(key.GetPublicElement().y) << endl;
}

void SavePrivateKey(const string& filename, const ECDSA<ECP, SHA256>::PrivateKey& key)
{
    key.Save(FileSink(filename.c_str(), true).Ref());
}

void SavePublicKey(const string& filename, const ECDSA<ECP, SHA256>::PublicKey& key)
{
    key.Save(FileSink(filename.c_str(), true).Ref());
}

void LoadPrivateKey(const string& filename, ECDSA<ECP, SHA256>::PrivateKey& key)
{
    key.Load(FileSource(filename.c_str(), true).Ref());
}

void LoadPublicKey(const string& filename, ECDSA<ECP, SHA256>::PublicKey& key)
{
    key.Load(FileSource(filename.c_str(), true).Ref());
}

bool SignMessage(const ECDSA<ECP, SHA256>::PrivateKey& key, const string& message, string& signature)
{
    AutoSeededRandomPool prng;

    signature.erase();

    StringSource(message, true,
        new SignerFilter(prng,
            ECDSA<ECP, SHA256>::Signer(key),
            new StringSink(signature))
    );

    return !signature.empty();
}

bool VerifyMessage(const ECDSA<ECP, SHA256>::PublicKey& key, const string& message, const string& signature)
{
    bool result = false;

    StringSource(signature + message, true,
        new SignatureVerificationFilter(
            ECDSA<ECP, SHA256>::Verifier(key),
            new ArraySink((unsigned char*)&result, sizeof(result)))
    );

    return result;
}

//UTF-8 Vietnamese


wstring string_to_wstring(const std::string& str)
{
    wstring_convert<codecvt_utf8<wchar_t>> towstring;
    return towstring.from_bytes(str);
}

string wstring_to_string(const std::wstring& str)
{
    wstring_convert<codecvt_utf8<wchar_t>> tostring;
    return tostring.to_bytes(str);
}

wstring integer_to_wstring(const CryptoPP::Integer& t)
{
    std::ostringstream oss;
    oss.str("");
    oss.clear();
    oss << t;
    std::string encoded(oss.str());
    std::wstring_convert<codecvt_utf8<wchar_t>> towstring;
    return towstring.from_bytes(encoded);
}

string integer_to_string(const CryptoPP::Integer& t)
{
    std::ostringstream oss;
    oss.str("");
    oss.clear();
    oss << t;
    std::string encoded(oss.str());
    return encoded;
}

string integer_to_hex(const CryptoPP::Integer& t)
{
    std::ostringstream oss;
    oss.str("");
    oss.clear();
    oss << std::hex << t;
    std::string encoded(oss.str());
    return encoded;
}

//Tính toán chữ ký ECDSA. 

void SignFunction()
{
    string signature, encode;
    string message;
    FileSource("input.txt", true, new StringSink(message));
    wcout << L"*** Dữ liệu nhập vào từ file ***" << endl;
    wcout << string_to_wstring(message) << endl << endl;
    int message_size = sizeof(message);

    ECDSA<ECP, SHA256>::PrivateKey Privatekey_val;
    LoadPrivateKey("ecc.private.der", Privatekey_val);

    wcout << "p = " << integer_to_wstring(Privatekey_val.GetGroupParameters().GetCurve().GetField().GetModulus()) << endl;
    wcout << "d = " << integer_to_wstring(Privatekey_val.GetPrivateExponent()) << endl;

    // Execute time
    int start_time = clock();
    for (int i = 0; i < 100; i++)
    {
        AutoSeededRandomPool prng;
        signature.erase();
        StringSource(message, true,
            new SignerFilter(prng,
                ECDSA<ECP, SHA256>::Signer(Privatekey_val),
                new Base64Encoder(new StringSink(signature))));
    }
    int stop_time = clock();
    double time = (stop_time - start_time) / double(CLOCKS_PER_SEC) * 100;

    wcout << L"Chữ ký:" << string_to_wstring(signature) << endl;
    wcout << L"Thời gian trung bình 100 lần chạy: " << time << " ms" << endl;
    wcout << L"Thời gian mã hóa: " << time / 100 << " ms" << endl;
}

// Xác minh chữ ký ECDSA. 
void VerifyFunction()
{
    string signature, encode;
    bool result;
    result = false;

    // Load key value
    ECDSA<ECP, SHA256>::PublicKey Publickey_val;
    ECDSA<ECP, SHA256>::PrivateKey Privatekey_val;

    LoadPublicKey("ecc.public.der", Publickey_val);

    string check_val, signature_val;
    FileSource("check.txt", true, new StringSink(check_val)); //check1.txt
    AutoSeededRandomPool prng;
    LoadPrivateKey("ecc.private.der", Privatekey_val);

    string message;
    FileSource("input.txt", true, new StringSink(message));
    signature.erase();
    StringSource(message, true,
        new SignerFilter(prng,
            ECDSA<ECP, SHA256>::Signer(Privatekey_val),
            new Base64Encoder(new StringSink(signature))));

    StringSource ss(signature, true,
        new Base64Decoder(
            new StringSink(signature_val))
    );

    // Execute time
    int start_time = clock();
    for (int i = 0; i < 100; i++)
    {
        result = VerifyMessage(Publickey_val, check_val, signature_val);
    }
    int stop_time = clock();
    double time = (stop_time - start_time) / double(CLOCKS_PER_SEC) * 1000;

    string check_status;

    if (result == 1) {
        wcout << L"Xác minh chữ kí số: Chính xác" << endl;
    }
    else {
        wcout << L"Xác minh chữ kí số: Không chính xác" << endl;
    }

    wcout << L"Thời gian trung bình 100 lần chạy: " << time << " ms" << endl;
    wcout << L"Thời gian giải mã: " << time / 100 << " ms" << endl;
}