#ifndef APP_HH
#define APP_HH

#include <GameBoardPanel.hh>
#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class App : public wxApp
{
public:
  bool OnInit();
  void OnInitFrame(int nRows, int nColumns, PlayerType player1, PlayerType player2);
  void Restart();
  void OnRestartButtonClicked(wxCommandEvent& evt);
  GameBoardPanel * drawPane;

};

#endif