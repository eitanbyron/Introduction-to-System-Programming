//
// Created by BBIRONN on 14/06/2021.
//

#ifndef EX2PARTB_CHARACTER_H
#define EX2PARTB_CHARACTER_H

#include "Auxiliaries.h"
#include <vector>
#include "Exceptions.h"
#include <memory>

class Character {
protected:
    mtm::Team team;
    mtm::units_t health;
    mtm::units_t ammo;
    mtm::units_t range;
    mtm::units_t power;

    mtm::units_t reload_rate;
    mtm::units_t steps;
    mtm::units_t ammo_waste;


    mtm::CharacterType type;

/**
* Character constructor: creating new general character class from
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

    Character(mtm::Team new_team, mtm::units_t new_health, mtm::units_t new_ammo, mtm::units_t new_range,
              mtm::units_t new_power, mtm::units_t new_reload_rate = 0, mtm::units_t new_steps = 0,
              mtm::units_t new_ammo_waste = 0);

    /**
* damage_character: reduce destination health depend on attacker power.
*
* @param board - game board.
* @param damage - the attacker power.
* @param dst_coordinates - coordinates of the target.

*/

    void damage_character(std::vector<std::vector<std::shared_ptr<Character>>> &board, mtm::units_t damage,
                          const mtm::GridPoint &dst_coordinates);


public:

    /**
* move: moving character from source to destination.
*
* @param src_coordinates - the source coordinates of the moving character.
* @param dst_coordinates - the destination coordinates to reach.

*/
    void move(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) const;

    /**
* duplucaiteCharacter: duplicating character class.
*
* @param existing_char - existing character.
*/
    static std::shared_ptr<Character> duplucaiteCharacter(const std::shared_ptr<Character> &existing_char);

    ~Character() = default;
/**
* attack: reduce destination health depend on attacker power.
*
* @param board - game board.
* @param board_width - number of board columns.
* @param board_height - number of board rows.
* @param src_coordinates - coordinates of the attacker.
* @param dst_coordinates - coordinates of the target.
*/

    void attack(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height,
                const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates);

/**
* secondaryEffect: harming the environment of the target depending on character's attack rules.
*
* @param board - game board.
* @param board_width - number of board columns.
* @param board_height - number of board rows.
* @param dst_coordinates - coordinates of the target.
* @param collateral_damage - the damage that apply on target's environment.
*/

    virtual void
    secondaryEffect(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height,
                    const mtm::GridPoint &dst_coordinates) = 0;

    /**
* mainAttack: reduce destination health depend on attacker power.
*
* @param board - game board.
* @param board_width - number of board columns.
* @param board_height - number of board rows.
* @param dst_coordinates - coordinates of the target.
*/
    virtual void
    mainAttack(std::vector<std::vector<std::shared_ptr<Character>>> &board, int board_width, int board_height,
               const mtm::GridPoint &dst_coordinates) = 0;

    /**
* checkIfMoveLegal: checking if it is possible to perform the move order.
*
* @param src_coordinates - coordinates of the Current Location.
* @param dst_coordinates - coordinates of the destination.
*/

    void checkIfMoveLegal(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates);

    /**
* doesDstOnTheSameTeam: checking if the attacker and the victim in the same team.
*
* @param dst - attacked character coordinates.
* @param attacker_team - attacker's team.
*
* @return
* true - if the attacker and the victim are in the same team.
* false - if the attacker and the victim arent in the same team.
*/
    bool doesDstOnTheSameTeam(std::shared_ptr<Character> dst, mtm::Team attacker_team) const;

    /**
* isAttackLegal: checking if it is possible to perform the attack order depending on character's attack rules.
*
* @param src_coordinates - coordinates of the attacker.
* @param dst_coordinates - coordinates of the target.
* @param board - game board.
* @param target_distance - distance between the attacker and the target.
*/
    virtual void isAttackLegal(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates,
                               std::vector<std::vector<std::shared_ptr<Character>>> &board,
                               int target_distance) const = 0;

    /**
* whoWon: checking if there is winning team.
*
* @param board - game board.
* @param winner -
* @param board_width - number of board columns.
* @param board_height - number of board rows.
*
* @return
* true - if there is a winning team.
* false - if there isn't a winning team.
*/
    static bool
    whoWon(const std::vector<std::vector<std::shared_ptr<Character>>> &board, mtm::Team *winner, int board_width,
           int board_height);

    /**
* reload: reloading/adding ammo.
*/
    void reload();

    /**
* convertToChar: making board to print for User convenience.
*
* @param board - game board.
* @param char_board - board to print with current locations.
* @param board_width - number of board columns.
* @param board_height - number of board rows.
*/

    void convertToChar(const std::vector<std::vector<std::shared_ptr<Character>>> &board, std::vector<char> &char_board,
                       int board_width,
                       int board_height);

};


#endif //EX2PARTB_CHARACTER_H
