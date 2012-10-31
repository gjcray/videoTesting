/*
 * parse.cpp
 * functions to parse params into globals
 */

#include "parse.h"
#include <string.h>
#include <stdlib.h>
#include <fstream>

int ORIGIN_WIDTH;
int ORIGIN_HEIGHT;
int SCALE_WIDTH;
int SCALE_HEIGHT;
int MATCHING_THRESHOLD;
int MATCHING_FRAME_NUM;

void Parse_C::Parse_Config_File(char *configFile)
{
	std::ifstream infile;
	infile.open(configFile);
	if (infile.is_open())
	{
		int count = 0;
		while (!infile.eof())
		{
			char tmp[100];
			infile.getline(tmp,100);
			if (strlen(tmp)!=0)
			{
				if (tmp[0] != '#')
				{
					char *pch;
					pch = strtok(tmp, "=");
					pch = strtok(NULL, "=");
					char paramData[100];
					strcpy(paramData, pch);
					int data = atoi(paramData);
					paramMap.push_back(data);
				}
			}
		}
		infile.close();
	}
	else
	{
		exit(0);
	}
}

bool Parse_C::Parse_Params(unsigned int paramNo, int &data)
{
	if (paramNo >= paramMap.size())
	{
		return 0;
	}
	else
	{
		data = paramMap[paramNo];
	}
	return 1;
}
