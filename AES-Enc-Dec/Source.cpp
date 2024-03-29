#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;
using Word = vector<unsigned char>;
using subMap = unordered_map<unsigned char, unsigned char>;





template <class T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		os << hex << static_cast<int>(vec[i]) << " ";
	}
	os << "\n";

	return os;
}

template <>
ostream& operator<< <Word>(ostream& os, const vector<Word>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		for (size_t j = 0; j < vec[i].size(); j++)
		{
			os << hex << static_cast<int>(vec[i][j]) << " ";
		}
		os << "\n";
	}
	os << "\n";
	return os;
}

Word operator^ (const Word& w1, const Word& w2)
{
	Word temp;
	if (w1.size() != w2.size())
		return temp;
	for (size_t i = 0; i < w1.size(); i++)
	{
		//cout << "w1 = " << static_cast<int>(w1[i]) << " w2 = " << static_cast<int>(w2[i]) << "\n";
		temp.push_back(w1[i] ^ w2[i]);
	}
	return temp;
}

const int BUFF_SIZE = 16;
const int ROWS = 4;
const int COLS = 4;
const int NB = 4;
int NR;
int NK;		//no. of columns of the key. The column consists of 4 bytes

const subMap subBytes{
	{0x0,0x63}	,{0x1, 0x7c}	,{0x2, 0x77},{0x3, 0x7b},{0x4, 0xf2},{0x5, 0x6b},{0x6, 0x6f},{0x7, 0xc5},
	{0x8, 0x30}	,{0x9, 0x01}	,{0xa, 0x67},{0xb, 0x2b},{0xc, 0xfe},{0xd, 0xd7},{0xe, 0xab},{0xf, 0x76},
	{0x10, 0xca},{0x11, 0x82}	,{0x12, 0xc9},{0x13, 0x7d},{0x14, 0xfa},{0x15, 0x59},{0x16, 0x47},{0x17, 0xf0},
	{0x18, 0xad},{0x19, 0xd4}	,{0x1a, 0xa2},{0x1b, 0xaf},{0x1c, 0x9c},{0x1d, 0xa4},{0x1e, 0x72},{0x1f, 0xc0},
	{0x20, 0xb7},{0x21, 0xfd}	,{0x22, 0x93},{0x23, 0x26},{0x24, 0x36},{0x25, 0x3f},{0x26, 0xf7},{0x27, 0xcc},
	{0x28, 0x34},{0x29, 0xa5}	,{0x2a, 0xe5},{0x2b, 0xf1},{0x2c, 0x71},{0x2d, 0xd8},{0x2e, 0x31},{0x2f, 0x15},
	{0x30, 0x04},{0x31, 0xc7}	,{0x32, 0x23},{0x33, 0xc3},{0x34, 0x18},{0x35, 0x96},{0x36, 0x05},{0x37, 0x9a},
	{0x38, 0x07},{0x39, 0x12}	,{0x3a, 0x80},{0x3b, 0xe2},{0x3c, 0xeb},{0x3d, 0x27},{0x3e, 0xb2},{0x3f, 0x75},
	{0x40, 0x09},{0x41, 0x83}	,{0x42, 0x2c},{0x43, 0x1a},{0x44, 0x1b},{0x45, 0x6e},{0x46, 0x5a},{0x47, 0xa0},
	{0x48, 0x52},{0x49, 0x3b}	,{0x4a, 0xd6},{0x4b, 0xb3},{0x4c, 0x29},{0x4d, 0xe3},{0x4e, 0x2f},{0x4f, 0x84},
	{0x50, 0x53},{0x51, 0xd1}	,{0x52, 0x00},{0x53, 0xed},{0x54, 0x20},{0x55, 0xfc},{0x56, 0xb1},{0x57, 0x5b},
	{0x58, 0x6a},{0x59, 0xcb}	,{0x5a, 0xbe},{0x5b, 0x39},{0x5c, 0x4a},{0x5d, 0x4c},{0x5e, 0x58},{0x5f, 0xcf},
	{0x60, 0xd0},{0x61, 0xef}	,{0x62, 0xaa},{0x63, 0xfb},{0x64, 0x43},{0x65, 0x4d},{0x66, 0x33},{0x67, 0x85},
	{0x68, 0x45},{0x69, 0xf9}	,{0x6a, 0x02},{0x6b, 0x7f},{0x6c, 0x50},{0x6d, 0x3c},{0x6e, 0x9f},{0x6f, 0xa8},
	{0x70, 0x51},{0x71, 0xa3}	,{0x72, 0x40},{0x73, 0x8f},{0x74, 0x92},{0x75, 0x9d},{0x76, 0x38},{0x77, 0xf5},
	{0x78, 0xbc},{0x79, 0xb6}	,{0x7a, 0xda},{0x7b, 0x21},{0x7c, 0x10},{0x7d, 0xff},{0x7e, 0xf3},{0x7f, 0xd2},
	{0x80, 0xcd},{0x81, 0x0c}	,{0x82, 0x13},{0x83, 0xec},{0x84, 0x5f},{0x85, 0x97},{0x86, 0x44},{0x87, 0x17},
	{0x88, 0xc4},{0x89, 0xa7}	,{0x8a, 0x7e},{0x8b, 0x3d},{0x8c, 0x64},{0x8d, 0x5d},{0x8e, 0x19},{0x8f, 0x73},
	{0x90, 0x60},{0x91, 0x81}	,{0x92, 0x4f},{0x93, 0xdc},{0x94, 0x22},{0x95, 0x2a},{0x96, 0x90},{0x97, 0x88},
	{0x98, 0x46},{0x99, 0xee}	,{0x9a, 0xb8},{0x9b, 0x14},{0x9c, 0xde},{0x9d, 0x5e},{0x9e, 0x0b},{0x9f, 0xdb},
	{0xa0, 0xe0},{0xa1, 0x32}	,{0xa2, 0x3a},{0xa3, 0x0a},{0xa4, 0x49},{0xa5, 0x06},{0xa6, 0x24},{0xa7, 0x5c},
	{0xa8, 0xc2},{0xa9, 0xd3}	,{0xaa, 0xac},{0xab, 0x62},{0xac, 0x91},{0xad, 0x95},{0xae, 0xe4},{0xaf, 0x79},
	{0xb0, 0xe7},{0xb1, 0xc8}	,{0xb2, 0x37},{0xb3, 0x6d},{0xb4, 0x8d},{0xb5, 0xd5},{0xb6, 0x4e},{0xb7, 0xa9},
	{0xb8, 0x6c},{0xb9, 0x56}	,{0xba, 0xf4},{0xbb, 0xea},{0xbc, 0x65},{0xbd, 0x7a},{0xbe, 0xae},{0xbf, 0x08},
	{0xc0, 0xba},{0xc1, 0x78}	,{0xc2, 0x25},{0xc3, 0x2e},{0xc4, 0x1c},{0xc5, 0xa6},{0xc6, 0xb4},{0xc7, 0xc6},
	{0xc8, 0xe8},{0xc9, 0xdd}	,{0xca, 0x74},{0xcb, 0x1f},{0xcc, 0x4b},{0xcd, 0xbd},{0xce, 0x8b},{0xcf, 0x8a},
	{0xd0, 0x70},{0xd1, 0x3e}	,{0xd2, 0xb5},{0xd3, 0x66},{0xd4, 0x48},{0xd5, 0x03},{0xd6, 0xf6},{0xd7, 0x0e},
	{0xd8, 0x61},{0xd9, 0x35}	,{0xda, 0x57},{0xdb, 0xb9},{0xdc, 0x86},{0xdd, 0xc1},{0xde, 0x1d},{0xdf, 0x9e},
	{0xe0, 0xe1},{0xe1, 0xf8}	,{0xe2, 0x98},{0xe3, 0x11},{0xe4, 0x69},{0xe5, 0xd9},{0xe6, 0x8e},{0xe7, 0x94},
	{0xe8, 0x9b},{0xe9, 0x1e}	,{0xea, 0x87},{0xeb, 0xe9},{0xec, 0xce},{0xed, 0x55},{0xee, 0x28},{0xef, 0xdf},
	{0xf0, 0x8c},{0xf1, 0xa1}	,{0xf2, 0x89},{0xf3, 0x0d},{0xf4, 0xbf},{0xf5, 0xe6},{0xf6, 0x42},{0xf7, 0x68},
	{0xf8, 0x41},{0xf9, 0x99}	,{0xfa, 0x2d},{0xfb, 0x0f},{0xfc, 0xb0},{0xfd, 0x54},{0xfe, 0xbb},{0xff, 0x16}
};

