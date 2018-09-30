/*---------------------------------------------------------*\
|  Definitions for MSI SteelSeries Keyboard Interface       |
|                                                           |
|  Adam Honse (calcprogrammer1@gmail.com), 12/11/2016       |
\*---------------------------------------------------------*/

#ifndef DREVO_KEYBOARD_H
#define DREVO_KEYBOARD_H
#include <sstream>
#include <wchar.h>
#include <string.h>

#include "VisualizerDefines.h"

class DrevoKeyboard
{
public:
	DrevoKeyboard();
    ~DrevoKeyboard();

    void Initialize();
    bool SetLEDs(COLORREF pixels[64][256]);
};
#endif

