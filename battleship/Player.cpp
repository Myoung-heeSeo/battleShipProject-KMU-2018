#include "Player.h"
#include "Map.h"
#include "Ship.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <ncurses.h>
using namespace std;

Player::Player() {
    m_Map = new Map();
}

Player::~Player() {
    delete m_Map;


    for(auto pShip : m_Ships) {
        if(pShip)
            delete pShip;
    }
    m_Ships.clear();
}

void Player::SetupShips(const SHIPS& ships) {
    m_Ships = ships; //Game.cpp에서 만든 vecShip을 m_Ships에 저장

    for(auto pShip : m_Ships) {
        Position pos;

        srand((unsigned int)time(0));
        while(true) { //배치중
            pos.x = rand() % MAP_SIZE;
            pos.y = rand() % MAP_SIZE;
            ShipType dataType = m_Map->GetData(pos); // 해당 자리가 어떤 것이 놓여 있는지 받아옴
            if(dataType != DATA_NONE) //그 자리에 배들이 놓여 있거나 DATA_ERROR라면.
                continue; // 새론운 좌표를 받기위해 while문을 continue

            Position dir;
            if(rand()%2) // x방향
                dir.x = rand()%2 ? 1 : -1; //rand()%2==1이면 1, 0이면 -1
            else //y방향
                dir.y = rand()%2 ? 1 : -1; //rand()%2==1이면 1, 0이면 -1

            bool bSuccess = true; //해당 좌표에 넣을 수 있는지 판단

            for(int i=0; i<pShip->GetLength(); i++) {
                pos = pos + dir; // 연산자 operator를 만들었음, pos.x + dir.x, pos.y + dir.y
                dataType = m_Map -> GetData(pos);
                if (dataType != DATA_NONE) { //배를 놓을 수 없는 위치라면
                    bSuccess = false;
                    break; //for문을 break
                }
                pShip->SetPosition(i,pos); //m_Pos vector에 좌표 저장
            }
            if(bSuccess) { // 배 객체 하나를 놓을 좌표가 다 정해졌다면
                for(auto pos : pShip->m_Pos) { //실제 map에 배치
                    m_Map->SetData(pos, pShip->m_Type);
                }
                break; //배치를 완료하고 while문 종료
            }
        }
    }
}

HitResult Player::HitCheck(const Position &pos) {
  if(m_Map->GetData(pos)==0) {
    return MISS;
  }
  else if(m_Map->GetData(pos)==AIRCRAFT){
    if(count_Aircraft==1) {
      count_Aircraft=0;
      return DESTROY;
    }
    else{
      count_Aircraft--;
      return Hit;
    }
  }
  else if(m_Map->GetData(pos)==BATTLESHIP){
    if(count_Battleship==1){
      count_Battleship=0;
      return DESTROY;
    }
    else{
      count_Battleship--;
      return Hit;
    }
  }
  else if(m_Map->GetData(pos)==CRUISER){
    if(count_Cruiser==1){
      count_Cruiser=0;
      return DESTROY;
    }
    else{
      count_Cruiser--;
      return Hit;
    }
  }
  else if(m_Map->GetData(pos)==DESTROYER){
    if(count_Destroyer==1){
      count_Destroyer=0;
      return DESTROY;
    }
    else{
      count_Destroyer--;
      return Hit;
    }
  }

}

Position Player::GetAttackPos() {
  Position pos;
  char guess[1];
  //inputPane 윈도우
  inputPane = newwin(5, 27, 14, 25);

  attron(COLOR_PAIR(5));
  wborder(inputPane,  '|', '|', '-', '-', '+', '+', '+', '+');
  attroff(COLOR_PAIR(5));
  wattron(inputPane, COLOR_PAIR(4));
  mvwprintw(inputPane, 1, 1,"Input position...(ex A 3)\n Input: ");
  curs_set(0);
  echo();
  mvprintw(14, 33, "< INPUT >");
  // mvwscanw(inputPane, 2, 7, "%s %d", guess, &pos.y);
  RandomAttack(guess, pos);
  mvwprintw(inputPane, 2, 7, "%s %d",guess,pos.y);
  mvwprintw(inputPane, 3, 2, "%s %d - ",guess,pos.y);
  // pos.x=guess[0]-'0';
  // pos.x-=17;
  pos.y--;
  wattroff(inputPane, COLOR_PAIR(4));
  // wrefresh(inputPane);
  // refresh();
  return pos;
}

void Player::RandomAttack(char*guess, Position &pos){
  int x, y;
  srand((unsigned int)time(0));
  while(true){
    x= rand() % MAP_SIZE;
    y= rand() % MAP_SIZE+1;
    if(m_Map->m_Data2[x][y-1]!='0') continue;
    else if((m_Map->GetData2(x,y-2)=='M'||m_Map->GetData2(x, y-2)=='1')&&
            (m_Map->GetData2(x,y)=='M'||m_Map->GetData2(x, y)=='1')&&
      (m_Map->GetData2(x-1,y-1)=='M'||m_Map->GetData2(x-1, y-1)=='1')&&
      (m_Map->GetData2(x+1,y-1)=='M'||m_Map->GetData2(x+1,y-1)=='1')) continue;
    else break;
  }
  guess[0]=char(x+65);
  pos.x = x;
  pos.y = y;
}