const vector<unsigned char> galoisMulBy2
{
	0x00,0x02,0x04,0x06,0x08,0x0a,0x0c,0x0e,0x10,0x12,0x14,0x16,0x18,0x1a,0x1c,0x1e,
0x20,0x22,0x24,0x26,0x28,0x2a,0x2c,0x2e,0x30,0x32,0x34,0x36,0x38,0x3a,0x3c,0x3e,
0x40,0x42,0x44,0x46,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x5a,0x5c,0x5e,
0x60,0x62,0x64,0x66,0x68,0x6a,0x6c,0x6e,0x70,0x72,0x74,0x76,0x78,0x7a,0x7c,0x7e,
0x80,0x82,0x84,0x86,0x88,0x8a,0x8c,0x8e,0x90,0x92,0x94,0x96,0x98,0x9a,0x9c,0x9e,
0xa0,0xa2,0xa4,0xa6,0xa8,0xaa,0xac,0xae,0xb0,0xb2,0xb4,0xb6,0xb8,0xba,0xbc,0xbe,
0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,0xce,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,0xdc,0xde,
0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xee,0xf0,0xf2,0xf4,0xf6,0xf8,0xfa,0xfc,0xfe,
0x1b,0x19,0x1f,0x1d,0x13,0x11,0x17,0x15,0x0b,0x09,0x0f,0x0d,0x03,0x01,0x07,0x05,
0x3b,0x39,0x3f,0x3d,0x33,0x31,0x37,0x35,0x2b,0x29,0x2f,0x2d,0x23,0x21,0x27,0x25,
0x5b,0x59,0x5f,0x5d,0x53,0x51,0x57,0x55,0x4b,0x49,0x4f,0x4d,0x43,0x41,0x47,0x45,
0x7b,0x79,0x7f,0x7d,0x73,0x71,0x77,0x75,0x6b,0x69,0x6f,0x6d,0x63,0x61,0x67,0x65,
0x9b,0x99,0x9f,0x9d,0x93,0x91,0x97,0x95,0x8b,0x89,0x8f,0x8d,0x83,0x81,0x87,0x85,
0xbb,0xb9,0xbf,0xbd,0xb3,0xb1,0xb7,0xb5,0xab,0xa9,0xaf,0xad,0xa3,0xa1,0xa7,0xa5,
0xdb,0xd9,0xdf,0xdd,0xd3,0xd1,0xd7,0xd5,0xcb,0xc9,0xcf,0xcd,0xc3,0xc1,0xc7,0xc5,
0xfb,0xf9,0xff,0xfd,0xf3,0xf1,0xf7,0xf5,0xeb,0xe9,0xef,0xed,0xe3,0xe1,0xe7,0xe5
};

