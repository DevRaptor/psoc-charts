/*
* Copyright © 2016 by Krzysztof Taperek <krzysztoftaperek@gmail.com>
*
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*/

#include "GUI/MainFrame.hpp"

class Application: public wxApp
{
	public:
		virtual bool OnInit()
		{
			MainFrame* frame = new MainFrame("psoc-charts", wxPoint(50, 50), wxSize(500, 500));
			frame->Show(true);
			return true;
		}
};

wxIMPLEMENT_APP(Application);
