#include <wx/wx.h>
#include <wx/event.h>
#include <NewGameDialog.hh>

NewGameDialog::NewGameDialog(wxWindow* parent, const wxString& title):
wxDialog(parent, -1, title, wxPoint(500,300), wxSize(800, 400)) 
{
  Bind(wxEVT_CLOSE_WINDOW, &NewGameDialog::OnClose, this);
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* playerSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* columnsRows = new wxBoxSizer(wxHORIZONTAL);
  //wxBoxSizer* colors = new wxBoxSizer(wxHORIZONTAL);

  //Type of players
  wxStaticText *playerOneType = new wxStaticText(this, wxID_ANY,"Type of player A: ");
  wxStaticText *playerTwoType = new wxStaticText(this, wxID_ANY,"Type of player B: ");

  wxArrayString choices;
  choices.Add("Human");
  choices.Add("AI-Easy");
  choices.Add("AI-Medium");
  choices.Add("AI-Hard");
  choices.Add("AI-Extreme");

  wxRadioBox *choiceA = new wxRadioBox(this, wxID_ANY, "", wxDefaultPosition,wxDefaultSize, choices, 5, wxRA_SPECIFY_ROWS);

  wxRadioBox *choiceB = new wxRadioBox(this, wxID_ANY, "", wxDefaultPosition,wxDefaultSize, choices, 5, wxRA_SPECIFY_ROWS);

  playerSizer -> Add(playerOneType);
  playerSizer -> Add(choiceA);
  playerSizer -> AddSpacer(70);
  playerSizer -> Add(playerTwoType);
  playerSizer -> Add(choiceB);

  //Set rows and cols
  wxStaticText *nRows = new wxStaticText(this,wxID_ANY,"Rows: ");
  wxStaticText *nColumns = new wxStaticText(this,wxID_ANY,"Columns: ");
  wxSlider * rows = new wxSlider(this,wxID_ANY, 10, 2, 20, wxDefaultPosition,wxSize(170,50),wxSL_LABELS|wxSL_AUTOTICKS);
  wxSlider * columns = new wxSlider(this,wxID_ANY, 10, 2, 20, wxDefaultPosition,wxSize(170,50),wxSL_LABELS|wxSL_AUTOTICKS);

  columnsRows->Add(nRows);
  columnsRows->Add(rows);
  columnsRows-> AddSpacer(50);
  columnsRows->Add(nColumns);
  columnsRows->Add(columns);

  /*
  //Set Color for players
  wxStaticText *colorA = new wxStaticText(this,wxID_ANY,"Choose a color to identify your turn Player A: ");
  wxStaticText *colorB = new wxStaticText(this,wxID_ANY,"Choose a color to identify your turn Player B: ");


  wxArrayString choicesColorA;
  choicesColorA.Add("Red");
  choicesColorA.Add("Green");
  choicesColorA.Add("Blue");
  choicesColorA.Add("Purple");
  wxRadioBox *choiceColorA = new wxRadioBox(this, wxID_ANY, "", wxDefaultPosition,wxDefaultSize,choicesColorA);

  wxArrayString choicesColorB;
  choicesColorB.Add("Orange");
  choicesColorB.Add("Yellow");
  choicesColorB.Add("Cyan");
  choicesColorB.Add("Pink");
  wxRadioBox *choiceColorB = new wxRadioBox(this, wxID_ANY, "", wxDefaultPosition,wxDefaultSize,choicesColorB);

  colors->Add(colorA);
  colors->Add(choiceColorA);
  colors->Add(colorB);
  colors->Add(choiceColorB);
  */

  //Puts everything together
  //wxSizer* buttonSizer = CreateButtonSizer(wxOK);

  wxPanel* Panel1 = new wxPanel(this, 11000);
  wxButton* button = new wxButton(Panel1, 10000, "First");
 

  mainSizer->Add(playerSizer, 0, wxLEFT | wxBOTTOM, 20);
  mainSizer->Add(columnsRows, 1, wxLEFT | wxBOTTOM, 20);

  mainSizer->Add(button, 2, wxLEFT | wxBOTTOM, 20);
  

  //button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
  //mainSizer->Add(colors,1, wxEXPAND | wxBOTTOM, 5);
  //mainSizer->Add(buttonSizer,0,wxALIGN_RIGHT|wxBOTTOM,5);
  SetSizer(mainSizer);
  SetMinSize(wxSize(535, 200));
  Fit();
}

void NewGameDialog::OnButtonClicked(wxCommandEvent& evt) {
	wxLogMessage("Work in progress...");
}

void NewGameDialog::OnClose(wxCloseEvent& event) {
	if (event.GetId() == wxOK) {
		wxLogMessage("Work in progress...");
	}
}
