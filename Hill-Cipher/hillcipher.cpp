#include <iostream>
#include <string>
#include <array>

using namespace std;

#define SIZEOF(arr) sizeof(arr) / sizeof(arr[0])

int gcd(int a, int b)
{
	while (b != 0)
	{
		int tmp = a;
		a = b;
		b = tmp % b;
	}
	return a;
}

int modInverse(int a, int b)
{
	int result = 1;

	while (result % a != 0)
	{
		result += b;
	}

	result /= a;

	return result;
}

std::array<std::array<int, 2>, 2> createKey(size_t matrixSize)
{
	std::array<std::array<int, 2>, 2> createdKey;
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			cout << "input " << i << ", " << j << " element: ";
			cin >> createdKey[i][j];
			cout << endl;
		}
	}
	return createdKey;
}

int determinant(std::array<std::array<int, 2>, 2> matrix)
{
	return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
}

std::array<std::array<int, 2>, 2> adjoin(std::array<std::array<int, 2>, 2> matrix)
{
	int temp;
	matrix[0][1] = -1 * matrix[0][1];
	matrix[1][0] = -1 * matrix[1][0];

	temp = matrix[0][0];
	matrix[0][0] = matrix[1][1];
	matrix[1][1] = temp;
	return matrix;
}

std::array<std::array<int, 2>, 2> inverseMatrix(std::array<std::array<int, 2>, 2> matrix)
{
	std::array<std::array<int, 2>, 2> inversed;
	size_t matrixSize = SIZEOF(matrix);

	const int D = modInverse(determinant(matrix), 26);
	std::array<std::array<int, 2>, 2> adjMatrix;
	adjMatrix = adjoin(matrix);

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			inversed[i][j] = (adjMatrix[i][j] * D) % 26;
			if (inversed[i][j] < 0)
			{
				inversed[i][j] += 26;
			}
		}
	}
	return inversed;
}

string encryption(string plainText, std::array<std::array<int, 2>, 2> key, size_t matrixSize)
{
	int initStrLength;
	string cipherText;
	int temp;
	int textIndex = 0;

	initStrLength = plainText.length();

	if (plainText.length() % matrixSize != 0)
	{
		plainText += 'x';
	}

	while (textIndex < plainText.length())
	{
		for (int i = 0; i < matrixSize; i++)
		{
			temp = 0;
			for (int j = 0; j < matrixSize; j++)
			{
				temp += key[i][j] * (plainText[textIndex + j] - 'a') % 26;
				temp = temp % 26;
			}

			cipherText += char(temp + 'a');
		}
		textIndex += 2;
	}

	if (initStrLength % 2 != 0)
	{
		cipherText.pop_back();
	}

	return cipherText;
}

string decryption(string cipherText, std::array<std::array<int, 2>, 2> key, size_t matrixSize)
{
	if ((gcd(determinant(key), 26) + 26) % 2 != 1)
	{
		return "matrix not inversible";
	}

	std::array<std::array<int, 2>, 2> inversed = inverseMatrix(key);

	int initStrLength;
	string plainText;
	int temp;
	int textIndex = 0;

	initStrLength = cipherText.length();

	if (cipherText.length() % matrixSize != 0)
	{
		cipherText += 'x';
	}

	while (textIndex < cipherText.length())
	{
		for (int i = 0; i < matrixSize; i++)
		{
			temp = 0;
			for (int j = 0; j < matrixSize; j++)
			{
				temp += inversed[i][j] * (cipherText[textIndex + j] - 'a') % 26;
				temp = temp % 26;
			}

			plainText += char(temp + 'a');
		}
		textIndex += 2;
	}

	if (initStrLength % 2 != 0)
	{
		plainText.pop_back();
	}

	return plainText;
}

std::array<std::array<int, 2>, 2> findKey(string plainText, string cipherText, size_t matrixSize)
{
	std::array<std::array<int, 2>, 2> plainM, cipherM;
	std::array<std::array<int, 2>, 2> resultM = {{{0, 0}, {0, 0}}};
	int textIndex = 0;

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			plainM[j][i] = plainText[textIndex + j] - 'a';
			cipherM[j][i] = cipherText[textIndex + j] - 'a';
		}
		cout << endl;
		textIndex += 2;
	}
	if ((gcd(determinant(plainM), 26) + 26) % 2 != 1)
	{
		cout << "matrix not inversible" << endl;
		return resultM;
	}
	plainM = inverseMatrix(plainM);

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			resultM[i][j] = 0;
			for (int k = 0; k < matrixSize; k++)
			{
				resultM[i][j] += cipherM[i][k] * plainM[k][j];
			}
			resultM[i][j] = (resultM[i][j] + 26) % 26;
		}
	}
	return resultM;
}

int main()
{
	std::array<std::array<int, 2>, 2> key = {{{7, 8}, {19, 3}}};
	std::array<std::array<int, 2>, 2> newKey;
	size_t matrixSize = SIZEOF(key);
	char choice;
	string text;

	while (true)
	{
		cout << "1. Encrypt" << endl;
		cout << "2. Decrypt" << endl;
		cout << "3. Find Key" << endl;
		cout << "4. Exit" << endl;
		cout << "Please chose action (1/2/3)" << endl;
		cin >> choice;
		cin.ignore();
		if (choice == '4')
		{
			cout << "BYE BYE";
			break;
		}
		else if (choice == '2')
		{
			cout << "Input text: " << endl;
			cin >> text;
			cout << "Input key: " << endl;
			key = createKey(matrixSize);

			cout << "hasil dekripsi : " << decryption(text, key, matrixSize) << endl;
		}
		else if (choice == '1')
		{
			cout << "Input text: " << endl;
			cin >> text;
			cout << "Input key: " << endl;
			key = createKey(matrixSize);

			cout << "hasil enkripsi : " << encryption(text, key, matrixSize) << endl;
		}
		else if (choice == '3')
		{
			string text2;
			cout << "Input plainText: " << endl;
			cin >> text;

			cout << "Input cipherText: " << endl;
			cin >> text2;

			key = findKey(text, text2, matrixSize);
			cout << "kunci cipher adalah : " << endl;
			for (int i = 0; i < matrixSize; i++)
			{
				for (int j = 0; j < matrixSize; j++)
				{
					cout << key[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		else
		{
			cout << "Input tidak ada di pilihan" << endl;
		}
	}
}