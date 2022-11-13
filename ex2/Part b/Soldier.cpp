//
// Created by BBIRONN on 14/06/2021.
//

#include "Soldier.h"
using mtm::units_t;
using mtm::Team;

Soldier::Soldier(Team new_team,units_t new_health, units_t new_ammo, units_t new_range,
                 units_t new_power, units_t new_reload_rate,units_t new_steps,
                 units_t new_ammo_waste) : Character(new_team, new_health, new_ammo, new_range, new_power,
                                                          new_reload_rate, new_steps, new_ammo_waste) {
    reload_rate =3;
    steps = 3;
    ammo_waste =1;
    type = mtm::SOLDIER;
}



void Soldier::secondaryEffect(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height, const mtm::GridPoint &dst_coordinates) {
    mtm::units_t collateral_damage = ceil((double) power/2);
    mtm::units_t splash_zone = ceil((double) range/3);
    for (int i = 0; i< board_height ; i++) {
        for (int j = 0; j < board_width; j++){
            mtm::GridPoint current_location(i,j);
            int distance_from_target = mtm::GridPoint::distance(current_location, dst_coordinates);
            if ((distance_from_target != 0) && (distance_from_target <= splash_zone)&&(!doesDstOnTheSameTeam(board[i][j], team)))
            {
                damage_character(board, collateral_damage,mtm::GridPoint(i,j));
            }
        }
    }
}

void Soldier::mainAttack(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height, const mtm::GridPoint &dst_coordinates) {
    if(!doesDstOnTheSameTeam(board[dst_coordinates.row][dst_coordinates.col], team)) {
        damage_character(board, power, dst_coordinates);
    }
    ammo-=ammo_waste;

}


void
Soldier::isAttackLegal(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates,
                       std::vector<std::vector<std::shared_ptr<Character>>> &board,int target_distance) const {
    if((target_distance>range)||((src_coordinates.row!=dst_coordinates.row)&&(src_coordinates.col!=dst_coordinates.col))) {
        throw mtm::OutOfRange();
    }
    if(ammo-ammo_waste<0) {
        throw mtm::OutOfAmmo();
    }

}












