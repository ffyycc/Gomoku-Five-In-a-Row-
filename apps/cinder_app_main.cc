#include "chess_game_app.h"

using chessgame::ChessGameApp;

void prepareSettings(ChessGameApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(ChessGameApp, ci::app::RendererGl, prepareSettings);
