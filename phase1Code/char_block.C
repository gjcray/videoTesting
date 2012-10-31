#include "char_block.h"
#include "struct.h"
#include "global.h"
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;

int Char_C::Char_Choose(Figure& data, Feature& f, int method, int orig_or_test) {
	f.timestamp = data.timestamp;
	switch (method) {
		case 0:
			Char_Y_Ave(data, f);
			break;
		default:
			Char_Y_Ave(data, f);
			break;
	}
	Save_To_File_Char(f, orig_or_test);
	return 0;
}

int Char_C::Char_Y_Ave(Figure &data, Feature &feature) {
	double res = 0;
	int cnt = 0;

	for (int i = 0; i < SCALE_HEIGHT*SCALE_WIDTH * 2; ++i)
		if (i % 2 == 0) {
			res += data.figure[i];
			++cnt;
		}

	feature.feature = res / (double)cnt;
	return 0;
}

int Char_C::Save_To_File_Char(Feature& feature, int orig_or_test) {
	FILE *fout;
	char direct[100], time[100];
	if (orig_or_test) 
		strcpy(direct, "../data/test_feature/feature");
	else
		strcpy(direct, "../data/orig_feature/feature");

	sprintf(time, "%f", feature.timestamp);

	fout = fopen(direct, "a");

	fprintf(fout, "%f\t%f\n", feature.timestamp, feature.feature);

	fclose(fout);
	return 0;
}


