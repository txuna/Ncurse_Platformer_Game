#include "main.h"

int NODE_INDEX=0;

bool running = true;

int main(void){
    init(); 
    // 초기화 대기 시간
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    GameManager* game_manager = new GameManager();
    game_manager->load_map();
    while(running){
        game_manager->update();
        std::this_thread::sleep_for(std::chrono::milliseconds(MS_PER_TICK));
    }
    endwin(); 
    return 0;
}

void init(){
    NODE_INDEX = 1;
    setlocale(LC_ALL, "");
    initscr(); 
    start_color();
    noecho(); 
    keypad(stdscr, TRUE); 
    cbreak();   
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    curs_set(0);
    refresh();
    
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

bool has_collision(Node* r1, Node* r2){
    int r1_x = r1->get_xpos(); 
    int r1_y = r1->get_ypos();
    int r1_w = r1->get_width(); 
    int r1_h = r1->get_height();

    int r2_x = r2->get_xpos(); 
    int r2_y = r2->get_ypos(); 
    int r2_w = r2->get_width(); 
    int r2_h = r2->get_height();

    if (r1_x < r2_x + r2_w 
        && r1_x + r1_w > r2_x 
        && r1_y < r2_y + r2_h 
        && r1_h + r1_y > r2_y){
            return true; 
    }else{
        return false;
    }
}