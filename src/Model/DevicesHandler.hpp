/*
* Copyright © 2016 by Krzysztof Taperek <krzysztoftaperek@gmail.com>
*
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*/

#pragma once

class DevicesHandler
{
	public:
		DevicesHandler();
		~DevicesHandler();

		void PrintDevicesList();

	private:
		void InitLibUSB();
		void CloseLibUSB();
};
