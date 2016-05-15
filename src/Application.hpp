/*
* Copyright © 2016 by Krzysztof Taperek <krzysztoftaperek@gmail.com>
*
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*/

#pragma once

#include <iostream>

#include "libusb.h"

#include "Log.hpp"

class Application
{
	public:
		Application();
		~Application();

		void PrintDevicesList();

	private:
		void InitLibUSB();
		void CloseLibUSB();
};
