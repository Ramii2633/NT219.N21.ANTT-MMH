#include<iostream>
#include<cstring>
#include<string>

using namespace std;


char keyMatrix[5][5];   //tạo ma trận khoá

void changeText(string& text) 
{
    for (int i = 0; i < text.length(); i++)
    {
        text[i] = toupper(text[i]);  //chuyển tất cả kí tự trong text về chữ in hoa
    }
    int i, count = 0;
    for (i = 0; i < text.length(); i++)
    {
        if ((text[i] >= 'A') && (text[i] <= 'Z'))
        {
            text[count++] = text[i];
            count;
        }
        else //xoá các ký tự không là chữ
        {
            text.erase(text.begin() + i);
            i--;
        }
    }
}


void createKeyMatrix(string key, char keyMatrix[5][5])
{
    int flag[26] = {}; //tạo mảng để đánh dấu sự xuất hiện của ký tự, mặc định = 0
    int row = 0, col = 0;
    for (int i = 0; i < key.length(); i++) //thêm các chữ trong key vào ma trận trước
    {
        if (key[i] == 'J') //vì lược bỏ J, I/J ở cùng 1 ô nên các vị trí có j sẽ được thay bằng i
            key[i] = 'I';
        if (flag[key[i] - 'A'] == 0) //thêm kí tự chưa có vào ma trận và bật cờ của chữ cái đó
        {
            flag[key[i] - 'A'] = 1;
            keyMatrix[row][col++] = key[i];
        }
        if (col == 5)//hêt hàng xuống hàng mới
        {
            row++;
            col= 0;
        }
    }
    for (char c='A'; c <= 'Z'; c++) //thêm các chữ cái trong bảng chữ cái vào ma trận
    {
        if (c == 'J') //vì lược bỏ J
            continue;
        if (flag[c - 'A'] == 0) //thêm kí tự chưa có vào ma trận và bật cờ của chữ cái đó
        {
            flag[c - 'A'] = 1;
            keyMatrix[row][col++] = c;
        }
        if (col == 5)//hêt hàng xuống hàng mới
        {
            row++;
            col = 0;
        }
    }

}


typedef struct //khai bao cau truc vi tri (hàng, cột) cua chu cai
{
    int row;
    int column;
} pos;

pos getPosition(char c)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (c == keyMatrix[i][j])
            {
                pos position = { i, j };
                return position;
            }
        }
    }
}

void handleText(string& text)
{

    for (int i = 0; i < text.length(); i++) // thay J bằng I
    {
        if (text[i] == 'J')
            text[i] = 'I';
    }
    for (int j = 1; j < text.length(); j = j + 2) // biến đổi text theo 2 ý đầu của thuận toán mã hoá
    {
        if (text[j] == text[j - 1])
            text.insert(text.begin() + j, 'X');
    }
    if (text.length() % 2 == 1) //nếu chuỗi lẻ, thêm ký tự X
        text = text + 'X';
}


void encrypt(string text)
{
    string output = "";
    for (int i = 0; i < text.length(); i += 2)
    {
        //lấy vị trí của 2 ký tự kề nhau
        pos p1 = getPosition(text[i]);
        pos p2 = getPosition(text[i + 1]);
        int x1 = p1.row; int y1 = p1.column;
        int x2 = p2.row; int y2 = p2.column;

        if (x1 == x2) // cùng hàng dịch phải 1, mod 5 nếu quá vòng
        {
            output = output + keyMatrix[x1][(y1 + 1) % 5];
            output = output + keyMatrix[x2][(y2 + 1) % 5];
        }
        else if (y1 == y2) // cùng cột dịch xuống 1, mod 5 nếu quá vòng
        {
            output = output + keyMatrix[(x1 + 1) % 5][y1];
            output = output + keyMatrix[(x2 + 1) % 5][y2];
        }
        else //khác, đổi cột
        {
            output = output + keyMatrix[x1][y2];
            output = output + keyMatrix[x2][y1];
        }
    }
    cout << "\nCiphertext: " << output;
}



void decrypt(string text)
{
    string output = "";
    for (int i = 0; i < text.length(); i += 2)
    {
        //lấy vị trí của 2 ký tự kề nhau
        pos p1 = getPosition(text[i]);
        pos p2 = getPosition(text[i + 1]);
        int x1 = p1.row; int y1 = p1.column;
        int x2 = p2.row; int y2 = p2.column;

        if (x1 == x2) // cùng hàng dịch phải 1, mod 5 nếu quá vòng
        {
            output = output + keyMatrix[x1][abs(y1 - 1 + 5) % 5];
            output = output + keyMatrix[x2][abs(y2 - 1 + 5) % 5];
        }
        else if (y1 == y2) // cùng cột dịch xuống 1, mod 5 nếu quá vòng
        {
            output = output + keyMatrix[abs(x1 - 1 + 5) % 5][y1];
            output = output + keyMatrix[abs(x2 - 1 + 5) % 5][y2];
        }
        else //khác, đổi cột
        {
            output = output + keyMatrix[x1][y2];
            output = output + keyMatrix[x2][y1];
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
    changeText(text);
    cout << "\nKey: ";
    getline(cin, key);
    changeText(key);
    createKeyMatrix(key, keyMatrix);
    cout << "\nKey matrix: " << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << keyMatrix[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "\nSelect (1) encrypt / (2) decrypt\n";
    cin >> choice;
    if (choice == 1)
    {
        handleText(text);
        encrypt(text);
    }
    else if (choice == 2)
        decrypt(text);
}