const vector<unsigned char> galoisMulBy3{
	0x00,0x03,0x06,0x05,0x0c,0x0f,0x0a,0x09,0x18,0x1b,0x1e,0x1d,0x14,0x17,0x12,0x11,
0x30,0x33,0x36,0x35,0x3c,0x3f,0x3a,0x39,0x28,0x2b,0x2e,0x2d,0x24,0x27,0x22,0x21,
0x60,0x63,0x66,0x65,0x6c,0x6f,0x6a,0x69,0x78,0x7b,0x7e,0x7d,0x74,0x77,0x72,0x71,
0x50,0x53,0x56,0x55,0x5c,0x5f,0x5a,0x59,0x48,0x4b,0x4e,0x4d,0x44,0x47,0x42,0x41,
0xc0,0xc3,0xc6,0xc5,0xcc,0xcf,0xca,0xc9,0xd8,0xdb,0xde,0xdd,0xd4,0xd7,0xd2,0xd1,
0xf0,0xf3,0xf6,0xf5,0xfc,0xff,0xfa,0xf9,0xe8,0xeb,0xee,0xed,0xe4,0xe7,0xe2,0xe1,
0xa0,0xa3,0xa6,0xa5,0xac,0xaf,0xaa,0xa9,0xb8,0xbb,0xbe,0xbd,0xb4,0xb7,0xb2,0xb1,
0x90,0x93,0x96,0x95,0x9c,0x9f,0x9a,0x99,0x88,0x8b,0x8e,0x8d,0x84,0x87,0x82,0x81,
0x9b,0x98,0x9d,0x9e,0x97,0x94,0x91,0x92,0x83,0x80,0x85,0x86,0x8f,0x8c,0x89,0x8a,
0xab,0xa8,0xad,0xae,0xa7,0xa4,0xa1,0xa2,0xb3,0xb0,0xb5,0xb6,0xbf,0xbc,0xb9,0xba,
0xfb,0xf8,0xfd,0xfe,0xf7,0xf4,0xf1,0xf2,0xe3,0xe0,0xe5,0xe6,0xef,0xec,0xe9,0xea,
0xcb,0xc8,0xcd,0xce,0xc7,0xc4,0xc1,0xc2,0xd3,0xd0,0xd5,0xd6,0xdf,0xdc,0xd9,0xda,
0x5b,0x58,0x5d,0x5e,0x57,0x54,0x51,0x52,0x43,0x40,0x45,0x46,0x4f,0x4c,0x49,0x4a,
0x6b,0x68,0x6d,0x6e,0x67,0x64,0x61,0x62,0x73,0x70,0x75,0x76,0x7f,0x7c,0x79,0x7a,
0x3b,0x38,0x3d,0x3e,0x37,0x34,0x31,0x32,0x23,0x20,0x25,0x26,0x2f,0x2c,0x29,0x2a,
0x0b,0x08,0x0d,0x0e,0x07,0x04,0x01,0x02,0x13,0x10,0x15,0x16,0x1f,0x1c,0x19,0x1a
};

const vector<unsigned char> galoisMulBy9{
	0x00,0x09,0x12,0x1b,0x24,0x2d,0x36,0x3f,0x48,0x41,0x5a,0x53,0x6c,0x65,0x7e,0x77,
0x90,0x99,0x82,0x8b,0xb4,0xbd,0xa6,0xaf,0xd8,0xd1,0xca,0xc3,0xfc,0xf5,0xee,0xe7,
0x3b,0x32,0x29,0x20,0x1f,0x16,0x0d,0x04,0x73,0x7a,0x61,0x68,0x57,0x5e,0x45,0x4c,
0xab,0xa2,0xb9,0xb0,0x8f,0x86,0x9d,0x94,0xe3,0xea,0xf1,0xf8,0xc7,0xce,0xd5,0xdc,
0x76,0x7f,0x64,0x6d,0x52,0x5b,0x40,0x49,0x3e,0x37,0x2c,0x25,0x1a,0x13,0x08,0x01,
0xe6,0xef,0xf4,0xfd,0xc2,0xcb,0xd0,0xd9,0xae,0xa7,0xbc,0xb5,0x8a,0x83,0x98,0x91,
0x4d,0x44,0x5f,0x56,0x69,0x60,0x7b,0x72,0x05,0x0c,0x17,0x1e,0x21,0x28,0x33,0x3a,
0xdd,0xd4,0xcf,0xc6,0xf9,0xf0,0xeb,0xe2,0x95,0x9c,0x87,0x8e,0xb1,0xb8,0xa3,0xaa,
0xec,0xe5,0xfe,0xf7,0xc8,0xc1,0xda,0xd3,0xa4,0xad,0xb6,0xbf,0x80,0x89,0x92,0x9b,
0x7c,0x75,0x6e,0x67,0x58,0x51,0x4a,0x43,0x34,0x3d,0x26,0x2f,0x10,0x19,0x02,0x0b,
0xd7,0xde,0xc5,0xcc,0xf3,0xfa,0xe1,0xe8,0x9f,0x96,0x8d,0x84,0xbb,0xb2,0xa9,0xa0,
0x47,0x4e,0x55,0x5c,0x63,0x6a,0x71,0x78,0x0f,0x06,0x1d,0x14,0x2b,0x22,0x39,0x30,
0x9a,0x93,0x88,0x81,0xbe,0xb7,0xac,0xa5,0xd2,0xdb,0xc0,0xc9,0xf6,0xff,0xe4,0xed,
0x0a,0x03,0x18,0x11,0x2e,0x27,0x3c,0x35,0x42,0x4b,0x50,0x59,0x66,0x6f,0x74,0x7d,
0xa1,0xa8,0xb3,0xba,0x85,0x8c,0x97,0x9e,0xe9,0xe0,0xfb,0xf2,0xcd,0xc4,0xdf,0xd6,
0x31,0x38,0x23,0x2a,0x15,0x1c,0x07,0x0e,0x79,0x70,0x6b,0x62,0x5d,0x54,0x4f,0x46
};

