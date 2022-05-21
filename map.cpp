#include "main.h"

MapWin::MapWin(){
    this->win = newwin(HEIGHT, WIDTH, C_YPOS, C_XPOS); 
    box(this->win, 0, 0); //WIN box border
    wrefresh(this->win);
}

MapWin::~MapWin(){
    delwin(this->win);
}

//매 프레임마다 호출되는 update함수이다. 해당 객체가 visible하다면 하위객체 update를 진행한다.
//업데이트후 렌더링 작업 실시
void MapWin::update(){
    // 맵의 경우 객체가 보이지 않는다면 업데이트 활성화 X 
    if(!this->visibility){
        return;
    }
    // 하위 종속 객체 update 
    for(auto const& obj : this->sub_objects){
        obj->update();
    }
    this->draw();
}

//맵 클래스가 가지고 있는 하위 객체들(업데이트된)을 렌더링하는 함수
// 렌더링의 순서는 상위계층부터 렌더링이 진행된다. 
// 오브젝트 -> update , collision check -> draw 
// wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' '); -> 오브젝트 파괴할 때
void MapWin::draw(){
    box(this->win, 0, 0);

    //wrefresh(this->win); 
    for(auto const& obj : this->sub_objects){
        // visible하지 않는다면 렌더링 제외
        if(!obj->get_visible()){
            continue;
        }
        obj->draw();
    }
    wrefresh(this->win);
}

/*
    튜토리얼맵 클래스 맵파일을 읽어들이고 설정 및 맵파일에 맞게 
    플레이어 및 몬스터 및 NPC를 스폰한다. 
*/
TutorialMap::TutorialMap(){
    /* setup map */
    this->type = T_WIN;
    /* Spawning Monster */
    Monster* monster = new Monster(3, 20, 1, 7, "(●'◡'●)",this->win);
    monster->set_visible(true);
    this->sub_objects.push_back((Node*)monster);
    /* Spawning Player */
    Player* player = new Player(3, 3, 1, 5, "(•_•)", this->win);
    player->set_visible(true);
    this->sub_objects.push_back((Node*)player);

}

TutorialMap::~TutorialMap(){
    delwin(win); 
    for(auto const& obj : this->sub_objects){
        delete obj;
    }
}
