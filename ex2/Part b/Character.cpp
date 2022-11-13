//
// Created by BBIRONN on 14/06/2021.
//

#include "Character.h"
#include "Exceptions.h"
#include "Game.h"


Character::Character(mtm::Team new_team, mtm::units_t new_health, mtm::units_t new_ammo, mtm::units_t new_range,
                     mtm::units_t new_power, mtm::units_t new_reload_rate, mtm::units_t new_steps,
                     mtm::units_t new_ammo_waste):
        team(new_team),
        health(new_health),
        ammo(new_ammo),
        range(new_range),
        power(new_power),
        reload_rate(new_reload_rate),
        steps(new_steps),
        ammo_waste(new_ammo_waste)
{
}


void Character::move(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) const {
    int distance_between_points = mtm::GridPoint::distance(src_coordinates, dst_coordinates);
        if (distance_between_points > steps)
        throw mtm::MoveTooFar();
}

void Character::reload() {
    ammo += reload_rate;
}


void Character::damage_character(std::vector<std::vector<std::shared_ptr<Character>>> &board, mtm::units_t damage,
                                 const mtm::GridPoint &dst_coordinates) {
    if (board[dst_coordinates.row][dst_coordinates.col] == nullptr)
        return;
       mtm::units_t* dst_health = &(board[dst_coordinates.row][dst_coordinates.col]->health);
    *dst_health -= damage;
    if (*dst_health <= 0)
        board[dst_coordinates.row][dst_coordinates.col] = nullptr;
}

void Character::attack(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height,
                       const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
        int target_distance = mtm::GridPoint::distance(src_coordinates, dst_coordinates);
       isAttackLegal(src_coordinates,dst_coordinates,board,target_distance);

        mainAttack(board, board_width, board_height, dst_coordinates);
    secondaryEffect(board, board_width, board_height, dst_coordinates);

    }

void Character::checkIfMoveLegal(const mtm::GridPoint &src_coordinates,
                                const mtm::GridPoint &dst_coordinates) {
    int target_distance = mtm::GridPoint::distance(src_coordinates, dst_coordinates);
    if (target_distance > steps)
        throw mtm::MoveTooFar();
}


void Character::convertToChar (const std::vector<std::vector<std::shared_ptr<Character>>> &board, std::vector<char>& char_board, int board_width,
                               int board_height)
{
    for (int i = 0; i<board_height; i++) {
    for (int j = 0; j <board_width; j++) {

            if (board[i][j] != nullptr) {
                if ((board[i][j]->type == mtm::SOLDIER) && (board[i][j]->team == mtm::POWERLIFTERS))
                    char_board[i*board_width + j] = 'S';
                if ((board[i][j]->type == mtm::SOLDIER) && (board[i][j]->team == mtm::CROSSFITTERS))
                    char_board[i*board_width + j] = 's';
                if ((board[i][j]->type == mtm::MEDIC) && (board[i][j]->team == mtm::POWERLIFTERS))
                    char_board[i*board_width + j] = 'M';
                if ((board[i][j]->type == mtm::MEDIC) && (board[i][j]->team == mtm::CROSSFITTERS))
                    char_board[i*board_width + j] = 'm';
                if ((board[i][j]->type == mtm::SNIPER) && (board[i][j]->team == mtm::POWERLIFTERS))
                    char_board[i*board_width + j] = 'N';
                if ((board[i][j]->type == mtm::SNIPER) && (board[i][j]->team == mtm::CROSSFITTERS))
                    char_board[i*board_width + j] = 'n';
            }
            }
        }
    }


bool Character::whoWon(const std::vector<std::vector<std::shared_ptr<Character>>>& board, mtm::Team *winner, int board_width,
                        int board_height) {
    int count_powerlifters = 0;
    int count_crossfitters = 0;
    for (int i = 0; i<board_height; i++) {
        for (int j = 0; j < board_width; j++) {
            if (board[i][j] != nullptr)
            {
                if (board[i][j]->team == mtm::POWERLIFTERS)
                    count_powerlifters++;
                else
                    count_crossfitters++;
            }
            if ((count_crossfitters >0) && (count_powerlifters > 0))
                return false;
        }
    }
    if(count_powerlifters>0||count_crossfitters>0) {
        if (count_powerlifters > 0)
            *winner = mtm::POWERLIFTERS;
        else
            *winner = mtm::CROSSFITTERS;

        return true;
    }
    return false;
}

std::shared_ptr<Character> Character::duplucaiteCharacter(const std::shared_ptr<Character> &existing_char)
{
    Game dummy(1,1);
    return(dummy.makeCharacter(existing_char->type,existing_char->team,existing_char->health,existing_char->ammo,existing_char->range,existing_char->power));


}

bool Character::doesDstOnTheSameTeam(std::shared_ptr<Character> dst, mtm::Team attacker_team) const {
    if((dst!=nullptr)&&(dst->team==team)){
        return true;
        }
    return false;
}
