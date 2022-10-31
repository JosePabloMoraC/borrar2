#ifndef GAMEBOARDPANEL_HH
#define GAMEBOARDPANEL_HH

#include <chrono>
#include <thread>
#include <wx/wx.h>
#include "wx/sizer.h"
#include "MiniMax.hh"
#include "PlayerFactory.hh"
#include <wx/timer.h>


class GameBoardPanel : public wxPanel 
{
  public:
    GameBoardPanel(wxFrame* parent, Board& board, PlayerType player1, PlayerType player2); 
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void renderGame(wxDC& dc);
    void playGame();
    short scorePlayer1;
    short scorePlayer2;
    bool doHumanMove(OwnerType owner);
    void OnTimer(wxTimerEvent& event);
  private:
    wxTimer m_timer;
    wxDECLARE_EVENT_TABLE();
    void OnMouseLeftClick(wxMouseEvent& evt);
    void OnMouseMove(wxMouseEvent& evt);
    void drawTemporalLine(wxDC& dc, int rowIndex, int columIndex, Directions direction, double cellWidth, double cellHeight); 
    Movement getTemporalMovement(double xMousePosition, double yMousePosition);
    Directions getDirection(double xPosition, double yPosition, int columnIndex, int rowIndex);
    Board& myBoard;
    PlayerType player1;
    PlayerType player2;
    Player* py1;
    Player* py2;
    Movement temporalMovement = Movement{ -1, -1, EMPTY };
    Movement humanMovement = Movement{-1, -1, EMPTY};
    bool displayedDialog;
    short gameTurn = 1; 
};

#endif