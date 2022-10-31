#include <wx/wxprec.h>
#include <wx/wx.h>
#include <iostream>
#include <App.hh>
#include <MenuFrame.hh>
#include <SelectionFrame.hh>

enum {
    myID_INSTRUCTIONS = wxID_HIGHEST + 1,
    myID_GAME = 1000
};

MenuFrame::MenuFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    wxSize size = this->GetSize();
    int height = size.y;
    int width = size.x;
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxStaticText* gameName = new wxStaticText(panel, wxID_ANY, "DOTS AND BOXES", wxPoint((width / 4) * 2.5, height / 5));
    wxButton* buttonGame = new wxButton(panel, myID_GAME, wxT("Play Game"), wxPoint((width / 3) * 2, (height / 5) * 2));
    Connect(myID_GAME, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MenuFrame::OnGame));
    wxButton* buttonInstructions = new wxButton(panel, myID_INSTRUCTIONS, wxT("Help"), wxPoint((width / 3) * 2, (height / 5) * 3));
    Connect(myID_INSTRUCTIONS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MenuFrame::OnInstructions));
    wxButton* buttonQuit = new wxButton(panel, wxID_EXIT, wxT("Quit"), wxPoint((width / 3) * 2, (height / 5) * 4));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MenuFrame::OnQuit));
    buttonQuit->SetFocus();
}

void MenuFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MenuFrame::OnInstructions(wxCommandEvent& event)
{
    wxMessageBox(wxString::Format("For playing you need to take turns between the system or "
        "another player. You will have to make lines between the dots, "
        "you win points by completing a box drawing it's forth wall. "
        "The player with most points will win."));
}

void MenuFrame::OnGame(wxCommandEvent& event)
{   
    SelectionFrame* selectionFrame = new SelectionFrame("Dots & Boxes configuration");
    selectionFrame->SetClientSize(535, 400);
    selectionFrame->Center();
    selectionFrame->SetBackgroundColour(*wxWHITE);
    selectionFrame->Show(true);
    //NewGameDialog* config = new NewGameDialog(this, wxT("Settings"));
    //config->ShowModal();
    //config->Destroy();
    this->Close();
}
