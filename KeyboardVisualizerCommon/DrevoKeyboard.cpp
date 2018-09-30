#include "DrevoKeyboard.h"
#include "VisualizerDefines.h"
#include "UsbDevice.h"
#define DREVO_ENABLED

#ifdef DREVO_ENABLED
int y_id_list[6];
int cols = 17;
int dev_columns;

static float LED_TABLE[6][18] = {
	//		esc			f1		f2			f3			f4						f5		 f6		f7			f8		 f9		f10		 f11		f12       PS 	  SL		PB
	/* 0 */	{0x29,    0x3a,     0x3b,     0x3c,       0x3d,       0x00,      0x3e,     0x3f,     0x40,    0x41,    0x42,      0x43,     0x44,     0x45, 0x00 ,  0x46, 0x47 ,  0x48},

	/* 1 */ {0x35,    0x1e,     0x1f,     0x20,       0x21,       0x22,      0x23,     0x24,     0x25,    0x26,    0x27,      0x2d,      0x2e,     0x2a,  0x00 ,   0x49,    0x4a,    0x4b},
	/* 2 */ {0x2b,    0x14,     0x1a,     0x08,       0x15,       0x17,      0x1c,     0x18,     0x0c,    0x12,    0x13,      0x2f,      0x30,     0x31,  0x00 ,   0x4c,    0x4d,    0x4e},
	/* 3 */ {0x39,    0x04,     0x16,     0x07,       0x09,       0x0a,      0x0b,     0x0d,     0x0e,    0x0f,    0x33,      0x34,      0x28,     0x00,  0x00 ,   0x00,    0x00,    0x00},
	/* 4 */ {0xe1,    0x1d,     0x1b,     0x06,       0x19,       0x05,      0x11,     0x10,     0x36,    0x37,    0x38,      0xe5,      0x00,     0x00,  0x00 ,   0x00,    0x52,    0x00},
	/* 5 */ {0xe0,    0xe3 ,    0xe2 ,    0x00,       0x00,       0x00,      0x2c,     0x00,     0x00,    0x00,    0xe6,      0xed,      0x65,     0xe4,  0x00 ,   0x50,    0x51,    0x4f}
};

int ZXIndex[18];
int ZYIndex[6];

static void SetupKeyboardGrid(int x_count, int y_count, int * x_idx_list, int * y_idx_list)
{
	for (int x = 0; x < x_count; x++)
	{
		if (x < ((x_count) / 2))
		{
			x_idx_list[x] = (x * (SPECTROGRAPH_COLS / (x_count - 1))) + (0.5f * (SPECTROGRAPH_COLS / (x_count - 1)));
		}
		else
		{
			x_idx_list[x] = (x * (SPECTROGRAPH_COLS / (x_count - 1))) - (0.5f * (SPECTROGRAPH_COLS / (x_count - 1)));
		}

	}
	for (int y = 0; y < y_count; y++)
	{
		y_idx_list[y] = ROW_IDX_SPECTROGRAPH_TOP + (y * (SPECTROGRAPH_ROWS / y_count )) + (0.5f * (SPECTROGRAPH_ROWS / y_count));
	}
}

static UsbDevice usb;
static bool init_ok = true;

DrevoKeyboard::DrevoKeyboard()
{
}


DrevoKeyboard::~DrevoKeyboard()
{
}


void DrevoKeyboard::Initialize()
{
#ifdef DREVO_ENABLED
    //Look for MSI SteelSeries Keyboard
    if (usb.OpenDevice(0x0416, 0xA0F8, 0))
    {
        init_ok = true;
    }
    else
    {
        init_ok = false;
    }

	SetupKeyboardGrid(18, 6, ZXIndex, ZYIndex);
	
#endif
}

bool DrevoKeyboard::SetLEDs(COLORREF pixels[64][256])
{
#ifdef DREVO_ENABLED
    //Shout out to bparker06 for reverse engineering the MSI keyboard USB protocol!
    // https://github.com/bparker06/msi-keyboard/blob/master/keyboard.cpp for original implementation
	int count = 0;
	int count2 = 0;
    if(!init_ok)
    {
        return false;
    }

    unsigned char buf[32] = { 0 };
	buf[0] = 0x06;
	buf[1] = 0xbe;
	buf[2] = 0x19;
	buf[3] = 0x00;
	buf[4] = 0x01;
	buf[5] = 0x01;
	buf[6] = 0x0e;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (LED_TABLE[i][j] >= 0)
			{
				COLORREF color = pixels[ZYIndex[i]][ZXIndex[j]];

				buf[7 + count] = LED_TABLE[i][j];

				int color_pos = count * 4;

				buf[12 + color_pos] = GetRValue(color);
				buf[13 + color_pos] = GetGValue(color);
				buf[14 + color_pos] = GetBValue(color);


				if (count == 4)
				{
					count = 0;


					usb.WriteToDevice(buf, 32);
				}
				else
					if (count2 == 107)
					{
						usb.WriteToDevice(buf, 32);
					}
				count++;
				count2++;
			}

		}
	}

#endif

    return init_ok;
}
#endif