//
// Created by BBIRONN on 14/06/2021.
//

#ifndef EX2PARTB_GAME_H
#define EX2PARTB_GAME_H

#include "Auxiliaries.h"
#include "Character.h"
#include <vector>
#include <memory>
#include "Exceptions.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include <memory>

class Game {
    int board_height;
    int board_width;
    std::vector<std::vector<std::shared_ptr<Character>>> board;

public:
    /**
* Game constructor: creating new class from type Game (including game board).
*
* @param height - the board height.
* @param width - the board width.
*/
    Game(int height, int width);

    /**
* Game destructor: deleting the game details.
*/
    ~Game();

/**
* Game copy constructor: copying the game deatails to new class.
*
* @param other - game to copy.
*/
    Game(const Game &other);

    /**
* operator=: assignment operator.
*
* @param other - game to assign.
*/
    Game &operator=(const Game &other);

    /**
* isCoordinatesLegal: checking if coordinates are legal.
*
* @param src_coordinates - active character coordinates.
* @param dst_coordinates - passive character coordinates.
*/
    void isCoordinatesLegal(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates);

    /**
* addCharacter: adding character to game board.
*
* @param coordinates - the coordinates that the character need to be in.
* @param character - pointer to existing character.
*/
    void addCharacter(const mtm::GridPoint &coordinates, std::shared_ptr<Character> character);

    /**
* makeCharacter: creating new character class.
*
* @param type - character type (soldier/medic/sniper).
* @param team - the team which will contains the character.
* @param health - amount of health the character is given.
* @param ammo - amount of ammo the character is given.
 * @param range - range of the character attacks.
 * @param power - amount of power the character is given.
*
* @return
* new_shared - pointer to the new character.
*/
    static std::shared_ptr<Character> makeCharacter(mtm::CharacterType type, mtm::Team team,
                                                    mtm::units_t health, mtm::units_t ammo, mtm::units_t range,
                                                    mtm::units_t power);

    /**
* move: moving character from source to destination.
*
* @param src_coordinates - the source coordinates of the moving character.
* @param dst_coordinates - the destination coordinates to reach.
*/
    void move(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates);

    /**
* attack: reduce destination health depend on attacker power.
*
* @param src_coordinates - coordinates of the attacker.
* @param dst_coordinates - coordinates of the victim.
*/

    void attack(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates);

    /**
* reload: reloading/adding ammo.
*
* @param coordinates - the coordinates of the reloading character.
*/
    void reload(const mtm::GridPoint &coordinates);

    /**
* operator<<: insertion operator.
*
* @param os - output stream object.
* @param game - game to send.
*/
    friend std::ostream &operator<<(std::ostream &os, const Game &game);

    /**
* isOver: checking if the game is over (if there is a winning team).
*
* @param winningTeam - pointer which will contain the winning team (if there is one).
*
* @return
* true - if there is a winning team.
* false - if there isn't a winning team.
*/
    bool isOver(mtm::Team *winningTeam = NULL) const;
};


#endif //EX2PARTB_GAME_H
