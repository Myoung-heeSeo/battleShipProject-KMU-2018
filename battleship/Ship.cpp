#include "Ship.h"

Ship::Ship(int length) : m_length(length){
    m_Pos.resize(length);
}

Ship::~Ship() {
}

void Ship::SetPosition(const int index, Position& pos) {
    m_Pos[index] = pos; // m_Pos에 좌표를 저장
}