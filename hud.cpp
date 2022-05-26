#include "main.h"

HUD::HUD(){

}

HUD::~HUD(){
    delwin(this->win);
}

void HUD::update(){

}

void HUD::draw(){

}

/* ScoreBoard */
ScoreBoard::ScoreBoard(){
    this->win = newwin(10, 30, C_YPOS, 5); // HEIGHT, WIDTH, YPOS, XPOS 
    box(this->win, 0, 0); 
    wrefresh(this->win); 

    this->set_position(10, 1); 
    this->set_size(10, 30);
    this->set_node_name("ScoreBoard");
}

ScoreBoard::~ScoreBoard(){

}

//x+(w-strlen("hello world")) / 2
void ScoreBoard::draw(){
    int h = this->get_height(); 
    int w = this->get_width();
    int x = this->get_xpos(); 
    int y = this->get_ypos(); 

    // 테두리 작업 
    box(this->win, 0, 0); 
    // Title 작업 
    mvwaddch(this->win, 2, 0, ACS_LTEE); 
    mvwhline(this->win, 2, 1, ACS_HLINE, w-2);
    mvwaddch(this->win, 2, w-1, ACS_RTEE); 
    mvwprintw(this->win, 1, x+(w-strlen("Score"))/2, "Score");
}