#include "UsbDevice.h"


UsbDevice::UsbDevice()
{

}

bool UsbDevice::OpenDevice(unsigned short vendor, unsigned short product, unsigned int MI)
{
    device = hid_open(vendor, product, 0);

    if (device == NULL)
    {
        return false;
    }

    return true;

}
bool UsbDevice::WriteToDevice(unsigned char* data, unsigned int length)
{

	hid_write(device, data, length);
	return true;
}
bool UsbDevice::SendToDevice(unsigned char* data, unsigned int length)
{
    hid_send_feature_report(device, data, length);
    return true;

}