const vector<unsigned char> galoisMulByB{
	0x00,0x0b,0x16,0x1d,0x2c,0x27,0x3a,0x31,0x58,0x53,0x4e,0x45,0x74,0x7f,0x62,0x69,
0xb0,0xbb,0xa6,0xad,0x9c,0x97,0x8a,0x81,0xe8,0xe3,0xfe,0xf5,0xc4,0xcf,0xd2,0xd9,
0x7b,0x70,0x6d,0x66,0x57,0x5c,0x41,0x4a,0x23,0x28,0x35,0x3e,0x0f,0x04,0x19,0x12,
0xcb,0xc0,0xdd,0xd6,0xe7,0xec,0xf1,0xfa,0x93,0x98,0x85,0x8e,0xbf,0xb4,0xa9,0xa2,
0xf6,0xfd,0xe0,0xeb,0xda,0xd1,0xcc,0xc7,0xae,0xa5,0xb8,0xb3,0x82,0x89,0x94,0x9f,
0x46,0x4d,0x50,0x5b,0x6a,0x61,0x7c,0x77,0x1e,0x15,0x08,0x03,0x32,0x39,0x24,0x2f,
0x8d,0x86,0x9b,0x90,0xa1,0xaa,0xb7,0xbc,0xd5,0xde,0xc3,0xc8,0xf9,0xf2,0xef,0xe4,
0x3d,0x36,0x2b,0x20,0x11,0x1a,0x07,0x0c,0x65,0x6e,0x73,0x78,0x49,0x42,0x5f,0x54,
0xf7,0xfc,0xe1,0xea,0xdb,0xd0,0xcd,0xc6,0xaf,0xa4,0xb9,0xb2,0x83,0x88,0x95,0x9e,
0x47,0x4c,0x51,0x5a,0x6b,0x60,0x7d,0x76,0x1f,0x14,0x09,0x02,0x33,0x38,0x25,0x2e,
0x8c,0x87,0x9a,0x91,0xa0,0xab,0xb6,0xbd,0xd4,0xdf,0xc2,0xc9,0xf8,0xf3,0xee,0xe5,
0x3c,0x37,0x2a,0x21,0x10,0x1b,0x06,0x0d,0x64,0x6f,0x72,0x79,0x48,0x43,0x5e,0x55,
0x01,0x0a,0x17,0x1c,0x2d,0x26,0x3b,0x30,0x59,0x52,0x4f,0x44,0x75,0x7e,0x63,0x68,
0xb1,0xba,0xa7,0xac,0x9d,0x96,0x8b,0x80,0xe9,0xe2,0xff,0xf4,0xc5,0xce,0xd3,0xd8,
0x7a,0x71,0x6c,0x67,0x56,0x5d,0x40,0x4b,0x22,0x29,0x34,0x3f,0x0e,0x05,0x18,0x13,
0xca,0xc1,0xdc,0xd7,0xe6,0xed,0xf0,0xfb,0x92,0x99,0x84,0x8f,0xbe,0xb5,0xa8,0xa3
};

const vector<unsigned char> galoisMulByD {
	0x00,0x0d,0x1a,0x17,0x34,0x39,0x2e,0x23,0x68,0x65,0x72,0x7f,0x5c,0x51,0x46,0x4b,
0xd0,0xdd,0xca,0xc7,0xe4,0xe9,0xfe,0xf3,0xb8,0xb5,0xa2,0xaf,0x8c,0x81,0x96,0x9b,
0xbb,0xb6,0xa1,0xac,0x8f,0x82,0x95,0x98,0xd3,0xde,0xc9,0xc4,0xe7,0xea,0xfd,0xf0,
0x6b,0x66,0x71,0x7c,0x5f,0x52,0x45,0x48,0x03,0x0e,0x19,0x14,0x37,0x3a,0x2d,0x20,
0x6d,0x60,0x77,0x7a,0x59,0x54,0x43,0x4e,0x05,0x08,0x1f,0x12,0x31,0x3c,0x2b,0x26,
0xbd,0xb0,0xa7,0xaa,0x89,0x84,0x93,0x9e,0xd5,0xd8,0xcf,0xc2,0xe1,0xec,0xfb,0xf6,
0xd6,0xdb,0xcc,0xc1,0xe2,0xef,0xf8,0xf5,0xbe,0xb3,0xa4,0xa9,0x8a,0x87,0x90,0x9d,
0x06,0x0b,0x1c,0x11,0x32,0x3f,0x28,0x25,0x6e,0x63,0x74,0x79,0x5a,0x57,0x40,0x4d,
0xda,0xd7,0xc0,0xcd,0xee,0xe3,0xf4,0xf9,0xb2,0xbf,0xa8,0xa5,0x86,0x8b,0x9c,0x91,
0x0a,0x07,0x10,0x1d,0x3e,0x33,0x24,0x29,0x62,0x6f,0x78,0x75,0x56,0x5b,0x4c,0x41,
0x61,0x6c,0x7b,0x76,0x55,0x58,0x4f,0x42,0x09,0x04,0x13,0x1e,0x3d,0x30,0x27,0x2a,
0xb1,0xbc,0xab,0xa6,0x85,0x88,0x9f,0x92,0xd9,0xd4,0xc3,0xce,0xed,0xe0,0xf7,0xfa,
0xb7,0xba,0xad,0xa0,0x83,0x8e,0x99,0x94,0xdf,0xd2,0xc5,0xc8,0xeb,0xe6,0xf1,0xfc,
0x67,0x6a,0x7d,0x70,0x53,0x5e,0x49,0x44,0x0f,0x02,0x15,0x18,0x3b,0x36,0x21,0x2c,
0x0c,0x01,0x16,0x1b,0x38,0x35,0x22,0x2f,0x64,0x69,0x7e,0x73,0x50,0x5d,0x4a,0x47,
0xdc,0xd1,0xc6,0xcb,0xe8,0xe5,0xf2,0xff,0xb4,0xb9,0xae,0xa3,0x80,0x8d,0x9a,0x97
};

