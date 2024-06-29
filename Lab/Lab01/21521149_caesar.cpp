#include<iostream>
#include<string>
#include<cstring>

using namespace std;

void encrypt(string text, int key) //ma hoa voi key
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
                output[j] = alphabet[abs(i + key) % 26];
                break;
            }
            else if (text[j] == alphabet1[i])
            {
                output[j] = alphabet1[abs(i + key) % 26];
                break;
            }
        }
    }
    cout << "\nCiphertext: " << output;
}



void decrypt(string text, int key) //giai ma voi key
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
                output[j] = alphabet[abs(i - key + 26) % 26];
                break;
            }
            else if (text[j] == alphabet1[i])
            {
                output[j] = alphabet1[abs(i - key + 26) % 26];
                break;
            }
        }
    }
    cout << "\nPlaintext: " << output;
}





void decrypt(string text) //giai ma brute-force
{
    char alphabet[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    char alphabet1[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    string output = text;
    for (int k = 0; k <= 25; k++)
    {
        for (int j = 0; j < text.length(); j++)
        {
            for (int i = 0; i < 26; i++)
            {
                if (text[j] == alphabet[i])
                {
                    output[j] = alphabet[abs(i - k + 26) % 26];
                    break;
                }
                else if (text[j] == alphabet1[i])
                {
                    output[j] = alphabet1[abs(i - k + 26) % 26];
                    break;
                }
            }
        }
        cout << "\nPlaintext with key = " << k << " : " << output<<endl;
    }
}
           

int main()
{
    string text;
    int key, choice;
    cout << "Input text: ";
    getline(cin, text);
    cout << "\nSelect (1) encrypt / (2) decrypt\n";
    cin >> choice;
    if (choice == 1)
    {
        cout << "\nInput key: ";
        cin >> key;
        encrypt(text, key);
    }
    else if (choice == 2)
    {
        int choice2;
        cout << "\nSelect (1) decrypt with key  / (2) decrypt brute-force\n";
        cin >> choice2;
        if (choice2 == 1)
        {
            cout << "\nInput key: ";
            cin >> key; 
            decrypt(text, key);
        }
        else if (choice2 == 2)
            decrypt(text);
    }
}