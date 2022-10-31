#include <SelectionFrame.hh>

SelectionFrame::SelectionFrame(const wxString& title) 
	: wxFrame(nullptr, wxID_ANY, title) 
{
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* playerSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* columnsRows = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	//Type of players
	wxStaticText* playerOneType = new wxStaticText(this, wxID_ANY, "Type of player A: ");
	wxStaticText* playerTwoType = new wxStaticText(this, wxID_ANY, "Type of player B: ");

	wxArrayString choices;
	choices.Add("Human");
	choices.Add("AI-Easy");
	choices.Add("AI-Medium");
	choices.Add("AI-Hard");
	choices.Add("AI-Extreme");

	wxRadioBox* choiceA = new wxRadioBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices, 5, wxRA_SPECIFY_ROWS);
	wxRadioBox* choiceB = new wxRadioBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices, 5, wxRA_SPECIFY_ROWS);

	choiceA-> Bind(wxEVT_RADIOBOX, &SelectionFrame::OnPlayer1, this);
	choiceB-> Bind(wxEVT_RADIOBOX, &SelectionFrame::OnPlayer2, this);


	playerSizer->Add(playerOneType);
	playerSizer->Add(choiceA);
	playerSizer->AddSpacer(70);
	playerSizer->Add(playerTwoType);
	playerSizer->Add(choiceB);

	wxStaticText* nRows = new wxStaticText(this, wxID_ANY, "Rows: ");
	wxStaticText* nColumns = new wxStaticText(this, wxID_ANY, "Columns: ");
	wxSlider* rows = new wxSlider(this, wxID_ANY, 5, 2, 20, wxDefaultPosition, wxSize(170, 50), wxSL_LABELS | wxSL_AUTOTICKS);
	wxSlider* columns = new wxSlider(this, wxID_ANY, 5, 2, 20, wxDefaultPosition, wxSize(170, 50), wxSL_LABELS | wxSL_AUTOTICKS);
	
	rows->Bind(wxEVT_SLIDER, &SelectionFrame::OnRowsSlider, this);
	columns->Bind(wxEVT_SLIDER, &SelectionFrame::OnColumnsSlider, this);


	columnsRows->Add(nRows);
	columnsRows->Add(rows);
	columnsRows->AddSpacer(50);
	columnsRows->Add(nColumns);
	columnsRows->Add(columns);

	wxButton* buttonStart = new wxButton(this, 1005, wxT("Start Game"), wxDefaultPosition, wxSize(80, 20));
	buttonStart->Bind(wxEVT_BUTTON, &SelectionFrame::OnButtonClicked, this);

	buttonSizer->Add(buttonStart);
	mainSizer->Add(playerSizer, 0, wxLEFT | wxBOTTOM, 20);
	mainSizer->Add(columnsRows, 1, wxLEFT | wxBOTTOM, 20);
	mainSizer->Add(buttonSizer, 2, wxALIGN_CENTRE);

	SetSizer(mainSizer);
	SetMinSize(wxSize(535, 200));
}

void SelectionFrame::OnButtonClicked(wxCommandEvent& evt) {
	MainFrame* mainFrame = new MainFrame("Dots & Boxes", nRows, nColumns, player1, player2);
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
	this->Close();
}

void SelectionFrame::OnInitGame() {

}
void SelectionFrame::OnPlayer1(wxCommandEvent& evt) {
	switch (evt.GetSelection())
	{
	case 0:
		player1 = HUMAN;
		break;
	case 1:
		player1 = EASY;
		break;
	case 2:
		player1 = MEDIUM;
		break;
	case 3:
		player1 = MINIMAX;
		break;
	case 4:
		player1 = ALFABETA_PRUNING;
		break;
	default:
		break;
	}
}

void SelectionFrame::OnPlayer2(wxCommandEvent& evt) {
	switch (evt.GetSelection())
	{
	case 0:
		player2 = HUMAN;
		break;
	case 1:
		player2 = EASY;
		break;
	case 2:
		player2 = MEDIUM;
		break;
	case 3:
		player2 = MINIMAX;
		break;
	case 4:
		player2 = ALFABETA_PRUNING;
		break;
	default:
		break;
	}
}

void SelectionFrame::OnRowsSlider(wxCommandEvent& evt){
	nRows = evt.GetInt();
}

void SelectionFrame::OnColumnsSlider(wxCommandEvent& evt) {
	nColumns = evt.GetInt();
}