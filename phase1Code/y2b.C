#include "y2b.h"
#include "global.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#define clip(min, x, max) x=(x < min) ? min:(x > max) ? max:x

TABLE_UYVY2RGB table_UYVY2rgb;

CUYVY2BMP::CUYVY2BMP(int width, int height) {
	m_nWidth = width;
	m_nHeight = height;
}

CUYVY2BMP::~CUYVY2BMP(){
}

int CUYVY2BMP::GetWidth() {
	return m_nWidth;
}

int CUYVY2BMP::GetHeight() {
	return m_nHeight;
}

void CUYVY2BMP::MakeConversionTable()
{
	for (long j = 0; j < 256; ++j) {
		table_UYVY2rgb.YtoR[j]=
		table_UYVY2rgb.YtoG[j]=table_UYVY2rgb.YtoB[j]=(unsigned short)(j << 7);
		table_UYVY2rgb.VtoR[j] = j*180;
		table_UYVY2rgb.VtoG[j] = j*91;
		table_UYVY2rgb.UtoG[j] = j*44;
		table_UYVY2rgb.UtoB[j] = j*226;
	}
}

bool CUYVY2BMP::UYVY2BMP(u_int8_t* pDst, u_int8_t* pSrc) {
	long m=0;
	long k=0;
	int n=m_nWidth/2;
	int dec=m_nWidth*4;

	int tmpR0 = 0;
	int tmpG0 = 0;
	int tmpB0 = 0;
	int tmpR1 = 0;
	int tmpG1 = 0;
	int tmpB1 = 0;

	MakeConversionTable();
	k=(m_nHeight-1)*m_nWidth<<1;
	for (int i=m_nHeight-1; i>-1; i--) {
		for (int j=0; j<n; j++) {
			tmpR0 =
	(table_UYVY2rgb.YtoR[pSrc[k+0]]+table_UYVY2rgb.VtoR[pSrc[k+3]]-22906) >> 7;
			tmpG0 = (table_UYVY2rgb.YtoG[pSrc[k+0]]-
	table_UYVY2rgb.VtoG[pSrc[k+3]]-table_UYVY2rgb.UtoG[pSrc[k+1]]+17264) >> 7;
			tmpB0 =
	(table_UYVY2rgb.YtoB[pSrc[k+0]]+table_UYVY2rgb.UtoB[pSrc[k+1]]-28928) >> 7;
			tmpR1 =
	(table_UYVY2rgb.YtoR[pSrc[k+2]]+table_UYVY2rgb.VtoR[pSrc[k+3]]-22906) >> 7;
			tmpG1 = (table_UYVY2rgb.YtoG[pSrc[k+2]]-
	table_UYVY2rgb.VtoG[pSrc[k+3]]-table_UYVY2rgb.UtoG[pSrc[k+1]]+17264) >> 7;
			tmpB1 =
	(table_UYVY2rgb.YtoB[pSrc[k+2]]+table_UYVY2rgb.UtoB[pSrc[k+1]]-28928)>>7;

			clip(0, tmpR0, 255);
			clip(0, tmpG0, 255);
			clip(0, tmpB0, 255);
			clip(0, tmpR1, 255);
			clip(0, tmpG1, 255);
			clip(0, tmpB1, 255);

			pDst[m+0] = tmpB0;
			pDst[m+1] = tmpG0;
			pDst[m+2] = tmpR0;
			pDst[m+3] = tmpB1;
			pDst[m+4] = tmpG1;
			pDst[m+5] = tmpR1;

			k += 4;
			m += 6;
		}
		
		k -= dec;
	}

	return 1;
}

bool CUYVY2BMP::WriteBMPFile(char* fn, u_int8_t *RGBBuf, int iBitCount) {
	long RGB_SIZE = m_nWidth * m_nHeight*3;
	if (iBitCount == 24) {
		FILE *fp;
		long count = 0;

		if ((fp = fopen(fn, "wb")) == NULL) {
			printf("Cannot create bmpfile %s\n", fn);
			return false;
		}
		//TODO: add BMP header for 80 * 60 resolution
		int h8060[60] = {66, 77, 118, 56, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0, 40, 0,
						0, 0, 80, 0, 0, 0, 60, 0, 0, 0, 1, 0, 24, 0, 0, 0, 0, 0,
						64, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 						0, 0, 255, 255, 255, 255, 255, 255};
		if (m_nHeight >= 255 || m_nWidth >= 255) {
			std::cout<<"Height, Width Too Large, Not Supported\n";
			std::exit(0);
		}

		h8060[18] = m_nWidth;
		h8060[22] = m_nHeight;
		for (int i = 0; i<54; i++) fprintf(fp, "%c", h8060[i]);
		if ((count=fwrite(RGBBuf, 1, RGB_SIZE, fp)) != RGB_SIZE)
			printf("Write BMP file data failed.\n");
			fclose(fp);
			return true;
		} else {
			return false;
		}
}

int y2bmain(Figure &scaled, char* argv) {
	CUYVY2BMP test(SCALE_WIDTH, SCALE_HEIGHT);
	int tmp;
	u_int8_t *pSrcBuf = scaled.figure;
	u_int8_t *pDstBuf = (u_int8_t*) malloc(test.GetHeight()*test.GetWidth()*3);

	printf("\n%i %i\n", pSrcBuf[0], pSrcBuf[1]);

	test.UYVY2BMP(pDstBuf, pSrcBuf);

	test.WriteBMPFile(argv, pDstBuf, 24);

	free(pDstBuf);
	return 0;
}
