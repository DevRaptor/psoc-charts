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

std::ostream* target;


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

	wxBoxSizer* sizer;
	sizer = new wxBoxSizer(wxVERTICAL);

	logger = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY);
	sizer->Add(logger, 1, wxALL|wxEXPAND, 5);

	SetSizer(sizer);
	Layout();


	redirect = new wxStreamToTextRedirector(logger, target);
	Log("Redirect log to wxTextCtrl\n");
}

MainFrame::~MainFrame()
{
	delete redirect;
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

