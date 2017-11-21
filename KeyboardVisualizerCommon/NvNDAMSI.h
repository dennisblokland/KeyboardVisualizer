#ifndef NvNDAMSI_H
#define NvNDAMSI_H

#include "..\KeyboardVisualizerVC\stdafx.h"

#include "VisualizerDefines.h"

class NvNDAMSI
{
public:
	NvNDAMSI();
	~NvNDAMSI();

	void Initialize();
	bool SetLEDs(COLORREF pixels[64][256]);
};

#endif
