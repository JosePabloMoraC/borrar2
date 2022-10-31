#ifndef SELECTIONFRAME_HH
#define SELECTIONFRAME_HH

#include <MainFrame.hh>
#include <wx/radiobut.h>


class SelectionFrame : public wxFrame
{
public:
	SelectionFrame(const wxString& title);
private:
	void OnButtonClicked(wxCommandEvent& evt);
	int nRows = 5;
	int nColumns = 5;
	PlayerType player1 = HUMAN;
	PlayerType player2 = HUMAN;
	void OnInitGame();
	void OnPlayer1(wxCommandEvent& evt);
	void OnPlayer2(wxCommandEvent& evt);
	void OnRowsSlider(wxCommandEvent& evt);
	void OnColumnsSlider(wxCommandEvent& evt);
};



#endif