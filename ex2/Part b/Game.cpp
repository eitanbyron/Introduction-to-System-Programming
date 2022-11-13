//
// Created by BBIRONN on 14/06/2021.
//

#include "Game.h"
#include <memory>
#include <utility>
#include <vector>
#include <memory>
#include "Auxiliaries.h"

using std::vector;
using std::shared_ptr;
using mtm::Team;
using mtm::printGameBoard;



    Game::Game(int height, int width) {
        if (height <= 0 || width <= 0)
            throw mtm::IllegalArgument();
        board_height = height;
        board_width = width;
        vector<vector<std::shared_ptr<Character>>> new_board(height, vector<std::shared_ptr<Character>>(width));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                new_board[i][j] = nullptr;
            }
        }
        board = new_board;
    }

    Game::~Game() {
        for (int i = 0; i < board_height; i++) {
            for (int j = 0; j < board_width; j++) {
                board[i][j] = nullptr;
            }
        }
    }

    Game::Game(const Game &other) {
        vector<vector<std::shared_ptr<Character>>> new_board(other.board_height,
                                                             vector<std::shared_ptr<Character>>(other.board_width));
        board = new_board;
        board_width = other.board_width;
        board_height = other.board_height;
        for (int i = 0; i < other.board_height; i++) {
            for (int j = 0; j < other.board_width; j++) {
                if (other.board[i][j] == nullptr) {
                    board[i][j] = nullptr;
                } else {
                    addCharacter(mtm::GridPoint(i, j), other.board[i][j]->duplucaiteCharacter(other.board[i][j]));
                }
            }
        }

    }

    Game &Game::operator=(const Game &other) {
        Game new_game(other);
        board = new_game.board;
        board_width = other.board_width;
        board_height = other.board_height;
        return *this;
    }

    void Game::isCoordinatesLegal(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
        if ((src_coordinates.col > board_width - 1) || (src_coordinates.row > board_height - 1) ||
            (src_coordinates.col < 0) || (src_coordinates.row < 0))
            throw mtm::IllegalCell();
        if ((dst_coordinates.col > board_width - 1) || (dst_coordinates.row > board_height - 1) ||
            (dst_coordinates.col < 0) || (dst_coordinates.row < 0))
            throw mtm::IllegalCell();
        if (board[src_coordinates.row][src_coordinates.col] == nullptr)
            throw mtm::CellEmpty();
    }

    void Game::attack(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
        isCoordinatesLegal(src_coordinates, dst_coordinates);
        board[src_coordinates.row][src_coordinates.col]->attack(board, board_width, board_height, src_coordinates,
                                                                dst_coordinates);
    }

    void Game::move(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
        isCoordinatesLegal(src_coordinates, dst_coordinates);
        board[src_coordinates.row][src_coordinates.col]->checkIfMoveLegal(src_coordinates, dst_coordinates);
        if (board[dst_coordinates.row][dst_coordinates.col] != nullptr) {
            throw mtm::CellOccupied();
        }
        board[dst_coordinates.row][dst_coordinates.col] = board[src_coordinates.row][src_coordinates.col];
        board[src_coordinates.row][src_coordinates.col] = nullptr;
    }

    void Game::reload(const mtm::GridPoint &coordinates) {
        isCoordinatesLegal(coordinates, coordinates);
        board[coordinates.row][coordinates.col]->reload();

    }

    void Game::addCharacter(const mtm::GridPoint &coordinates, std::shared_ptr<Character> character) {
        if ((coordinates.col > board_width - 1) || (coordinates.row > board_height - 1) ||
            (coordinates.col < 0) || (coordinates.row < 0))
            throw mtm::IllegalCell();
        if (board[coordinates.row][coordinates.col] != nullptr)
            throw mtm::CellOccupied();
        board[coordinates.row][coordinates.col] = std::move(character);
    }


    std::shared_ptr<Character>
    Game::makeCharacter(mtm::CharacterType type, mtm::Team team, mtm::units_t health, mtm::units_t ammo,
                        mtm::units_t range,
                        mtm::units_t power) {
        if ((health <= 0)||(range<0)||(power<0)||(ammo<0)) {
            throw mtm::IllegalArgument();
        }
        shared_ptr<Character> new_shared = nullptr;
        if (type == mtm::SOLDIER) {
            new_shared = std::make_shared<Soldier>(team, health, ammo, range, power);

        }
        if (type == mtm::MEDIC) {
            new_shared = std::make_shared<Medic>(team, health, ammo, range, power);
        }
        if (type == mtm::SNIPER) {
            new_shared = std::make_shared<Sniper>(team, health, ammo, range, power);
        }

        return new_shared;
    }

    bool Game::isOver(Team *winningTeam) const {
        Team winner = mtm::CROSSFITTERS;  // default value
        Soldier dummy_soldier(mtm::POWERLIFTERS, 1, 1, 1, 1, 1, 1, 1);
         if(dummy_soldier.whoWon(board, &winner, board_width, board_height)==true) {
             if(winningTeam!= nullptr) {
                 *winningTeam = winner;
             }
          return true;
         }
         return false;
    }


    std::ostream &operator<<(std::ostream &os, const Game &game) {
        vector<char> char_board(game.board_height * game.board_width + 1, ' ');
        Soldier dummy_soldier(mtm::POWERLIFTERS, 1, 1, 1, 1, 1, 1, 1);
        dummy_soldier.convertToChar(game.board, char_board, game.board_width, game.board_height);
        const char *first = &char_board[0];
        const char *last = &char_board[game.board_height * game.board_width];
        printGameBoard(os, first, last, (unsigned int)  game.board_width);
        return os;
    }


