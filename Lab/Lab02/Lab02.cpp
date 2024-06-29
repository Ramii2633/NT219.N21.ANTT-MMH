/*
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include "aes.h"
#include "ccm.h"
#include "cryptlib.h"
#include "files.h"
#include "filters.h"
#include "modes.h"
#include "xts.h"
#include "osrng.h"
#include "hex.h"

//using namespace std;
using namespace CryptoPP;

void encrypt(int a);

void decrypt(int a);

int main()
{
    int choice, mode;
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    SecByteBlock iv(AES::BLOCKSIZE);
    std::cout << "\n1. Encrypt / 2.Decrypt\n";
    std::cin >> choice;
    std::cout << "\nMode: 1.ECB / 2.CBC / 3.OFB / 4.CFB / 5.CTR / 6.XTS / 7.CCM\n";
    std::cin >> mode;
    if (choice == 1)
        encrypt(mode);
    else if (choice == 2)
        decrypt(mode);
    return 0;
}


void encrypt(int mode)
{
    int choice;
    std::string filename;
    std::string input, output;
    std::cout << "\nInput plaintext: 1.Input from keyboard/ 2.Input from file\n";
    std::cin >> choice;
    if (choice == 1)
    {
        std::cout << "\nInput plaintext:";
        std::cin.ignore();
        getline(std::cin, input);
    }

    else if (choice == 2)
    {
        std::cout << "\nInput file name: ";
        std::cin.ignore();
        getline(std::cin, filename);
        filename = filename + ".txt";
        std:: ifstream ifs(filename);
        input.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    }

    std::cout << "\nEncrypt with KEY and IV random\n";
    // Mode: 1.ECB / 2.CBC / 3.OFB / 4.CFB / 5.CTR / 6.XTS / 7.CCM
    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    SecByteBlock iv(AES::BLOCKSIZE);

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());


    if (mode == 1) //ECB
    {
        ECB_Mode<AES>::Encryption encryptor;
        encryptor.SetKey(key, key.size());

        StringSource s(input, true, new StreamTransformationFilter(encryptor,new StringSink(output)));
        std::cout << "\nKey: ";
        encoder.Put(key, key.size());
        encoder.MessageEnd();

        std::cout << "\nCiphertext: ";
        encoder.Put((const byte*)&output[0], output.size());
        encoder.MessageEnd();
    }


    else if (mode == 2) //CBC
    {
        CBC_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), iv);

        StringSource s(input, true,new StreamTransformationFilter(encryptor, new StringSink(output)));

        std::cout << "\nKey: ";
        encoder.Put(key, key.size());
        encoder.MessageEnd();

        std::cout << "\nIV: ";
        encoder.Put(iv, iv.size());
        encoder.MessageEnd();

        std::cout << "\nCiphertext: ";
        encoder.Put((const byte*)&output[0], output.size());
        encoder.MessageEnd();

    }


    else if (mode == 3) //OFB
    {
        OFB_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), iv);

        StringSource s(input, true,new StreamTransformationFilter(encryptor, new StringSink(output)));

        std::cout << "\nKey: ";
        encoder.Put(key, key.size());
        encoder.MessageEnd();

        std::cout << "\nIV: ";
        encoder.Put(iv, iv.size());
        encoder.MessageEnd();

        std::cout << "\nCiphertext: ";
        encoder.Put((const byte*)&output[0], output.size());
        encoder.MessageEnd();
    }


    else if (mode == 4)  //CFB
    {
        CFB_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), iv);

        StringSource s(input, true, new StreamTransformationFilter(encryptor,new StringSink(output)));

        std::cout << "\nKey: ";
        encoder.Put(key, key.size());
        encoder.MessageEnd();

        std::cout << "\nIV: ";
        encoder.Put(iv, iv.size());
        encoder.MessageEnd();

        std::cout << "\nCiphertext: ";
        encoder.Put((const byte*)&output[0], output.size());
        encoder.MessageEnd();
    }


    else if (mode == 5) //CTR
    {
        byte ctr[AES::BLOCKSIZE];
        prng.GenerateBlock(ctr, sizeof(ctr));

        CTR_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), ctr);

        StringSource s(input, true, new StreamTransformationFilter(encryptor, new StringSink(output)));

        std::cout << "\nKey: ";
        encoder.Put(key, key.size());
        encoder.MessageEnd();

        std::cout << "\nCTR: ";
        encoder.Put(ctr, sizeof(ctr));
        encoder.MessageEnd();

        std::cout << "\nCiphertext: ";
        encoder.Put((const byte*)&output[0], output.size());
        encoder.MessageEnd();

    }


    else if (mode == 6) //XTS
    {
        SecByteBlock key_XTS(32);
        prng.GenerateBlock(key_XTS, key_XTS.size());

        XTS_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key_XTS, key_XTS.size(), iv);

        StringSource s(input, true, new StreamTransformationFilter(encryptor, new StringSink(output)));

        std::cout << "\nKey: ";
        encoder.Put(key_XTS, key_XTS.size());
        encoder.MessageEnd();

        std::cout << "\nIV: ";
        encoder.Put(iv, iv.size());
        encoder.MessageEnd();

        std::cout << "\nCiphertext: ";
        encoder.Put((const byte*)&output[0], output.size());
        encoder.MessageEnd();

    }


    else //CCM
    {
        CCM<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), iv);

        StringSource s(input, true, new StreamTransformationFilter(encryptor, new StringSink(output)));

        std::cout << "\nKey: ";
        encoder.Put(key, key.size());
        encoder.MessageEnd();

        std::cout << "\nIV: ";
        encoder.Put(iv, iv.size());
        encoder.MessageEnd();

        std::cout << "\nCiphertext: ";
        encoder.Put((const byte*)&output[0], output.size());
        encoder.MessageEnd();
    }
}




void decrypt(int mode)
{
    std::string input, output, key_raw, iv_raw, input_raw;
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    byte iv[CryptoPP::AES::BLOCKSIZE] = {};

    std::string filename, kivname;
    int choice, choice2;
    std::cout << "\nInput Ciphertext:  1.Input from keyboard/ 2.Input from file\n";
    std::cin >> choice;

    if (choice == 1)
    {
        std::cout << "\nInput Ciphertext: ";
        std::cin.ignore();
        getline(std::cin, input);
    }
    else if (choice == 2)
    {
        std::cout << "\nInput file name: ";
        std::cin.ignore();
        getline(std::cin, filename);
        filename += ".txt";
        std::ifstream ifs(filename);
        input.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    }


    {
        CryptoPP::HexDecoder decoder;
        decoder.Put((byte*)input.data(), input.size());
        decoder.MessageEnd();

        long long size = decoder.MaxRetrievable();
        input_raw.resize(size);
        decoder.Get((byte*)input_raw.data(), input_raw.size());
    }

    std::cout << "\nInput KEY & IV: 1.Input from keyboard/ 2.Input from file\n";
    std::cin >> choice2;
    if (choice2 == 1)
    {
        std::cout << "\nInput KEY (hex format): ";
        std::cin >> key_raw;
        {
            CryptoPP::HexDecoder decoder;
            decoder.Put((byte*)key_raw.data(), key_raw.size());
            decoder.MessageEnd();
            decoder.Get(key, sizeof(key));
        }
        if (mode != 1) //EBC kh dùng IV
        {
            std::cout << "\nInput IV (hex format): ";
            std::cin >> iv_raw;
            {
                CryptoPP::HexDecoder decoder;
                decoder.Put((byte*)iv_raw.data(), iv_raw.size());
                decoder.MessageEnd();
                decoder.Get(iv, sizeof(iv));
            }
        }
    }


    else if (choice == 2)
    {
        std::cout << "\nInput file name of KEY & IV: ";
        std::cin >> kivname;
        kivname += ".txt";

        std::ifstream ifs(kivname);
        std::vector<std::string> content;
        std::string line;
        while (getline(ifs, line))
        {
            content.push_back(line);
        }

        key_raw = content[0];
        {
            CryptoPP::HexDecoder decoder;
            decoder.Put((byte*)key_raw.data(), key_raw.size());
            decoder.MessageEnd();
            decoder.Get(key, sizeof(key));
        }
        if (mode != 1)
        {
            iv_raw = content[1];
            {
                CryptoPP::HexDecoder decoder;
                decoder.Put((byte*)iv_raw.data(), iv_raw.size());
                decoder.MessageEnd();
                decoder.Get(iv, sizeof(iv));
            }
        }
    }

    if (mode == 1) //ecb
    {
        ECB_Mode< AES >::Decryption d;
        d.SetKey(key, sizeof(key));

        StringSource s(input_raw, true,new StreamTransformationFilter(d,new StringSink(output)));
        std::cout << "\nPlaintext: " << output;
    }



    else if (mode == 2) //cbc
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);

        StringSource s(input_raw, true, new StreamTransformationFilter(d, new StringSink(output)));
        std::cout << "\nPlaintext: " << output;
    }


    else if (mode == 3) //ofb
    {
        OFB_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);

        StringSource s(input_raw, true, new StreamTransformationFilter(d, new StringSink(output)));
        std::cout << "\nPlaintext: " << output;
    }


    else if (mode == 4) //cfb
    {
        CFB_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);

        StringSource s(input_raw, true,new StreamTransformationFilter(d, new StringSink(output)));
        std::cout << "\nPlaintext: " << output;
    }


    else if (mode == 5) //ctr
    {
        CTR_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);

        StringSource s(input_raw, true, new StreamTransformationFilter(d, new StringSink(output)));
        std::cout << "\nPlaintext: " << output;
    }


    else if (mode == 6) //XTS
    {
        byte key_XTS[32];

        {
            CryptoPP::HexDecoder decoder;
            decoder.Put((byte*)key_raw.data(), key_raw.size());
            decoder.MessageEnd();
            decoder.Get(key_XTS, sizeof(key_XTS));
        }

        XTS_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key_XTS, sizeof(key_XTS), iv);

        StringSource s(input_raw, true, new StreamTransformationFilter(d, new StringSink(output)));
        std::cout << "\nPlaintext: " << output;
    }


    else //CCM
    {
        CCM< AES >::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);

        StringSource s(input_raw, true, new StreamTransformationFilter(d, new StringSink(output)));
        std::cout << "\nPlaintext: " << output;
    }
}

*/

