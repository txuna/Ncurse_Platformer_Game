#include "main.h"

MapWin::MapWin(){
    this->win = newwin(HEIGHT, WIDTH, C_YPOS, C_XPOS); 
    box(this->win, 0, 0); //WIN box border
    wrefresh(this->win);
    this->set_position(C_YPOS, C_XPOS); 
    this->set_size(HEIGHT, WIDTH);
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

    // Collision Check 
    // Actor만이 Collision을 가짐
    for(auto const& checker : this->sub_objects){
        // Actor가 아니라면 
        if(checker->get_node_type() != ACTOR) continue;
        // 충돌상태가 비활성화 상태라면
        if(!((Actor*)checker)->collision->collision_state()) continue;
        for(auto const& victim : this->sub_objects){
            // Actor가 아니라면
            if(checker->get_node_type() != ACTOR) continue;
            // 동일한 객체
            if(checker->get_id() == victim->get_id()) continue;
            //checker의 layer와 victim의 mask에 & 연산 - Collision 대상인지 확인
            //즉, Victom이 Checker의 충돌대상인지 확인한 다음 충돌중인지 확인
            if(!((Actor*)checker)->collision->check_mask(((Actor*)victim)->collision->get_layer())) continue; 
            
            // 충돌 계산 
            if(has_collision((Actor*)checker, (Actor*)victim)){
                // Callback 호출
                // 구조물이 아닌 몬스터의 경우 오버래핑 한번의 충돌이면 되므로 음 ... 무적시간? 
                ((Actor*)checker)->occur_collision((Actor*)victim);
            }
        }
    }
    // Object Draw
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
    this->type = MAP;
    this->set_node_name("TutorialMap");
    /* Spawning Box */
    Box* box = new Box(35, 20, 4, 30, "*", "Box1", this->win);
    box->set_visible(true); 
    this->sub_objects.push_back((Node*)box);

    Box* box2 = new Box(27, 60, 12, 8, "*", "Box2", this->win);
    box->set_visible(true); 
    this->sub_objects.push_back((Node*)box2);

    Box* box3 = new Box(34, 90, 5, 20, "*", "Box3", this->win);
    box->set_visible(true); 
    this->sub_objects.push_back((Node*)box3);

    Box* box4 = new Box(29, 76, 3, 25, "*", "Box4", this->win);
    box->set_visible(true); 
    this->sub_objects.push_back((Node*)box4);

    Box* box5 = new Box(24, 2, 2, 48, "*", "Box5", this->win);
    box->set_visible(true); 
    this->sub_objects.push_back((Node*)box5);

    /* Spawning Monster */
    Monster* monster = new Monster(3, 40, 1, 7, "(●'◡'●)", "Monster1", this->win);
    monster->set_visible(true);
    this->sub_objects.push_back((Node*)monster);

    /* Spawning Player */
    Player* player = new Player(3, 3, 1, 5, "(•_•)", "Player", this->win);
    player->set_visible(true);
    this->sub_objects.push_back((Node*)player);
}

TutorialMap::~TutorialMap(){
    delwin(win); 
    for(auto const& obj : this->sub_objects){
        delete obj;
    }
}
