#include "main.h"


GameManager::GameManager(){
    this->set_node_name("Game");
    this->set_position(0, 0); 
    this->set_size(0, 0);
}

// sub_object delete 
GameManager::~GameManager(){
    int index=0;
    for(auto const& obj : this->sub_objects){
        del_panel(this->node_panels[index]);
        delete obj;
        index+=1;
    }
    //del_panel(this->node_panels);
}

//맵클래스를 객체화시킨다음 하위계층에 편입시킨다. 
//생성된 맵객체는 WINDOW를 가지므로 다루기 쉽게 패널에 넣는다.
void GameManager::load_map(){
    TutorialMap* tutorial_map = new TutorialMap();
    tutorial_map->set_visible(true);
    this->sub_objects.push_back((Node*)tutorial_map); 
    // 맵의 window를 상위 노드의 패널에 연결
    this->node_panels[0] = new_panel(tutorial_map->get_win());
}

void GameManager::load_scoreboard(){
    ScoreBoard* scoreboard = new ScoreBoard(); 
    scoreboard->set_visible(true);
    this->sub_objects.push_back((Node*)scoreboard);
    this->node_panels[1] = new_panel(scoreboard->get_win());
}

// 매 프레임마다 하위객체 update진행
void GameManager::update(){
    //this->draw();
    for(auto const& obj : this->sub_objects){
        obj->update();
    }
    this->draw();
}
/*
    GameManager클래스에 편입된 하위객체들의 render작업을 진행한다. 
    게임매니저 클래스에 들어가는 객체들은 T_WIN값을 가져야 draw렌더링이 가능하다. T_WIN은 WINDOW객체를 가지고 있냐의 차이
    또한 해당 하위 객체가 visible하다면 show, 그렇지 않다면 hide를 진행한다.
*/
void GameManager::draw(){
    int index=0;
    for(auto const& obj : this->sub_objects){
        // obj 마다 index속성 부여 해야할듯
        if(obj->get_visible()){
            obj->draw();
            show_panel(this->node_panels[index]);
        }else{
            hide_panel(this->node_panels[index]);
        }
        index+=1;
        //wrefresh(panel_window(this->node_panels[index]));
    }
    //패널에 대한 변경사항(패널 내부의 렌더작업) 최종적으로 가상화면으로 전송한다. 
    update_panels();
    //가상화면으로 전송된 출력 데이터를 실제 물리화면으로 전송한다.
    doupdate();
}

Node* GameManager::get_node(std::string node_name){
    for(auto const& obj : this->sub_objects){
        if(obj->get_node_name() == node_name){
            return obj;
        }
    }
    return NULL;
}

/*
Node* GameManager::get_node(std::string node_name){
    for(auto const& obj : this->sub_objects){
        if(node->get_node_name() == node_name){
            return node;
        }
        Node* node = obj->get_node(node_name); 
        if(node == NULL){
            continue;
        }
        
    }
    return NULL;
}
*/