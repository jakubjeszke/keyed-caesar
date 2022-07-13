#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


using namespace std;

const string alphabet("abcdefghijklmnopqrstuvwxyz");        //sta�a zawieraj�ca alfabet, potrzebna do wype�nienia tablicy

const int arraySize = 26;

void moveStringBackwards(string &keyword, int pos)          //funkcja wstawiaj�ca spacj� we wskazanym miejscu ci�gu znak�w i przesuwaj�ca reszt� liter do ty�u
{
    keyword.resize(keyword.length() + 1);
    for (int i = keyword.length() - 1; i >= pos; i--)
    {
        keyword[i + 1] = keyword[i];
    }
    keyword[pos] = ' ';
}

void extendKeyword(string plaintext, string &keyword)       //funkcja rozszerzaj�ca klucz do d�ugo�ci tekstu jawnego
{
    if (keyword.length() >= plaintext.length())
    {
        int kLength = keyword.length();
        for (int i = 0; i < plaintext.length(); i++)        //wstawianie spacji, bez powielania liter (klucz d�u�szy od tekstu jawnego)
        {
            if (plaintext[i] == ' ')
            {
                moveStringBackwards(keyword, i);
            }

        }
        while (keyword.length() != plaintext.length())      //p�tla usuwa nadmiar znak�w z rozszerzonego klucza
        {
            keyword.resize(keyword.length() - 1);
        }
    }
    else
    {
        int kLength = keyword.length();
        int additionalLength = plaintext.length() - keyword.length();
        for (int i = 0; i < additionalLength; i++)          //p�tla powiela klucz, aby dopasowa� go ilo�ci� znak�w do tekstu jawnego
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
        while (keyword.length() > plaintext.length())      //p�tla usuwa nadmiar znak�w z rozszerzonego klucza
        {
            keyword.resize(keyword.length() - 1);
        }
    }
}

void fillArray(char array[arraySize][arraySize])            //funkcja wype�niaj�ca dwuwymiarow� tablic� znak�w
{
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = 0; j < arraySize; j++)
        {
            if(j+i<arraySize)
                array[i][j] = alphabet[j+i];
            else
                array[i][j] = alphabet[j + i-26];
        }
    }
}

int findColumnOrRow(char letter, char array[arraySize][arraySize])  //funkcja odnajduje jedn� ze wsp�rz�dnych liter na tablicy
{
    int i = 0;
    while (letter != array[i][0])
    {
        i++;
    }
    return i;
}

char encryptLetter(char plaintext, char keyword, char array[arraySize][arraySize])  //szyfrowanie pojedynczych liter
{
    int x = findColumnOrRow(plaintext, array);
    int y = findColumnOrRow(keyword, array);
    char encryptedLetter = array[x][y];
    return encryptedLetter;
}

string encryptText(string plaintext, string keyword, char array[arraySize][arraySize])  //szyfrowanie ci�gu znak�w
{
    string encrypted;
    for (int i = 0; i < plaintext.length(); i++)
    {
        if (plaintext[i] == ' ')
        {
            encrypted += ' ';
        }
        else
        {
            encrypted += encryptLetter(plaintext[i], keyword[i], array);
        }
    }
    return encrypted;
}

int main()
{
    ofstream output("encryptedtext.txt");
    ofstream key("key.txt");
    char array[arraySize][arraySize];
    string plaintext, keyword;
    fillArray(array);
    cout << "Enter the phrase you'd like to cypher: ";
    getline(cin, plaintext);                            //getline - mo�liwo�� pobrania wielu wyraz�w
    cout << "Enter key: ";
    cin >> keyword;                                     //cin - pobiera tylko jeden wyraz
    extendKeyword(plaintext, keyword);
    string encryptedText;
    encryptedText = encryptText(plaintext, keyword, array);
    output << encryptedText;
    key << keyword;
    cout << "Ciphered phrase: " << encryptedText << endl;
    system("pause");
    return 0;
}
