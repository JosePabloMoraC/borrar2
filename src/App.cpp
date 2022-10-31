#include <App.hh>
#include <MainFrame.hh>
#include <MenuFrame.hh>
#include <GameBoardPanel.hh>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    this->Bind(wxEVT_BUTTON, &App::OnRestartButtonClicked, this);
    MenuFrame* menuFrame = new MenuFrame("Prueba");
    menuFrame->SetClientSize(600, 400);
    menuFrame->Center();
    menuFrame->Show(true);

    return true;

  //drawPane = new GameBoardPanel((wxFrame*)mainFrame);
    //OnInitFrame(3, 5, HUMAN, ALFABETA_PRUNING);
}

void App::OnInitFrame(int nRows, int nColumns, PlayerType player1, PlayerType player2) {
    MainFrame* mainFrame = new MainFrame("Dots & Boxes", nRows, nColumns, player1, player2);
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show();    
}

void App::Restart() {
    this->Bind(wxEVT_BUTTON, &App::OnRestartButtonClicked, this);
    MenuFrame* menuFrame = new MenuFrame("Prueba");
    menuFrame->SetClientSize(600, 400);
    menuFrame->Center();
    menuFrame->Show(true);

}

void App::OnRestartButtonClicked(wxCommandEvent& evt) {
    Restart();
}