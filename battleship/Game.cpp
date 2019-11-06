#include "Map.h"
#include "Player.h"
#include "Game.h"
#include "Aircraft.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include <cstddef>
#include <iostream>



using namespace std;
//delay함수
void delay(clock_t n){
  clock_t start = clock();
  while(clock() - start<n);
}

Game::Game() {
    m_Attacker = NULL;
    m_Defender = NULL;
}

Game::~Game() {
    if(m_Attacker) { //Null 이라면 0이다. 정확히 NULL은 0을 define한 것이다.
        delete m_Attacker;
        m_Attacker = NULL;
    }
    if(m_Defender) {
        delete m_Defender;
        m_Defender = NULL;
    }
}

void Game::Init() {
    m_Attacker = new Player();
    m_Defender = new Player();

    SHIPS vecShip; //프로그햄이 종료되면 vector는 사라지지만 그안에 있는 객체들은 남아 있다.
    vecShip.push_back(new Aircraft());
    vecShip.push_back(new BattleShip());
    vecShip.push_back(new Cruiser());
    vecShip.push_back(new Destroyer());
    vecShip.push_back(new Destroyer());

    m_Defender->SetupShips(vecShip); //배를 배치
}

int Game::Play() {

    WINDOW *mapPane1;
    WINDOW *mapPane2;
    WINDOW *statusPane;
    int turn=0, state=0;
    //ncurses 모드 시작
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);

    resize_term(30, 60);

    while(state==0){    //게임이 끝나기 전까지 계속 실행
      Position PS;
      HitResult HR;

      mvprintw(1, 18, "<BATTLESHIP GAME>");

      //mapPane1 윈도우
      mvprintw(4, 3, "A");
      mvprintw(5, 3, "B");
      mvprintw(6, 3, "C");
      mvprintw(7, 3, "D");
      mvprintw(8, 3, "E");
      mvprintw(9, 3, "F");
      mvprintw(10, 3, "G");
      mvprintw(11, 3, "H");

      mvprintw(13, 6, "1");
      mvprintw(13, 7, "2");
      mvprintw(13, 8, "3");
      mvprintw(13, 9, "4");
      mvprintw(13, 10, "5");
      mvprintw(13, 11, "6");
      mvprintw(13, 12, "7");
      mvprintw(13, 13, "8");
      refresh();
      mapPane1 = newwin(10, 10, 3, 5);

      wattron(mapPane1, COLOR_PAIR(1));
      mvprintw(3, 6, "DEFENDER");
      for (int i=0; i<MAP_SIZE; i++){
        for (int j=0; j<MAP_SIZE; j++){
          if(m_Defender->m_Map->m_Data[i][j]==0) mvwprintw(mapPane1, i+1, j+1, "0");
          else if(m_Defender->m_Map->m_Data[i][j]==1) mvwprintw(mapPane1, i+1, j+1, "1");
          else if(m_Defender->m_Map->m_Data[i][j]==2) mvwprintw(mapPane1, i+1, j+1, "2");
          else if(m_Defender->m_Map->m_Data[i][j]==3) mvwprintw(mapPane1, i+1, j+1, "3");
          else if(m_Defender->m_Map->m_Data[i][j]==4) mvwprintw(mapPane1, i+1, j+1, "4");
        }
      }
      wattroff(mapPane1, COLOR_PAIR(1));
      attron(COLOR_PAIR(5));
      wborder(mapPane1,  '|', '|', '-', '-', '+', '+', '+', '+');
      attroff(COLOR_PAIR(5));
      wrefresh(mapPane1);

      //mapPane2 윈도우
      mvprintw(16, 3, "A");
      mvprintw(17, 3, "B");
      mvprintw(18, 3, "C");
      mvprintw(19, 3, "D");
      mvprintw(20, 3, "E");
      mvprintw(21, 3, "F");
      mvprintw(22, 3, "G");
      mvprintw(23, 3, "H");

      mvprintw(25, 6, "1");
      mvprintw(25, 7, "2");
      mvprintw(25, 8, "3");
      mvprintw(25, 9, "4");
      mvprintw(25, 10, "5");
      mvprintw(25, 11, "6");
      mvprintw(25, 12, "7");
      mvprintw(25, 13, "8");
      refresh();

      mapPane2 = newwin(10, 10, 15, 5);
      for (int i=0; i<MAP_SIZE; i++){
        for (int j=0; j<MAP_SIZE; j++){
          if(m_Attacker->m_Map->m_Data2[i][j]=='0') {
            wattron(mapPane2, COLOR_PAIR(1));
            mvwprintw(mapPane2, i+1, j+1, "0");
            wattroff(mapPane2, COLOR_PAIR(1));
          }
          else if(m_Attacker->m_Map->m_Data2[i][j]=='M') {
            wattron(mapPane2, COLOR_PAIR(2));
            mvwprintw(mapPane2, i+1, j+1, "M");
            wattroff(mapPane2, COLOR_PAIR(2));
          }
          else if(m_Attacker->m_Map->m_Data2[i][j]=='H'){
             wattron(mapPane2, COLOR_PAIR(2));
             mvwprintw(mapPane2, i+1, j+1, "H");
             wattroff(mapPane2, COLOR_PAIR(2));
           }
        }
      }
      attron(COLOR_PAIR(5));
      wborder(mapPane2,  '|', '|', '-', '-', '+', '+', '+', '+');
      attroff(COLOR_PAIR(5));
      mvprintw(15, 6, "ATTACKER");
      wrefresh(mapPane2);
      refresh();


      //statusPane 윈도우
      statusPane = newwin(7, 27, 3, 25);
      attron(COLOR_PAIR(5));
      wborder(statusPane,  '|', '|', '-', '-', '+', '+', '+', '+');
      mvprintw(3, 32, "< STATUS >");
      attroff(COLOR_PAIR(5));
      wattron(statusPane, COLOR_PAIR(3));
      mvwprintw(statusPane, 1, 1, "TURN: %d", turn);
      if(m_Defender->count_Aircraft>0) mvwprintw(statusPane, 2, 1, "AIRCRAFT : AAAAA");
      if(m_Defender->count_Battleship>0) mvwprintw(statusPane, 3, 1, "BATTLESHIP : BBBB");
      if(m_Defender->count_Cruiser>0) mvwprintw(statusPane, 4, 1, "CRUISER : CCC");
      if(m_Defender->count_Destroyer>0) mvwprintw(statusPane, 5, 1, "DESTROYER : DD DD");
      wattroff(statusPane, COLOR_PAIR(3));

      wattron(statusPane, COLOR_PAIR(6));
      if(m_Defender->count_Aircraft<=0) mvwprintw(statusPane, 2, 1, "AIRCRAFT : AAAAA");
      if(m_Defender->count_Battleship<=0) mvwprintw(statusPane, 3, 1, "BATTLESHIP : BBBB");
      if(m_Defender->count_Cruiser<=0) mvwprintw(statusPane, 4, 1, "CRUISER : CCC");
      if(m_Defender->count_Destroyer<=0) mvwprintw(statusPane, 5, 1, "DESTROYER : DD DD");
      wattroff(statusPane, COLOR_PAIR(6));
      wrefresh(statusPane);
      refresh();

      //if문 위치 바꾸고 continue 추가
      if(m_Defender->count_Aircraft<=0&&m_Defender->count_Battleship<=0&&
          m_Defender->count_Cruiser<=0&&m_Defender->count_Destroyer<=0){
        mvwprintw(m_Attacker->inputPane, 3, 1,"<<GAME CLEAR>>\n");
        wrefresh(m_Attacker->inputPane);
        state=1;
        continue;
      }
      //inputPane
      PS=m_Attacker->GetAttackPos();
      //이미 시도한 Position을 칠 경우 무시하고 다시 while문의 처음으로 돌아감
      if(m_Attacker->m_Map->m_Data2[PS.x][PS.y]=='M'||m_Attacker->m_Map->m_Data2[PS.x][PS.y]=='H') continue;
      HR=m_Defender->HitCheck(PS);
      wattron(m_Attacker->inputPane, COLOR_PAIR(4));
      if(HR==Hit) mvwprintw(m_Attacker->inputPane, 3, 8,"Hit!\n");
      else if(HR==MISS) mvwprintw(m_Attacker->inputPane, 3, 8,"Miss!\n");
      else if(m_Defender->m_Map->GetData(PS)==1) mvwprintw(m_Attacker->inputPane, 3, 1,"AIRCRAFT Destroy!\n");
      else if(m_Defender->m_Map->GetData(PS)==2) mvwprintw(m_Attacker->inputPane, 3, 1,"BATTLESHIP Destroy!\n");
      else if(m_Defender->m_Map->GetData(PS)==3) mvwprintw(m_Attacker->inputPane, 3, 1,"CRUISER Destroy!\n");
      else if(m_Defender->m_Map->GetData(PS)==4) mvwprintw(m_Attacker->inputPane, 3, 1,"DESTROYER Destroy!\n");

      wattroff(m_Attacker->inputPane, COLOR_PAIR(4));
      m_Attacker->m_Map->SetData2(PS, HR);

      wrefresh(m_Attacker->inputPane);
      refresh();
      delay(100000);  //시간 지연함수 delay
      // getch();
      turn++;
    }
    // getch();
    endwin(); //윈도우 종료
    return turn;
}
