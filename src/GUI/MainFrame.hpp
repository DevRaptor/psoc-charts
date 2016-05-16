/*
* Copyright © 2016 by Krzysztof Taperek <krzysztoftaperek@gmail.com>
*
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*/

#pragma once

#include "wx/wx.h"

#include "../Model/DevicesHandler.hpp"


class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	private:
		DevicesHandler devhandler;

		void OnExit();
		void OnAbout();
};
