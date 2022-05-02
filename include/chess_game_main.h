#pragma once

#include "cinder/gl/gl.h"
#include <iostream>
#include <string>
#include <cinder/app/MouseEvent.h>
#include "cinder/Font.h"
#include "cinder/audio/Voice.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/audio/Node.h"

using namespace std;
using glm::vec2;

namespace chessgame {

/**
 * The container in which all of the chess board information are contained.
 */
class ChessGame {
 public:
    /**
     * empty constructor
     */
    ChessGame();

    /**
     * struct for one single chess
     */
    struct ChessPoint {
        int x_;
        int y_;
    };

    /**
     * struct for single chess theme
     */
    struct ColorTheme {
        cinder::ColorT<float> background_color_;
        cinder::ColorT<float> boundary_color_;
        cinder::ColorT<float> text_color_;
        cinder::ColorT<float> player_one_color_;
        cinder::ColorT<float> player_two_color_;
        cinder::ColorT<float> icon_color_;
        cinder::ColorT<float> win_message_color_;
    };

    /**
     * set black board
     * @param blackBoard black board reference
     */
    void setBlackBoard(const vector<vector<bool>> &blackBoard);

    /**
     * set white board
     * @param whiteBoard white board reference
     */
    void setWhiteBoard(const vector<vector<bool>> &whiteBoard);

    /**
     * Displays the chess board game
     */
    void Display();

    /**
     * Initial function to generate board
     */
    void generateBoard() const;

    /**
     * action when player uses mouse to click
     * @param event mouse event
     */
    void mouseDown(ci::app::MouseEvent event);

    ColorTheme color_design_one_ = {"burlywood","black","black","black","white","grey","wheat"};
    ColorTheme color_design_two_ = {"grey","whitesmoke","whitesmoke","black","white","slategrey","lightsalmon"};
    ColorTheme color_design_three_ = {"grey","black","black","black","white","slategrey","lightsalmon"};
    ColorTheme color_design_four_ = {"forestgreen","black","black","black","white","lightseagreen","greenyellow"};
    ColorTheme color_design_five_ = {"purple","darkgrey","darkgrey","darkblue","hotpink","olive","orange"};
    std::vector<ColorTheme> color_theme_list_ = {color_design_one_,color_design_two_,color_design_three_,color_design_four_,color_design_five_};
    int cur_theme_index_ = 0;

    /**
     * music setter function
     * @param musicRef music reference
     */
    void setGameMusic(ci::audio::VoiceRef musicRef) {
        game_voice_ = musicRef;
    }

    /**
     * function to evaluate winning state
     * @param newChess current chess on board
     * @return whether current player wins
     */
    bool evaluateWinStatus(ChessPoint newChess);

 private:
    /**
    * private class variable
    */
    cinder::ColorT<float> boundary_color_ = color_theme_list_.at(cur_theme_index_).boundary_color_;
    cinder::ColorT<float> icon_color_ = color_theme_list_.at(cur_theme_index_).icon_color_;
    cinder::ColorT<float> text_color_ = color_theme_list_.at(cur_theme_index_).text_color_;
    cinder::ColorT<float> player_one_color_ = color_theme_list_.at(cur_theme_index_).player_one_color_;
    cinder::ColorT<float> player_two_color_ = color_theme_list_.at(cur_theme_index_).player_two_color_;
    cinder::ColorT<float> win_message_color_ = color_theme_list_.at(cur_theme_index_).win_message_color_;

    glm::vec2 left_up_position_ = vec2(100, 50);
    glm::vec2 right_bot_position_ = vec2(800, 750);
    int gaps_ = 14;
    int chess_radius_ = 22;
    int example_chess_radius_ = 15;
    double width_ = 700/gaps_;
    vector<vec2> mouse_points_;
    bool black_turn_ = true;
    bool black_win_ = false;
    bool white_win_ = false;
    bool first_add_ = false;
    ci::audio::VoiceRef game_voice_;
    double button_width_ = 2*width_;
    double button_height_ = width_;

    /**
     * chess score table
     */
    const int kScoreTable_[3][6] = {
          {0,0,0,0,0,10000},
          {0,0,20,100,500,10000},
          {0,20,100,500,2500,10000}
    };

    // different direction for AI evaluation
    std::vector<int> x_dir_list_ = {1,0,1,1};
    std::vector<int> y_dir_list_ = {0,1,1,-1};

    // buttons position
    glm::vec2 left_up_reset_button_ = vec2(left_up_position_.x + 15*width_, left_up_position_.y+14*width_);
    glm::vec2 right_bot_reset_button_ = vec2(left_up_position_.x + 15*width_+ button_width_, left_up_position_.y+14*width_ + button_height_);

    glm::vec2 left_up_theme_button_ = vec2(left_up_position_.x + 15*width_, left_up_position_.y+12*width_);
    glm::vec2 right_bot_theme_button_ = vec2(left_up_position_.x + 15*width_ + button_width_,left_up_position_.y+12*width_ + button_height_);

    glm::vec2 left_up_sound_button_ = vec2(left_up_position_.x + 15*width_, left_up_position_.y+10*width_);
    glm::vec2 right_bot_sound_button_ = vec2(left_up_position_.x + 15*width_ + button_width_,left_up_position_.y+10*width_ + button_height_);

