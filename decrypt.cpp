#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

const string alphabet("abcdefghijklmnopqrstuvwxyz");        //sta³a zawieraj¹ca alfabet, potrzebna do wype³nienia tablicy

const int arraySize = 26;

void moveStringBackwards(string &keyword, int pos)          //funkcja wstawiaj¹ca spacjê we wskazanym miejscu ci¹gu znaków i przesuwaj¹ca resztê liter do ty³u
{
    keyword.resize(keyword.length() + 1);
    for (int i = keyword.length() - 1; i >= pos; i--)
    {
        keyword[i + 1] = keyword[i];
    }
    keyword[pos] = ' ';
}

void fillArray(char arrayy[arraySize][arraySize])            //funkcja wype³niaj¹ca dwuwymiarow¹ tablicê znaków
{
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = 0; j < arraySize; j++)
        {
            if(j+i<arraySize)
                arrayy[i][j] = alphabet[j+i];
            else
                arrayy[i][j] = alphabet[j + i-26];
        }
    }
}

int findColumnOrRow(char letter, char array[arraySize][arraySize])  //funkcja odnajduje jedn¹ ze wspó³rzêdnych liter na tablicy
{
    int i = 0;
    while (letter != array[i][0])
    {
        i++;
    }
    return i;
}

void extendKeyword(string plaintext, string &keyword)       //funkcja rozszerzaj¹ca klucz do d³ugoœci tekstu jawnego
{
    if (keyword.length() >= plaintext.length())
    {
        int kLength = keyword.length();
        for (int i = 0; i < plaintext.length(); i++)        //wstawianie spacji, bez powielania liter (klucz d³u¿szy od tekstu jawnego)
        {
            if (plaintext[i] == ' ')
            {
                moveStringBackwards(keyword, i);
            }

        }
        while (keyword.length() != plaintext.length())      //pêtla usuwa nadmiar znaków z rozszerzonego klucza
        {
            keyword.resize(keyword.length() - 1);
        }
    }
    else
    {
        int kLength = keyword.length();
        int additionalLength = plaintext.length() - keyword.length();
        for (int i = 0; i < additionalLength; i++)          //pêtla powiela klucz, aby dopasowaæ go iloœci¹ znaków do tekstu jawnego
        {
            keyword.resize(keyword.length() + 1);
            keyword[kLength + i] = keyword[i];
        }
        for (int i = 0; i < plaintext.length(); i++)
        {
            if (plaintext[i] == ' ')
            {
                moveStringBackwards(keyword, i);
            }
        }
        while (keyword.length() > plaintext.length())      //pêtla usuwa nadmiar znaków z rozszerzonego klucza
        {
            keyword.resize(keyword.length() - 1);
        }
    }
}

char decryptLetter(char cryptogram, char keyword, char array[arraySize][arraySize])     //odszyfrowywanie litery kryptogramu
{
    int y = findColumnOrRow(keyword, array);
    int i=0;
    while (cryptogram != array[i][y] )
    {
        i++;
    }
    int x = i;
    return array[x][0];
}

string decryptText(string cryptogram, string keyword, char array[arraySize][arraySize]) //odszyfrowywanie ci¹gu znaków
{
    string decrypted;
    for (int i = 0; i < cryptogram.length(); i++)
    {
        if (cryptogram[i] == ' ')
        {
            decrypted += ' ';
        }
        else
        {
            decrypted += decryptLetter(cryptogram[i], keyword[i], array);
        }
    }
    return decrypted;
}

int main()
{
    ifstream input("encryptedtext.txt");
    ifstream key("key.txt");
    char arrayy[arraySize][arraySize];
    string encryptedText, keyword, decryptedText;
    input >> encryptedText;
    key >> keyword;
    extendKeyword(encryptedText, keyword);
    fillArray(arrayy);
    decryptedText = decryptText(encryptedText, keyword, arrayy);
    cout << "Deciphered phrase: " << decryptedText << endl;
    system("pause");
    return 0;

}
