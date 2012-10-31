/*
 * main.cpp
 * the main function of the system
 */

//extern "C"
//{
#include "videocapture.h"
#include "sockclnt.h"
//}

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/time.h>

#include "struct.h"
#include "parse.h"
#include "scale_block.h"
#include "char_block.h"
#include "matching.h"
using namespace std;

int ORIG_OR_TEST;

int main() {
	//parsing parameters
	Parse_C parse_class;
	parse_class.Parse_Config_File((char *)"../param/param.conf");

	parse_class.Parse_Params(0, ORIGIN_WIDTH);
	parse_class.Parse_Params(1, ORIGIN_HEIGHT);
	parse_class.Parse_Params(2, SCALE_WIDTH);
	parse_class.Parse_Params(3, SCALE_HEIGHT);
	parse_class.Parse_Params(4, MATCHING_THRESHOLD);
	parse_class.Parse_Params(5, MATCHING_FRAME_NUM);
	parse_class.Parse_Params(6, ORIG_OR_TEST);

	//set up capture and structures
	Capture_Setup();
	Figure originalFig, scaledFig;
	Feature feature;
	originalFig.figure = new u_int8_t [ORIGIN_WIDTH*ORIGIN_HEIGHT*2];
	originalFig.length = ORIGIN_WIDTH*ORIGIN_HEIGHT*2;
	originalFig.timestamp = 0;

	scaledFig.figure = new u_int8_t [ORIGIN_WIDTH*ORIGIN_HEIGHT*2];

	struct timeval startTime,currentTime;

	//trigger the socket connection
	if (ORIG_OR_TEST == 0)
	{
		Socket_trigger(8000);
	}
	else
	{
		Socket_trigger(4000);
	}

	//sync the timeline
	int syncBegin = 0;
	int syncDone = 0;
	Char_C char_class;
	Scale_C scale_class;
	while (syncDone == 0)
	{
		mainloop(originalFig.figure);
		scale_class.Scale_Body (originalFig, scaledFig, ORIG_OR_TEST);
		char_class.Char_Choose(scaledFig, feature, 0, ORIG_OR_TEST);
		if (feature.feature < 19)
		{
			syncBegin = 1;
		}
		if (syncBegin == 1)
		{
			while (1)
			{
				mainloop(originalFig.figure);
				scale_class.Scale_Body(originalFig,scaledFig,ORIG_OR_TEST);
				char_class.Char_Choose(scaledFig, feature, 0, ORIG_OR_TEST);
				if (feature.feature > 19)
				{
					syncDone = 1;
					break;
				}
			}
		}
	}

	gettimeofday(&startTime,NULL);

	//if testing the original video
	if (ORIG_OR_TEST == 0)
	{
		for (int i = 0; i < 205; i++)
		{
			std::cout<<i<<std::endl;

			//video capture
			mainloop(originalFig.figure);

			//get time
			gettimeofday(&currentTime,NULL);
			double span = currentTime.tv_sec-startTime.tv_sec + 
							(currentTime.tv_usec - startTime.tv_usec)/1000000.0;
			originalFig.timestamp = span;

			//scale image
			scale_class.Scale_Body (originalFig, scaledFig, ORIG_OR_TEST);

			//generate characteristic
			char_class.Char_Choose(scaledFig, feature, 0, ORIG_OR_TEST);
		}
	}
	//if testing the testing video
	else
	{
		Feature_Matching_Class matching(MATCHING_THRESHOLD, MATCHING_FRAME_NUM);
		for (int i = 0; i < 205; i++)
		{
			std::cout<<i<<std::endl;

			//video capture
			mainloop(originalFig.figure);

			//get time
			gettimeofday(&currentTime,NULL);
			double span = currentTime.tv_sec-startTime.tv_sec + 
							(currentTime.tv_usec - startTime.tv_usec)/1000000.0;
			originalFig.timestamp = span;

			//scale image
			scale_class.Scale_Body (originalFig, scaledFig, ORIG_OR_TEST);

			//generate characteristic
			char_class.Char_Choose(scaledFig, feature, 0, ORIG_OR_TEST);

			//feature matching
			matching.Feature_Matching(feature);
		}
	}
	//close device
	Capture_Finish();

	std::cout << ORIGIN_WIDTH << ORIGIN_HEIGHT << SCALE_WIDTH << SCALE_HEIGHT
			  << MATCHING_THRESHOLD << std::endl;

	//copy pics for html presentation
	if (ORIG_OR_TEST == 1)
	{
		system("firefox ../demo/demo_v2.html");
		std::ifstream infile;
		infile.open("../data/result");
		if (infile.is_open())
		{
			while (!infile.eof())
			{
				char tmp[100];
				for (int i=1; i<=MATCHING_FRAME_NUM; i++)
				{
					char testCommand[100], origCommand[100];
					char testPic[100], origPic[100];
					char destTestPic[100], destOrigPic[100];
					char series[100];

					memset(testCommand, 0, 100);
					memset(origCommand, 0, 100);
					memset(testPic, 0, 100);
					memset(origPic, 0, 100);
					memset(destTestPic, 0, 100);
					memset(destOrigPic, 0, 100);
					memset(series, 0, 100);

					infile>>testPic;
					infile>>origPic;
					infile>>tmp;

					strcat(testPic, ".bmp");
					strcat(origPic, ".bmp");
					sprintf(series, "%d", i);
					strcpy(destTestPic, series);
					strcpy(destOrigPic, series);
					strcat(destTestPic, "t.bmp");
					strcat(destOrigPic, "o.bmp");

					strcpy(testCommand, "cp ../data/test_snapshots/");
					strcat(testCommand, testPic);
					strcat(testCommand, " ../demo/");
					strcat(testCommand, destTestPic);

					strcpy(origCommand, "cp ../data/orig_snapshots/");
					strcat(origCommand, origPic);
					strcat(origCommand, " ../demo/");
					strcat(origCommand, destOrigPic);

					std::cout<<testPic<<std::endl;
					std::cout<<origCommand<<std::endl;
					std::cout<<testCommand<<std::endl;

					system(testCommand);
					system(origCommand);
				}
				infile.getline(tmp, 100);
				infile.getline(tmp, 100);
			}
		}
		infile.close();
	}

	return 0;
}
