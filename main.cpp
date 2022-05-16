#include "main.h"

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