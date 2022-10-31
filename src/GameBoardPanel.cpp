#include <App.hh>
#include <MainFrame.hh>
#include <GameBoardPanel.hh>
#include <stdio.h>


#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

wxBEGIN_EVENT_TABLE(GameBoardPanel, wxPanel)
    EVT_TIMER(1500, GameBoardPanel::OnTimer)
wxEND_EVENT_TABLE()


GameBoardPanel::GameBoardPanel(wxFrame* parent, Board& board, PlayerType player1, PlayerType player2) :
    wxPanel(parent), myBoard(board), player1(player1), player2(player2), scorePlayer1(0), scorePlayer2(0),
    m_timer(this, 1500), displayedDialog(false)
{
    //movements = 10;
    PlayerFactory factory;
    py1 = factory.build(player1, PLAYER1);
    py2 = factory.build(player2, PLAYER2);
    Bind(wxEVT_PAINT, &GameBoardPanel::paintEvent, this);
    Bind(wxEVT_LEFT_DOWN, &GameBoardPanel::OnMouseLeftClick, this);
    Bind(wxEVT_MOTION, &GameBoardPanel::OnMouseMove, this);
    m_timer.Start(17);  
}


void GameBoardPanel::paintEvent(wxPaintEvent & evt){
  wxPaintDC dc(this);
  renderGame(dc);
  //render(dc);
}

void GameBoardPanel::paintNow() {
  wxClientDC dc(this);
  renderGame(dc);
  //render(dc);
}

void GameBoardPanel::renderGame(wxDC& dc){
    wxSize size = this->GetSize();
    dc.SetPen(*wxBLACK_PEN);
    int nrows = myBoard.getBoardRowSize();
    int ncolumns = myBoard.getBoardColSize();

    double xMargin = 27; 
    double yMargin = 27; 

    double boardWidth = size.x - 2*xMargin; 
    double boardHeight = size.y - 2*yMargin;

    double cellWidth = boardWidth / ncolumns; 
    double cellHeight = boardHeight / nrows;

    drawTemporalLine(dc, temporalMovement.getXPos(), temporalMovement.getYPos(), temporalMovement.getLineDirection(), cellWidth, cellHeight);

    double columnStartPosition = xMargin;
    for (int i = 0; i < ncolumns + 1; i++) {
      double rowStartPosition = yMargin;
      for (int j = 0; j < nrows + 1; j++) {       
        Cell* celda = myBoard.getCell(j, i);
            // Dibujar celdas rellenas 
            if (i < ncolumns && j < nrows) {
                if (celda->getBoxOwner() == PLAYER1) {
                    dc.SetBrush(*wxBLUE_BRUSH);
                    dc.DrawRectangle((columnStartPosition - 2 ), (rowStartPosition - 2), (cellWidth + 2), (cellHeight + 2));

                }
                else {
                    if (celda->getBoxOwner() == PLAYER2) {
                        dc.SetBrush(*wxRED_BRUSH);
                        dc.DrawRectangle((columnStartPosition - 2), (rowStartPosition - 2), (cellWidth + 2), (cellHeight + 2));
                    }
                }

               // Dibujar línea de la derecha de las cajas
              if (celda->east == PLAYER1){
                dc.SetBrush(*wxBLUE_BRUSH);
                dc.DrawRectangle((columnStartPosition + cellWidth - 2), rowStartPosition, 5, cellHeight);
              } else {
                    if (celda->east == PLAYER2) {
                      dc.SetBrush(*wxRED_BRUSH);
                      dc.DrawRectangle((columnStartPosition + cellWidth - 2), rowStartPosition, 5, cellHeight);
                    }
                }  
              // Dibujar línea de la izquieda de las cajas
              if (celda->west == PLAYER1){
                dc.SetBrush(*wxBLUE_BRUSH);
                dc.DrawRectangle((columnStartPosition - 2), rowStartPosition, 5, cellHeight);
              } else {
                    if (celda->west == PLAYER2) {
                      dc.SetBrush(*wxRED_BRUSH);
                      dc.DrawRectangle((columnStartPosition - 2), rowStartPosition, 5, cellHeight);
                    }
                } 
              // Dibujar línea superior 
               if (celda -> north == PLAYER1) {
                    dc.SetBrush(*wxBLUE_BRUSH);
                    dc.DrawRectangle((columnStartPosition - 2), (rowStartPosition-2), cellWidth, 5);
                }
                else {
                    if (celda->north == PLAYER2) {
                        dc.SetBrush(*wxRED_BRUSH);
                        dc.DrawRectangle((columnStartPosition - 2), (rowStartPosition-2), cellWidth, 5);
                    }
                }
            // Dibujar línea inferior 
            if (celda -> south == PLAYER1) {
                    dc.SetBrush(*wxBLUE_BRUSH);
                    dc.DrawRectangle((columnStartPosition - 2), (rowStartPosition + cellHeight - 2), cellWidth, 5);
                }
                else {
                    if (celda -> south == PLAYER2) {
                        dc.SetBrush(*wxRED_BRUSH);
                        dc.DrawRectangle((columnStartPosition - 2), (rowStartPosition+ cellHeight - 2), cellWidth, 5);
                    }
                }
          }
        dc.SetBrush(*wxBLACK_BRUSH);
        //Dibujar el circulo
        dc.DrawCircle(columnStartPosition, rowStartPosition, 5);
        rowStartPosition += cellHeight;
      }
        columnStartPosition +=  cellWidth;
    }
}

