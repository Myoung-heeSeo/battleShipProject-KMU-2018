#include "Game.h"
#include <iostream>
using namespace std;

int main(void) {

    int average=0;
    Game GameManager;
    for(int i=0; i<10; i++){  //게임 10번 실행
      GameManager.Init();
      average+=GameManager.Play();
    }

    cout << "turn: "<<average/10 << endl;
}