    glm::vec2 left_up_revert_button_ = vec2(left_up_position_.x + 15*width_, left_up_position_.y+8*width_);
    glm::vec2 right_bot_revert_button_ = vec2(left_up_position_.x + 15*width_+ button_width_, left_up_position_.y+8*width_ + button_height_);

    glm::vec2 left_up_restart_button_ = vec2(left_up_position_.x + 15*width_, left_up_position_.y+6*width_);
    glm::vec2 right_bot_restart_button_ = vec2(left_up_position_.x + 15*width_+ button_width_, left_up_position_.y+6*width_ + button_height_);

    glm::vec2 left_up_mode_button_ = vec2(left_up_position_.x + 15*width_, left_up_position_.y+4*width_);
    glm::vec2 right_bot_mode_button_ = vec2(left_up_position_.x + 15*width_+ button_width_, left_up_position_.y+4*width_ + button_height_);

    glm::vec2 left_up_win_position_ = vec2(left_up_position_.x + 14.5*width_, left_up_position_.y+1.5*width_);
    glm::vec2 right_bot_win_position_ = vec2(left_up_position_.x + 15.5*width_+ button_width_, left_up_position_.y+1.5*width_ + 2*button_height_);

    glm::vec2 player_one_example_position_ = vec2(left_up_position_.x + 15.5*width_, left_up_position_.y-0.5*width_);
    glm::vec2 player_two_example_position_ = vec2(left_up_position_.x + 15.5*width_, left_up_position_.y+0.5*width_);

    glm::vec2 player_one_example_position_chess_ = vec2(left_up_position_.x + 17*width_, left_up_position_.y-0.35*width_);
    glm::vec2 player_two_example_position_chess_ = vec2(left_up_position_.x + 17*width_, left_up_position_.y+0.65*width_);

    // lists containing all current chess point
    std::vector<ChessPoint> black_list_;
    std::vector<ChessPoint> white_list_;

    // board position to show whether the board has chess on that point
    vector<vector<bool>> black_board_;

private:
    vector<vector<bool>> white_board_;

    // overall winning number for two players for now
    vector<int> winning_nums_ = {0,0};

    // boolean value initialization
    bool sound_mode_ = true;
    bool sound_ = false;
    bool end_game_ = false;
    bool mode_PvP_ = true;

    // text size
    float kPlayerTextSize = 20.0;
    float kIconTextSize = 20.0;

    /**
     * function to generate chess board
     */
    void generateChess() const;

    /**
     * function to transit mouse click point to board position
     * @param position position mouse on board
     */
    void transitPosition(vec2 position);

    /**
     * whether player clicks the button on board
     * @param leftUpPosition left up position of button
     * @param rightBotPosition right bottom position of button
     * @param mousePosition mouse clicked position
     * @return whether player clicks the button
     */
    bool inBoundIcon(vec2 leftUpPosition, vec2 rightBotPosition, vec2 mousePosition);

    /**
     * function to create board table to record whether a chess is in that position. Default value is false
     */
    void createTable();

    /**
     * evaluate whether player wins on row
     * @param board table of chess on board
     * @param newChess current chess
     * @return true of player has five same chess on any row
     */
    bool evaluateRows(vector<vector<bool>> board,ChessPoint newChess);

    /**
     * evaluate whether player wins on column
     * @param board table of chess on board
     * @param newChess current chess
     * @return true of player has five same chess on any column
     */
    bool evaluateCols(vector<vector<bool>> board,ChessPoint newChess);

    /**
     * evaluate whether player wins on diagonal
     * @param board table of chess on board
     * @param newChess current chess
     * @return true of player has five same chess on any diagonal position
     */
    bool evaluateDiags(vector<vector<bool>> board,ChessPoint newChess);

    /**
     * helper function to transit on next action
     * @param position mouse position
     */
    void takeIconAction(vec2 position);

    /**
     * revert player action.
     */
    void revertStep();

    /**
     * restart game and clean board
     */
    void restartGame();

    /**
     * function to reset board
     */
    void resetBoard();

    /**
     * function to change PvE to PvP or change PvP to PvE
     */
    void changeGameMode();

    /**
     * main function to proceed player vs player game
     * @param newChess current chess point on board
     */
    void proceedPvPGame(ChessPoint newChess);

    /**
     * main function to proceed player vs environment game
     * @param newChess current chess point on board
     */
    void proceedPvEGame(ChessPoint newChess);

    /**
     * use brute force to evaluate each score on board
     * @param i row position
     * @param j column position
     * @param isBlack whether chess is black
     * @return integer score value
     */
    int evaluateScore(int i, int j, bool isBlack);

    /**
     * Whether the current index is in bound of chessboard
     * @param x row position
     * @param y column position
     * @return boolean value for whethter position in 15x15 board
     */
    bool scorePointInBound(int x, int y);

    /**
     * action for AI to play chess
     * @return a chess point for AI next step
     */
    ChessPoint takeAIAction();

    /**
     * action for change game theme
     */
    void changeGameTheme();

     /**
      * stop or restart sound
      */
     void decideSoundDecision();

     /**
      * show number of games player wins
      */
     void resetGameCount();
};

}  // namespace chessgame
