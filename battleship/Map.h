// C++ BattleShip 프로젝트
// 작성 일자 : 2018-06-01
// 학번 : 20171627 이름 : 서명희
#pragma once
#include "Common.h"


class Map {
public :
    Map();
    ~Map();

    ShipType GetData(const Position& pos);
    char GetData2(int, int);  //RandomAttack을 위해 새로 생성
    void SetData(const Position& pos, const ShipType type);
    void SetData2(const Position& pos, const HitResult res);
// protected :
    ShipType m_Data[MAP_SIZE][MAP_SIZE];
    char m_Data2[MAP_SIZE][MAP_SIZE];
};
