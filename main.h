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
#include <locale.h>

#define MS_PER_TICK 1000 / 45

#define Y_POS 1
#define X_POS 2
#define YX_POS 3 

#define WIDTH 120    //60
#define HEIGHT 40   //20 

// Window 객체를가지고 있는 클래스 
#define T_WIN true 
// Window 객체를가지고 있지 않는 클래스 
#define T_NON_WIN false

#define C_XPOS (COLS-WIDTH)/2    //중심좌표 
#define C_YPOS (LINES-HEIGHT)/2  //중심좌표

#define GRAVITY 1
#define JUMP 8
#define SPEED 1

#define PLAYER_LAYER 1 
#define MONSTER_LAYER 2 
#define STRUCTURE_LAYER 4

#define MAP 1 
#define ACTOR 2 
#define UI 3


class Velocity{
    public:
        int y; 
        int x; 
        Velocity(int y, int x);
};

// Rendering은 맵 -> 플레이어,몬스터 렌더링 순으로 진행
// Node 클래스로부터 모두 상속받음 -> update메소드 virtual -> 물체 tick마다 update진행 
// 맵 안에 객체가 존재한다면 해당 객체는 특정 틱마다 update 메소드 호출
/*
    종속된 노드는 상위 노드가 움직일 시 같이 이동
*/

class Node{
    protected:
        int id;
        WINDOW* win;
        int xpos; 
        int ypos;
        int width; 
        int height;
        bool visibility;
        int type; 
        // 일단은 임시로 패널 한개만 담기 가능 추후 realloc같은걸로 지속적 할당 예정
        PANEL* node_panels; 
        /*계층적 구조 | 해당 노드의 하위에 속하는 노드들*/
        std::list<Node*> sub_objects;     
    public:
        Node();
        //Godot에서 _physis_process 느낌 매 프레임마다 업데이트 내부에 this->draw()진행
        virtual void update();
        virtual void draw();
        virtual ~Node();
        void set_visible(bool flag); 
        bool get_visible(); 
        void set_position(int ypos, int xpos);
        void set_size(int height, int width);
        int get_xpos();
        int get_ypos();
        int get_width();
        int get_height();
        WINDOW* get_win();
        int get_node_type();
        void transform_position(Velocity* velocity);
        int get_id();
};

// 객체 관리 및 게임진행 관련 클래스
class GameManager : public Node{
    private:

    public:
        GameManager(); 
        virtual ~GameManager(); 
        virtual void update(); 
        virtual void draw();
        void load_map();
};

class Collision : public Node{
    private:
        bool is_collision; 
        char layer; // 자기 자신이 속한 레이어 
        char mask;  // 충돌체크할 레이어 
        bool is_pass; // 충돌후 통과 가능 여부
    public:
        Collision(int ypos, int xpos, int height, int width); 
        virtual ~Collision(); 
        void enable_collision(bool flag);
        virtual void update(); 
        virtual void draw();
        void set_layer(char layer, char mask);
        char get_mask(); 
        char get_layer();
        bool check_mask(char victim_layer);
};

class Actor : public Node{
    protected:
        std::string texture;
        //chtype texture; //game character 
        std::string name; 
        bool is_jump; 
        int jump_height;
        bool is_floor;
        WINDOW* canvas; // 그려질 맵 WINDOW;
        int prev_xpos; 
        int prev_ypos; 
        
    public:
        Collision* collision; 
        Actor(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas);
        virtual ~Actor();
        // Actor 입장에서는 actor_move 반영 및 render 
        virtual void update();
        virtual void draw();
        void actor_move(Velocity* velocity); 
        std::string get_texture();
        void set_canvas_win(WINDOW* canvas); 
        void occur_collision();
};


class Player : public Actor{
    private:
        // 현재 키를 누르고 있는지 확인
        Velocity* velocity;
    public:
        Player(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas); 
        virtual ~Player();
        virtual void update(); 
        virtual void draw();
};


class Monster : public Actor{
    private:
        Velocity* velocity;
        int direction; 
    public:
        Monster(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas); 
        virtual ~Monster(); 
        virtual void update(); 
        virtual void draw();
};
/*
class Wall : public Actor{
    private:
        Velocity* velocity;
        int direction; 
    public:
        Wall(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas); 
        virtual ~Wall(); 
        virtual void update(); 
        virtual void draw();
};
*/

/*
class Npc : public Actor{

};
*/

class MapWin : public Node{
    protected:
        chtype map_config[HEIGHT][WIDTH];
        //WINDOW* win;
    public:
        MapWin();
        virtual ~MapWin();
        virtual void update();
        virtual void draw(); //특정 fps마다 맵에서 draw() 진행
};

class TutorialMap : public MapWin{
    private:

    public:
        //map_config 세팅
        TutorialMap();
        ~TutorialMap();
};




bool has_collision(Node* r1, Node* r2); 
void init();
int kbhit(); 