/*
 * struct.h
 * define all the common structs
 */

#ifndef STRUCT_H
#define STRUCT_H

#include <vector>
#include <stdlib.h>

// the struct for images
struct Figure
{
	u_int8_t * figure;
	size_t length;
	double timestamp;
};

//the struct for features generated from images
struct Feature
{
	double feature;
	double timestamp;
};

#endif
