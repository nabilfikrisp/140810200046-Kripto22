/*
    Affine Cipher
    Muhammad Nabil Fikri Sudjarpadi Putra
    140810200046
    Praktikum Kriptografi
*/

#include <iostream>
#include <windows.h>
#include <algorithm>
#include <string>
using namespace std;

string encrypt(string text, int key)
{

  string encrypted;
  for (int i = 0; i < text.length(); ++i)
  {
    if (text[i] >= 'a' && text[i] <= 'z')
    {
      encrypted += char(int(text[i] - 'a' + key) % 26 + 'a');
    }
    else if (text[i] >= 'A' && text[i] <= 'Z')
    {
      encrypted += char(int(text[i] - 'A' + key) % 26 + 'A');
    }
    else
    {
      encrypted += text[i];
    }
  }
  return encrypted;
}

string decrypt(string text, int key)
{

  string decrypted;
  for (int i = 0; i < text.length(); ++i)
  {
    if (text[i] >= 'a' && text[i] <= 'z')
    {
      decrypted += char(int(text[i] - 'a' - key) % 26 + 'a');
    }
    else if (text[i] >= 'A' && text[i] <= 'Z')
    {
      decrypted += char(int(text[i] - 'A' - key) % 26 + 'A');
    }
    else
    {
      decrypted += text[i];
    }
  }
  return decrypted;
}

int main()
{
  char choice;
  int key1;
  int key2;
  string text;
  while (true)
  {
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "3. Exit" << endl;
    cout << "Please chose action (1/2/3)" << endl;
    cin >> choice;
    cin.ignore();
    if (choice == '3')
    {
      cout << "BYE BYE";
      break;
    }
    else if (choice == '2')
    {
      cout << "Input text: " << endl;
      getline(cin, text);
      cout << "Input key: ";
      cin >> key1;

      cout << "Plain text: " << decrypt(text, key1) << endl
           << endl;
    }
    else if (choice == '1')
    {
      cout << "Input text: " << endl;
      getline(cin, text);
      cout << "Input key: ";
      cin >> key1;

      cout << "Cipher text: " << encrypt(text, key1) << endl
           << endl;
    }
    else
    {
      cout << "Input tidak ada di pilihan" << endl;
    }
  }
}