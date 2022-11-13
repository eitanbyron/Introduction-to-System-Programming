//
// Created by BBIRONN on 14/06/2021.
//

#ifndef EX2PARTB_SOLDIER_H
#define EX2PARTB_SOLDIER_H

#include "Character.h"
#include "Exceptions.h"


class Soldier : public Character {

private:
    /**
* secondaryEffect: harming the environment of the target depending on character's attack rules.
*
* @param board - game board.
* @param board_width - number of board columns.
* @param board_height - number of board rows.
* @param dst_coordinates - coordinates of the target.
* @param collateral_damage - the damage that apply on target's environment.
*/
    void secondaryEffect(std::vector<std::vector<std::shared_ptr<Character>>>& board, int board_width, int board_height, const mtm::GridPoint &dst_coordinates) override;

public:
/**
* Soldier constructor: creating new class from type Soldier.
*
* @param new_team - the team which will contains the character.
* @param new_health - amount of health the character is given.
* @param new_ammo - amount of ammo the character is given.
* @param new_range - range of the character attacks.
* @param new_power - amount of power the character is given.
* @param new_reload_rate - the reload rate of the character.
* @param new_steps - the number of steps of the character while moving.
* @param new_ammo_waste - the ammo waste of the character while attacking.
*/

    Soldier(mtm::Team new_team, mtm::units_t new_health, mtm::units_t new_ammo, mtm::units_t new_range,
            mtm::units_t new_power, mtm::units_t new_reload_rate = 0, mtm::units_t new_steps = 0,
            mtm::units_t new_ammo_waste = 0);

    /**
* Soldier copy constructor: copying the soldier deatails to new class.
*
* @param old_soldier - soldier to copy.
*/
    Soldier(const Soldier &old_soldier) = default;

    /**
* mainAttack: reduce destination health depend on attacker power.
*
* @param board - game board.
* @param board_width - number of board columns.
* @param board_height - number of board rows.
* @param dst_coordinates - coordinates of the target.
*/

    void mainAttack(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height, const mtm::GridPoint &dst_coordinates) override;

/**
* isAttackLegal: checking if it is possible to perform the attack order depending on character's attack rules.
*
* @param src_coordinates - coordinates of the attacker.
* @param dst_coordinates - coordinates of the target.
* @param board - game board.
* @param target_distance - distance between the attacker and the target.
*/

   void isAttackLegal(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates,std::vector<std::vector<std::shared_ptr<Character>>> &board,int target_distance) const override;



};


#endif //EX2PARTB_SOLDIER_H
