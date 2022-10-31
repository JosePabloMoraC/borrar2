#include <wx/wx.h>

class MenuFrame : public wxFrame {
public:
	MenuFrame(const wxString& title);
private:
	void OnQuit(wxCommandEvent& event);
	void OnInstructions(wxCommandEvent& event);
	void OnGame(wxCommandEvent& event);
};