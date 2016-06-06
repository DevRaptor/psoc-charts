/*
* Copyright © 2016 by Krzysztof Taperek <krzysztoftaperek@gmail.com>
*
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*/

#include <wx/stdstream.h>
#include <wx/sizer.h>

#include "../Log.hpp"
#include "MainFrame.hpp"

std::ostream* target = &std::cout;

LogPanel::LogPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(500, 300))
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	logger = std::make_unique<wxTextCtrl>(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY);
	sizer->Add(logger.get(), 1, wxALL|wxEXPAND, 5);

	SetSizer(sizer);
	Layout();

	redirect = std::make_unique<wxStreamToTextRedirector>(logger.get(), target);
	Log("Redirect log to wxTextCtrl\n");


}

SettingsPanel::SettingsPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 500))
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	button = std::make_unique<wxButton>(this, wxID_ANY, "Button");
	description = std::make_unique<wxStaticText>(this, wxID_ANY, "Description");

	sizer->Add(description.get(), 1, wxALL|wxEXPAND, 5);
	sizer->Add(button.get(), 1, wxALL|wxEXPAND, 5);

	SetSizer(sizer);
	Layout();
}

ChartPanel::ChartPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 500))
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	button = std::make_unique<wxButton>(this, wxID_ANY, "Button");
	description = std::make_unique<wxStaticText>(this, wxID_ANY, "Description");

	sizer->Add(description.get(), 1, wxALL|wxEXPAND, 5);
	sizer->Add(button.get(), 1, wxALL|wxEXPAND, 5);

	SetSizer(sizer);
	Layout();
}

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxMenu* menu_file = new wxMenu;

	menu_file->AppendSeparator();

	wxMenuItem* item_devlist = new wxMenuItem(menu_file, wxID_ANY, "Print devices list\tCtrl-P");
	menu_file->Append(item_devlist);

	wxMenuItem* item_exit = new wxMenuItem(menu_file, wxID_ANY, "Exit\tCtrl-Q");
	menu_file->Append(item_exit);


	wxMenu* menu_help = new wxMenu;

	wxMenuItem* item_help = new wxMenuItem(menu_help, wxID_ANY, "About...\tF1");
	menu_help->Append(item_help);

	wxMenuBar* menubar = new wxMenuBar;
	menubar->Append(menu_file, "&File");
	menubar->Append(menu_help, "&Help");

	SetMenuBar(menubar);
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");


	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, [&](auto) {this->devhandler.PrintDevicesList();},
	item_devlist->GetId());
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, [&](auto) {this->OnExit();}, item_exit->GetId());
	menu_help->Bind(wxEVT_COMMAND_MENU_SELECTED, [&](auto) {this->OnAbout();}, item_help->GetId());

	///////////////////////////////////////////


	layoutmanager.SetManagedWindow(this);


	chartpanel = std::make_unique<ChartPanel>(this);
	layoutmanager.AddPane(chartpanel.get(), wxCENTER, "Chart viewport");


	logpanel = std::make_unique<LogPanel>(this);
	layoutmanager.AddPane(logpanel.get(), wxBOTTOM, "Log");


	settingspanel = std::make_unique<SettingsPanel>(this);
	layoutmanager.AddPane(settingspanel.get(), wxAuiPaneInfo().Caption("Settings").Left().Layer(1).CloseButton(false));


	layoutmanager.Update();
}

MainFrame::~MainFrame()
{
	/*
	if sizer is a std::unique_ptr, then must detach sizer and don't auto delete him;
		sizer will be destroyed by unique pointer
	//SetSizer(NULL, false);
	*/

	layoutmanager.UnInit();
}


void MainFrame::OnExit()
{
	Close(true);
}

void MainFrame::OnAbout()
{
	wxMessageBox("psoc-charts help",
				 "About psoc-charts", wxOK | wxICON_INFORMATION);
}

