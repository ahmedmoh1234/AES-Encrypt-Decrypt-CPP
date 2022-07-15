#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int BUFF_SIZE = 16;

inline string readFileName() ;

inline void encryption();
inline void decryption();

//What will happen if the file size is smaller than 128 bits ??

int main()
{
	//Ask the user whether they want to encrypt or decrypt

	int encDecChoice;
	cout << "Enter 1 to ecrypt\n";
	cout << "Enter 2 to decrypt\n";
	cin >> encDecChoice;
	
	while (encDecChoice != 1 && encDecChoice != 2)
	{
		cout << "Wrong choice please enter a correct choice\n";
		cin >> encDecChoice;
	}

	if (encDecChoice == 1)
	{
		encryption();
	}
	else
	{
		decryption();
	}

	



	return 0;
}

inline string readFileName()
{
	string fileNameTemp;
	cout << "Please input filename/path : ";
	cin >> fileNameTemp;
	cout << "\n";

	if (fileNameTemp[0] == '"')
		fileNameTemp.erase(0, 1);
	if (fileNameTemp[fileNameTemp.size()-1] == '"')
		fileNameTemp.erase(fileNameTemp.size() - 1, 1);


	return std::move(fileNameTemp);

}

inline void encryption()
{
	//Ask the user whether to generate a random key or to enter a key

	//The choice of the user
	int keyChoice;

	//The key that will be used in encryption
	vector<char> key;
	cout << "Enter 1 to generate a key randomly\n";
	cout << "Enter 2 to enter a key manually\n";
	cin >> keyChoice;

	while (keyChoice != 1 && keyChoice != 2)
	{
		cout << "Wrong choice please enter a correct choice\n";
		cin >> keyChoice;
	}

	if (keyChoice == 1)
	{
		//Random key
		//Random key will have 3 options
		//1- 128-bit key
		//2- 192-bit key
		//3- 256-bit key

	}
	else
	{
		//Key entered manually
		//Ask the user to enter the size of the key
		//128 bits -> 16 characters
		//192 bits -> 24 characters
		//256 bits -> 32 characters

		//I did not use a hash function because I want to implement the standart algorithm so any AES decryptor can decrypt it.
	}
	


	//Reading 128 bits from file
	char buff[BUFF_SIZE];


	string fileName = readFileName();


	ifstream inputFile(fileName, ios::binary);

	while (!inputFile.is_open())
	{
		cout << "Could not open file. ";
		fileName = readFileName();

		inputFile.open(fileName, ios::binary);
	}
	cout << "File opened successfully\n";



	if (!inputFile.read(buff, BUFF_SIZE))
	{
		//There was an error reading 16 bytes

		//check the number of bytes actually read
		int readBytesCount = inputFile.gcount();
		for (int i = 0; i < readBytesCount; i++)
		{
			cout << buff[i] << " ";
		}
	}
	else
	{
		//16 bytes were read no problem
		for (int i = 0; i < BUFF_SIZE; i++)
		{
			cout << buff[i] << " ";
		}
	}
}

inline void decryption()
{
}
