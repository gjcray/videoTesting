#include "scale_block.h"
#include "global.h"
#include "y2b.h"
#include <stdio.h>
#include <cstring>

int Scale_C::Scale_Body (Figure &orig, Figure &scaled, int orig_or_test) {
	int width_rate, height_rate,
	y1_sum = 0, y2_sum = 0,
	u_sum = 0, v_sum = 0;
	width_rate = ORIGIN_WIDTH / SCALE_WIDTH;
	height_rate = ORIGIN_HEIGHT / SCALE_HEIGHT;

	scaled.timestamp = orig.timestamp;
	scaled.length = SCALE_HEIGHT * SCALE_WIDTH *2;

	for (int j = 0; j < SCALE_HEIGHT; ++j) {
		for (int i = 0; i < SCALE_WIDTH * 2; ) {
			for (int k = 0; k < width_rate; ++k) {
				for (int l = 0; l < height_rate; ++l) {
					switch (k % 4)
					{
						case 0:
							y1_sum += orig.figure[(i*width_rate+k) +
										2*ORIGIN_WIDTH*(j*height_rate+l)];
							break;
						case 1:
							u_sum += orig.figure[(i*width_rate+k) +
										2*ORIGIN_WIDTH*(j*height_rate+l)];
							break;
						case 2:
							y2_sum += orig.figure[(i*width_rate+k) +
										2*ORIGIN_WIDTH*(j*height_rate+l)];
							break;
						case 3:
							v_sum += orig.figure[(i*width_rate+k) +
										2*ORIGIN_WIDTH*(j*height_rate+l)];
							break;
					}
				}
			}
			y1_sum = 4*y1_sum / (width_rate * height_rate);
			y2_sum = 4*y2_sum / (width_rate * height_rate);
			u_sum = 4*u_sum / (width_rate * height_rate);
			v_sum = 4*v_sum / (width_rate * height_rate);
			scaled.figure[i + 2*SCALE_WIDTH*j] = y1_sum;
			scaled.figure[i + 1 + 2*SCALE_WIDTH*j] = u_sum;
			scaled.figure[i + 2 + 2*SCALE_WIDTH*j] = y2_sum;
			scaled.figure[i + 3 + 2*SCALE_WIDTH*j] = v_sum;

			i += 4;
			y1_sum = 0;
			y2_sum = 0;
			u_sum = 0;
			v_sum = 0;
		}
	}

	Save_To_File(scaled, orig_or_test);
	return 0;
}

int Scale_C::Save_To_File (Figure &scaled, int orig_or_test) {
	FILE *fout;
	char direct[100], time[100];
	if (orig_or_test)
		strcpy(direct, "../data/test_snapshots/");
	else
		strcpy(direct, "../data/orig_snapshots/");

	sprintf(time, "%f", scaled.timestamp);

	strcat(direct, time);

	char picDirect[100];
	strcpy(picDirect, direct);
	strcat(picDirect, ".bmp");
	y2bmain(scaled, picDirect);

	fout = fopen(direct, "w");

	for (unsigned int j = 0; j < scaled.length; ++j) {
		int tmp = scaled.figure[j];
		fprintf(fout, "%i ", tmp);
		if ((j+1)%(SCALE_WIDTH*2) == 0)
		{
			fprintf(fout, "\n");
		}
	}
	fclose(fout);
	return 0;
}