//để tiến hành đọc file nhanh và dễ tính, mặc định đọc file có sẵn và TH này chỉ xét encrypt

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <time.h>
#include "aes.h"
#include "ccm.h"
#include "cryptlib.h"
#include "files.h"
#include "filters.h"
#include "modes.h"
#include "xts.h"
#include "osrng.h"
#include "hex.h"



using namespace CryptoPP;

SecByteBlock key(AES::DEFAULT_KEYLENGTH);
SecByteBlock iv(AES::BLOCKSIZE);
std::string KIVFile = "kiv.txt";
//std::string filename = "input100MB.txt";
//std::string filename = "input1MB.txt";
std::string filename = "input.txt";

void encrypt_ECB();
void encrypt_CBC();
void encrypt_OFB();
void encrypt_CFB();
void encrypt_CTR();
void encrypt_XTS();
void encrypt_CCM();

void decrypt_ECB();
void decrypt_CBC();
void decrypt_OFB();
void decrypt_CFB();
void decrypt_CTR();
void decrypt_XTS();
void decrypt_CCM();

int main()
{
    clock_t start, end;
    double time;

    start = clock();
    for (int i = 0; i <= 99; i++)
    {
       encrypt_ECB();
    }
    end = clock();
    time = ((double)(end - start)) / (100 * CLOCKS_PER_SEC);
    std::cout << "\nAverage time of ECB mode when encrypt 100 times " << time;


    start = clock();
    for (int i = 0; i <= 99; i++)
    {
        encrypt_CBC();
    }
    end = clock();
    time = ((double)(end - start)) / (100 * CLOCKS_PER_SEC);
    std::cout << "\nAverage time of CBC mode when encrypt 100 times " << time;


    start = clock();
    for (int i = 0; i <= 99; i++)
    {
        encrypt_OFB();
    }
    end = clock();
    time = ((double)(end - start)) / (100 * CLOCKS_PER_SEC);
    std::cout << "\nAverage time of OFB mode when encrypt 100 times " << time;


    start = clock();
    for (int i = 0; i <= 99; i++)
    {
        encrypt_CFB();
    }
    end = clock();
    time = ((double)(end - start)) / (100 * CLOCKS_PER_SEC);
    std::cout << "\nAverage time of CFB mode when encrypt 100 times " << time;


    start = clock();
    for (int i = 0; i <= 99; i++)
    {
        encrypt_CTR();
    }
    end = clock();
    time = ((double)(end - start)) / (100 * CLOCKS_PER_SEC);
    std::cout << "\nAverage time of CTR mode when encrypt 100 times " << time;


    start = clock();
    for (int i = 0; i <= 99; i++)
    {
        encrypt_XTS();
    }
    end = clock();
    time = ((double)(end - start)) / (100 * CLOCKS_PER_SEC);
    std::cout << "\nAverage time of XTS mode when encrypt 100 times " << time;

    start = clock();
    for (int i = 0; i <= 99; i++)
    {
        encrypt_CCM();
    }
    end = clock();
    time = ((double)(end - start)) / (100 * CLOCKS_PER_SEC);
    std::cout << "\nAverage time of CCM mode when encrypt 100 times " << time;
}


