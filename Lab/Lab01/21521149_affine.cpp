#include<iostream>
#include<string>
#include<cstring>

using namespace std;



void encrypt(string text, int a, int b)
{
    char alphabet[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    char alphabet1[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    string output = text;
    for (int j = 0; j < text.length(); j++)
    {
        for (int i = 0; i < 26; i++)
        {
            if (text[j] == alphabet[i])
            {
                output[j] = alphabet[abs(a * i + b) % 26];
                break;
            }
            else if (text[j] == alphabet1[i])
            {
                output[j] = alphabet1[abs(a * i + b) % 26];
                break;
            }
        }
    }
    cout << "\nCiphertext: " << output;
}



void decrypt(string text, int a, int b)
{
    char alphabet[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    char alphabet1[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    int modulDN = 0, check = 0;
    string output = text;

    for (int i = 0; i <= 25; i++)//tìm modul đảo nghịch của a
    {
        check = (a * i) % 26;
        if (check == 1)
        {
            modulDN = i;
        }
    }
    
    for (int j = 0; j < text.length(); j++)
    {
        for (int i = 0; i < 26; i++)
        {
            if (text[j] == alphabet[i])
            {
                output[j] = alphabet[abs(modulDN * (i - b + 26))% 26];
                break;
            }
            else if (text[j] == alphabet1[i])
            {
                output[j] = alphabet1[abs(modulDN * (i - b + 26)) % 26];
                break;
            }
        }
    }
    cout << "\nPlaintext: " << output;
}


int main()
{
    string text;
    int choice, a, b;
    cout << "Input text: ";
    getline(cin, text);
    cout << "\nInput key (a, b): ";
    cin >> a;
    cin >> b;
    cout << "\nSelect (1) encrypt / (2) decrypt\n";
    cin >> choice;
    if (choice == 1)
    {
        encrypt(text, a, b);
    }
    else if (choice == 2)
    {
        decrypt(text, a, b);
    }
}