void GameBoardPanel::OnTimer(wxTimerEvent& event){
    playGame();

    if (gameTurn == 1) {
        wxLogStatus("Next turn : Player 1");
    }
    else {
        wxLogStatus("Next turn : Player 2");
    }

    Refresh();
}


void GameBoardPanel::OnMouseLeftClick(wxMouseEvent& evt) {
    wxPoint position = evt.GetPosition();
    Movement movement = getTemporalMovement(position.x, position.y);
    humanMovement = movement;
    temporalMovement = Movement{ -1, -1, EMPTY };
}


void GameBoardPanel::OnMouseMove(wxMouseEvent& evt) {
    wxClientDC dc(this);
    wxPoint position = evt.GetPosition();

    Movement move = getTemporalMovement(position.x, position.y);
    temporalMovement = move;
}


void GameBoardPanel::drawTemporalLine(wxDC& dc, int rowIndex, int columIndex, Directions direction, double cellWidth, double cellHeight){
    double xMargin = 27; 
    double yMargin = 27; 
    switch (direction) {
      dc.SetBrush(*wxWHITE_BRUSH);
    case WEST:
        dc.DrawRectangle((xMargin + (columIndex) * (cellWidth) - 2), (yMargin + rowIndex*cellHeight - 2), 5, cellHeight);    
      break;
    case EAST:
        //dc.DrawRectangle((columnStartPosition + cellWidth - 2), rowStartPosition, 7, cellHeight);
        dc.DrawRectangle((xMargin + (columIndex + 1) * (cellWidth) - 2), (yMargin + rowIndex*cellHeight - 2), 5, cellHeight);
      break;
    case NORTH:
      dc.DrawRectangle((xMargin + (columIndex) * (cellWidth) - 2), (yMargin + rowIndex*cellHeight - 2), cellWidth, 5);
      break;
    case SOUTH:
      dc.DrawRectangle((xMargin + (columIndex) * (cellWidth) - 2), (yMargin + (rowIndex + 1)*cellHeight - 2), cellWidth, 5);
      break;
    default:
      break;
    }
}

