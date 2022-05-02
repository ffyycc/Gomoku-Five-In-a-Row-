#include "chess_game_main.h"
#include <stdlib.h>
#define BOARD_SIZE   15
#define NUM_WIN 5

namespace chessgame {

using glm::vec2;

ChessGame::ChessGame() {
    // Start playing audio from the voice:
    if (sound_mode_) {
        ci::audio::SourceFileRef sourceFile = ci::audio::load( ci::app::loadAsset("Gomoku_music.mp3"));
        game_voice_ = ci::audio::Voice::create(sourceFile);
    }
    winning_nums_.push_back(0);
    winning_nums_.push_back(0);
    createTable();
}

void ChessGame::generateBoard() const {
    // draw player chess example
    ci::gl::drawStringCentered("Player 1 -", player_one_example_position_,text_color_,cinder::Font("Helvetica Neue", kPlayerTextSize));
    ci::gl::drawStringCentered("Player 2 -",player_two_example_position_,text_color_,cinder::Font("Helvetica Neue", kPlayerTextSize));

    for (int i = 1; i < gaps_; i++) {
        vec2 temp_top = vec2(left_up_position_.x +i*width_,left_up_position_.y);
        vec2 temp_bot = vec2(left_up_position_.x + i*width_,right_bot_position_.y);
        vec2 temp_left = vec2(left_up_position_.x,left_up_position_.y +i*width_);
        vec2 temp_right = vec2(right_bot_position_.x,left_up_position_.y+i*width_);
        ci::gl::drawLine(temp_top,temp_bot);
        ci::gl::drawLine(temp_left,temp_right);
    }

    // draw small circles on board to normalize
    int small_circle_radius = 5;
    ci::gl::drawSolidCircle( vec2(left_up_position_.x+3*width_,left_up_position_.y+3*width_),small_circle_radius);
    ci::gl::drawSolidCircle( vec2(left_up_position_.x+11*width_,left_up_position_.y+3*width_),small_circle_radius);
    ci::gl::drawSolidCircle( vec2(left_up_position_.x+3*width_,left_up_position_.y+11*width_),small_circle_radius);
    ci::gl::drawSolidCircle( vec2(left_up_position_.x+11*width_,left_up_position_.y+11*width_),small_circle_radius);
    ci::gl::drawSolidCircle( vec2(left_up_position_.x+7*width_,left_up_position_.y+7*width_),small_circle_radius);

    // draw icons
    ci::gl::color(ci::Color(icon_color_));
    if (sound_mode_) {
        ci::gl::drawSolidRect(ci::Rectf(left_up_sound_button_,right_bot_sound_button_));
    }
    ci::gl::drawSolidRect(ci::Rectf(left_up_revert_button_,right_bot_revert_button_));
    ci::gl::drawSolidRect(ci::Rectf(left_up_restart_button_,right_bot_restart_button_));
    ci::gl::drawSolidRect(ci::Rectf(left_up_mode_button_,right_bot_mode_button_));
    ci::gl::drawSolidRect(ci::Rectf(left_up_theme_button_,right_bot_theme_button_));
    ci::gl::drawSolidRect(ci::Rectf(left_up_reset_button_,right_bot_reset_button_));

    ci::gl::color(ci::Color(boundary_color_));
    if (sound_mode_) {
        ci::gl::drawStrokedRect(ci::Rectf(left_up_sound_button_,right_bot_sound_button_));
    }
    ci::gl::drawStrokedRect(ci::Rectf(left_up_revert_button_,right_bot_revert_button_));
    ci::gl::drawStrokedRect(ci::Rectf(left_up_restart_button_,right_bot_restart_button_));
    ci::gl::drawStrokedRect(ci::Rectf(left_up_mode_button_,right_bot_mode_button_));
    ci::gl::drawStrokedRect(ci::Rectf(left_up_theme_button_,right_bot_theme_button_));
    ci::gl::drawStrokedRect(ci::Rectf(left_up_reset_button_,right_bot_reset_button_));

    vec2 center_sound_position = vec2((left_up_sound_button_.x + right_bot_sound_button_.x)/2, (left_up_sound_button_.y + right_bot_sound_button_.y)/2-10);
    vec2 center_revert_position = vec2((left_up_revert_button_.x + right_bot_revert_button_.x)/2, (left_up_revert_button_.y + right_bot_revert_button_.y)/2-10);
    vec2 center_restart_position = vec2((left_up_restart_button_.x + right_bot_restart_button_.x)/2, (left_up_restart_button_.y + right_bot_restart_button_.y)/2-10);
    vec2 center_mode_position = vec2((left_up_mode_button_.x + right_bot_mode_button_.x)/2, (left_up_mode_button_.y + right_bot_mode_button_.y)/2-10);
    vec2 center_theme_position = vec2((left_up_theme_button_.x + right_bot_theme_button_.x)/2, (left_up_theme_button_.y + right_bot_theme_button_.y)/2-10);
    vec2 center_reset_position = vec2((left_up_reset_button_.x + right_bot_reset_button_.x)/2, (left_up_reset_button_.y + right_bot_reset_button_.y)/2-10);

    if (sound_mode_) {
        if (sound_) {
            ci::gl::drawStringCentered("sound off",center_sound_position,ci::Color(text_color_),cinder::Font("Helvetica Neue", kIconTextSize));
        } else {
            ci::gl::drawStringCentered("sound on",center_sound_position,ci::Color(text_color_),cinder::Font("Helvetica Neue", kIconTextSize));
        }
    }

    ci::gl::drawStringCentered("take back",center_revert_position,ci::Color(text_color_),cinder::Font("Helvetica Neue", kIconTextSize));
    ci::gl::drawStringCentered("restart",center_restart_position,ci::Color(text_color_),cinder::Font("Helvetica Neue", kIconTextSize));
    if (mode_PvP_) {
        ci::gl::drawStringCentered("turn PvE",center_mode_position,ci::Color(text_color_),cinder::Font("Helvetica Neue", kIconTextSize));
    } else {
        ci::gl::drawStringCentered("turn PvP",center_mode_position,ci::Color(text_color_),cinder::Font("Helvetica Neue", kIconTextSize));
    }
    ci::gl::drawStringCentered("opt theme",center_theme_position,ci::Color(text_color_),cinder::Font("Helvetica Neue", kIconTextSize));

    ci::gl::drawStringCentered("player 1 win: " + to_string(winning_nums_[0]),vec2(left_up_position_.x + width_*3, right_bot_position_.y+10),ci::Color(text_color_),cinder::Font("Helvetica Neue", kIconTextSize));
    ci::gl::drawStringCentered("player 2 win: " + to_string(winning_nums_[1]),vec2(left_up_position_.x + width_*8, right_bot_position_.y+10),ci::Color(text_color_),cinder::Font("Helvetica Neue", kIconTextSize));

    ci::gl::drawStringCentered("reset",center_reset_position,ci::Color(text_color_),cinder::Font("Helvetica Neue", kIconTextSize));
}

void ChessGame::Display() {
  ci::gl::color(ci::Color(boundary_color_));
  ci::gl::drawStrokedRect(ci::Rectf(left_up_position_, right_bot_position_));

  ChessGame::generateBoard();
  ChessGame::generateChess();
  float size = 25.0;
  if (black_win_) {
      ci::gl::color(win_message_color_);
      ci::gl::drawSolidRect(ci::Rectf(left_up_win_position_,right_bot_win_position_));
      ci::gl::drawStringCentered("Player 1",vec2((right_bot_win_position_.x+left_up_win_position_.x)/2,(right_bot_win_position_.y+left_up_win_position_.y)/2-button_height_/2),text_color_,cinder::Font("Helvetica Neue", size));
      ci::gl::drawStringCentered("Wins !",vec2((right_bot_win_position_.x+left_up_win_position_.x)/2,(right_bot_win_position_.y+left_up_win_position_.y)/2+button_height_/4),text_color_,cinder::Font("Helvetica Neue", size));
      if (end_game_ == true && first_add_ == false) {
          winning_nums_[0] += 1;
          first_add_ = true;
      }
  }

  if (white_win_) {
      ci::gl::color(win_message_color_);
      ci::gl::drawSolidRect(ci::Rectf(left_up_win_position_,right_bot_win_position_));
      ci::gl::drawStringCentered("Player 2",vec2((right_bot_win_position_.x+left_up_win_position_.x)/2,(right_bot_win_position_.y+left_up_win_position_.y)/2-button_height_/2),text_color_,cinder::Font("Helvetica Neue", size));
      ci::gl::drawStringCentered("Wins !",vec2((right_bot_win_position_.x+left_up_win_position_.x)/2,(right_bot_win_position_.y+left_up_win_position_.y)/2+button_height_/4),text_color_,cinder::Font("Helvetica Neue", size));
      if (end_game_ == true && first_add_ == false) {
          winning_nums_[1] += 1;
          first_add_ = true;
      }
  }
}

void ChessGame::createTable() {
    vector<vector<bool>> black_board;
    vector<vector<bool>> white_board;
    for (int i = 0; i < gaps_+1; i++) {
        std::vector<bool> temp_row;
        for (int j = 0; j <gaps_+1;j++) {
            temp_row.push_back(false);
        }

        black_board.push_back(temp_row);
        white_board.push_back(temp_row);
    }

    black_board_ = black_board;
    white_board_ = white_board;
}

void ChessGame::generateChess() const {
    ci::gl::color(player_one_color_);
    // draw black example chess
    ci::gl::drawSolidCircle(player_one_example_position_chess_,example_chess_radius_);
    for (int i = 0; i < black_list_.size();i++) {
        vec2 temp_vec = vec2(black_list_.at(i).x_ * width_, black_list_.at(i).y_ * width_);
        ci::gl::drawSolidCircle(left_up_position_ + temp_vec,chess_radius_);
    }

    ci::gl::color(player_two_color_);
    // draw white example chess
    ci::gl::drawSolidCircle(player_two_example_position_chess_,example_chess_radius_);
    for (int i = 0; i < white_list_.size();i++) {
        vec2 temp_vec = vec2(white_list_.at(i).x_ * width_, white_list_.at(i).y_ * width_);
        ci::gl::drawSolidCircle(left_up_position_ + temp_vec,chess_radius_);
    }
}

bool ChessGame::evaluateRows(vector<vector<bool>> board, ChessPoint newChess) {
    for (int i = -2; i <= 2; i++) {
        if (2 <=newChess.x_+i and newChess.x_+i <= 12) {
            for (int j = -2; j <= 2; j++) {
                if (!board.at(newChess.y_).at(newChess.x_+i+j)) {
                    break;
                }
                if (j == 2) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessGame::evaluateCols(vector<vector<bool>> board, ChessPoint newChess) {
    for (int i = -2; i <= 2; i++) {
        if (2 <=newChess.y_+i and newChess.y_+i <= 12) {
            for (int j = -2; j <= 2; j++) {
                if (!board.at(newChess.y_+i+j).at(newChess.x_)) {
                    break;
                }
                if (j == 2) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessGame::evaluateDiags(vector<vector<bool>> board, ChessPoint newChess) {
    // left up to right bottom
    for (int i = -2; i <= 2; i++) {
        if (2 <= newChess.x_+i and newChess.x_+i <= 12 and 2 <= newChess.y_+i and newChess.y_+i <= 12) {
            for (int j = -2; j <= 2; j++) {
                if (!board.at(newChess.y_+i+j).at(newChess.x_+i+j)) {
                    break;
                }
                if (j == 2) {
                    return true;
                }
            }
        }
    }

    // right up to left bottom
    for (int i = -2; i <= 2; i++) {
        if (2 <= newChess.x_-i and newChess.x_-i <= 12 and 2 <= newChess.y_+i and newChess.y_+i <= 12) {
            for (int j = -2; j <= 2; j++) {
                if (!board.at(newChess.y_+i+j).at(newChess.x_-i-j)) {
                    break;
                }
                if (j == 2) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ChessGame::evaluateWinStatus(ChessPoint newChess) {
    vector<vector<bool>> board;
    if (black_turn_) {
        board = black_board_;
    } else {
        board = white_board_;
    }

    if (evaluateRows(board,newChess) || evaluateCols(board, newChess) || evaluateDiags(board, newChess)) {
        end_game_ = true;
        return true;
    }
    return false;
}

bool ChessGame::inBoundIcon(vec2 leftUpPosition, vec2 rightBotPosition, vec2 mousePosition) {
    if (leftUpPosition.x <= mousePosition.x and mousePosition.x <= rightBotPosition.x) {
        if (leftUpPosition.y <= mousePosition.y and mousePosition.y <= rightBotPosition.y) {
            return true;
        }
    }
    return false;
}

void ChessGame::revertStep() {
    int size_black = black_list_.size();
    int size_white = white_list_.size();
    if (mode_PvP_) {
        if (black_turn_ and size_white != 0) {
            // remove any links to the last step for white player
            ChessPoint last_step = white_list_.back();
            white_board_.at(last_step.y_).at(last_step.x_) = false;
            white_list_.pop_back();
            black_turn_ = false;
        } else if (!black_turn_ and size_black != 0) {
            // remove any links to the last step for black player
            ChessPoint last_step = black_list_.back();
            black_board_.at(last_step.y_).at(last_step.x_) = false;
            black_list_.pop_back();
            black_turn_ = true;
        }
    } else {
        if (size_white != 0) {
            ChessPoint last_step_black = black_list_.back();
            ChessPoint last_step_white = white_list_.back();
            black_board_.at(last_step_black.y_).at(last_step_black.x_) = false;
            white_board_.at(last_step_white.y_).at(last_step_white.x_) = false;
            black_list_.pop_back();
            white_list_.pop_back();
        }
    }

}

void ChessGame::resetBoard() {
    for (int i = 0; i < black_board_.size(); i++) {
        for (int j = 0; j < black_board_.size(); j++) {
            black_board_.at(i).at(j) = false;
            white_board_.at(i).at(j) = false;
        }
    }
}

void ChessGame::restartGame() {
    end_game_ = false;
    black_win_ = false;
    white_win_ = false;
    black_turn_ = true;
    first_add_ = false;
    black_list_.clear();
    white_list_.clear();

    resetBoard();
}

void ChessGame::changeGameMode() {
    mode_PvP_ = !mode_PvP_;
    restartGame();
}

void ChessGame::changeGameTheme() {
    cur_theme_index_ = (cur_theme_index_+1) % color_theme_list_.size();
    boundary_color_ = color_theme_list_.at(cur_theme_index_).boundary_color_;
    icon_color_ = color_theme_list_.at(cur_theme_index_).icon_color_;
    text_color_ = color_theme_list_.at(cur_theme_index_).text_color_;
    player_one_color_ = color_theme_list_.at(cur_theme_index_).player_one_color_;
    player_two_color_ = color_theme_list_.at(cur_theme_index_).player_two_color_;
    win_message_color_ = color_theme_list_.at(cur_theme_index_).win_message_color_;
}

void ChessGame::decideSoundDecision() {
    if (sound_ == true) {
        sound_ = false;
        game_voice_->stop();
    } else {
        sound_ = true;
        game_voice_->start();
    }
}

void ChessGame::resetGameCount() {
    winning_nums_[0] = 0;
    winning_nums_[1] = 0;
}

void ChessGame::takeIconAction(vec2 position) {
    // sound button
    if (sound_mode_) {
        if (inBoundIcon(left_up_sound_button_, right_bot_sound_button_, position)) {
            decideSoundDecision();
        }
    }

    // revert button
    if (inBoundIcon(left_up_revert_button_,right_bot_revert_button_,position)) {
        revertStep();
    }

    // restart button
    if (inBoundIcon(left_up_restart_button_,right_bot_restart_button_,position)) {
        restartGame();
    }

    // game mode button
    if (inBoundIcon(left_up_mode_button_,right_bot_mode_button_,position)) {
        changeGameMode();
    }

    // game theme button
    if (inBoundIcon(left_up_theme_button_,right_bot_theme_button_,position)) {
        changeGameTheme();
    }

    // game reset button
    if (inBoundIcon(left_up_reset_button_,right_bot_reset_button_,position)) {
        resetGameCount();
    }
}

void ChessGame::proceedPvPGame(ChessPoint newChess) {
    if (black_board_.at(newChess.y_).at(newChess.x_) || white_board_.at(newChess.y_).at(newChess.x_)) {
        return;
    }

    if (black_turn_) {
        black_board_.at(newChess.y_).at(newChess.x_) = true;
        black_list_.push_back(newChess);
        black_win_ = evaluateWinStatus(newChess);

    } else {
        white_board_.at(newChess.y_).at(newChess.x_) = true;
        white_list_.push_back(newChess);
        white_win_ = evaluateWinStatus(newChess);
    }
    black_turn_ = !black_turn_;
}

bool ChessGame::scorePointInBound(int x, int y) {
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        return true;
    }
    return false;
}

int ChessGame::evaluateScore(int x, int y, bool isBlack) {
    int out_score = 0;

    for (int i = 0; i < x_dir_list_.size(); i++) {
        int open_positions = 0;
        int num_connect = 1;

        for (int j = -1; j < 2; j+= 2) {
            int eval_x = x + x_dir_list_.at(i) * j;
            int eval_y = y + y_dir_list_.at(i) * j;
            while (scorePointInBound(eval_x,eval_y)) {
                if (isBlack) {
                    if (black_board_.at(eval_y).at(eval_x)) {
                        num_connect += 1;
                    } else {
                        // point is not opponent chess, and it is empty
                        if (!white_board_.at(eval_y).at(eval_x)) {
                            open_positions += 1;
                        }
                        break;
                    }
                } else {
                    if (white_board_.at(eval_y).at(eval_x)) {
                        num_connect += 1;
                    } else {
                        // point is not opponent chess, and it is empty
                        if (!black_board_.at(eval_y).at(eval_x)) {
                            open_positions += 1;
                        }
                        break;
                    }
                }

                eval_x += x_dir_list_.at(i) * j;
                eval_y += y_dir_list_.at(i) * j;
            }

        }

        if (num_connect > NUM_WIN) {
            num_connect = NUM_WIN;
        }
        out_score += kScoreTable_[open_positions][num_connect];
    }
    return out_score;
}

ChessGame::ChessPoint ChessGame::takeAIAction() {
    int max_score = INT_MIN;
    // may contain multiple best solutions
    vector<int> x_list;
    vector<int> y_list;
    vector<vector<int>> score_black_table;
    vector<vector<int>> score_white_table;

    for (int x = 0;x < BOARD_SIZE; x++) {
        vector<int> score_black_row;
        vector<int> score_white_row;
        for (int y = 0; y <BOARD_SIZE; y++) {
            if (!black_board_.at(y).at(x) and !white_board_.at(y).at(x)) {
                int score_black = evaluateScore(x,y,true);
                int score_white = evaluateScore(x,y,false);
                int temp_score = max(score_black,score_white);
                score_black_row.push_back(score_black);
                score_white_row.push_back(score_white);

                if (temp_score >= max_score) {
                    if (temp_score > max_score) {
                        max_score = temp_score;
                        x_list.clear();
                        y_list.clear();
                    }

                    x_list.push_back(x);
                    y_list.push_back(y);
                }
            }
        }
        score_black_table.push_back(score_black_row);
        score_white_table.push_back(score_white_row);
    }

    int decision_index = rand() % x_list.size();

    struct ChessPoint AI_chess;
    AI_chess.x_ = x_list.at(decision_index);
    AI_chess.y_ = y_list.at(decision_index);
    return AI_chess;
}

void ChessGame::proceedPvEGame(ChessPoint newChess) {
    if (black_board_.at(newChess.y_).at(newChess.x_)) {
        return;
    }

    // player move
    black_turn_ = true;
    black_board_.at(newChess.y_).at(newChess.x_) = true;
    black_list_.push_back(newChess);
    black_win_ = evaluateWinStatus(newChess);
    if (black_win_) {
        return;
    }

    // AI move
    black_turn_ = false;
    ChessPoint AI_chess = takeAIAction();
    white_board_.at(AI_chess.y_).at(AI_chess.x_) = true;
    white_list_.push_back(AI_chess);
    white_win_ = evaluateWinStatus(AI_chess);
}

void ChessGame::transitPosition(vec2 position) {
    vec2 left_up_bound = vec2(left_up_position_.x - width_ / 2, left_up_position_.y - width_ / 2);
    struct ChessPoint new_chess;
    new_chess.x_ = (int) (position.x - left_up_bound.x) / width_;
    new_chess.y_ = (int) (position.y - left_up_bound.y) / width_;

    if (new_chess.x_ < 0 or new_chess.x_ > gaps_ or new_chess.y_ < 0 or new_chess.y_ > gaps_) {
        takeIconAction(position);
        return;
    }

    if (!end_game_) {
        if (mode_PvP_) {
            proceedPvPGame(new_chess);
        } else {
            proceedPvEGame(new_chess);
        }
    }
}

void ChessGame::mouseDown(ci::app::MouseEvent event) { transitPosition(event.getPos()); }

void ChessGame::setBlackBoard(const vector<vector<bool>> &blackBoard) {
    black_board_ = blackBoard;
}

void ChessGame::setWhiteBoard(const vector<vector<bool>> &whiteBoard) {
    white_board_ = whiteBoard;
}

}  // namespace chessgame
