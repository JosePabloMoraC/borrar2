#pragma once
#include <wx/wx.h>
#include "PlayerFactory.hh"

class NewGameDialog : public wxDialog {
public:
  NewGameDialog(wxWindow* parent, const wxString& title);
//virtual ~NewGameDialog();
private:
	void OnButtonClicked(wxCommandEvent& evt);
	void OnClose(wxCloseEvent& event);
	int nRows;
	int nColums;
	PlayerType player1;
	PlayerType player2;
};