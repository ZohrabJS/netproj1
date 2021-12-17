//#include<iostream>
//#include <string>
#include "net-utils.h"

string encode(string str)
{
	// stores output string
	string encoding = "";
	int count;

	for (int i = 0; str[i]; i++)
	{
		// count occurrences of character at index i
		count = 1;
		while (str[i] == str[i + 1])
			count++, i++;

		// append current character and its count to the result
		encoding += to_string(count) + str[i];
	}

	return encoding;
}

string decode(string str)
{
	string decoding = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] <= '9' && str[i] >= '0')
		{
			for (int j = 0; j < str[i] - '0'; j++)
			{
				decoding += str[i + 1];
			}
			i++;
		}
	}
	return decoding;
}