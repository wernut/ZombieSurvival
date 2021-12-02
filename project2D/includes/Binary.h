#pragma once

class Binary
{
public:

	// Convert binary number stored as a string into decimal integar.
	static int binToDec(const char* binaryString);

	// Convert decimal value to binary number stored in string.
	static void decToBin(char* binaryString, int len, int value);

	static void setBit(char& bitfield, int bit, bool value);
	static bool checkBit(char& bitfeild, int bit);
};

