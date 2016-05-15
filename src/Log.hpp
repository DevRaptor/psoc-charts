/*
* Copyright © 2016 by Krzysztof Taperek <krzysztoftaperek@gmail.com>
*
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*/

#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

extern std::ostream* target;

template<typename T>
void Log(T arg)
{
	(*target)<<arg;
	(*target).flush();
}

template<typename T1, typename ...Ts>
void Log(T1 arg, Ts... args)
{
	Log(arg);
	Log(args...);
}

template< typename T >
std::string IntToHexString(T i)
{
	std::stringstream stream;
	stream << std::setfill ('0') << std::setw(sizeof(T)*2)
		   << std::hex << i;
	return stream.str();
}
