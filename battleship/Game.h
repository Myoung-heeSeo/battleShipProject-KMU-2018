// C++ BattleShip 프로젝트
// 작성 일자 : 2018-06-01
// 학번 : 20171627 이름 : 서명희
#pragma once
#include <ncurses.h>
class Player;

class Game
{
public :

    Game();
    ~Game();

    void Init();
    int Play();
protected :
    Player* m_Attacker;
    Player* m_Defender;
};
