/*
 * matching.cpp
 * compare original video and testing video
 */

#include <math.h>
#include <iostream>
#include "matching.h"

Feature_Matching_Class::Feature_Matching_Class(int threshold, int frameNum)
{
	matchingThreshold = frameNum*threshold*threshold;
	matchingFrameNum = frameNum;
	std::ifstream infile;
	infile.open("../data/orig_feature/feature");
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			char tmpTimestamp[100];
			infile>>tmpTimestamp;
			char tmpData[100];
			infile>>tmpData;
			double timestamp = atof(tmpTimestamp);
			double data = atof(tmpData);
			origTimestamp.push_back(timestamp);
			origFeature.push_back(data);
		}
		infile.close();
	}
	origTimestamp.pop_back();
	origFeature.pop_back();
	outfile = fopen("../data/result", "w");
}

Feature_Matching_Class::~Feature_Matching_Class()
{
	fclose(outfile);
}

void Feature_Matching_Class::Feature_Matching(Feature& feature)
{
	double currentOrigTimestamp = origTimestamp.front();
	double currentTestTimestamp = feature.timestamp;
	while (origTimestamp.size()!=1)
	{
		if (currentTestTimestamp > currentOrigTimestamp)
		{
			origTimestamp.pop_front();
			origFeature.pop_front();
			currentOrigTimestamp = origTimestamp.front();
		}
		else
		{
			break;
		}
	}
	double difference;
	difference = origFeature.front() - feature.feature;
	difference = difference*difference;
	errorSum = errorSum+difference;
	error.push_back(difference);
	testTimestamp.push_back(currentTestTimestamp);
	corOrigTimestamp.push_back(currentOrigTimestamp);
	if (error.size()>matchingFrameNum)
	{
		errorSum = errorSum - error.front();
		error.pop_front();
		testTimestamp.pop_front();
		corOrigTimestamp.pop_front();
	}
	if (errorSum > matchingThreshold)
	{
		std::list<double>::iterator it, it1, it2;
		it1 = testTimestamp.begin();
		it2 = corOrigTimestamp.begin();
		for (it = error.begin(); it != error.end(); it++)
		{
			fprintf(outfile, "%f %f %f\n", *it1, *it2, *it);
			it1++;
			it2++;
		}
		fprintf(outfile, "%f %f\n\n", errorSum, matchingThreshold);
	}
}

