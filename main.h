// -lncursesw
#include <ncursesw/curses.h>
#include <ncursesw/panel.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <iostream>
#include <string>
#include <list>
#include <chrono>
#include <thread>

#define MS_PER_TICK 1000 / 60

#define WIDTH 60    //60
#define HEIGHT 20   //20 

// Window 객체를가지고 있는 클래스 
#define T_WIN true 
// Window 객체를가지고 있지 않는 클래스 
#define T_NON_WIN false

#define C_XPOS (COLS-WIDTH)/2    //중심좌표 
#define C_YPOS (LINES-HEIGHT)/2  //중심좌표

// Rendering은 맵 -> 플레이어,몬스터 렌더링 순으로 진행
// Node 클래스로부터 모두 상속받음 -> update메소드 virtual -> 물체 tick마다 update진행 
// 맵 안에 객체가 존재한다면 해당 객체는 특정 틱마다 update 메소드 호출
class Node{
    protected:
        bool visibility;
        int type; 
        /*계층적 구조 | 해당 노드의 하위에 속하는 노드들*/
        std::list<Node*> sub_objects; 
    public:
        Node();
        //Godot에서 _physis_process 느낌 매 프레임마다 업데이트 내부에 this->draw()진행
        virtual void update();
        virtual void draw();
        virtual ~Node();
        int get_node_type(); 
        void set_visible(bool flag); 
        bool get_visible(); 
};

// 객체 관리 및 게임진행 관련 클래스
class GameManager : public Node{
    private:
        int panel_index;
        //추후 맵, 인벤토리 등등 창을 넣어야함
        /*
            임시로 0: tutorial Map, 1:Inventory, 2:Status 3:HUD
        */
        PANEL* map_panel; //창 객체 담기위한 패널
    public:
        GameManager(); 
        virtual ~GameManager(); 
        virtual void update(); 
        virtual void draw();
        void load_map();
};


class Actor : public Node{
    protected:
        int xpos; //start position x
        int ypos; //start position y
        int prev_xpos; 
        int prev_ypos; 
        chtype texture; //game character 
        std::string name; 
        bool is_jump; 
        int jump_height;
    public:
        Actor(int ypos, int xpos, chtype texture);
        virtual ~Actor();
        // Actor 입장에서는 actor_move 반영 및 render 
        virtual void update();
        virtual void draw();
        void actor_move(int ypos, int xpos); 
        int get_xpos(); 
        int get_ypos();
        int get_prev_xpos(); 
        int get_prev_ypos();
        chtype get_texture();
        void backup_pos();
        //virtual void is_collision(); // Actor 간의 충돌 체크
};

class Player : public Actor{
    private:
        int level; 
        int hp; 
        int current_hp; 
    public:
        Player(int ypos, int xpos, chtype texture); 
        virtual ~Player();
        virtual void update(); 
        virtual void draw();
};

/*
class Monster : public Actor{
    private:
        int level; 
        int hp; 
        int current_hp; 
    
    public:
        Monster(); 
        virtual ~Monster(); 
        void monster_move(); 
        void update(); 
};
*/
/*
class Npc : public Actor{

};
*/

class MapWin : public Node{
    protected:
        chtype map_config[HEIGHT][WIDTH];
        WINDOW* win;
    public:
        MapWin(){}
        virtual ~MapWin(){}
        virtual void update();
        virtual void draw(); //특정 fps마다 맵에서 draw() 진행
        WINDOW* get_win();
};

class TutorialMap : public MapWin{
    private:

    public:
        //map_config 세팅
        TutorialMap();
        ~TutorialMap();
};

void init();
int kbhit(); 