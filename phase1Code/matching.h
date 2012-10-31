/*
 * matching.h
 * compare original video and testing video
 */

#ifndef MATCHING_H
#define MATCHING_H

#include "struct.h"
#include <list>
#include <fstream>

class Feature_Matching_Class{
public:
	Feature_Matching_Class(int threshold, int frameNum);
	~Feature_Matching_Class();

	//compare the features from original and testing videos
	void Feature_Matching(Feature& feature);
private:
	double matchingThreshold;
	int matchingFrameNum;
	double errorSum;
	std::list<double> origTimestamp, origFeature;
	std::list<double> testTimestamp, corOrigTimestamp, error;
	FILE* outfile;
};

#endif