const vector<unsigned char> galoisMulByE{
	0x00,0x0e,0x1c,0x12,0x38,0x36,0x24,0x2a,0x70,0x7e,0x6c,0x62,0x48,0x46,0x54,0x5a,
0xe0,0xee,0xfc,0xf2,0xd8,0xd6,0xc4,0xca,0x90,0x9e,0x8c,0x82,0xa8,0xa6,0xb4,0xba,
0xdb,0xd5,0xc7,0xc9,0xe3,0xed,0xff,0xf1,0xab,0xa5,0xb7,0xb9,0x93,0x9d,0x8f,0x81,
0x3b,0x35,0x27,0x29,0x03,0x0d,0x1f,0x11,0x4b,0x45,0x57,0x59,0x73,0x7d,0x6f,0x61,
0xad,0xa3,0xb1,0xbf,0x95,0x9b,0x89,0x87,0xdd,0xd3,0xc1,0xcf,0xe5,0xeb,0xf9,0xf7,
0x4d,0x43,0x51,0x5f,0x75,0x7b,0x69,0x67,0x3d,0x33,0x21,0x2f,0x05,0x0b,0x19,0x17,
0x76,0x78,0x6a,0x64,0x4e,0x40,0x52,0x5c,0x06,0x08,0x1a,0x14,0x3e,0x30,0x22,0x2c,
0x96,0x98,0x8a,0x84,0xae,0xa0,0xb2,0xbc,0xe6,0xe8,0xfa,0xf4,0xde,0xd0,0xc2,0xcc,
0x41,0x4f,0x5d,0x53,0x79,0x77,0x65,0x6b,0x31,0x3f,0x2d,0x23,0x09,0x07,0x15,0x1b,
0xa1,0xaf,0xbd,0xb3,0x99,0x97,0x85,0x8b,0xd1,0xdf,0xcd,0xc3,0xe9,0xe7,0xf5,0xfb,
0x9a,0x94,0x86,0x88,0xa2,0xac,0xbe,0xb0,0xea,0xe4,0xf6,0xf8,0xd2,0xdc,0xce,0xc0,
0x7a,0x74,0x66,0x68,0x42,0x4c,0x5e,0x50,0x0a,0x04,0x16,0x18,0x32,0x3c,0x2e,0x20,
0xec,0xe2,0xf0,0xfe,0xd4,0xda,0xc8,0xc6,0x9c,0x92,0x80,0x8e,0xa4,0xaa,0xb8,0xb6,
0x0c,0x02,0x10,0x1e,0x34,0x3a,0x28,0x26,0x7c,0x72,0x60,0x6e,0x44,0x4a,0x58,0x56,
0x37,0x39,0x2b,0x25,0x0f,0x01,0x13,0x1d,0x47,0x49,0x5b,0x55,0x7f,0x71,0x63,0x6d,
0xd7,0xd9,0xcb,0xc5,0xef,0xe1,0xf3,0xfd,0xa7,0xa9,0xbb,0xb5,0x9f,0x91,0x83,0x8d
};

