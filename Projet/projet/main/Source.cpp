#include "source.h"

using namespace std;

bool estDansString(string string1, string string2)
{
	int i = 0;
	int j = 0;
	if (string1 == string2)
		return true;
	if (string1.size() <= string2.size())
	{
		while (i < string2.size() - string1.size())
		{
			j = i;
			while (string1[j] == string2[j])
			{
				++j;
			}
			if (j - i == string1.size())
				return true;
			++i;
		}
	}
	return false;

}