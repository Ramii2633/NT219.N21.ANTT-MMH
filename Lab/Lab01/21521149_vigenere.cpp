#include<iostream>
#include<string>

using namespace std;

void createNewKey(string text, string key, string& newkey) //tạo key mới có độ dài bằng độ dài text bằng cách lặp lại key
{
	int i, j;
	for (i = 0, j = 0; i < text.length(); i++, j++)
	{
        if (((text[i]>='A') && (text[i]<='Z'))|| ((text[i] >= 'a') && (text[i] <= 'z')))//nếu ký tự là chữ thì lặp lại trong key mới, còn không giữ nguyên
        {
            if (j == key.length())
                j = 0; //khi j = độ dài chuỗi key, lặp lại key trong chuỗi mới
            newkey[i] = key[j];
        }
        else
        {
            j--;
        }
	}
}

void CHUIN(string& text) //chuyển tất cả kí tự trong text về chữ in hoa
{
    for (int i = 0; i < text.length(); i++)
    {
        text[i] = toupper(text[i]);
    }
}

void encrypt(string text, string key)
{
    char alphabet[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    string output = text;

    for (int j = 0; j < text.length(); j++)
    {
        for (int i = 0; i < 26; i++)
        {
            if (text[j] == alphabet[i])
            {
                output[j] = alphabet[abs(text[j]+key[j]) % 26];
                break;
            }
        }
    }
    cout << "\nCiphertext: " << output;
}

void decrypt(string text, string key)
{
    char alphabet[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    string output = text;

    for (int j = 0; j < text.length(); j++)
    {
        for (int i = 0; i < 26; i++)
        {
            if (text[j] == alphabet[i])
            {
                output[j] = alphabet[abs(text[j] - key[j] + 26) % 26];
                break;
            }
        }
    }
    cout << "\nPlaintext: " << output;
}

int main()
{
    string text, key, newkey;
    int choice;
    cout << "Input text: ";
    getline(cin, text);
    newkey = text;
    cout << "\nKey: ";
    getline(cin, key);
    CHUIN(text);
    CHUIN(key);
    createNewKey(text, key, newkey);
    cout << "\nNew key: " << newkey << endl;
    cout << "\nSelect (1) encrypt / (2) decrypt\n";
    cin >> choice;
    if (choice == 1)
        encrypt(text, newkey);
    else if (choice == 2)
        decrypt(text, newkey);
}