//The first entry in the Rcon array is useless since the indexing of rcon starts at 1 not 0
const unsigned char Rcon [] = {0x01, 0x01,0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

inline string readFileName();

inline void encryption();
inline void decryption();

inline void cipherRound();
inline vector<Word> keyExpansion(vector<unsigned char> key);
inline void rotateWord(Word& word);
inline void subWord(Word& word);
inline void subState(vector<Word>& state);
inline void shiftRows(vector<Word>& words);
inline void mixColumns(vector<Word>& words);
inline void addRoundKey(vector<Word>& words, const vector<Word>& keys);

//What will happen if the file size is smaller than 128 bits ??
//Padding will be used

class UnitTest
{
public:
	UnitTest()
	{
		cerr << "Started Testing\n";
		keyExpTest();
		rotateWordTest();
		mixColTest();
		addRoundKeyTest();
		subStateTest();

		cerr << "Ended testing\n";
	};

private:

	void printResult(string testName, const vector<Word>& testCase, const vector<Word>& result, const vector<Word>& testOutput)
	{
		if (testOutput != result)
		{
			cerr << testName << " not working\n";
			cerr << "Test vector is " << testCase << "\n";
			cerr << "right result is " << result << "\n";
			cerr << "actual result is " << testOutput << "\n";
		}
		else
		{
			cerr << "Passed\n";
		}
	}

	void keyExpTest()
	{

		//Test for 128-bit key expansion
		Word test128{
			0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
		};

		vector<Word> actual128 = keyExpansion(test128);

		vector<Word> result128{
			{0x00,0x01,0x02,0x03},{0x04,0x05,0x06,0x07},{0x08,0x09,0x0a,0x0b},{0x0c,0x0d,0x0e,0x0f},
			{0xd6,0xaa,0x74,0xfd},{0xd2,0xaf,0x72,0xfa},{0xda,0xa6,0x78,0xf1},{0xd6,0xab,0x76,0xfe},
			{0xb6,0x92,0xcf,0x0b},{0x64,0x3d,0xbd,0xf1},{0xbe,0x9b,0xc5,0x00},{0x68,0x30,0xb3,0xfe},
			{0xb6,0xff,0x74,0x4e},{0xd2,0xc2,0xc9,0xbf},{0x6c,0x59,0x0c,0xbf},{0x04,0x69,0xbf,0x41},
			{0x47,0xf7,0xf7,0xbc},{0x95,0x35,0x3e,0x03},{0xf9,0x6c,0x32,0xbc},{0xfd,0x05,0x8d,0xfd},
			{0x3c,0xaa,0xa3,0xe8},{0xa9,0x9f,0x9d,0xeb},{0x50,0xf3,0xaf,0x57},{0xad,0xf6,0x22,0xaa},
			{0x5e,0x39,0x0f,0x7d},{0xf7,0xa6,0x92,0x96},{0xa7,0x55,0x3d,0xc1},{0x0a,0xa3,0x1f,0x6b},
			{0x14,0xf9,0x70,0x1a},{0xe3,0x5f,0xe2,0x8c},{0x44,0x0a,0xdf,0x4d},{0x4e,0xa9,0xc0,0x26},
			{0x47,0x43,0x87,0x35},{0xa4,0x1c,0x65,0xb9},{0xe0,0x16,0xba,0xf4},{0xae,0xbf,0x7a,0xd2},
			{0x54,0x99,0x32,0xd1},{0xf0,0x85,0x57,0x68},{0x10,0x93,0xed,0x9c},{0xbe,0x2c,0x97,0x4e},
			{0x13,0x11,0x1d,0x7f},{0xe3,0x94,0x4a,0x17},{0xf3,0x07,0xa7,0x8b},{0x4d,0x2b,0x30,0xc5}
		};																	  


		if (result128 != actual128)
		{
			cerr << "128-bit key expansion not working !!!\n";
			cerr << "Test vector is " << test128 << "\n";
			cerr << "right result is " << result128 << "\n";
			cerr << "actual result is " << actual128 << "\n";

		}
		else
		{
			cerr << "Passed\n";
		}

		//Test for 192-bit key expansion
		Word test192{
			0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
			0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17
		};

		vector<Word> actual192 = keyExpansion(test192);

		vector<Word> result192{
			{0x00,0x01,0x02,0x03},{0x04,0x05,0x06,0x07},{0x08,0x09,0x0a,0x0b},{0x0c,0x0d,0x0e,0x0f},
			{0x10,0x11,0x12,0x13},{0x14,0x15,0x16,0x17},{0x58,0x46,0xf2,0xf9},{0x5c,0x43,0xf4,0xfe},
			{0x54,0x4a,0xfe,0xf5},{0x58,0x47,0xf0,0xfa},{0x48,0x56,0xe2,0xe9},{0x5c,0x43,0xf4,0xfe},
			{0x40,0xf9,0x49,0xb3},{0x1c,0xba,0xbd,0x4d},{0x48,0xf0,0x43,0xb8},{0x10,0xb7,0xb3,0x42},
			{0x58,0xe1,0x51,0xab},{0x04,0xa2,0xa5,0x55},{0x7e,0xff,0xb5,0x41},{0x62,0x45,0x08,0x0c},
			{0x2a,0xb5,0x4b,0xb4},{0x3a,0x02,0xf8,0xf6},{0x62,0xe3,0xa9,0x5d},{0x66,0x41,0x0c,0x08},
			{0xf5,0x01,0x85,0x72},{0x97,0x44,0x8d,0x7e},{0xbd,0xf1,0xc6,0xca},{0x87,0xf3,0x3e,0x3c},
			{0xe5,0x10,0x97,0x61},{0x83,0x51,0x9b,0x69},{0x34,0x15,0x7c,0x9e},{0xa3,0x51,0xf1,0xe0},
			{0x1e,0xa0,0x37,0x2a},{0x99,0x53,0x09,0x16},{0x7c,0x43,0x9e,0x77},{0xff,0x12,0x05,0x1e},
			{0xdd,0x7e,0x0e,0x88},{0x7e,0x2f,0xff,0x68},{0x60,0x8f,0xc8,0x42},{0xf9,0xdc,0xc1,0x54},
			{0x85,0x9f,0x5f,0x23},{0x7a,0x8d,0x5a,0x3d},{0xc0,0xc0,0x29,0x52},{0xbe,0xef,0xd6,0x3a},
			{0xde,0x60,0x1e,0x78},{0x27,0xbc,0xdf,0x2c},{0xa2,0x23,0x80,0x0f},{0xd8,0xae,0xda,0x32},
			{0xa4,0x97,0x0a,0x33},{0x1a,0x78,0xdc,0x09},{0xc4,0x18,0xc2,0x71},{0xe3,0xa4,0x1d,0x5d}
		};

		if (result192 != actual192)
		{
			cerr << "192-bit key expansion not working !!!\n";
			cerr << "Test vector is " << test192 << "\n";
			cerr << "right result is " << result192 << "\n";
			cerr << "actual result is " << actual192 << "\n";
		}
		else
		{
			cerr << "Passed\n";
		}

		//Test for 256-bit key expansion
		Word test256{ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
			0x0e, 0x0f ,0x10 ,0x11 ,0x12 ,0x13 ,0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a ,0x1b ,0x1c ,
			0x1d ,0x1e ,0x1f };

		vector<Word> actual256 = keyExpansion(test256);

		vector<Word> result256{
			{0x00,0x01,0x02,0x03},{0x04,0x05,0x06,0x07},{0x08,0x09,0x0a,0x0b},{0x0c,0x0d,0x0e,0x0f},
			{0x10,0x11,0x12,0x13},{0x14,0x15,0x16,0x17},{0x18,0x19,0x1a,0x1b},{0x1c,0x1d,0x1e,0x1f},
			{0xa5,0x73,0xc2,0x9f},{0xa1,0x76,0xc4,0x98},{0xa9,0x7f,0xce,0x93},{0xa5,0x72,0xc0,0x9c},
			{0x16,0x51,0xa8,0xcd},{0x02,0x44,0xbe,0xda},{0x1a,0x5d,0xa4,0xc1},{0x06,0x40,0xba,0xde},
			{0xae,0x87,0xdf,0xf0},{0x0f,0xf1,0x1b,0x68},{0xa6,0x8e,0xd5,0xfb},{0x03,0xfc,0x15,0x67},
			{0x6d,0xe1,0xf1,0x48},{0x6f,0xa5,0x4f,0x92},{0x75,0xf8,0xeb,0x53},{0x73,0xb8,0x51,0x8d},
			{0xc6,0x56,0x82,0x7f},{0xc9,0xa7,0x99,0x17},{0x6f,0x29,0x4c,0xec},{0x6c,0xd5,0x59,0x8b},
			{0x3d,0xe2,0x3a,0x75},{0x52,0x47,0x75,0xe7},{0x27,0xbf,0x9e,0xb4},{0x54,0x07,0xcf,0x39},
			{0x0b,0xdc,0x90,0x5f},{0xc2,0x7b,0x09,0x48},{0xad,0x52,0x45,0xa4},{0xc1,0x87,0x1c,0x2f},
			{0x45,0xf5,0xa6,0x60},{0x17,0xb2,0xd3,0x87},{0x30,0x0d,0x4d,0x33},{0x64,0x0a,0x82,0x0a},
			{0x7c,0xcf,0xf7,0x1c},{0xbe,0xb4,0xfe,0x54},{0x13,0xe6,0xbb,0xf0},{0xd2,0x61,0xa7,0xdf},
			{0xf0,0x1a,0xfa,0xfe},{0xe7,0xa8,0x29,0x79},{0xd7,0xa5,0x64,0x4a},{0xb3,0xaf,0xe6,0x40},
			{0x25,0x41,0xfe,0x71},{0x9b,0xf5,0x00,0x25},{0x88,0x13,0xbb,0xd5},{0x5a,0x72,0x1c,0x0a},
			{0x4e,0x5a,0x66,0x99},{0xa9,0xf2,0x4f,0xe0},{0x7e,0x57,0x2b,0xaa},{0xcd,0xf8,0xcd,0xea},
			{0x24,0xfc,0x79,0xcc},{0xbf,0x09,0x79,0xe9},{0x37,0x1a,0xc2,0x3c},{0x6d,0x68,0xde,0x36},
		};

		if (result256 != actual256)
		{
			cerr << "256-bit key expansion not working !!!\n";
			cerr << "Test vector is " << test256 << "\n";
			cerr << "right result is " << result256 << "\n";
			cerr << "actual result is " << actual256 << "\n";
		}
		else
		{
			cerr << "Passed\n";
		}

	}

	void rotateWordTest()
	{

		vector<Word> test{
			{0xd4,0xe0,0xb8,0x1e},
			{0x27,0xbf,0xb4,0x41},
			{0x11,0x98,0x5d,0x52},
			{0xae,0xf1,0xe5,0x30}
		};

		vector<Word> testOld{
			{0xd4,0xe0,0xb8,0x1e},
			{0x27,0xbf,0xb4,0x41},
			{0x11,0x98,0x5d,0x52},
			{0xae,0xf1,0xe5,0x30}
		};
		shiftRows(test);

		vector<Word> result{
			{0xd4,0xe0,0xb8,0x1e},
			{0xbf,0xb4,0x41,0x27},
			{0x5d,0x52,0x11,0x98},
			{0x30,0xae,0xf1,0xe5}
		};

		printResult("Rotate Word ( Shift Rows )", testOld, result, test);

		
	}

	void mixColTest()
	{
		vector<Word> test = {
		{0xd4,0xe0,0xb8,0x1e},
		{0xbf,0xb4,0x41,0x27},
		{0x5d,0x52,0x11,0x98},
		{0x30,0xae,0xf1,0xe5}
		};

		vector<Word> testOld = {
		{0xd4,0xe0,0xb8,0x1e},
		{0xbf,0xb4,0x41,0x27},
		{0x5d,0x52,0x11,0x98},
		{0x30,0xae,0xf1,0xe5}
		};

		mixColumns(test);

		vector<Word> result = {
			{0x4, 0xe0, 0x48,0x28 },
			{0x66, 0xcb, 0xf8,0x06 },
			{0x81, 0x19, 0xd3,0x26 },
			{0xe5, 0x9a, 0x7a,0x4c }
		};

		printResult("Mix Columns", testOld, result, test);

	}

	void addRoundKeyTest()
	{
		vector<Word> test = {
			{0x04, 0xe0, 0x48, 0x28},
			{0x66, 0xcb, 0xf8, 0x06},
			{0x81, 0x19, 0xd3, 0x26},
			{0xe5, 0x9a, 0x7a, 0x4c},
		};

		vector<Word> testOld = {
			{0x04, 0xe0, 0x48, 0x28},
			{0x66, 0xcb, 0xf8, 0x06},
			{0x81, 0x19, 0xd3, 0x26},
			{0xe5, 0x9a, 0x7a, 0x4c},
		};

		vector<Word> key = {
			{0xa0, 0x88, 0x23, 0x2a},
			{0xfa, 0x54, 0xa3, 0x6c},
			{0xfe, 0x2c, 0x39, 0x76},
			{0x17, 0xb1, 0x39, 0x05},
		};

		vector<Word> result = {
			{0xa4, 0x68, 0x6b, 0x02},
			{0x9c, 0x9f, 0x5b, 0x6a},
			{0x7f, 0x35, 0xea, 0x50},
			{0xf2, 0x2b, 0x43, 0x49},
		};

		vector<Word> actual; 
		addRoundKey(test, key);

		printResult("Add round key", testOld, result, test);

	}

	void subStateTest()
	{
		vector<Word> test = {
			{0xaa, 0x61, 0x82, 0x68},
			{0x8f, 0xdd, 0xd2, 0x32},
			{0x5f, 0xe3, 0x4a, 0x46},
			{0x03, 0xef, 0xd2, 0x9a},
		};

		vector<Word> testOld = {
			{0xaa, 0x61, 0x82, 0x68},
			{0x8f, 0xdd, 0xd2, 0x32},
			{0x5f, 0xe3, 0x4a, 0x46},
			{0x03, 0xef, 0xd2, 0x9a},
		};

		vector<Word> result = {
			{0xac, 0xef, 0x13, 0x45},
			{0x73, 0xc1, 0xb5, 0x23},
			{0xcf, 0x11, 0xd6, 0x5a},
			{0x7b, 0xdf, 0xb5, 0xb8},
		};

		subState(test);


		printResult("SubState", testOld, result, test);

	}
};

int main()
{
	//This will run unit tests
	UnitTest ut;


	//Ask the user whether they want to encrypt or decrypt

	Word key{0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4};
	keyExpansion(key);

	int encDecChoice;
	cout << "Enter 1 to encrypt\n";
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
	if (fileNameTemp[fileNameTemp.size() - 1] == '"')
		fileNameTemp.erase(fileNameTemp.size() - 1, 1);


	return std::move(fileNameTemp);

}

inline void encryption()
{
	//Ask the user whether to generate a random key or to enter a key

	//The choice of the user
	int keyChoice;

	//The key that will be used in encryption
	vector<unsigned char> key;
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

		int keySizeChoice;
		cout << "Enter 1, 2 or 3 for key size 16, 24 or 32 characters : ";
		cin >> keySizeChoice;

		while (keySizeChoice != 1 && keySizeChoice != 2 && keySizeChoice != 3)
		{
			cout << "Please enter a correct key choice\n";
			cout << "Enter 1, 2 or 3 for key size 16, 24 or 32 characters : ";
			cin >> keySizeChoice;
		}

		// Initializing a random seed
		srand(time( NULL));

		if (keySizeChoice == 1)
		{
			for (size_t i = 0; i < 16; i++)
			{
				int randNum = rand() % 256;
				key.push_back(randNum);
			}

		}
		else if (keySizeChoice == 2)
		{
			for (size_t i = 0; i < 24; i++)
			{
				int randNum = rand() % 256;
				key.push_back(randNum);
			}
		}
		else if (keySizeChoice == 3)
		{
			for (size_t i = 0; i < 32; i++)
			{
				int randNum = rand() % 256;
				key.push_back(randNum);
			}
		}
		else
		{
			cerr << "Wrong key size choice\n";
		}

		//print the randomly generated key
		cout << "The generated key is : ";

		for (int i = 0; i < key.size(); i++)
		{
			cout << static_cast<int>(key[i]) << " ";
		}
		cout << "\n";
		cout << "SAVE THIS NUMBER AS IT IS VERY IMPORTANT FOR DECRYPTION!!!!!!\n";
	}
	else
	{
		//Key entered manually
		//Ask the user to enter the size of the key
		//128 bits -> 16 characters
		//192 bits -> 24 characters
		//256 bits -> 32 characters

		//I did not use a hash function because I want to implement the standard algorithm so any AES decryptor can decrypt it.
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

		//Padding is required
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



inline vector<Word> keyExpansion(vector<unsigned char> key)
{
	//cout << "Entered keyExpansion\n";
	//w: key schedule
	//the first 4 words of the key schedule is the the first 4 words of the key
	//for 16 byte key, afterwards, w[i] = w[i-1] ^ w[i-4]
	//if i is a multiple of 4, w[i] = g(w[i-1]) ^ w[i-4]
	//function g() is composed of 3 steps
	//1- rotate left (e.g. b0,b1,b2,b3 --> b1,b2,b3,b0)
	//2- perform SubByte on each byte
	//3- XOR with Rcon[j]

	vector<Word> w;
	int keySize = key.size();
	NK = keySize / 4;

	//cout << "NK = " << NK << "\n";
	if (keySize == 16)
	{
		NR = 10;
	}
	else if (keySize == 24)
	{
		NR = 12;
	}
	else if (keySize == 32)
	{
		NR = 14;
	}
	else
	{
		cout << "Error. Wrong key size\n";
	}

	w.resize(NB * (NR + 1));

	for (size_t i = 0; i < NK; i++)
	{
		//take 4 bytes and make a word
		w[i] = { key[4*i] , key[4*i+1], key[4*i+2], key[4*i+3]};
	}

	for (size_t i = NK; i < NB*(NR+1); i++)
	{
		Word temp = w[i - 1];

		//cout << "temp = " << temp ;
		

		if (i % NK == 0)
		{
			//1- rotate left (e.g. b0,b1,b2,b3 --> b1,b2,b3,b0)
			rotateWord(temp);
			//cout << "After RotWord = " << temp;
			//2- perform SubByte on each byte
			subWord(temp);
			//cout << "After subWord = " << temp;
			//3- XOR with Rcon[j]
			//cout << " i / NK = " << i / NK << "\n";
			temp = temp ^ Word{ Rcon[i / NK], 0x0,0x0,0x0 };
			//cout << "After Rcon XOR = " << temp;


		}
		else if (NK > 6 && (i % NK == 4))
			//Special case for NK = 8
			// if NK == 8 && i-4 is a multiple of NK
		{
			subWord(temp);
		}

		w[i] = w[i - NK] ^ temp;

		if (w[i].size() == 0)
		{
			cout << "Error. XOR operands have unequal sizes\n";
		}

		//TESTING
		//cout << "w[" << i << "] = " << hex << w[i] << "\n";
	}

	return w;
}

inline void rotateWord(Word& word) // TESTED
{

	unsigned char temp = word[0];
	word.erase(word.begin());
	word.push_back(temp);
	

}

inline void subWord(Word& word) //TESTED
{
	for (int i = 0; i < word.size(); i++)
	{
		//cout << "Replacing " << hex << static_cast<int>(word[i]) << " with " << hex << static_cast<int>(subBytes.at(word[i])) << "\n";;
		word[i] = subBytes.at(word[i]);
	}
}

inline void subState(vector<Word>& state)
{
	for (size_t i = 0; i < COLS; i++)
	{
		subWord(state[i]);
	}
}

inline void shiftRows( vector<Word>& words)		//TESTED
{
	for (size_t i = 1; i < COLS; i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			unsigned char temp = words[i][0];
			words[i].erase(words[i].begin());
			words[i].push_back(temp);
		}
	}
}

inline void mixColumns(vector<Word>& words)
{
	//Instead of implementing Galois multiplication, we can use lookup table since this is a
	//finite field
	for (size_t i = 0; i < COLS; i++)
	{
		Word oldWord = { words[0][i], words[1][i], words[2][i], words[3][i]};
		//cout << "old column \n" << oldWord;

		words[0][i] = (galoisMulBy2[oldWord[0]])		^ (galoisMulBy3[oldWord[1]])	^ (oldWord[2])					^ (oldWord[3]);
		words[1][i] = (oldWord[0])						^ (galoisMulBy2[oldWord[1]])	^ (galoisMulBy3[oldWord[2]])	^ (oldWord[3]);
		words[2][i] = (oldWord[0])						^ (oldWord[1])					^ (galoisMulBy2[oldWord[2]])	^ (galoisMulBy3[oldWord[3]]);
		words[3][i] = (galoisMulBy3[oldWord[0]])		^ (oldWord[1])					^ (oldWord[2])					^ (galoisMulBy2[oldWord[3]]);
	}
}

inline void addRoundKey(vector<Word>& words, const vector<Word>& keys)
{
	for (size_t i = 0; i < COLS; i++)
	{
		words[i] = words[i] ^ keys[i];
	}
}

inline vector<Word> cipherRound(vector<Word>& state, const vector<Word>& key)
{
	//subWord(state);
	//shiftRows(state);

}