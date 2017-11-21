
#include "stdafx.h"
#include "VisualizerDefines.h"
#include "NvNDAMSI.h"
#include <windows.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

static boolean failed;


int nda_init();
int nda_setled(int percent, int r, int g, int b);
void nda_close();

NvNDAMSI::NvNDAMSI()
{
}


NvNDAMSI::~NvNDAMSI()
{
}

void NvNDAMSI::Initialize()
{
	//failed = !nda_init();

	//nda_close();
}
unsigned int createRGB(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

bool NvNDAMSI::SetLEDs(COLORREF pixels[64][256])
{

		
		COLORREF single_color = pixels[ROW_IDX_SINGLE_COLOR][0];
		nda_init();
		nda_setled(-1, GetRValue(single_color) / 2.55f, GetGValue(single_color) / 2.55f, GetBValue(single_color) / 2.55f);
		nda_close();
		return TRUE;
	

}
