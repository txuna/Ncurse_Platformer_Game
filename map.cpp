#include "main.h"

//매 프레임마다 호출되는 update함수이다. 해당 객체가 visible하다면 하위객체 update를 진행한다.
//업데이트후 렌더링 작업 실시
void MapWin::update(){
    //자체 WINDOW가 없는 하위 객체들은 update만 진행
    if(!this->visibility){
        return;
    }
    // 하위 종속 객체 update 
    for(auto const& obj : this->sub_objects){
        // 객체 업데이트 전 지우기 
        this->clear_obj(obj);
        obj->update();
    }
    this->draw();
}

void MapWin::clear_obj(Node* node){
    int node_x = node->get_xpos(); 
    int node_y = node->get_ypos(); 
    mvwaddch(win, node_y, node_x, ' ');
}

//맵 클래스가 가지고 있는 하위 객체들(업데이트된)을 렌더링하는 함수
// 렌더링의 순서는 상위계층부터 렌더링이 진행된다. 
// 오브젝트 -> update , collision check -> draw 
void MapWin::draw(){
    for(auto const& obj : this->sub_objects){
        // visible하지 않는다면 렌더링 제외
        if(!obj->get_visible()){
            break; 
        }
        //this->clear_obj(obj);
        int obj_x = obj->get_xpos(); //(Actor*) 캐스팅 안해도 되게 하기
        int obj_y = obj->get_ypos();
        chtype texture = ((Actor*)obj)->get_texture();
        wattron(win, COLOR_PAIR(1));
        mvwaddch(win, obj_y, obj_x, texture); //새로운 플레이어 좌표 이전 좌표 지워야함
        wattroff(win, COLOR_PAIR(1));
    } 
    box(this->win, 0, 0);
}


// 맵 클래스가 가지고 있는 window 반환함수
WINDOW* MapWin::get_win(){
    return this->win;
}

/*
    튜토리얼맵 클래스 맵파일을 읽어들이고 설정 및 맵파일에 맞게 
    플레이어 및 몬스터 및 NPC를 스폰한다. 
*/
TutorialMap::TutorialMap(){
    this->type = T_WIN; 
    this->win = newwin(HEIGHT, WIDTH, C_YPOS, C_XPOS); 
    box(this->win, 0, 0); //WIN box border

    /* Spawning Player */
    Player* player = new Player(3, 3, '@');
    player->set_visible(true);
    this->sub_objects.push_back((Node*)player);
    /* Spawning Monster */
}

TutorialMap::~TutorialMap(){
    delwin(win); 
    for(auto const& obj : this->sub_objects){
        delete obj;
    }
}
