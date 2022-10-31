#ifndef MAINFRAME_HH
#define MAINFRAME_HH

#include <wx/wx.h>
#include <GameBoardPanel.hh>

class MainFrame : public wxFrame
{
public:
  MainFrame(const wxString& title, int nRows, int nColumns, PlayerType player1, PlayerType player2);
  void OnTimerMF(wxTimerEvent& event);
private:
	wxTimer m_timer;
	wxTimer* timer;
	wxStaticText* staticText;
	void OnButtonClicked(wxCommandEvent& evt);
	Board board;
};



#endif