void encrypt_ECB()
{
    std::string input, output;
    std::ifstream ifs(filename);
    input.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    prng.GenerateBlock(key, key.size());
    
    ECB_Mode<AES>::Encryption encryptor;
    encryptor.SetKey(key, key.size());

    StringSource s(input, true, new StreamTransformationFilter(encryptor, new StringSink(output)));
}

void encrypt_CBC()
{
    std::string input, output;
    std::ifstream ifs(filename);
    input.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    
    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());
    CBC_Mode<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);

    StringSource s(input, true,new StreamTransformationFilter(encryptor,new StringSink(output)));
}

void encrypt_OFB()
{
    std::string input, output;
    std::ifstream ifs(filename);
    input.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());
    OFB_Mode<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);

    StringSource s(input, true, new StreamTransformationFilter(encryptor, new StringSink(output)));
}

void encrypt_CFB()
{
    std::string input, output;
    std::ifstream ifs(filename);
    input.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());
    CFB_Mode<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);

    StringSource s(input, true, new StreamTransformationFilter(encryptor, new StringSink(output)));
}

void encrypt_CTR()
{
    std::string input, output;
    std::ifstream ifs(filename);
    input.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    byte ctr[AES::BLOCKSIZE];
    prng.GenerateBlock(ctr, sizeof(ctr));

    CTR_Mode<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), ctr);

    StringSource s(input, true, new StreamTransformationFilter(encryptor, new StringSink(output)));
}

void encrypt_XTS()
{
    std::string input, output;
    std::ifstream ifs(filename);
    input.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    SecByteBlock key_XTS(32);
    prng.GenerateBlock(key_XTS, key_XTS.size());

    XTS_Mode<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key_XTS, key_XTS.size(), iv);

    StringSource s(input, true, new StreamTransformationFilter(encryptor, new StringSink(output)));

}

void encrypt_CCM()
{
    std::string input, output;
    std::ifstream ifs(filename);
    input.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    CCM<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), iv);

    StringSource s(input, true, new StreamTransformationFilter(encryptor, new StringSink(output)));

}

void decrypt_ECB()
{

}
void decrypt_CBC()
{

}
void decrypt_OFB()
{

}
void decrypt_CFB()
{

}
void decrypt_CTR()
{

}
void decrypt_XTS()
{

}
void decrypt_CCM()
{

}


