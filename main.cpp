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
    init_pair(2, COLOR_RED, COLOR_BLACK);
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

bool has_collision(Actor* r1, Actor* r2){
    int r1_x = r1->collision->get_xpos(); 
    int r1_y = r1->collision->get_ypos();
    int r1_w = r1->collision->get_width(); 
    int r1_h = r1->collision->get_height();

    int r2_x = r2->collision->get_xpos(); 
    int r2_y = r2->collision->get_ypos(); 
    int r2_w = r2->collision->get_width(); 
    int r2_h = r2->collision->get_height();

    if (r1_x < r2_x + r2_w 
        && r1_x + r1_w > r2_x 
        && r1_y < r2_y + r2_h 
        && r1_h + r1_y > r2_y){
            return true; 
    }else{
        return false;
    }
}

/*
bool IsIntersecting(Position a, Position b, Position c, Position d)
{
    float denominator = ((b.X - a.X) * (d.Y - c.Y)) - ((b.Y - a.Y) * (d.X - c.X));
    float numerator1 = ((a.Y - c.Y) * (d.X - c.X)) - ((a.X - c.X) * (d.Y - c.Y));
    float numerator2 = ((a.Y - c.Y) * (b.X - a.X)) - ((a.X - c.X) * (b.Y - a.Y));

    // Detect coincident lines (has a problem, read below)
    if (denominator == 0) return numerator1 == 0 && numerator2 == 0;
    
    float r = numerator1 / denominator;
    float s = numerator2 / denominator;

    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}
*/