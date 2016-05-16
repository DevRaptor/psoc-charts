/*
* Copyright © 2016 by Krzysztof Taperek <krzysztoftaperek@gmail.com>
*
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*/


#include <iostream>

#include "libusb.h"

#include "../Log.hpp"
#include "DevicesHandler.hpp"

std::ostream* target;

void DevicesHandler::InitLibUSB()
{
	int libcode = libusb_init(NULL);

	if(libcode < 0)
		return;
}

void DevicesHandler::CloseLibUSB()
{
	libusb_exit(NULL);
}

DevicesHandler::DevicesHandler()
{
	InitLibUSB();

	target = &std::cout;
	Log("Init log!\n");
}

DevicesHandler::~DevicesHandler()
{
	CloseLibUSB();
}

void DevicesHandler::PrintDevicesList()
{
	libusb_device** devices;

	int errorcode = libusb_get_device_list(NULL, &devices);
	if (errorcode < 0)
		return;


	libusb_device* dev;

	uint8_t path[8];

	int i = 0;
	while ((dev = devices[i++]) != NULL)
	{
		libusb_device_descriptor desc;
		int r = libusb_get_device_descriptor(dev, &desc);
		if (r < 0)
		{
			Log("failed to get device descriptor");
			return;
		}

		int bus = libusb_get_bus_number(dev);
		int adress = libusb_get_device_address(dev);
		Log(IntToHexString(desc.idVendor), ":", IntToHexString(desc.idProduct),
			"\t(bus: ", bus, ", device: ", adress, ") \t");

		r = libusb_get_port_numbers(dev, path, sizeof(path));
		if (r > 0)
		{
			Log("path: ");
			for(int j = 0; j < r; j++)
				Log(static_cast<int>(path[j]), " ");
		}

		char buffer[128];

		uint8_t string_index[3];
		string_index[0] = desc.iManufacturer;
		string_index[1] = desc.iProduct;
		string_index[2] = desc.iSerialNumber;

		libusb_device_handle* handle = libusb_open_device_with_vid_pid(NULL, desc.idVendor, desc.idProduct);

		if(handle == NULL)
		{
			Log("\nCannot read descriptors\n");
			continue;
		}

		printf("\nReading buffer descriptors:\n");
		for (int k = 0; k < 3; k++)
		{
			if (string_index[k] == 0)
				continue;

			if (libusb_get_string_descriptor_ascii(handle, string_index[k], (unsigned char*)buffer, 128) >= 0)
			{
				Log("-", static_cast<int>(string_index[k]), ": ", buffer, "\n");
			}
		}

		Log("\n");

		libusb_close(handle);
	}

	libusb_free_device_list(devices, 1); //1 for unref all devices
}
