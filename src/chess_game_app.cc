#include "chess_game_app.h"

namespace chessgame {

ChessGameApp::ChessGameApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void ChessGameApp::draw() {
  ci::Color background_color(container_.color_theme_list_.at(container_.cur_theme_index_).background_color_);
  ci::gl::clear(background_color);

  container_.Display();
}

void ChessGameApp::update() {
}

void ChessGameApp::mouseDown(ci::app::MouseEvent event) {
    container_.mouseDown(event);
}

}  // namespace chessgame
