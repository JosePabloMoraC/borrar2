#include <MainFrame.hh>
#include <iostream>
#include <GameBoardPanel.hh>
#include <wx/dcclient.h>



// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

using namespace std;

MainFrame :: MainFrame (const wxString& title, int nRows, int nColumns, PlayerType player1, PlayerType player2): 
    wxFrame(nullptr, wxID_ANY, title), board(Board{(nRows + 1), (nColumns +1)})
{
    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 300));
    wxSize size = panel->GetSize();

    //board = Board{ 4,6 };
    wxPanel* game_panel = new GameBoardPanel((wxFrame*)this, board, player1, player2);
    game_panel->SetDoubleBuffered(true);
    game_panel->SetBackgroundColour(*wxWHITE);

    this->timer = new wxTimer(this);
    (*this->timer).Start(100);
    this->Bind(wxEVT_TIMER, &MainFrame::OnTimerMF, this);

    this->staticText = new wxStaticText(panel, wxID_ANY, " ", wxPoint(10, 100));

    auto button = new wxButton(panel, wxID_ANY, "Nueva Partida", wxPoint(3, 20), wxSize(100, 40));
    button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
    
    CreateStatusBar();

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel, 1 , wxEXPAND | wxLEFT| wxTOP | wxRIGHT, 4);
    sizer->Add(game_panel, 2, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 4);
    this->SetSizerAndFit(sizer); 
}

void MainFrame::OnTimerMF(wxTimerEvent& event) {
    wxString message = wxString::Format("Player                   Points\n\nPlayer 1:                   %d\nPlayer 2:                   %d", 
                                        board.getScoreP1(), board.getScoreP2());
    this->staticText->SetLabel(message);
}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
    Close(true);
    evt.Skip();
}
