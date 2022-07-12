#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int BUFF_SIZE = 16;

inline string readFileName() ;

int main()
{
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