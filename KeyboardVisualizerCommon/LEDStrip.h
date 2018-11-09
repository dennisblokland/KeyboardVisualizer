/*---------------------------------------------------------*\
|  Definitions for Generic LED Strip Interface              |
|                                                           |
|  Adam Honse (calcprogrammer1@gmail.com), 12/11/2016       |
\*---------------------------------------------------------*/

#ifndef LED_STRIP_H
#define LED_STRIP_H

#include "net_port.h"
#include "serial_port.h"

#include "VisualizerDefines.h"

#ifndef TRUE
#define TRUE true
#define FALSE false
#endif

enum
{
    LED_STRIP_NORMAL,
    LED_STRIP_XMAS,
    LED_STRIP_HUE_PLUS
};

class LEDStrip
{
public:
    LEDStrip();
    ~LEDStrip();

    void Initialize(int led_type, char* ledstring, int matrix_size, int matrix_pos, int sections, int rotate_x, bool mirror_x, bool mirror_y, bool single_color);
    void InitializeHuePlus(char * ledstring);
    void InitializeSerial(char* portname, int baud);
    void InitializeUDP(char* clientname, char* port);
    void InitializeEspurna(char* clientname, char* port, char * apikey);
    char* GetLEDString();
    void SetNumLEDs(int numleds, int matrix_size, int matrix_pos, int sections, int rotate_x, bool mirror_x, bool mirror_y, bool single_color);
    void SetLEDs(COLORREF pixels[64][256]);
    void SetLEDsEspurna(COLORREF pixels[64][256]);
    void SetLEDsXmas(COLORREF pixels[64][256]);
    void SetLEDsHuePlus(COLORREF pixels[64][256]);
    void SetPixels(COLORREF pixels[64][256]);
    void SetDelay(int delay);
    void LEDStripUpdateThread();

	int led_type = LED_STRIP_NORMAL;

private:
    int baud_rate;
    int num_leds;
    int fans;
    int channel;
    int led_delay = 10;
    const int hueSize = 125;

    int * LEDStripXIndex;
    int * LEDStripYIndex;

    char led_string[1024];
    char port_name[128];
    char client_name[1024];
    char espurna_apikey[128];
    COLORREF (*led_pixels)[256] = NULL;
    serial_port *serialport;
    net_port *udpport;
    net_port *tcpport;
};

#endif
