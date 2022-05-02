#include <catch2/catch.hpp>

#include <chess_game_main.h>

using chessgame::ChessGame;

TEST_CASE("Test: test horizontal cases for winning evaluation") {
    ChessGame container;
    vector<vector<bool>> board;
    for (int i = 0; i < 15; i++) {
        std::vector<bool> temp_row;
        for (int j = 0; j < 15;j++) {
            temp_row.push_back(false);
        }
        board.push_back(temp_row);
    }
    container.setBlackBoard(board);
    ChessGame::ChessPoint cur_chess;
    cur_chess.x_ = 0;
    cur_chess.y_ = 0;

    board[0][0] = true;
    container.setBlackBoard(board);
    SECTION("Put first chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 0;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[0][1] = true;
    container.setBlackBoard(board);
    SECTION("Put second chess on board. REQUIRE: False") {
        cur_chess.x_ = 1;
        cur_chess.y_ = 0;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[0][2] = true;
    container.setBlackBoard(board);
    SECTION("Put third chess on board. REQUIRE: False") {
        cur_chess.x_ = 2;
        cur_chess.y_ = 0;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[0][3] = true;
    container.setBlackBoard(board);
    SECTION("Put fourth chess on board. REQUIRE: False") {
        cur_chess.x_ = 3;
        cur_chess.y_ = 0;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[0][4] = true;
    container.setBlackBoard(board);
    SECTION("Put fifth chess on board. REQUIRE: True") {
        cur_chess.x_ = 4;
        cur_chess.y_ = 0;
        bool temp = container.evaluateWinStatus(cur_chess);
        REQUIRE(temp == true);
    }
}

TEST_CASE("Test: test vertical cases for winning evaluation") {
    ChessGame container;
    vector<vector<bool>> board;
    for (int i = 0; i < 15; i++) {
        std::vector<bool> temp_row;
        for (int j = 0; j < 15;j++) {
            temp_row.push_back(false);
        }
        board.push_back(temp_row);
    }
    container.setBlackBoard(board);
    ChessGame::ChessPoint cur_chess;
    cur_chess.x_ = 0;
    cur_chess.y_ = 0;

    board[0][0] = true;
    container.setBlackBoard(board);
    SECTION("Put first chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 0;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[1][0] = true;
    container.setBlackBoard(board);
    SECTION("Put second chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 1;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[2][0] = true;
    container.setBlackBoard(board);
    SECTION("Put third chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 2;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[3][0] = true;
    container.setBlackBoard(board);
    SECTION("Put fourth chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 3;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[4][0] = true;
    container.setBlackBoard(board);
    SECTION("Put fifth chess on board. REQUIRE: True") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 4;
        bool temp = container.evaluateWinStatus(cur_chess);
        REQUIRE(temp == true);
    }
}

TEST_CASE("Test: test diagonal cases for winning evaluation") {
    ChessGame container;
    vector<vector<bool>> board;
    for (int i = 0; i < 15; i++) {
        std::vector<bool> temp_row;
        for (int j = 0; j < 15;j++) {
            temp_row.push_back(false);
        }
        board.push_back(temp_row);
    }
    container.setBlackBoard(board);
    ChessGame::ChessPoint cur_chess;
    cur_chess.x_ = 0;
    cur_chess.y_ = 0;

    board[0][0] = true;
    container.setBlackBoard(board);
    SECTION("Put first chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 0;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[1][1] = true;
    container.setBlackBoard(board);
    SECTION("Put second chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 1;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[2][2] = true;
    container.setBlackBoard(board);
    SECTION("Put third chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 2;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[3][3] = true;
    container.setBlackBoard(board);
    SECTION("Put fourth chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 3;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[4][4] = true;
    container.setBlackBoard(board);
    SECTION("Put fifth chess on board. REQUIRE: True") {
        cur_chess.x_ = 4;
        cur_chess.y_ = 4;
        bool temp = container.evaluateWinStatus(cur_chess);
        REQUIRE(temp == true);
    }
}

TEST_CASE("Test: test disjoint cases for winning evaluation") {
    ChessGame container;
    vector<vector<bool>> board;
    for (int i = 0; i < 15; i++) {
        std::vector<bool> temp_row;
        for (int j = 0; j < 15;j++) {
            temp_row.push_back(false);
        }
        board.push_back(temp_row);
    }
    container.setBlackBoard(board);
    ChessGame::ChessPoint cur_chess;
    cur_chess.x_ = 0;
    cur_chess.y_ = 0;

    board[0][0] = true;
    container.setBlackBoard(board);
    SECTION("Put first chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 0;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[1][1] = true;
    container.setBlackBoard(board);
    SECTION("Put second chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 1;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[2][2] = true;
    container.setBlackBoard(board);
    SECTION("Put third chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 2;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[4][4] = true;
    container.setBlackBoard(board);
    SECTION("Put fourth chess on board after disjoint. REQUIRE: False") {
        cur_chess.x_ = 4;
        cur_chess.y_ = 4;
        bool temp = container.evaluateWinStatus(cur_chess);
        REQUIRE(temp == false);
    }

    board[5][5] = true;
    container.setBlackBoard(board);
    SECTION("Put fifth chess on board after disjoint. REQUIRE: False") {
        cur_chess.x_ = 5;
        cur_chess.y_ = 5;
        bool temp = container.evaluateWinStatus(cur_chess);
        REQUIRE(temp == false);
    }

}

TEST_CASE("Test: test six chess connected for winning evaluation") {
    ChessGame container;
    vector<vector<bool>> board;
    for (int i = 0; i < 15; i++) {
        std::vector<bool> temp_row;
        for (int j = 0; j < 15;j++) {
            temp_row.push_back(false);
        }
        board.push_back(temp_row);
    }
    container.setBlackBoard(board);
    ChessGame::ChessPoint cur_chess;
    cur_chess.x_ = 0;
    cur_chess.y_ = 0;

    board[0][0] = true;
    container.setBlackBoard(board);
    SECTION("Put first chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 0;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[1][1] = true;
    container.setBlackBoard(board);
    SECTION("Put second chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 1;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[2][2] = true;
    container.setBlackBoard(board);
    SECTION("Put third chess on board. REQUIRE: False") {
        cur_chess.x_ = 0;
        cur_chess.y_ = 2;
        REQUIRE(container.evaluateWinStatus(cur_chess) == false);
    }

    board[3][3] = true;
    container.setBlackBoard(board);
    SECTION("Put fourth chess on board after disjoint. REQUIRE: False") {
        cur_chess.x_ = 3;
        cur_chess.y_ = 3;
        bool temp = container.evaluateWinStatus(cur_chess);
        REQUIRE(temp == false);
    }

    board[4][4] = true;
    container.setBlackBoard(board);
    SECTION("Put fifth chess on board after disjoint. REQUIRE: True") {
        cur_chess.x_ = 4;
        cur_chess.y_ = 4;
        bool temp = container.evaluateWinStatus(cur_chess);
        REQUIRE(temp == true);
    }

    board[5][5] = true;
    container.setBlackBoard(board);
    SECTION("Put sixth chess on board after disjoint. REQUIRE: True") {
        cur_chess.x_ = 5;
        cur_chess.y_ = 5;
        bool temp = container.evaluateWinStatus(cur_chess);
        REQUIRE(temp == true);
    }

}

