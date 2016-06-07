/*
* Copyright © 2016 by Krzysztof Taperek <krzysztoftaperek@gmail.com>
*
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*/

#pragma once

#include <vector>
#include <string>
#include "libusb.h"

struct command_status_wrapper
{
	uint8_t dCSWSignature[4];
	uint32_t dCSWTag;
	uint32_t dCSWDataResidue;
	uint8_t bCSWStatus;
};

class DevicesHandler
{
	public:
		DevicesHandler();
		~DevicesHandler();

		std::vector<std::string> PrintDevicesList();
		void OpenDevice(int vid, int pid);

	private:
		void InitLibUSB();
		void CloseLibUSB();
};
