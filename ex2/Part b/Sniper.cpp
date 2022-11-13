//
// Created by BBIRONN on 15/06/2021.
//

#include "Sniper.h"

Sniper::Sniper(mtm::Team new_team, mtm::units_t new_health, mtm::units_t new_ammo, mtm::units_t new_range,
               mtm::units_t new_power, mtm::units_t new_reload_rate, mtm::units_t new_steps,
               mtm::units_t new_ammo_waste) : Character(new_team, new_health, new_ammo, new_range, new_power,
                                                        new_reload_rate, new_steps, new_ammo_waste) {
    reload_rate =2;
    steps = 4;
    ammo_waste =1;
    sniper_count = 1;
    type = mtm::SNIPER;
}

void Sniper::isAttackLegal(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates,
                           std::vector<std::vector<std::shared_ptr<Character>>> &board,int target_distance) const {
    if (board[src_coordinates.row][src_coordinates.col] == nullptr)
    {
        throw mtm::CellEmpty();
    }
    mtm::units_t min_distance = ceil((double) range/2);
    if((target_distance>range) || (mtm::GridPoint::distance(src_coordinates,dst_coordinates)<min_distance))
    {
        throw mtm::OutOfRange();
    }
    if(ammo-ammo_waste<0)
    {
        throw mtm::OutOfAmmo();
    }
    if ((board[dst_coordinates.row][dst_coordinates.col] == nullptr) ||
        doesDstOnTheSameTeam(board[dst_coordinates.row][dst_coordinates.col], team)) {
        throw mtm::IllegalTarget();
    }
   }

void Sniper::mainAttack(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height,
                        const mtm::GridPoint &dst_coordinates) {
if (sniper_count == 3) {
  damage_character(board, power*2, dst_coordinates);
   sniper_count = 1;
}
else
{
    damage_character(board, power, dst_coordinates);
    sniper_count++;
}
ammo-=ammo_waste;
}

void Sniper::secondaryEffect(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height,
                             const mtm::GridPoint &dst_coordinates) {

}

