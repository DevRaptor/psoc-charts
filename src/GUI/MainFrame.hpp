/*
* Copyright © 2016 by Krzysztof Taperek <krzysztoftaperek@gmail.com>
*
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*/

#pragma once

#include <memory>
#include <wx/wx.h>
#include <wx/aui/framemanager.h>

#include "../Model/DevicesHandler.hpp"


class LogPanel : public wxPanel
{
	public:
		LogPanel(wxWindow* parent);

		~LogPanel() {}

	protected:
		std::unique_ptr<wxTextCtrl> logger;
		std::unique_ptr<wxStreamToTextRedirector> redirect;

};

class SettingsPanel : public wxPanel
{
	public:
		SettingsPanel(wxWindow* parent);

		~SettingsPanel() {}

	protected:
		std::unique_ptr<wxButton> button;
		std::unique_ptr<wxStaticText> description;
};

class ChartPanel : public wxPanel
{
	public:
		ChartPanel(wxWindow* parent);

		~ChartPanel() {}

	protected:
		std::unique_ptr<wxButton> button;
		std::unique_ptr<wxStaticText> description;
};



class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
		~MainFrame();
	private:
		DevicesHandler devhandler;


		wxAuiManager layoutmanager;

		std::unique_ptr<ChartPanel> chartpanel;
		std::unique_ptr<LogPanel> logpanel;
		std::unique_ptr<SettingsPanel> settingspanel;

		void OnExit();
		void OnAbout();
};

