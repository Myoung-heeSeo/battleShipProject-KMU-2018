// C++ BattleShip 프로젝트
// 작성 일자 : 2018-06-01
// 학번 : 20171627 이름 : 서명희
#pragma once
#include <ncurses.h>
#include "Common.h"

class Map;
class Ship;

#define SHIPS std::vector<Ship*>

class Player {
public :
    WINDOW *inputPane;

    int count_Aircraft=5;
    int count_Battleship=4;
    int count_Cruiser=3;
    int count_Destroyer=4;
    Player();
    ~Player();

    //defender가 사용
    void SetupShips(const SHIPS& ships);
    HitResult HitCheck(const Position& pos);

    //attacker가 사용
    Position GetAttackPos(); //공격할 위치 반환
    void RandomAttack(char*, Position&);
    Map* m_Map;
protected :

    SHIPS m_Ships;
};
