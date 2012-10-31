/*
 * y2b.h
 * convert the scaled yuyv matrix into a bmp file
 */
#ifndef Y2B_H
#define Y2B_H
#include <cstdlib>
#include "struct.h"

/*
 * The only function needs to call for the yuv2bmp process
 * Input: Figure &scaled and char* argv(the filename want to save)
 * Output: The corresponding bmp file
 */
int y2bmain(Figure &scaled, char* argv);

class CUYVY2BMP {
public:
	CUYVY2BMP(int width, int height);
	~CUYVY2BMP();
	int GetHeight();
	int GetWidth();
	bool WriteBMPFile(char* fn, u_int8_t *RGBBuf, int iBitCount);
	bool UYVY2BMP(u_int8_t* pDst, u_int8_t * pSrc);
private:
	void MakeConversionTable();
	int m_nHeight;
	int m_nWidth;
};

typedef struct tagTABLE_UYVY2RGB {
	unsigned short YtoR[256];
	unsigned short YtoG[256];
	unsigned short YtoB[256];
	unsigned short UtoG[256];
	unsigned short UtoB[256];
	unsigned short VtoR[256];
	unsigned short VtoG[256];
} TABLE_UYVY2RGB;

#endif
