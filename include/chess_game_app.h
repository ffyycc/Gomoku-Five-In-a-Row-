#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "chess_game_main.h"

namespace chessgame {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class ChessGameApp : public ci::app::App {
 public:
    /**
     * constructor for ChessGameApp
     */
    ChessGameApp();

    /**
     * main draw function
     */
    void draw() override;

    /**
     * main update function
     */
    void update() override;

    /**
     * function for mouse click
     * @param event mouse event in Cinder
     */
    void mouseDown(ci::app::MouseEvent event) override;

    // provided that you can see the entire UI on your screen.
    const int kWindowSize = 1000;

 private:
    ChessGame container_;
    ci::audio::VoiceRef game_voice_;


};

}  // namespace idealgas
