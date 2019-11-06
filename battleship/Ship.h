// C++ BattleShip 프로젝트
// 작성 일자 : 2018-06-01
// 학번 : 20171627 이름 : 서명희
#pragma once
#include "Common.h"

class Ship {
public:
    Ship(int length);
    virtual ~Ship();

    ShipType GetType() const {
        return m_Type;
    }
    int GetLength() const {
        return m_length;
    }
    void SetPosition(const int index, Position& pos);

    std::vector<Position> m_Pos; //map을 공격하는 것이 아니라 배를 공격하기 때문에 필요
        ShipType m_Type;
// protected :
    int m_length;
};