Movement GameBoardPanel::getTemporalMovement(double xMousePosition, double yMousePosition){
  double xMargin = 27; 
  double yMargin = 27; 

  wxSize size = this->GetSize();

  int nrows = myBoard.getBoardRowSize(); //TODO
  int ncolumns = myBoard.getBoardColSize(); //TODO

  double boardWidth = size.x - 2*xMargin; 
  double boardHeight = size.y - 2*yMargin;

  double cellWidth = boardWidth / ncolumns; 
  double cellHeight = boardHeight / nrows;
  //Para obtener la posición X (columna) en board.
  double xPosition = (xMousePosition - xMargin) / cellWidth;
    //Para obtener la posición Y (fila) en board.
  double yPosition = (yMousePosition - yMargin) / cellHeight;

  int columnIndex = int(xPosition);
  int rowIndex = int(yPosition);

  columnIndex = std::min(ncolumns-1, columnIndex);
  rowIndex = std::min(nrows - 1, rowIndex);

  double columnStartPosition = xMargin;
  double rowStartPosition = yMargin;

  return Movement(rowIndex, columnIndex, getDirection(xPosition, yPosition, columnIndex, rowIndex));
}

Directions GameBoardPanel::getDirection(double xPosition, double yPosition, int columnIndex, int rowIndex){
  double fromXstart = xPosition - columnIndex; 
  double fromYstart = yPosition - rowIndex; 
  // Usamos como "margen" de las líneas 0.2 
  if(fromYstart < 0.2 && fromYstart > -0.2 && fromXstart > 0.1 && fromXstart < 0.9){
    return NORTH; 
  } 

  if(fromYstart < 1.2 && fromYstart > 0.8 && fromXstart > 0.1 && fromXstart < 0.9){
    return SOUTH;
  }

  if(fromYstart > 0.1 && fromYstart < 0.9 && fromXstart > -0.2 && fromXstart < 0.2){
    return WEST;
  }
  
  if(fromYstart > 0.1 && fromYstart < 0.9 && fromXstart > 0.8 && fromXstart < 1.2){
    return EAST;
  }
  return EMPTY;
}

bool GameBoardPanel::doHumanMove(OwnerType owner) {

  if (humanMovement.getLineDirection() != EMPTY) {
      humanMovement.playAndAssignOwner(myBoard, owner);
      humanMovement = Movement{-1, -1, EMPTY};
      return true;
    } 
    return false;
}


void GameBoardPanel::playGame(){
    if (myBoard.getAvailableMoves().size() > 0) {
        if (gameTurn == 1) {
            if (player1 != HUMAN) {
                py1->rehearsedPlay(myBoard).playAndAssignOwner(myBoard, PLAYER1);
                gameTurn *= -1;
            }
            else {
                if (doHumanMove(PLAYER1)) {
                    gameTurn *= -1;
                }                
            }
            int auxiliarScorePlayer1 = myBoard.getScoreP1();

            if (auxiliarScorePlayer1 > scorePlayer1) {
                scorePlayer1 = auxiliarScorePlayer1;
                gameTurn *= -1;
            }
        }
        else {
            if (player2 != HUMAN) {
                py2->rehearsedPlay(myBoard).playAndAssignOwner(myBoard, PLAYER2);
                gameTurn *= -1;
            }
            else {
                if (doHumanMove(PLAYER2)) {
                    gameTurn *= -1;
                }
            }
            int auxiliarScorePlayer2 = myBoard.getScoreP2();

            if (auxiliarScorePlayer2 > scorePlayer2) {
                scorePlayer2 = auxiliarScorePlayer2;
                gameTurn *= -1;
            }
        }
    }
    else {
        if (displayedDialog == false)
            if (myBoard.getScoreP1() > myBoard.getScoreP2()) {
                wxLogMessage("Player 1 win the game.");
            }
            else {
                if (myBoard.getScoreP1() < myBoard.getScoreP2()) {
                    wxLogMessage("Player 2 win the game.");
                }
                else {
                    wxLogMessage("The players tied the game.");
                }

            }
            displayedDialog = true;
    }
}

