//
// Created by dolle on 14/06/2021.
//

#include "Medic.h"




void Medic::isAttackLegal(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates,
                          std::vector<std::vector<std::shared_ptr<Character>>> &board,int target_distance) const {
    if(target_distance>range) {
        throw mtm::OutOfRange();
    }
    if((ammo-ammo_waste<0)&& (doesDstOnTheSameTeam(board[dst_coordinates.row][dst_coordinates.col],team)!=true)) {
        throw mtm::OutOfAmmo();
    }
    if((board[dst_coordinates.row][dst_coordinates.col]== nullptr)||(dst_coordinates==src_coordinates))
    {
        throw mtm::IllegalTarget();
    }

}

Medic::Medic(mtm::Team new_team, mtm::units_t new_health, mtm::units_t new_ammo, mtm::units_t new_range,
             mtm::units_t new_power, mtm::units_t new_reload_rate, mtm::units_t new_steps, mtm::units_t new_ammo_waste)
        : Character(new_team, new_health, new_ammo, new_range, new_power, new_reload_rate, new_steps, new_ammo_waste) {
        reload_rate =5;
        steps = 5;
        ammo_waste =1;
        type = mtm::MEDIC;
    }

void Medic::mainAttack(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height, const mtm::GridPoint &dst_coordinates) {
    if(!doesDstOnTheSameTeam(board[dst_coordinates.row][dst_coordinates.col],team)) {
        damage_character(board, power, dst_coordinates);
        ammo -= ammo_waste;
    }
    else
    {
        damage_character(board,-power,dst_coordinates);

    }
}


void Medic::secondaryEffect(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height,
                            const mtm::GridPoint &dst_coordinate) {
    }

