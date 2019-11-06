#include "Map.h"
#include <iostream>
Map::Map() {
    for(int i=0; i<MAP_SIZE; i++) {
        for(int j=0; j<MAP_SIZE; j++) {
            m_Data[i][j] = DATA_NONE;
            m_Data2[i][j] = '0';
        }
    }
}

Map::~Map() {

}
ShipType Map::GetData(const Position &pos) {
    if(((pos.x < 0) || (pos.x >= MAP_SIZE))||((pos.y<0)||(pos.y >= MAP_SIZE))) // 좌표가 이상하다면
        return DATA_ERROR; //DATA_ERROR 반환

    return m_Data[pos.x][pos.y]; //좌표에 해당하는 ShipType반환
}

//RandomAttack을 위해 새로 생성
char Map::GetData2(int x, int y) {
    Position pos1;
    pos1.x=x;
    pos1.y=y;
    if(((pos1.x < 0) || (pos1.x >= MAP_SIZE))||((pos1.y<0)||(pos1.y >= MAP_SIZE))) // 좌표가 이상하다면
        return '1';   //0인 경우만 뽑아내기 위한 것이므로 임시로 1리턴

    return m_Data2[pos1.x][pos1.y]; //좌표에 해당하는 ShipType반환
}

void Map::SetData(const Position& pos, const ShipType type) {
    if(((pos.x < 0) || (pos.x >= MAP_SIZE))||((pos.y<0)||(pos.y >= MAP_SIZE)))
        return ;
    m_Data[pos.x][pos.y] = type;
}

void Map::SetData2(const Position& pos, const HitResult res){
  if(((pos.x < 0) || (pos.x >= MAP_SIZE))||((pos.y<0)||(pos.y >= MAP_SIZE)))
      return ;
  if(res==0) m_Data2[pos.x][pos.y] = 'M';
  else m_Data2[pos.x][pos.y] = 'H';
}
