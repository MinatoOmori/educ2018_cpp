#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	int answer[100] = {};

	ifstream ifs(argv[1]);
	if (!ifs)
	{
		cout<<"text file error."<<endl;
		return -1;
	}

	vector<char> memory;
	char tmp;

	while (ifs.get(tmp))
	{
		memory.push_back(tmp);
	}

	auto itr = memory.begin();
	int* ptr;
        ptr = &answer[0];
	auto left_par = memory.begin();

	while (itr != memory.end())
	{
		if (*itr == '>')
		{
			ptr++;
		}
		else if (*itr == '<')
		{
			ptr--;
		}
		else if (*itr == '+')
		{
			(*ptr)++;
		}
		else if (*itr == '-')
		{
			(*ptr)--;
		}
		else if (*itr == '.')
		{
			putchar(*ptr);
		}
		else if (*itr == ',')
		{
			*ptr = getchar();
		}
		else if (*itr == '[')
		{
			if (*ptr == 0)
			{
				for (auto right_par = itr; right_par != memory.end(); right_par++)
				{
					if (*right_par == ']')
					{
						itr = right_par;
						break;
					}
				}
			}
			else
			{
				left_par = itr;
			}
		}
		else if (*itr == ']')
		{
			itr = left_par-1;
		}

		itr++;

	}

	return 0;

}
