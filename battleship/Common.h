// C++ BattleShip 프로젝트
// 작성 일자 : 2018-06-01
// 학번 : 20171627 이름 : 서명희
#pragma once
#include <vector>

struct Position
{
    Position() : x(0), y(0) {}

    int x;
    int y;

    Position operator + (const Position& pos) {
        Position retPos;
        retPos.x = x + pos.x;
        retPos.y = y + pos.y;
        return retPos;
    }

    Position operator - (const Position& pos) {
        Position retPos;
        retPos.x = x - pos.x;
        retPos.y = y - pos.y;
        return retPos;
    }
};

enum ShipType
{
    DATA_ERROR = -1,
    DATA_NONE, //enum은 0부터 시작
    AIRCRAFT,
    BATTLESHIP,
    CRUISER,
    DESTROYER,
};

enum HitResult
{
    MISS,
    Hit,
    DESTROY,
};

static const int MAP_SIZE = 8;
